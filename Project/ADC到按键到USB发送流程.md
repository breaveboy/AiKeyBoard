# ADC 到按键状态再到 USB HID 发送流程

本文档按当前代码版本梳理一次完整链路：从霍尔传感器的 ADC 采集，到按键状态判断，再到生成 USB HID 键盘报告并发送给 PC。

## 总体流程

```text
系统初始化
  -> 初始化行 GPIO / 列 ADC / DMA
  -> 校准每个键的空闲 ADC 基准值
  -> 初始化 USB HID 设备
  -> 启动第一次 ADC DMA 采样

主循环
  -> lib_hall_sensor_task()
       如果 DMA 已完成:
         读取当前行 14 路 ADC
         对每个有效按键做滤波
         更新动态基准
         判断按下/松开状态
         切到下一行
         重新启动 ADC DMA

  -> Task_exec()
       App_adkey_scan_task()
         对比 keys[][] 和 last_key_state[][]
         如果状态变化，置 report_dirty = true

       App_usb_process_task()
         如果 report_dirty = true
         生成 8 字节标准键盘 HID report
         调用 usbd_ep_start_write(0x81, report, 8)

USB 中断
  -> PC 取走 IN 数据
  -> usbd_hid_int_callback()
  -> hid_state = HID_STATE_IDLE
```

## 1. 初始化阶段

入口在 `User/Src/main.c`。

### 1.1 系统和外设初始化

`main()` 先执行：

```c
HAL_Init();
APP_SystemClockConfig();
bsp_usart_init(115200);
bsp_tim_init();
```

其中 `bsp_tim_init()` 启动 TIM6。TIM6 每 1ms 进一次中断，最终调用：

```c
Task_update();
```

`Task_update()` 只做一件事：

```c
g_cnt++;
```

后面的 `Task_exec()` 依赖 `g_cnt` 来调度应用任务。

### 1.2 霍尔扫描初始化

`main()` 调用：

```c
lib_hall_sensor_init();
```

这个函数在 `Lib/src/lib_hall_sensor.c` 中，主要完成：

- 开启 GPIOA/GPIOB/GPIOC 时钟。
- 配置 5 条行扫描 GPIO：`PC6~PC9` 和 `PA8`。
- 配置 14 路列输入为模拟输入：`PA0~PA7`、`PB0~PB1`、`PC0~PC3`。
- 调用 `bsp_adc_dma_init()` 初始化 ADC1 + DMA1 Channel1。

### 1.3 ADC + DMA 初始化

`bsp_adc_dma_init()` 在 `Bsp/src/bsp_adc_dma.c` 中。

关键配置：

```c
AdcHandle.Instance = ADC1;
AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
AdcHandle.Init.ScanConvMode = ADC_SCAN_ENABLE;
AdcHandle.Init.ContinuousConvMode = DISABLE;
AdcHandle.Init.NbrOfConversion = 14;
AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
```

含义：

- ADC1 使用 12 位分辨率。
- 开启扫描模式，一次转换 14 个通道。
- 非连续转换，每次需要软件启动。
- DMA 把 14 个 ADC 结果搬到 `gADCxConvertedData[14]`。

14 路通道映射如下：

```text
列 0~7   -> PA0~PA7 -> ADC_CHANNEL_0~7
列 8~9   -> PB0~PB1 -> ADC_CHANNEL_8~9
列 10~13 -> PC0~PC3 -> ADC_CHANNEL_10~13
```

DMA 配置：

```c
DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
DMA1_Channel1->CMAR = (uint32_t)gADCxConvertedData;
DMA1_Channel1->CNDTR = 14;
DMA1_Channel1->CCR = DMA_CCR_MINC | DMA_CCR_PSIZE_0 | DMA_CCR_MSIZE_0 | DMA_CCR_PL;
```

意思是：ADC 数据寄存器固定不变，内存地址递增，一次搬 14 个 halfword。

### 1.4 空闲基准校准

`main()` 调用：

```c
lib_hall_sensor_calibration();
```

当前版本的校准逻辑是逐行扫描：

