# 下位机 App 层分析与稳定性优化总结

本文档整理本轮对 `AiKeyBoard` 下位机端代码的分析，重点面向初学者解释：

- App 层每个文件的职责
- 按键从 ADC 到 USB 打字的完整链路
- 灯光和上位机通信链路
- “键盘使用一段时间无法打字，但灯光正常”的可能原因
- USB `0x81` 卡死恢复的优化思路和代码
- ADC DMA 扫描看门狗的优化思路和代码
- USB `0x82` 自定义 HID busy 保护的优化思路和代码
- `process_key_logic()` 中 RT 动态触发逻辑的优化
- App 层后续架构优化建议

本文中的路径均基于工程根目录：

```text
D:\sike_local\AiKeyBoard
```

---

## 1. App 层整体作用

`App` 层是整个下位机固件的“业务逻辑层”。

可以把整个固件分为几层：

```text
User
    main.c、task.c、USB 描述符和中断入口

Bsp
    GPIO、ADC、DMA、SPI、TIM、UART 等底层驱动

Lib
    霍尔键盘扫描、WS2812 灯珠驱动等基础库

App
    按键业务、USB 键盘报告、灯效业务、上位机协议

CherryUSB
    USB 协议栈和 PY32 USB 端口驱动
```

App 层主要文件：

```text
App/inc/App.h
App/src/App.c

App/inc/App_key.h
App/src/App_key.c

App/inc/App_usb.h
App/src/App_usb.c

App/inc/App_lighting.h
App/src/App_lighting.c

App/inc/App_protocol.h
App/src/App_protocol.c
```

还有一个：

```text
App/src/App copy.c
```

这是旧版本/备份文件，建议后续移出源码目录，避免误改或误读。

---

## 2. App.h / App.c 分析

### 2.1 `App.h`

文件位置：

```text
App/inc/App.h
```

核心内容：

```c
#ifndef __APP_H__
#define __APP_H__

#include "usbd_core.h"
#include "usbd_hid.h"

#include "App_key.h"
#include "App_usb.h"
#include "App_lighting.h"
#include "App_protocol.h"

void App_init(void);

#endif
```

作用：

```text
1. 防止头文件重复包含
2. 汇总 App 层所有子模块头文件
3. 声明 App_init()
```

`App.h` 可以理解成 App 层的总入口头文件。

### 2.2 `App.c`

文件位置：

```text
App/src/App.c
```

当前内容：

```c
#include "App.h"
#include <string.h>

void App_init(void) {
    report_dirty = false;
    g_led_dirty = true;
    memset(last_key_state, 0, sizeof(last_key_state));
    memset(last_fn_state, 0, sizeof(last_fn_state));
    g_light_mode = LIGHT_MODE_OFF;
}
```

逐句说明：

```c
report_dirty = false;
```

初始化时没有键盘报告需要发给电脑。

```c
g_led_dirty = true;
```

强制灯光系统刷新一次，确保上电后灯光状态被写到灯珠。

```c
memset(last_key_state, 0, sizeof(last_key_state));
```

清空上一次普通按键状态。

```c
memset(last_fn_state, 0, sizeof(last_fn_state));
```

清空 Fn 内部功能键状态，防止上电误触发。

```c
g_light_mode = LIGHT_MODE_OFF;
```

默认灯光关闭。

---

## 3. App_key.h / App_key.c 分析

### 3.1 `App_key.h`

文件位置：

```text
App/inc/App_key.h
```

关键宏：

```c
#define KEY_NONE       0x00
#define KEY_FN         0xF0
#define KEY_LIGHT      0xF1
#define KEY_WINLOCK    0xF2
#define KEY_MAC        0xF3
#define KEY_WIN        0xF4
#define KEY_AI_TRIGGER 0xF5
#define KEY_AI_CONFIRM 0xF6
#define KEY_AI_CANCEL  0xF7
```

说明：

```text
KEY_NONE
    无效键，不发送，不处理

KEY_FN
    Fn 键

KEY_LIGHT
    内部功能键：切换灯光模式

KEY_AI_TRIGGER / KEY_AI_CONFIRM / KEY_AI_CANCEL
    内部功能键：AI 相关上报
```

注意：

```text
0xF0 以上不是标准键盘 HID keycode。
这些值只在固件内部使用，不应该直接发给电脑作为普通键。
```

