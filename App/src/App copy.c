#include "App.h"
#include "lib_config.h"
#include "bsp_uart.h"
#include "usb_config.h"
#include "lib_ws2812.h"
#include "lib_hall_sensor.h"
#include <stdio.h>
#include <string.h>

#include <stdint.h>

static bool report_dirty = false; //usb报告更新标志位
static bool g_led_dirty = false; //灯光更新标志位
static uint8_t last_key_state[ROW_COUNT][COL_COUNT] = {0};  //上次的按键状态值
static uint8_t last_fn_state[ROW_COUNT][COL_COUNT] = {0};    //上次的fn的状态值






//usb通讯的任务
extern volatile uint8_t hid_state; // 声明外部变量
#ifndef HID_STATE_IDLE   //发送完毕的宏
	#define HID_STATE_IDLE 0  
#endif
#ifndef HID_STATE_BUSY
	#define HID_STATE_BUSY 1
#endif

#ifndef HID_INT_EP
	#define HID_INT_EP  0x81  // 通常键盘端点地址是 0x81
#endif




#define KEY_NONE    0x00   // 无效键，不处理
#define KEY_FN      0xF0   // Fn，固件内部用，不发给电脑
#define KEY_LIGHT   0xF1   // 灯光切换，固件内部用
#define KEY_WINLOCK 0xF2   // Win锁，固件内部用
#define KEY_MAC     0xF3   // MAC模式，固件内部用
#define KEY_WIN     0xF4   // WIN模式，固件内部用
/////////////////////////////////////////////////////////ws2812相关/////////////////////////////////////////////////
typedef enum {
    LIGHT_MODE_OFF = 0,    // 关闭
    LIGHT_MODE_BREATH,     // 呼吸
    LIGHT_MODE_RAINBOW,    // 炫彩
    LIGHT_MODE_KEY_PRESS,  // 按键按下
    LIGHT_MODE_STATIC,     // 静态常亮
    LIGHT_MODE_WAVE,       // 波浪
    LIGHT_MODE_MAX
} LightMode_t;

static LightMode_t g_light_mode = LIGHT_MODE_OFF;
static uint8_t g_pending_internal_key = KEY_NONE; // 待处理的内部功能键
static uint32_t ws2812_tick = 0;




// 直接定义 60% 键盘的 16 进制映射表
static const uint8_t g_key_map[5][14] = {
    /* Row 0: Esc(29), 1-0(1E-27), -(2D), =(2E), Backspace(2A) */
    {0x29, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x2A},

    /* Row 1: Tab(2B), Q(14), W(1A), E(08), R(15), T(17), Y(1C), U(18), I(0C), O(12), P(13), [(2F), ](30), \(31) */
    {0x2B, 0x14, 0x1A, 0x08, 0x15, 0x17, 0x1C, 0x18, 0x0C, 0x12, 0x13, 0x2F, 0x30, 0x31},

    /* Row 2: Caps(39), A(04), S(16), D(07), F(09), G(0A), H(0B), J(0D), K(0E), L(0F), ;(33), '(34), 00 , Enter(28)*/
    {0x39, 0x04, 0x16, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x33, 0x34, KEY_NONE ,0x28},

    /* Row 3: L-Shift(E1),  00,Z(1D), X(1B), C(06), V(19), B(05), N(11), M(10), ,(36), .(37), /(38), 00, R-Shift(E5) */
    {0xE1, 0x00, 0x1D, 0x1B, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38, KEY_NONE, 0xE5},

    /* Row 4: L-Ctrl(E0), L-Win(E3), L-Alt(E2), Space(2C), R-Alt(E6), Menu(65), R-Ctrl(E4), Fn(00) */
    {0xE0, 0xE3, 0xE2,  KEY_NONE, KEY_NONE, KEY_NONE,0x2C, KEY_NONE, KEY_NONE,KEY_NONE, 0xE6, 0x65, 0xE4,  KEY_FN}
};