```c
for (uint8_t r = 0; r < ROW_COUNT; r++) {
    select_row(r);
    Bsp_Delay_Us(SETTLING_TIME_US);
    g_adc_complete = 0;
    bsp_adc_dma_start();
    while (!g_adc_complete) {}
    g_adc_complete = 0;

    for (uint8_t c = 0; c < COL_COUNT; c++) {
        uint16_t idle = gADCxConvertedData[c];
        keys[r][c].idele_adc = idle;
        ...
    }
}
```

每个键初始化这些参数：

```c
keys[r][c].idele_adc = idle;
keys[r][c].drift_cnt = 0;
keys[r][c].actuation_point = 350;
keys[r][c].top_deadzone = 80;
keys[r][c].bottom_deadzone = 1050;
keys[r][c].rt_press_sens = 50;
keys[r][c].rt_release_sens = 50;
keys[r][c].is_pressed = 0;
keys[r][c].in_rt_cycle = 0;
keys[r][c].max_offset = 0;
keys[r][c].min_offset = 0;
```

同时初始化滤波器状态：

```c
raw_history[r][c][0] = idle;
raw_history[r][c][1] = idle;
raw_history[r][c][2] = idle;
ema_accumulator[r][c] = ((uint32_t)idle << EMA_SHIFT);
logical_output[r][c] = idle;
```

这里的 `idele_adc` 是后续判断按键位移的基准值。

### 1.5 USB HID 初始化

`main()` 调用：

```c
APP_USBInit();
```

里面会：

```c
__HAL_RCC_SYSCFG_CLK_ENABLE();
SET_BIT(RCC->CFGR1, RCC_CFGR1_USBSELHSI48_Msk);
__HAL_RCC_USB_CLK_ENABLE();
hid_keyboard_init();
NVIC_EnableIRQ(USBD_IRQn);
```

`hid_keyboard_init()` 在 `User/Src/usbd_hid_keyboard_if.c` 中。

它注册两个 USB HID interface：

```text
Interface 0: 标准键盘 HID
  IN endpoint: 0x81
  packet size: 8 bytes

Interface 1: 自定义 HID
  OUT endpoint: 0x02, PC -> MCU
  IN endpoint:  0x82, MCU -> PC
  packet size: 64 bytes
```

普通键盘打字走的是标准键盘 IN endpoint `0x81`。

### 1.6 启动第一次运行扫描

初始化结束后，`main()` 启动第一次 ADC DMA：

```c
g_scan_complete = 0;
select_row(0);
Bsp_Delay_Us(SETTLING_TIME_US);
bsp_adc_dma_start();
```

从这里开始，扫描链路进入运行状态。

## 2. 行扫描和 ADC 采集

键盘矩阵是 5 行 x 14 列。

### 2.1 选择当前行

`select_row(index)` 做两步：

1. 先关闭所有行：

```c
ROW_ALL_OFF();
```

2. 再把目标行拉低：

```c
case 0: CLR_IO(GPIOA, GPIO_PIN_8); break;
case 1: CLR_IO(GPIOC, GPIO_PIN_9); break;
case 2: CLR_IO(GPIOC, GPIO_PIN_8); break;
case 3: CLR_IO(GPIOC, GPIO_PIN_7); break;
case 4: CLR_IO(GPIOC, GPIO_PIN_6); break;
```

当前选中的这一行会影响 14 路霍尔传感器输出，随后 ADC 同时扫描这 14 个列通道。

### 2.2 启动 ADC DMA

`bsp_adc_dma_start()` 每次启动一轮 14 通道采样：

```c
DMA1_Channel1->CCR &= ~DMA_CCR_EN;
DMA1_Channel1->CMAR = (uint32_t)gADCxConvertedData;
DMA1_Channel1->CNDTR = 14;
DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
ADC1->SR = ~(ADC_SR_EOC | ADC_SR_STRT);

DMA1_Channel1->CCR |= (DMA_CCR_TCIE | DMA_CCR_EN);
ADC1->CR2 |= ADC_CR2_SWSTART;
```

执行后：

- ADC1 依次转换 14 个通道。
- DMA 把 14 个结果写入 `gADCxConvertedData[0..13]`。
- DMA 完成后触发 `DMA1_Channel1_IRQHandler()`。

### 2.3 DMA 完成中断

当前版本的 DMA 中断很轻：