全局变量声明：

```c
extern bool report_dirty;
extern uint8_t last_key_state[ROW_COUNT][COL_COUNT];
extern uint8_t last_fn_state[ROW_COUNT][COL_COUNT];
extern const uint8_t g_key_map[ROW_COUNT][COL_COUNT];
extern const uint8_t g_fn_key_map[ROW_COUNT][COL_COUNT];
```

说明：

```text
report_dirty
    按键状态变化后置 true，USB 层看到后发送键盘 report。

last_key_state
    保存上一帧每个键的按下/松开状态。

last_fn_state
    内部功能键防重复触发状态。

g_key_map
    普通层键位表。

g_fn_key_map
    Fn 层键位表。
```

函数声明：

```c
void App_adkey_scan_task(void);
void App_handle_internal_key(uint8_t code);
```

### 3.2 `App_key.c`

文件位置：

```text
App/src/App_key.c
```

#### 3.2.1 全局状态

```c
bool report_dirty = false;
uint8_t last_key_state[ROW_COUNT][COL_COUNT] = {0};
uint8_t last_fn_state[ROW_COUNT][COL_COUNT] = {0};
```

作用：

```text
report_dirty
    标记当前是否需要重新发送 USB 键盘报告。

last_key_state
    用于判断本次按键状态和上次相比有没有变化。

last_fn_state
    用于 Fn + 内部功能键的防连发。
```

#### 3.2.2 普通层键位表

```c
const uint8_t g_key_map[ROW_COUNT][COL_COUNT] = {
    {0x29, 0x1E, 0x1F, ...},
    ...
};
```

这里的数值是 HID keycode。

例如：

```text
0x04 = A
0x05 = B
0x1E = 1
0x28 = Enter
0x2C = Space
0xE0 = Left Ctrl
0xE1 = Left Shift
```

#### 3.2.3 Fn 层键位表

```c
const uint8_t g_fn_key_map[ROW_COUNT][COL_COUNT] = {
    ...
    {KEY_NONE, KEY_NONE, KEY_LIGHT, ...}
};
```

当 Fn 被按下时，同一个物理键会查 `g_fn_key_map`。

其中 `KEY_LIGHT`、`KEY_AI_TRIGGER` 等是内部功能键。

#### 3.2.4 `update_baseline_tracking()`

作用：

```text
当按键没有按下时，缓慢校准 idle_adc，抵消温漂。
```

简化逻辑：

```text
如果按键正在按下：
    不校准

如果当前 ADC 和 idle_adc 差距很小：
    观察一段时间
    如果持续稳定，idle_adc 慢慢向当前值移动

如果差距突然很大：
    认为用户可能正在按键，不校准
```

为什么需要？

磁轴霍尔传感器的 ADC 值会受温度、器件偏差、供电等影响慢慢漂移。如果不校准，可能出现：

```text
误触
触发变浅/变深
某些键不灵敏
```

#### 3.2.5 `process_key_logic()` 原始问题

原逻辑中有：

```c
if (offset < k->min_offset) {
    k->min_offset = offset;
}
```

但初始化时：

```c
k->min_offset = 0;
```

而 `offset` 本身不会小于 0。

所以第一次未按下时，这段几乎没有意义。

另外：

```c
uint16_t release_line = k->max_offset - k->rt_release_sens;
```

如果 `max_offset < rt_release_sens`，可能发生无符号下溢。

例如：

```text
30 - 50 = 65516
```

这在 C 的 `uint16_t` 中是可能发生的。

#### 3.2.6 优化后的 `process_key_logic()` 代码

建议保留旧代码：

```c
#if 0
// old process_key_logic()
#endif
```

然后使用优化版：