static const uint8_t g_fn_key_map[5][14] = {
    /*
       Row0:
       Esc    1     2     3     4     5     6     7     8     9     0     -     =     
       `      F1    F2    F3    F4    F5    F6    F7    F8    F9    F10   F11   F12   
    */
    {0x35, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, KEY_NONE},

    /*1
       Row1:
       Tab Q W E R T Y U I O P [ ] \
           比如 W = ↑
    */
    {KEY_NONE, KEY_NONE, 0x52, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},

    /*
       Row2:
       Caps A S D F G H J K L ; ' none Enter
            A=← S=↓ D=→
    */
    {KEY_NONE, 0x50, 0x51, 0x4F, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},

    /*
       Row3:
       可以做 Home / Insert / End / PgUp / PgDn / Delete
    */
    {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},

    /*
       Row4:
       Fn 自己还是 Fn
    */
    {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_LIGHT, KEY_NONE, KEY_NONE, KEY_FN}
};


void App_init(void)
{
   
    //初始化状态标志位
    report_dirty = false;
    g_led_dirty = false;

    memset(last_key_state, 0, sizeof(last_key_state));
    memset(last_fn_state,0,sizeof(last_fn_state));
	  g_light_mode = LIGHT_MODE_STATIC; // 默认静态
   
}
//按键扫描的任务
void App_adkey_scan_task(void)
{
    lib_hall_sensor_task();

    // 按键联动逻辑
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            // 增加掩码判断，只处理有效的按键
            if (key_mask[r][c] == 0) continue;

            if (keys[r][c].is_pressed != last_key_state[r][c]) {
                last_key_state[r][c] = keys[r][c].is_pressed;
                report_dirty = true;
            }
        }
    }
}



void App_key_press_light_task(void)
{
    static uint8_t last_light_state[ROW_COUNT][COL_COUNT] = {0};

    if (g_light_mode != LIGHT_MODE_KEY_PRESS) {
        return;
    }

    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {

            if (key_mask[r][c] == 0) {
                continue;
            }

            if (keys[r][c].is_pressed != last_light_state[r][c]) {
                last_light_state[r][c] = keys[r][c].is_pressed;

                if (keys[r][c].is_pressed) {
                    lib_ws2812_set_key_color(r, c, 0, 255, 255);
                } else {
                    lib_ws2812_set_key_color(r, c, 0, 0, 0);
                }

                g_led_dirty = true;
            }
        }
    }
}
//灯光模式切换
void App_light_effect_task(void){
	  static LightMode_t last_mode = LIGHT_MODE_MAX;
	  //检测模式是否发生变化
	  uint8_t mode_changed=0;
	if(last_mode!=g_light_mode){
	   last_mode=g_light_mode;
		 mode_changed=1;
	
	}
    switch(g_light_mode){
        case LIGHT_MODE_OFF:
            break;
        case LIGHT_MODE_BREATH:
            ws2812_tick++;
            lib_ws2812_breath_mode(ws2812_tick);
            g_led_dirty = true;
            break;
        case LIGHT_MODE_RAINBOW:
            ws2812_tick++;
            lib_ws2812_rainbow_mode(ws2812_tick);
            g_led_dirty = true;
            break;
        case LIGHT_MODE_KEY_PRESS:
            App_key_press_light_task();
            break;
        case LIGHT_MODE_STATIC:
             // 静态灯只在刚进入该模式时设置一次
            if (mode_changed) {
                lib_ws2812_set_all(100, 100, 100);
                g_led_dirty = true;
            }
            break;
        case LIGHT_MODE_WAVE:
            // TODO: 实现波浪灯效
            break;
        default:
            break;
    }
}
//ws2812显示的任务
void App_display_task(void)
{  
    if (g_led_dirty) {
        // 调用硬件接口刷新数据
        if (lib_ws2812_update() == 0) { // 0 is HAL_OK
            g_led_dirty = false;
        }
    }
}


/////////////////////////////////////////////////////usb相关的代码///////////////////////////////////////////////////////










/* ===================== 内部功能键处理 ===================== */

/*
   Fn + 某键 = 切灯效
   Fn + 某键 = Win 锁
   Fn + 某键 = Mac/Win 模式切换
*/
static void App_handle_internal_key(uint8_t code){
    switch(code){
        case KEY_LIGHT:
            printf("fn internal light: switch mode\r\n");
            // 状态机的切换
            g_light_mode++;
            if(g_light_mode >= LIGHT_MODE_MAX){
                g_light_mode = LIGHT_MODE_OFF;
            }
						ws2812_tick=0; //切换模式清除tick
						lib_ws2812_set_all(0,0,0);
						 g_led_dirty = true;
            break;
        case KEY_WINLOCK:
            printf("fn internal lock\r\n");
            break;
        case KEY_MAC:  // 切换不同的层级
            printf("Fn internal: MAC\r\n");
            break;
        case KEY_WIN:
            printf("Fn internal: WIN\r\n");
            break;
        default:
            break;
    }
}