```c
void DMA1_Channel1_IRQHandler(void) {
    if(DMA1->ISR & (DMA_ISR_TCIF1 | DMA_ISR_TEIF1)) {
        DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
        DMA1_Channel1->CCR &= ~DMA_CCR_EN;
        g_adc_complete = 1;
    }
}
```

它只做：

- 清 DMA 标志。
- 关闭 DMA。
- 置位 `g_adc_complete = 1`。

真正的数据处理不在中断里做，而是在主循环的 `lib_hall_sensor_task()` 里做。

## 3. 主循环推进扫描状态机

`main()` 的主循环：

```c
while (1) {
    lib_hall_sensor_task();
    Task_exec();
}
```

### 3.1 等待 DMA 完成

`lib_hall_sensor_task()` 开头：

```c
if (!g_adc_complete) {
    return;
}

g_adc_complete = 0;
```

如果 ADC DMA 还没完成，函数立刻返回。  
如果 DMA 已完成，就开始处理当前行。

### 3.2 处理当前行的 14 列

当前行索引用 `g_current_row` 表示。

```c
for (uint8_t c = 0; c < COL_COUNT; c++) {
    if (key_mask[g_current_row][c] == 0) {
        continue;
    }

    uint16_t adc = process_hall_filter(g_current_row, c, gADCxConvertedData[c]);

    Key_t *k = &keys[g_current_row][c];
    update_baseline_tracking(k, adc);
    process_key_logic(k, adc);
}
```

对每个有效按键依次执行：

1. 从 `gADCxConvertedData[c]` 取当前列 ADC。
2. 调用 `process_hall_filter()` 滤波。
3. 调用 `update_baseline_tracking()` 做动态基准追踪。
4. 调用 `process_key_logic()` 更新 `keys[row][col].is_pressed`。

`key_mask` 为 0 的位置是无效按键，不参与处理。

### 3.3 切到下一行并再次启动 ADC

当前行处理完后：

```c
g_current_row++;
if (g_current_row >= ROW_COUNT) {
    g_current_row = 0;
    g_scan_complete = 1;
}

select_row(g_current_row);
Bsp_Delay_Us(SETTLING_TIME_US);
bsp_adc_dma_start();
```

也就是说，每次 DMA 完成后只处理一行。处理完后立刻切下一行并启动下一次 ADC DMA。

完整扫描顺序：

```text
row 0 ADC -> 处理 row 0 -> 启动 row 1 ADC
row 1 ADC -> 处理 row 1 -> 启动 row 2 ADC
row 2 ADC -> 处理 row 2 -> 启动 row 3 ADC
row 3 ADC -> 处理 row 3 -> 启动 row 4 ADC
row 4 ADC -> 处理 row 4 -> g_scan_complete = 1 -> 启动 row 0 ADC
```

当前有效代码中 `g_scan_round` 暂时没有参与运行扫描。

## 4. ADC 数据滤波

滤波函数：

```c
uint16_t process_hall_filter(uint8_t row, uint8_t col, uint16_t new_raw)
```

当前使用三层处理。

### 4.1 三点中值滤波

保存最近三次原始 ADC：

```c
raw_history[row][col][0] = raw_history[row][col][1];
raw_history[row][col][1] = raw_history[row][col][2];
raw_history[row][col][2] = new_raw;
```

然后取中间值：

```c
uint16_t median_val = fast_median(...);
```

作用：去掉单次毛刺。

### 4.2 EMA 滑动平均

```c
ema_accumulator[row][col] += median_val - (ema_accumulator[row][col] >> EMA_SHIFT);
uint16_t ema_val = ema_accumulator[row][col] >> EMA_SHIFT;
```

`EMA_SHIFT = 3`，相当于比较平滑的低通滤波。

作用：降低 ADC 噪声，但会带来一点响应延迟。

### 4.3 迟滞死区

```c
int16_t delta = (int16_t)ema_val - (int16_t)logical_output[row][col];
if (delta > HYSTERESIS_DEADZONE) {
    logical_output[row][col] = ema_val - HYSTERESIS_DEADZONE;
} else if (delta < -HYSTERESIS_DEADZONE) {
    logical_output[row][col] = ema_val + HYSTERESIS_DEADZONE;
}
```

`HYSTERESIS_DEADZONE = 4`。

作用：ADC 只小幅抖动时，不让逻辑值跟着来回跳。

最终返回：