```c
// AP/RT 判断优化版：首次按压用 AP，松开后进入 RT 动态触发循环。
static uint8_t process_key_logic(Key_t *k, uint16_t cur_adc)
{
    // 计算按下深度。数值越大，按得越深。
    int32_t diff = (int32_t)k->idele_adc - (int32_t)cur_adc;
    uint16_t offset = (diff > 0) ? (uint16_t)diff : 0U;

    // 完全回到顶部死区：退出 RT 循环，下次重新使用固定触发点。
    if (offset < k->top_deadzone) {
        k->is_pressed = 0;
        k->in_rt_cycle = 0;
        k->max_offset = 0;
        k->min_offset = offset;
        return 0;
    }

    // 底部保护：限制最大行程，避免异常 ADC 值影响判断。
    if (offset > k->bottom_deadzone) {
        offset = k->bottom_deadzone;
    }

    if (!k->is_pressed) {
        uint16_t trigger_line;

        if (k->in_rt_cycle) {
            // RT 循环中：持续记录松开后的最浅位置。
            if (offset < k->min_offset) {
                k->min_offset = offset;
            }

            trigger_line = k->min_offset + k->rt_press_sens;
            if (trigger_line > k->bottom_deadzone) {
                trigger_line = k->bottom_deadzone;
            }
        } else {
            // 首次触发：使用固定 AP。
            trigger_line = k->actuation_point;
        }

        if (offset >= trigger_line) {
            k->is_pressed = 1;
            k->max_offset = offset;
        }
    } else {
        // 已经按下：持续记录本次按压的最深位置。
        if (offset > k->max_offset) {
            k->max_offset = offset;
        }

        // 防止 uint16_t 下溢。
        uint16_t release_line = 0;
        if (k->max_offset > k->rt_release_sens) {
            release_line = k->max_offset - k->rt_release_sens;
        }

        if (offset <= release_line) {
            k->is_pressed = 0;
            k->in_rt_cycle = 1;
            k->min_offset = offset;
        }
    }

    return k->is_pressed;
}
```

优化点：

```text
1. offset 改成 uint16_t，更符合“按下深度不会为负”的语义。
2. 首次触发和 RT 再触发分开写。
3. release_line 做防下溢保护。
4. 松开后才进入 RT 循环。
5. trigger_line 限制在 bottom_deadzone 内。
```

#### 3.2.7 数据验证示例

参数：

```text
actuation_point = 350
top_deadzone = 80
rt_press_sens = 50
rt_release_sens = 50
```

第一次按下：

```text
offset: 0 -> 100 -> 200 -> 350

offset >= 350
触发
```

按深：

```text
offset = 500
max_offset = 500
```

回弹：

```text
release_line = 500 - 50 = 450

offset 回到 450
松开
min_offset = 450
in_rt_cycle = 1
```

半抬后再按：

```text
offset 回弹到 400
min_offset = 400

再次下压：
trigger_line = 400 + 50 = 450

offset 到 450
再次触发
```

完全抬起：

```text
offset = 70
top_deadzone = 80

offset < top_deadzone
退出 RT
下次重新用 actuation_point = 350
```

---

## 4. App_usb.h / App_usb.c 分析

### 4.1 `App_usb.h`

```c
void App_usb_process_task(void);
```

声明标准键盘 HID 发送任务。

### 4.2 `App_usb.c`

文件位置：

```text
App/src/App_usb.c
```

核心作用：

```text
把 keys[][] 当前按键状态转换成标准 8 字节键盘 HID report，
然后通过 USB 0x81 IN 端点发给电脑。
```

#### 4.2.1 标准键盘 HID report 格式

标准 8 字节键盘 report：

```text
byte0:
    Ctrl / Shift / Alt / Win 修饰键位图

byte1:
    保留

byte2~byte7:
    最多 6 个普通键 keycode
```

所以当前代码是 6KRO，不是 NKRO。

#### 4.2.2 按键到 USB 的流程

```text
App_key.c 发现按键变化
    report_dirty = true

App_usb_process_task()
    生成 current_report[8]

usbd_ep_start_write(0x81, current_report, 8)
    发送给电脑

发送成功
    hid_state = BUSY

USB IN 完成回调
    hid_state = IDLE
```

#### 4.2.3 内部功能键重复处理问题

原来 `App_usb.c` 中也会处理：

```c
if (code >= 0xF0) {
    App_handle_internal_key(code);
}
```

但 `App_key.c` 已经通过 `App_process_internal_keys()` 处理内部功能键。

所以职责重复。

建议 `App_usb.c` 改为：

```c
if (code >= 0xF0) {
    continue;
}
```

含义：

```text
USB 层只负责普通键盘 HID。
内部功能键由 App_key.c 统一处理。
```

#### 4.2.4 0x81 卡死恢复问题

你遇到的现象：

```text
键盘使用一段时间无法打字
灯光正常
Fn 可以切换灯光模式
```

