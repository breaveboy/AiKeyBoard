#ifndef __APP_LIGHTING_H__
#define __APP_LIGHTING_H__

#include <stdint.h>
#include <stdbool.h>


typedef enum {
    LIGHT_MODE_OFF = 0,        // 0: 关闭
    LIGHT_MODE_STATIC,         // 1: 常亮 (移到了最前面)
    LIGHT_MODE_BREATH,         // 2: 呼吸 (单色动画)
    LIGHT_MODE_KEY_PRESS,      // 3: 按下点亮 (单色触发)
    LIGHT_MODE_RAINBOW,        // 4: 彩虹炫彩 (多色开始)
    LIGHT_MODE_COLLIDE,        // 5: 对角碰撞
    LIGHT_MODE_DAZZLE_MARQUEE, // 6: 流水
    LIGHT_MODE_HALO,           // 7: 十字交叉
    LIGHT_MODE_BOUNCE_MARQUEE, // 8: 左右折返
    LIGHT_MODE_SNAKE_MARQUEE,  // 9: S形贪吃蛇
    LIGHT_MODE_CYBER_SNAKE,    // 10：赛博贪吃蛇
    LIGHT_MODE_MUSIC,          // 11: PC音乐律动推流模式
    LIGHT_MODE_MAX             // 模式总数计算位
} LightMode_t;


// 定义坐标结构体，贪吃蛇的左边
typedef struct {
    uint8_t r;
    uint8_t c;
} Pos_t;

//////灯光的全局变量///////////
extern bool g_led_dirty;
extern LightMode_t g_light_mode;
extern uint32_t ws2812_tick;
extern uint8_t g_light_r;
extern uint8_t g_light_g;
extern uint8_t g_light_b;
extern uint8_t g_light_brightness;
extern uint8_t g_light_speed;
////////音乐律动外部时间戳与模式备份变量//////////
extern uint32_t g_last_music_rx_time;
extern LightMode_t g_backup_light_mode;


///////////灯光引擎函数接口///////////////////////
void App_led_animation_task(void);
void App_led_display_task(void);
void App_set_light_config(uint8_t mode, uint8_t r, uint8_t g, uint8_t b, uint8_t br, uint8_t speed);
void App_get_light_config(uint8_t *mode, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *br, uint8_t *speed);

#endif