```c
return logical_output[row][col];
```

后面的按键判断都基于这个滤波后的 ADC。

## 5. 动态基准追踪

函数：

```c
void update_baseline_tracking(Key_t* k, uint16_t cur_adc)
```

作用：长期空闲时，让 `idele_adc` 缓慢跟随温漂。

逻辑：

1. 如果按键已经处于按下状态，不更新基准：

```c
if (k->is_pressed) {
    k->drift_cnt = 0;
    return;
}
```

2. 计算当前 ADC 和空闲基准的差：

```c
int32_t diff = (int32_t)k->idele_adc - (int32_t)cur_adc;
```

3. 如果偏差在 `-30 ~ +30` 内，认为可能是温漂：

```c
if (diff < 30 && diff > -30) {
    k->drift_cnt++;
    if (k->drift_cnt > 1000) {
        if (diff > 0) k->idele_adc--;
        else if (diff < 0) k->idele_adc++;
        k->drift_cnt = 0;
    }
}
```

4. 如果偏差超过范围，认为可能有人按键，不更新基准：

```c
else {
    k->drift_cnt = 0;
}
```

这个机制只会在空闲、小偏差、持续稳定时慢慢修正基准。

## 6. 按键按下/松开判断

函数：

```c
uint8_t process_key_logic(Key_t* k, uint16_t cur_adc)
```

### 6.1 计算按键偏移量

```c
int32_t diff = (int32_t)k->idele_adc - (int32_t)cur_adc;
int16_t offset = (diff > 0) ? (int16_t)diff : 0;
```

当前逻辑认为：按下时 ADC 会比空闲基准低，所以用：

```text
offset = idle_adc - current_adc
```

如果 `current_adc` 比 `idle_adc` 高，则 offset 置 0。

### 6.2 顶部死区

```c
if (offset < k->top_deadzone) {
    k->is_pressed = 0;
    k->in_rt_cycle = 0;
    k->max_offset = 0;
    k->min_offset = 0;
    return 0;
}
```

当前 `top_deadzone = 80`。

当偏移量小于顶部死区时，认为按键处于完全松开区域。

### 6.3 底部死区

```c
if (offset > k->bottom_deadzone) offset = k->bottom_deadzone;
```

当前 `bottom_deadzone = 1050`。

作用是限制最大行程，避免异常 ADC 导致逻辑过冲。

### 6.4 未按下状态下的触发判断

```c
if (!k->is_pressed) {
    if (offset < k->min_offset) k->min_offset = offset;
    uint16_t trigger_line = k->in_rt_cycle ? (k->min_offset + k->rt_press_sens) : k->actuation_point;
    if (offset >= trigger_line) {
        k->is_pressed = 1;
        k->in_rt_cycle = 1;
        k->max_offset = offset;
    }
}
```

第一次触发时通常使用：

```c
k->actuation_point = 350;
```

也就是说 `offset >= 350` 时认为按下。

进入 RT 周期后，触发线变成：

```text
min_offset + rt_press_sens
```

当前 `rt_press_sens = 50`。

### 6.5 已按下状态下的释放判断

```c
else {
    if (offset > k->max_offset) k->max_offset = offset;
    uint16_t release_line = k->max_offset - k->rt_release_sens;
    if (offset <= release_line) {
        k->is_pressed = 0;
        k->min_offset = offset;
    }
}
```

释放线是：

```text
max_offset - rt_release_sens
```

当前 `rt_release_sens = 50`。

这就是 RT 的核心：按下后，释放不是回到固定 AP，而是相对最大按下位置回弹一定距离后释放。

## 7. 按键状态变化检测

按键逻辑更新后，`keys[row][col].is_pressed` 已经是当前状态。

`Task_exec()` 每 1ms 调用一次：

```c
App_adkey_scan_task();
```

当前版本中，`App_adkey_scan_task()` 已经不再调用 `lib_hall_sensor_task()`，它只负责比较状态变化：

```c
void App_adkey_scan_task(void) {
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            if (key_mask[r][c] == 0) continue;
            if (keys[r][c].is_pressed != last_key_state[r][c]) {
                last_key_state[r][c] = keys[r][c].is_pressed;
                report_dirty = true;
            }
        }
    }
}
```

这里有两个关键变量：