说明：

```text
主循环大概率还活着
ADC 扫描大概率还活着
按键内部功能大概率还活着

普通打字走 0x81
所以优先怀疑 USB 0x81 IN 端点卡住
```

原来的 busy 恢复：

```c
if (hid_state == HID_STATE_BUSY) {
    if (++busy_ticks < HID_BUSY_TIMEOUT_TICKS) {
        return;
    }

    hid_state = HID_STATE_IDLE;
    busy_ticks = 0;
}
```

问题：

```text
这里只改了软件变量 hid_state。
如果 USB 硬件端点本身还卡着，下一次发送仍可能失败。
```

---

## 5. USB 0x81 卡死恢复优化

### 5.1 为什么会出现 USB->INDEX 竞态

PY32 USB 外设通过 `USB->INDEX` 选择当前端点：

```text
USB->INDEX = 1
    操作端点 1，也就是 0x81

USB->INDEX = 2
    操作端点 2，也就是 0x82
```

问题是：

```text
USB->INDEX 是全局选择器。
主循环会改它。
USB 中断也会改它。
```

场景：

```text
T1 主循环准备发键盘 report
T2 主循环 USB->INDEX = 1，选中 0x81
T3 USB 中断突然进来
T4 中断 USB->INDEX = 2，处理 0x82
T5 中断返回
T6 主循环以为自己还在操作 0x81
T7 实际写到了 0x82 的寄存器
```

结果：

```text
0x81 没有正确发送
0x82 可能被错误改状态
USB 状态机可能乱掉
```

这类问题是偶发的，因为必须刚好卡在很短的时间窗口里。

### 5.2 新增 USB 临界区代码

文件：

```text
CherryUSB/port/usb_dc_py32.c
```

新增：

```c
static uint32_t usb_dc_enter_critical(void)
{
  uint32_t primask = __get_PRIMASK();

  __disable_irq();
  return primask;
}

static void usb_dc_exit_critical(uint32_t primask)
{
  __set_PRIMASK(primask);
}
```

小白解释：

```text
usb_dc_enter_critical()
    进入关键区域，暂时不让中断打断。

usb_dc_exit_critical()
    离开关键区域，恢复之前的中断状态。
```

目的：

```text
保证：
选择端点 -> 操作端点 -> 恢复端点
这几个动作中间不被 USB 中断打断。
```

### 5.3 在 `usbd_ep_start_write()` 中使用临界区

优化前：

```c
old_ep_idx = pyusb_get_active_ep();
pyusb_set_active_ep(ep_idx);

/* 操作 USB 端点 */

pyusb_set_active_ep(old_ep_idx);
return 0;
```

优化后：

```c
uint32_t primask;

primask = usb_dc_enter_critical();
old_ep_idx = pyusb_get_active_ep();
pyusb_set_active_ep(ep_idx);

if (USB->IN_CSR1 & USB_INCSR_IPR)
{
  pyusb_set_active_ep(old_ep_idx);
  usb_dc_exit_critical(primask);
  return -3;
}

/* 操作 USB 端点 */

pyusb_set_active_ep(old_ep_idx);
usb_dc_exit_critical(primask);
return 0;
```

作用：

```text
保护 usbd_ep_start_write()
防止操作 USB->INDEX 时被中断打断。
```

`usbd_ep_start_read()` 也建议加同样保护。

### 5.4 新增 `usbd_ep_flush()`

声明文件：

```text
CherryUSB/common/usb_dc.h
```

新增：

```c
int usbd_ep_flush(const uint8_t ep);
```

实现文件：

```text
CherryUSB/port/usb_dc_py32.c
```

新增：

```c
int usbd_ep_flush(const uint8_t ep)
{
  uint8_t ep_idx = USB_EP_GET_IDX(ep);
  uint8_t old_ep_idx;
  uint32_t primask;

  if (ep_idx == 0) {
    return -1;
  }

  if (USB_EP_DIR_IS_OUT(ep)) {
    return -1;
  }

  if (!g_pyusb_udc.in_ep[ep_idx].ep_enable) {
    return -2;
  }

  primask = usb_dc_enter_critical();
  old_ep_idx = pyusb_get_active_ep();
  pyusb_set_active_ep(ep_idx);

  USB->IN_CSR1 = (USB_INCSR_FF | USB_INCSR_CDT);
  g_pyusb_udc.in_ep[ep_idx].xfer_buf = NULL;
  g_pyusb_udc.in_ep[ep_idx].xfer_len = 0;
  g_pyusb_udc.in_ep[ep_idx].actual_xfer_len = 0;

  pyusb_set_active_ep(old_ep_idx);
  usb_dc_exit_critical(primask);
  return 0;
}
```