/**
 * @brief 灯光处理统一入口
 * 包含：内部按键处理、灯效逻辑计算、硬件显示刷新
 */
void App_lighting_process_task(void)
{
    // 1. 处理内部功能键（如切换灯效）
    if (g_pending_internal_key != KEY_NONE) {
        App_handle_internal_key(g_pending_internal_key);
        g_pending_internal_key = KEY_NONE;
    }

    // 2. 执行灯效演算
    App_light_effect_task();

    // 3. 刷新硬件显示
    App_display_task();
}











void App_usb_process_task(void)
{
    /*
       USB 忙碌时不发送。
       注意：USB IN 端点发送完成回调里必须把 hid_state 改回 HID_STATE_IDLE。
    */
	  static uint8_t busy_timeout=0;
    if (hid_state == HID_STATE_BUSY) {
				busy_timeout++;
			  if(busy_timeout>10){
					hid_state=HID_STATE_IDLE;
					busy_timeout = 0;
				
				}else {
            return;
        }
    }

    uint8_t current_report[8] = {0};
    uint8_t key_count = 0;
    uint8_t fn_pressed = 0;

    /*
       第一步：判断 Fn 是否正在按下。
    */
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {

            if (key_mask[r][c] == 0) {
                continue;
            }

            if (keys[r][c].is_pressed && g_key_map[r][c] == KEY_FN) {
                fn_pressed = 1;
            }
        }
    }

    /*
       第二步：根据 Fn 状态生成 HID 报告。
    */
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {

            if (key_mask[r][c] == 0) {
                continue;
            }

            /*
               如果这个键没有按下，跳过。
            */
            if (!keys[r][c].is_pressed) {
                last_fn_state[r][c] = 0;   // 松开后，Fn内部功能键允许下次重新触发
                continue;
            }

            uint8_t code = KEY_NONE;

            /*
               如果 Fn 正在按下：
               优先查 Fn 层 g_fn_key_map。
               如果 Fn 层这个位置没定义，再回退到普通层 g_key_map。
            */
            if (fn_pressed) {
                code = g_fn_key_map[r][c];

                if (code == KEY_NONE) {
                    code = g_key_map[r][c];
                }
            } else {
                code = g_key_map[r][c];
            }

            /*
               KEY_NONE：无效键，不处理
            */
            if (code == KEY_NONE) {
                continue;
            }

            /*
               KEY_FN：Fn 自己不发给电脑
            */
            if (code == KEY_FN) {
                continue;
            }

            /*
               内部功能键：
               KEY_LIGHT、KEY_WINLOCK、KEY_MAC、KEY_WIN
               这些不发给电脑，只在固件内部处理。
            */
            if (code >= 0xF0) {
                if (last_fn_state[r][c] == 0) {
                    g_pending_internal_key = code; // 标记有内部功能键待处理
                    last_fn_state[r][c] = 1;
                }
                continue;
            }

            /*
               修饰键：
               0xE0 ~ 0xE7
               E0 左Ctrl
               E1 左Shift
               E2 左Alt
               E3 左Win
               E4 右Ctrl
               E5 右Shift
               E6 右Alt
               E7 右Win
            */
            if (code >= 0xE0 && code <= 0xE7) {
                current_report[0] |= (uint8_t)(1U << (code - 0xE0));
            }
            /*
               普通键：
               放到 current_report[2] ~ current_report[7]
               最多 6 个普通键。
            */
            else {
                if (key_count < 6) {
                    current_report[2 + key_count] = code;
                    key_count++;
                }
            }
        }
    }

    /*
       last_report 保存上一次发送给电脑的 HID 报告。
       只要当前报告和上次不同，就发送。

       松开所有键时，current_report 会变成全 0，
       这时也会发送全 0 包，电脑才知道按键松开。
    */
    static uint8_t last_report[8] = {0};

    if (memcmp(current_report, last_report, sizeof(current_report)) != 0) {
        if (usbd_ep_start_write(HID_INT_EP, current_report, sizeof(current_report)) == 0) {
            hid_state = HID_STATE_BUSY;
            memcpy(last_report, current_report, sizeof(last_report));
					  report_dirty = false;
        }
    }else{
		   report_dirty = false;
		
		}

  
}