```c
keys[r][c].is_pressed
last_key_state[r][c]
```

当两者不同，说明这个键发生了按下或松开变化，于是：

```c
report_dirty = true;
```

`report_dirty` 的含义是：键盘 HID report 需要重新生成并发送给 PC。

## 8. HID 键盘报告生成

`Task_exec()` 每 1ms 调用：

```c
App_usb_process_task();
```

如果没有状态变化，直接返回：

```c
if (!report_dirty) return;
```

### 8.1 标准键盘 8 字节 report

当前使用标准 Boot Keyboard 风格的 8 字节报告：

```text
Byte 0: modifier 位图
Byte 1: reserved
Byte 2: keycode 1
Byte 3: keycode 2
Byte 4: keycode 3
Byte 5: keycode 4
Byte 6: keycode 5
Byte 7: keycode 6
```

所以普通非修饰键最多同时上报 6 个。

### 8.2 判断 Fn 是否按下

先扫描全矩阵，看是否有 `KEY_FN` 被按下：

```c
bool fn_pressed = false;

for (uint8_t r = 0; r < ROW_COUNT; r++) {
    for (uint8_t c = 0; c < COL_COUNT; c++) {
        if (keys[r][c].is_pressed && g_key_map[r][c] == KEY_FN) {
            fn_pressed = true;
            break;
        }
    }
}
```

如果 Fn 按下，后续优先使用 `g_fn_key_map`。  
如果 Fn 没按下，使用普通层 `g_key_map`。

### 8.3 生成当前 report

```c
uint8_t current_report[8] = {0};
uint8_t key_count = 0;
```

遍历所有按下的有效键：

```c
uint8_t code = fn_pressed ? g_fn_key_map[r][c] : g_key_map[r][c];
if (code == KEY_NONE) code = g_key_map[r][c];
if (code == KEY_NONE || code == KEY_FN) continue;
```

含义：

- Fn 层有定义，就用 Fn 层。
- Fn 层没定义，回退到普通层。
- `KEY_NONE` 和 `KEY_FN` 本身不发给 PC。

### 8.4 内部功能键处理

如果键码大于等于 `0xF0`，认为是内部功能键：

```c
if (code >= 0xF0) {
    if (last_fn_state[r][c] == 0) {
        App_handle_internal_key(code);
        last_fn_state[r][c] = 1;
    }
    continue;
}
```

这些键不会进入标准键盘 report。

例如 `KEY_LIGHT` 会在 `App_handle_internal_key()` 中切换灯光：

```c
g_light_mode = (LightMode_t)((g_light_mode + 1) % LIGHT_MODE_MAX);
ws2812_tick = 0;
lib_ws2812_set_all(0, 0, 0);
g_led_dirty = true;
```

这也是为什么有时 `Fn + 灯光键` 能用，但普通打字不能用：灯光切换是本地逻辑，不依赖 PC 成功接收 USB 键盘报告。

### 8.5 修饰键处理

如果键码在 `0xE0~0xE7`，放进 Byte 0：

```c
if (code >= 0xE0 && code <= 0xE7) {
    current_report[0] |= (1U << (code - 0xE0));
}
```

对应关系：

```text
0xE0 -> Left Ctrl
0xE1 -> Left Shift
0xE2 -> Left Alt
0xE3 -> Left GUI
0xE4 -> Right Ctrl
0xE5 -> Right Shift
0xE6 -> Right Alt
0xE7 -> Right GUI
```

### 8.6 普通键处理

普通键放入 Byte 2~Byte 7：

```c
else if (key_count < 6) {
    current_report[2 + key_count++] = code;
}
```

超过 6 个普通键时，当前代码会忽略第 7 个及之后的普通键。

## 9. HID 报告发送到 PC

`App_usb_process_task()` 生成 `current_report` 后，会和上一次发送的报告比较：

```c
static uint8_t last_report[8] = {0};
if (memcmp(current_report, last_report, 8) != 0) {
    if (usbd_ep_start_write(HID_INT_EP, current_report, 8) == 0) {
        hid_state = HID_STATE_BUSY;
        memcpy(last_report, current_report, 8);
        report_dirty = false;
    }
} else {
    report_dirty = false;
}
```

只有当前 report 和上一次不同，才会发送。

发送使用：