逐句解释：

```c
uint8_t ep_idx = USB_EP_GET_IDX(ep);
```

把 `0x81` 转成端点号 `1`。

```c
if (ep_idx == 0) return -1;
```

不允许清 EP0。EP0 是 USB 控制端点，不能随便 flush。

```c
if (USB_EP_DIR_IS_OUT(ep)) return -1;
```

这里只处理 IN 端点。

```c
if (!g_pyusb_udc.in_ep[ep_idx].ep_enable) return -2;
```

端点没启用就不能 flush。

```c
USB->IN_CSR1 = (USB_INCSR_FF | USB_INCSR_CDT);
```

核心语句。

```text
FF:
    Flush FIFO，清空端点 FIFO。

CDT:
    Clear Data Toggle，清数据切换状态。
```

```c
g_pyusb_udc.in_ep[ep_idx].xfer_buf = NULL;
g_pyusb_udc.in_ep[ep_idx].xfer_len = 0;
g_pyusb_udc.in_ep[ep_idx].actual_xfer_len = 0;
```

清软件层传输状态。

### 5.5 App_usb.c 中使用 `usbd_ep_flush()`

优化前：

```c
if (hid_state == HID_STATE_BUSY) {
    if (++busy_ticks < HID_BUSY_TIMEOUT_TICKS) {
        return;
    }

    hid_state = HID_STATE_IDLE;
    busy_ticks = 0;
}
```

优化后：

```c
if (hid_state == HID_STATE_BUSY) {
    if (++busy_ticks < HID_BUSY_TIMEOUT_TICKS) {
        return;
    }

    (void)usbd_ep_flush(HID_INT_EP);
    hid_state = HID_STATE_IDLE;
    busy_ticks = 0;
    memset(last_report, 0xFF, sizeof(last_report));
    report_dirty = true;
}
```

逐句解释：

```c
(void)usbd_ep_flush(HID_INT_EP);
```

清 0x81 硬件端点。

```c
hid_state = HID_STATE_IDLE;
```

软件状态恢复为空闲。

```c
busy_ticks = 0;
```

busy 超时计数清零。

```c
memset(last_report, 0xFF, sizeof(last_report));
```

让上一次 report 失效。

为什么？

因为代码里有：

```c
if (memcmp(current_report, last_report, sizeof(current_report)) == 0) {
    report_dirty = false;
    return;
}
```

如果不让 `last_report` 失效，恢复后可能因为“当前 report 和上次一样”而不重发。

```c
report_dirty = true;
```

强制下次重新发送键盘 report。

发送失败时也处理 `-3`：

```c
if (ret == -2 || ret == -3) {
    if (ret == -3) {
        (void)usbd_ep_flush(HID_INT_EP);
        memset(last_report, 0xFF, sizeof(last_report));
    }
    hid_state = HID_STATE_IDLE;
}
```

`ret == -3` 表示：

```text
USB IN 端点还忙，上一包还没完成。
```

遇到 `-3`，直接清 0x81 并强制下次重发。

### 5.6 这个优化是否商业级

结论：

```text
这不是完整商业级 USB 恢复方案，
但它是合理的第一层稳定性增强。
```

原代码：

```text
只靠 hid_state 一个软件 busy。
```

优化后：

```text
1. hid_state busy 超时恢复
2. ret == -3 硬件 busy 恢复
3. 端点 flush
4. 强制重发 report
5. USB->INDEX 临界区保护
```

商业级还建议继续补：

```text
1. USB configured/suspend 状态判断
2. 错误计数和现场诊断
3. 分级恢复策略
4. 0x82 发送 busy 保护
5. 长时间压力测试
6. 睡眠唤醒/插拔测试
```

---

## 6. ADC DMA 扫描看门狗

### 6.1 它解决什么问题

ADC DMA 负责按键扫描。

正常流程：

