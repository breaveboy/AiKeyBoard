#ifndef __APP_LIGHTING_H__
#define __APP_LIGHTING_H__

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    LIGHT_MODE_OFF = 0, 
    LIGHT_MODE_BREATH, //呼吸
    LIGHT_MODE_RAINBOW, //炫彩
    LIGHT_MODE_KEY_PRESS, //按下点亮
    LIGHT_MODE_STATIC,  //常量
    LIGHT_MODE_COLLIDE, //对角碰撞
    LIGHT_MODE_DAZZLE_MARQUEE, //流水
    LIGHT_MODE_HALO,         // <--- 新增：十字交叉模式
    LIGHT_MODE_BOUNCE_MARQUEE, // <--- 新增：左右折返彩虹跑马灯
    LIGHT_MODE_SNAKE_MARQUEE,  // <--- 新增：S形贪吃蛇彩虹流水
    LIGHT_MODE_MAX
} LightMode_t;

extern bool g_led_dirty;
extern LightMode_t g_light_mode;
extern uint32_t ws2812_tick;
extern uint8_t g_light_r;
extern uint8_t g_light_g;
extern uint8_t g_light_b;
extern uint8_t g_light_brightness;
extern uint8_t g_light_speed;

void App_led_animation_task(void);
void App_led_display_task(void);
void App_set_light_config(uint8_t mode, uint8_t r, uint8_t g, uint8_t b, uint8_t br, uint8_t speed);
void App_get_light_config(uint8_t *mode, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *br, uint8_t *speed);

#endif