```c
usbd_ep_start_write(HID_INT_EP, current_report, 8)
```

其中：

```c
#define HID_INT_EP 0x81
```

`0x81` 是标准键盘 IN endpoint，也就是 MCU -> PC 的键盘输入端点。

发送成功后：

```c
hid_state = HID_STATE_BUSY;
memcpy(last_report, current_report, 8);
report_dirty = false;
```

注意：当前代码设置了 `hid_state = HID_STATE_BUSY`，但发送前没有用 `hid_state` 做保护或超时恢复。

## 10. USB 发送完成回调

PC 取走 endpoint `0x81` 的数据后，USB 中断会进入 CherryUSB，并最终调用：

```c
static void usbd_hid_int_callback(uint8_t ep, uint32_t nbytes)
```

当前逻辑：

```c
if (ep == HID_INT_EP) {
    hid_state = HID_STATE_IDLE;
} else if (ep == HID_CUSTOM_IN_EP) {
    custom_hid_state = HID_STATE_IDLE;
}
```

也就是说，标准键盘报告发送完成后：

```c
hid_state = HID_STATE_IDLE;
```

这表示 USB IN 端点上一包已经发完。

## 11. 一个按键按下到 PC 收到字符的例子

假设按下 `A` 键。

1. 某一行被 `select_row()` 选中。
2. `bsp_adc_dma_start()` 启动 14 列 ADC 扫描。
3. DMA 把 14 个 ADC 值写入 `gADCxConvertedData[]`。
4. DMA 中断置 `g_adc_complete = 1`。
5. 主循环调用 `lib_hall_sensor_task()`。
6. `process_hall_filter()` 对 A 键位置的 ADC 做滤波。
7. `process_key_logic()` 计算：

```text
offset = idele_adc - cur_adc
```

8. 如果 `offset >= actuation_point`，则：

```c
keys[row][col].is_pressed = 1;
```

9. `Task_exec()` 调用 `App_adkey_scan_task()`。
10. 发现：

```c
keys[row][col].is_pressed != last_key_state[row][col]
```

11. 置：

```c
report_dirty = true;
```

12. `Task_exec()` 调用 `App_usb_process_task()`。
13. 查表 `g_key_map[row][col]` 得到 A 的 HID keycode，通常是 `0x04`。
14. 生成 report：

```text
00 00 04 00 00 00 00 00
```

15. 调用：

```c
usbd_ep_start_write(0x81, current_report, 8);
```

16. PC 收到 HID report，系统输入一个 A 按键事件。
17. PC 取走数据后，`usbd_hid_int_callback()` 把 `hid_state` 改回 `IDLE`。

松开 A 时流程类似，只是 `keys[row][col].is_pressed` 变成 0，最终发送全 0 report：

```text
00 00 00 00 00 00 00 00
```

PC 收到后认为 A 键释放。

## 12. 当前链路中的关键变量

| 变量 | 所在模块 | 作用 |
| --- | --- | --- |
| `gADCxConvertedData[14]` | `bsp_adc_dma.c` | 当前行 14 列 ADC 采样结果 |
| `g_adc_complete` | `lib_hall_sensor.c` | DMA 完成标志 |
| `g_current_row` | `lib_hall_sensor.c` | 当前扫描行 |
| `keys[row][col].idele_adc` | `lib_hall_sensor.c` | 每个键的空闲 ADC 基准 |
| `keys[row][col].is_pressed` | `lib_hall_sensor.c` | 当前按键逻辑状态 |
| `last_key_state[row][col]` | `App_key.c` | 上一次上报前记录的按键状态 |
| `report_dirty` | `App_key.c` | 是否需要重新发送键盘 report |
| `current_report[8]` | `App_usb.c` | 当前生成的 USB HID 键盘报告 |
| `last_report[8]` | `App_usb.c` | 上一次成功发送的键盘报告 |
| `hid_state` | `usbd_hid_keyboard_if.c` | 标准键盘 IN 端点发送状态 |

## 13. 当前代码需要特别注意的点

### 13.1 `lib_hall_sensor_task()` 现在只有一个主入口

当前已经调整为：

```text
main() -> lib_hall_sensor_task()
Task_exec() -> App_adkey_scan_task()
```

`App_adkey_scan_task()` 不再调用 `lib_hall_sensor_task()`。