```text
选择一行
启动 ADC DMA
DMA 采 14 列
DMA 完成中断
g_adc_complete = 1

lib_hall_sensor_task()
处理这一行
切下一行

5 行完成
g_scan_complete = 1

App_key.c
处理整帧按键
```

如果 ADC DMA 卡住：

```text
g_adc_complete 一直是 0
lib_hall_sensor_task() 一直 return
按键状态不再更新
```

表现：

```text
键盘自己不知道你有没有按键。
Fn 灯光切换也可能失效。
按下点亮灯效也可能不响应。
```

### 6.2 建议添加的看门狗代码

文件：

```text
Lib/src/lib_hall_sensor.c
```

新增全局变量：

```c
#define HALL_SCAN_TIMEOUT_MS 5U

static uint32_t g_hall_scan_start_tick = 0;
static volatile uint8_t g_hall_scan_restart_request = 0;
volatile uint32_t g_hall_scan_recover_count = 0;
volatile uint32_t g_hall_dma_error_count = 0;
```

新增启动当前行函数：

```c
static void hall_start_current_row(void)
{
    g_adc_complete = 0;
    select_row(g_current_row);
    Bsp_Delay_Us(SETTLING_TIME_US);
    g_hall_scan_start_tick = HAL_GetTick();
    bsp_adc_dma_start();
}
```

新增重启扫描函数：

```c
static void hall_restart_scan(void)
{
    DMA1_Channel1->CCR &= ~DMA_CCR_EN;
    DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
    g_adc_complete = 0;
    g_scan_complete = 0;
    g_current_row = 0;
    ROW_ALL_OFF();
    g_hall_scan_recover_count++;
    hall_start_current_row();
}
```

优化 DMA 中断：

```c
void DMA1_Channel1_IRQHandler(void)
{
    uint32_t isr = DMA1->ISR;

    if (isr & (DMA_ISR_TCIF1 | DMA_ISR_TEIF1)) {
        DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
        DMA1_Channel1->CCR &= ~DMA_CCR_EN;

        if (isr & DMA_ISR_TEIF1) {
            g_hall_dma_error_count++;
            g_hall_scan_restart_request = 1;
            return;
        }

        g_adc_complete = 1;
    }
}
```

优化扫描启动：

```c
void lib_hall_sensor_start_scan(void)
{
    g_scan_complete = 0;
    g_current_row = 0;
    hall_start_current_row();
}
```

优化扫描任务：

```c
void lib_hall_sensor_task(void)
{
    if (g_hall_scan_restart_request) {
        g_hall_scan_restart_request = 0;
        hall_restart_scan();
        return;
    }

    if (g_scan_complete) {
        return;
    }

    if (!g_adc_complete) {
        if ((HAL_GetTick() - g_hall_scan_start_tick) > HALL_SCAN_TIMEOUT_MS) {
            hall_restart_scan();
        }
        return;
    }

    g_adc_complete = 0;

    for (uint8_t c = 0; c < COL_COUNT; c++) {
        if (key_mask[g_current_row][c] == 0) {
            g_hall_adc_frame[g_current_row][c] = 0;
            continue;
        }

        g_hall_adc_frame[g_current_row][c] =
            process_hall_filter(g_current_row, c, gADCxConvertedData[c]);
    }

    g_current_row++;
    if (g_current_row >= ROW_COUNT) {
        g_current_row = 0;
        g_scan_complete = 1;
        ROW_ALL_OFF();
        return;
    }

    hall_start_current_row();
}
```

### 6.3 优点

```text
1. ADC DMA 卡住后能自动重启扫描。
2. DMA 传输错误不会被当作正常完成。
3. 避免键盘扫描状态机永久停住。
4. 可以通过 g_hall_scan_recover_count 判断是否发生过恢复。
```

---

## 7. 0x82 自定义 HID busy 保护

### 7.1 它解决什么问题

`0x82` 是自定义 HID IN 端点。

它用于：

```text
键盘 -> 上位机

灯效配置 ACK
读取配置回复
AI 按键主动上报
```

当前发送位置：

```text
App_protocol.c
    协议 ACK

App_key.c
    AI 冒泡上报
```

如果上一包 0x82 还没发完，又发下一包，可能返回 `-3`。

当前如果不检查返回值，就会导致：