这是合理的，因为：

- `lib_hall_sensor_task()` 负责扫描状态机。
- `App_adkey_scan_task()` 只负责状态变化检测。

这样职责清楚，扫描状态机不会被两个地方推进。

### 13.2 当前运行扫描没有 DMA 看门狗

当前有效版本中：

```c
if (!g_adc_complete) {
    return;
}
```

如果某次 ADC/DMA 没有再产生完成中断，扫描链路会一直停在这里。

旧版 `#if 0` 中有 `scan_watchdog`，当前有效代码没有。

如果要增强稳定性，建议后续给当前扫描方式也加一个扫描超时恢复。

### 13.3 HID 发送没有失败处理

当前代码只在 `usbd_ep_start_write()` 返回 0 时处理成功：

```c
if (usbd_ep_start_write(HID_INT_EP, current_report, 8) == 0) {
    ...
}
```

如果返回失败，当前没有打印、没有计数、没有恢复。

常见失败包括：

```text
-2: endpoint 没打开
-3: IN endpoint 上一包还没发完，端点忙
```

如果出现“Fn 能切灯，但不能打字”，优先看这里。

### 13.4 USB suspend/resume 当前没有应用层处理

CherryUSB 底层能收到 USB suspend/resume 事件，但当前 HID interface 没有挂应用层 `notify_handler`。

所以 PC 空闲挂起 USB 后，应用层不会主动同步：

- `hid_state`
- endpoint 状态
- custom HID OUT 接收
- remote wakeup

这和“停一段时间不能打字，断开重连恢复”的现象高度相关。

## 14. 排查建议

如果后续要定位“扫描问题还是 USB 问题”，建议加以下计数器。

### 14.1 DMA 中断计数

在 `DMA1_Channel1_IRQHandler()` 中：

```c
volatile uint32_t adc_dma_irq_cnt = 0;

void DMA1_Channel1_IRQHandler(void) {
    adc_dma_irq_cnt++;
    ...
}
```

不能打字时，如果这个计数还在增长，说明 ADC/DMA 扫描还活着。

### 14.2 按键状态变化计数

在 `App_adkey_scan_task()` 中：

```c
volatile uint32_t key_change_cnt = 0;

if (keys[r][c].is_pressed != last_key_state[r][c]) {
    key_change_cnt++;
    ...
}
```

不能打字时，如果这个计数还会变，说明按键识别还活着。

### 14.3 USB 写入返回值

在 `App_usb_process_task()` 中：

```c
int ret = usbd_ep_start_write(HID_INT_EP, current_report, 8);
printf("hid write ret=%d\r\n", ret);
```

判断：

```text
ret = 0   -> 已提交给 USB endpoint
ret = -2  -> endpoint 未打开或配置异常
ret = -3  -> endpoint 忙，上一包没完成
```

### 14.4 USB IN 完成计数

在 `usbd_hid_int_callback()` 中：

```c
volatile uint32_t hid_in_done_cnt = 0;

if (ep == HID_INT_EP) {
    hid_in_done_cnt++;
    hid_state = HID_STATE_IDLE;
}
```

如果 `usbd_ep_start_write()` 返回 0，但 `hid_in_done_cnt` 不增长，说明 PC 没有取走 IN 数据或 USB 中断/端点状态卡住。

## 15. 简短结论

当前完整链路是：

```text
ADC DMA 采样当前行 14 列
  -> DMA 中断置 g_adc_complete
  -> main 中 lib_hall_sensor_task 处理 ADC
  -> 滤波 + 动态基准 + RT/AP 判断
  -> 更新 keys[row][col].is_pressed
  -> 1ms 任务 App_adkey_scan_task 发现状态变化
  -> report_dirty = true
  -> 1ms 任务 App_usb_process_task 生成 8 字节 HID report
  -> usbd_ep_start_write(0x81)
  -> PC 收到键盘输入
```

如果本地 Fn 灯光能切换但 PC 不能打字，说明链路大概率断在：

```text
App_usb_process_task()
  -> usbd_ep_start_write(0x81)
  -> USB IN 完成回调
  -> PC 接收
```

如果 Fn 灯光也不能切，才优先回头查：

```text
ADC/DMA 扫描
按键状态判断
主循环/任务调度
```