```text
上位机偶尔收不到 ACK
AI 键偶尔没反应
灯效设置偶尔失败
```

### 7.2 建议添加发送封装

头文件：

```text
App/inc/App_protocol.h
```

新增：

```c
#include <stdbool.h>

bool App_protocol_send_packet(Packet_t *pkt);
```

实现文件：

```text
App/src/App_protocol.c
```

新增：

```c
#define HID_STATE_IDLE 0
#define HID_STATE_BUSY 1

volatile uint32_t g_protocol_tx_busy_count = 0;
volatile uint32_t g_protocol_tx_fail_count = 0;

extern volatile uint8_t custom_hid_state;

bool App_protocol_send_packet(Packet_t *pkt)
{
    if (custom_hid_state == HID_STATE_BUSY) {
        g_protocol_tx_busy_count++;
        return false;
    }

    int ret = usbd_ep_start_write(PROTOCOL_PKT_ACK_EP,
                                  (uint8_t *)pkt,
                                  PROTOCOL_PKT_SIZE);

    if (ret == 0) {
        custom_hid_state = HID_STATE_BUSY;
        return true;
    }

    g_protocol_tx_fail_count++;
    custom_hid_state = HID_STATE_IDLE;
    return false;
}
```

把原来：

```c
usbd_ep_start_write(PROTOCOL_PKT_ACK_EP, (uint8_t *)&tx_pkt, PROTOCOL_PKT_SIZE);
```

改成：

```c
App_protocol_send_packet(&tx_pkt);
```

把 AI 冒泡：

```c
usbd_ep_start_write(PROTOCOL_PKT_ACK_EP, (uint8_t *)&bubble_pkt, PROTOCOL_PKT_SIZE);
```

改成：

```c
App_protocol_send_packet(&bubble_pkt);
```

### 7.3 优点

```text
1. 所有 0x82 发送统一入口。
2. 不会在 0x82 还 busy 时继续硬发。
3. 后续要加 TX 队列或重试机制，只需要改一个函数。
4. 上位机 ACK、AI 上报、灯效读取更稳定。
```

---

## 8. `__disable_irq()` 队列保护分析

`App_protocol_pop_rx()` 中：

```c
__disable_irq();
if (g_rx_count > 0U) {
    memcpy(pkt, &g_rx_queue[g_rx_tail], PROTOCOL_PKT_SIZE);
    g_rx_tail = (uint8_t)((g_rx_tail + 1U) % PROTOCOL_RX_QUEUE_SIZE);
    g_rx_count--;
    has_pkt = true;
}
__enable_irq();
```

作用：

```text
防止 USB 中断正在写队列时，主循环同时读队列。
```

会不会影响其他中断？

```text
会。
在 __disable_irq() 到 __enable_irq() 之间，普通中断都不能进。
```

包括：

```text
USB 中断
ADC DMA 中断
SPI DMA 中断
TIM6 中断
USART 中断
```

但这段很短，只复制 64 字节，通常影响很小。

更精细的优化是只关 USB 中断：

```c
NVIC_DisableIRQ(USBD_IRQn);
...
NVIC_EnableIRQ(USBD_IRQn);
```

但当前写法简单可靠，现阶段可以接受。

---

## 9. App_lighting.c 过大的优化建议

当前 `App_led_animation_task()` 里放了：

```text
音乐超时
SPI busy 判断
速度控制
颜色计算
所有灯效算法
CapsLock 覆盖
```

后期维护会变难。

建议拆成：

```c
static void App_light_handle_music_timeout(void);
static bool App_light_should_update_animation(void);
static void App_light_apply_caps_lock(void);

static void App_light_mode_off(void);
static void App_light_mode_static(uint8_t r, uint8_t g, uint8_t b);
static void App_light_mode_key_press(uint8_t r, uint8_t g, uint8_t b);
static void App_light_mode_halo(uint8_t brightness);
static void App_light_mode_bounce_marquee(uint8_t brightness);
static void App_light_mode_snake_marquee(uint8_t brightness);
static void App_light_mode_cyber_snake(uint8_t brightness);
```

拆分后主函数变成：

```c
void App_led_animation_task(void)
{
    App_light_handle_music_timeout();

    if (!App_light_should_update_animation()) {
        return;
    }

    uint8_t cur_r = (g_light_r * g_light_brightness) / 100;
    uint8_t cur_g = (g_light_g * g_light_brightness) / 100;
    uint8_t cur_b = (g_light_b * g_light_brightness) / 100;

    switch (g_light_mode) {
        case LIGHT_MODE_OFF:
            App_light_mode_off();
            break;

        case LIGHT_MODE_STATIC:
            App_light_mode_static(cur_r, cur_g, cur_b);
            break;

        case LIGHT_MODE_KEY_PRESS:
            App_light_mode_key_press(cur_r, cur_g, cur_b);
            break;

        default:
            break;
    }

    App_light_apply_caps_lock();
}
```

优点：

```text
1. 主流程更清楚。
2. 每个灯效单独维护。
3. 改一个灯效不容易影响其他灯效。
4. 后续可以拆成 App_light_modes.c / App_light_modes.h。
```

---

## 10. 三条关键链路总结

### 10.1 按键到电脑打字链路

```text
Bsp
    ADC + DMA 采集

Lib
    lib_hall_sensor_task()
    生成 g_hall_adc_frame

App_key
    App_adkey_scan_task()
    process_key_logic()
    report_dirty = true

App_usb
    App_usb_process_task()
    生成 current_report[8]
    usbd_ep_start_write(0x81, report, 8)

User USB
    0x81 IN 完成回调
    hid_state = IDLE

PC
    收到键盘输入
```

### 10.2 Fn 切换灯光链路

```text
Lib
    扫描 ADC

App_key
    判断 Fn + KEY_LIGHT
    App_handle_internal_key(KEY_LIGHT)
    g_light_mode++
    g_led_dirty = true

App_lighting
    计算灯效
    App_led_display_task()

Lib/Bsp
    WS2812 SPI DMA 输出
```

### 10.3 上位机控制灯光链路

```text
PC 上位机
    HID OUT 0x02 发命令

User USB
    usbd_custom_hid_out_callback()

App_protocol
    App_protocol_on_rx()
    App_protocol_task()
    App_set_light_config()

App_lighting
    g_led_dirty = true
    App_led_display_task()

WS2812
    灯效变化
```

---

## 11. 故障现象判断

现象：

```text
键盘使用一段时间无法打字
灯光正常
Fn 可以切换灯光模式
```

推理：

```text
灯光能切换
    说明 App_key 内部功能键还在工作

App_key 还在工作
    说明 ADC 扫描大概率还在
    说明主循环大概率还在

不能打字
    普通按键报告没有到电脑

普通打字走 0x81
    所以优先怀疑 0x81 HID IN 端点卡住
```

所以优先优化：

```text
USB 0x81 卡死恢复
```

其次优化：

```text
0x82 自定义 HID busy 保护
ADC DMA 扫描看门狗
```

---

## 12. 优化优先级建议

第一优先级：

```text
USB 0x81 卡死恢复
```

原因：

```text
最符合“灯正常但不能打字”的现象。
```

第二优先级：

```text
0x82 自定义 HID busy 保护
```

原因：

```text
提高上位机通信、AI 上报、灯效 ACK 稳定性。
```

第三优先级：

```text
ADC DMA 扫描看门狗
```

原因：

```text
防止扫描链路长期运行中卡死。
```

第四优先级：

```text
App_lighting.c 拆函数
```

原因：

```text
改善维护性，不是当前故障第一原因。
```

---

## 13. 商业级代码还需要补什么

当前优化属于：

```text
工程增强级 / 第一层稳定性保护
```

还不算完整商业级。

商业级建议继续补：

```text
1. USB configured / suspend 状态判断
2. USB 0x81 分级恢复策略
3. 0x82 发送队列或重试机制
4. ADC DMA 扫描超时恢复
5. SPI DMA 灯效刷新超时恢复
6. IWDG 独立看门狗
7. 错误计数和可读取诊断
8. USB 插拔测试
9. PC 睡眠/唤醒测试
10. 长时间压力测试
```

---

## 14. 最简单记忆

```text
0x81
    键盘打字通道
    解决不能打字

ADC DMA
    按键扫描通道
    解决键盘自己不知道有没有按键

0x82
    上位机通信通道
    解决灯效 ACK / AI 上报不稳定
```

如果现象是：

```text
灯光正常
Fn 能切灯
电脑不能打字
```

优先看：

```text
USB 0x81
```

