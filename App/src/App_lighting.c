#include "App_lighting.h"
#include "lib_hall_sensor.h"
#include "lib_ws2812.h"

bool g_led_dirty = false;
LightMode_t g_light_mode = LIGHT_MODE_OFF;
uint32_t ws2812_tick = 0;
uint8_t g_light_r = 30;
uint8_t g_light_g = 180;
uint8_t g_light_b = 255;
uint8_t g_light_brightness = 100;
uint8_t g_light_speed = 10;

void App_led_animation_task(void) {
    static uint8_t speed_prescaler = 0;
    uint8_t target_delay = 11 - (g_light_speed > 10 ? 10 : g_light_speed);
    if (++speed_prescaler < target_delay) {
        return;
    }
    speed_prescaler = 0;

    uint8_t cur_r = (g_light_r * g_light_brightness) / 100;
    uint8_t cur_g = (g_light_g * g_light_brightness) / 100;
    uint8_t cur_b = (g_light_b * g_light_brightness) / 100;

    switch (g_light_mode) {
        case LIGHT_MODE_BREATH:
            lib_ws2812_breath_mode(++ws2812_tick);
            g_led_dirty = true;
            break;
        case LIGHT_MODE_RAINBOW:
            lib_ws2812_rainbow_mode(++ws2812_tick);
            g_led_dirty = true;
            break;
        case LIGHT_MODE_STATIC:
            lib_ws2812_set_all(cur_r, cur_g, cur_b);
            g_led_dirty = true;
            break;
        case LIGHT_MODE_KEY_PRESS:
            for (uint8_t r = 0; r < ROW_COUNT; r++) {
                for (uint8_t c = 0; c < COL_COUNT; c++) {
                    if (key_mask[r][c] == 0) continue;
                    if (keys[r][c].is_pressed)
                        lib_ws2812_set_key_color(r, c, cur_r, cur_g, cur_b);
                    else
                        lib_ws2812_set_key_color(r, c, 0, 0, 0);
                }
            }
            g_led_dirty = true;
            break;
        case LIGHT_MODE_COLLIDE:
            lib_ws2812_collide_ripple_mode(++ws2812_tick);
            g_led_dirty = true;
            break;
        case LIGHT_MODE_DAZZLE_MARQUEE:
            lib_ws2812_dazzle_marquee_mode(++ws2812_tick);
            g_led_dirty = true;
            break;
        case LIGHT_MODE_HALO:
        {
            static uint8_t halo_fade[ROW_COUNT][COL_COUNT] = {0};
            
         
            ws2812_tick++; 

            
            for (uint8_t r = 0; r < ROW_COUNT; r++) {
                for (uint8_t c = 0; c < COL_COUNT; c++) {
                    if (key_mask[r][c] == 0) continue;
                    
                    if (keys[r][c].is_pressed) {
                        
                        for (int dr = -1; dr <= 1; dr++) {
                            for (int dc = -1; dc <= 1; dc++) {
                                int target_r = r + dr;
                                int target_c = c + dc;
                                
                              
                                if (target_r >= 0 && target_r < ROW_COUNT && 
                                    target_c >= 0 && target_c < COL_COUNT) {
                                    if (key_mask[target_r][target_c] != 0) {
                                       
                                        halo_fade[target_r][target_c] = 255;
                                    }
                                }
                            }
                        }
                    }
                }
            }

         
            for (uint8_t r = 0; r < ROW_COUNT; r++) {
                for (uint8_t c = 0; c < COL_COUNT; c++) {
                    if (key_mask[r][c] == 0) continue;

                    if (halo_fade[r][c] > 0) {
                        uint8_t rb_r, rb_g, rb_b;
                        
                       
                        uint16_t hue = (r * 10 + c * 10 + ws2812_tick * 4) % 256;
                        
                       
                        lib_ws2812_hsv_to_rgb(hue, &rb_r, &rb_g, &rb_b);

                       
                        uint8_t r_fade = (rb_r * g_light_brightness / 100 * halo_fade[r][c]) / 255;
                        uint8_t g_fade = (rb_g * g_light_brightness / 100 * halo_fade[r][c]) / 255;
                        uint8_t b_fade = (rb_b * g_light_brightness / 100 * halo_fade[r][c]) / 255;

                        lib_ws2812_set_key_color(r, c, r_fade, g_fade, b_fade);

                       
                        uint8_t decay_speed = 15; 
                        if (halo_fade[r][c] > decay_speed) {
                            halo_fade[r][c] -= decay_speed;
                        } else {
                            halo_fade[r][c] = 0;
                        }
                    } else {

                        lib_ws2812_set_key_color(r, c, 0, 0, 0);
                    }
                }
            }
            g_led_dirty = true;
            break;
        }
       
       
        case LIGHT_MODE_BOUNCE_MARQUEE:  //点击多量
        {
            
            ws2812_tick++;

            uint16_t cycle_step = (ws2812_tick / 2) % 26; 
            
            int head_col;           
            bool is_moving_right; 

            if (cycle_step < 14) {
              
                head_col = cycle_step;
                is_moving_right = true;
            } else {
               
                head_col = 26 - cycle_step;
                is_moving_right = false;
            }

            for (uint8_t r = 0; r < ROW_COUNT; r++) {
                for (uint8_t c = 0; c < COL_COUNT; c++) {
                    if (key_mask[r][c] == 0) continue;

                   
                    int tail_dist;
                    if (is_moving_right) {
                        tail_dist = head_col - c; 
                    } else {
                        tail_dist = c - head_col; 
                    }

                   
                    if (tail_dist >= 0 && tail_dist <= 5) {
                        
                       
                        uint16_t hue = (ws2812_tick * 2 + c * 15) % 256;
                        uint8_t rb_r, rb_g, rb_b;
                        lib_ws2812_hsv_to_rgb(hue, &rb_r, &rb_g, &rb_b);

                
                        uint8_t tail_brightness = 255 - (tail_dist * 50);

                      
                        uint8_t r_fade = (rb_r * g_light_brightness / 100 * tail_brightness) / 255;
                        uint8_t g_fade = (rb_g * g_light_brightness / 100 * tail_brightness) / 255;
                        uint8_t b_fade = (rb_b * g_light_brightness / 100 * tail_brightness) / 255;

                        lib_ws2812_set_key_color(r, c, r_fade, g_fade, b_fade);
                    } else {
                    
                        lib_ws2812_set_key_color(r, c, 0, 0, 0);
                    }
                }
            }
            g_led_dirty = true;
            break;
        }
     
        case LIGHT_MODE_SNAKE_MARQUEE:  //跑马灯
        {
            ws2812_tick++;
            
            const uint8_t TOTAL_STEPS = ROW_COUNT * COL_COUNT; 
            const uint8_t TAIL_LEN = 16;

         
            uint16_t head_pos = (ws2812_tick / 2) % TOTAL_STEPS;

           
            for (uint8_t r = 0; r < ROW_COUNT; r++) {
                for (uint8_t c = 0; c < COL_COUNT; c++) {
                    if (key_mask[r][c] != 0) {
                        lib_ws2812_set_key_color(r, c, 0, 0, 0);
                    }
                }
            }

            
            for (uint8_t i = 0; i < TOTAL_STEPS; i++) {
                
                uint8_t r = i / COL_COUNT; 
                uint8_t c;

               
                if (r % 2 == 0) {
                   
                    c = i % COL_COUNT;
                } else {
                   
                    c = (COL_COUNT - 1) - (i % COL_COUNT);
                }

               
                if (key_mask[r][c] == 0) continue;

              
                int dist = (head_pos - i + TOTAL_STEPS) % TOTAL_STEPS;

               
                if (dist < TAIL_LEN) {
                    
                   
                    uint16_t hue = (ws2812_tick * 4 + i * 12) % 256;
                    uint8_t rb_r, rb_g, rb_b;
                    lib_ws2812_hsv_to_rgb(hue, &rb_r, &rb_g, &rb_b);

                  
                    uint8_t tail_brightness = 255 - (dist * 255 / TAIL_LEN);

                   
                    uint8_t r_fade = (rb_r * g_light_brightness / 100 * tail_brightness) / 255;
                    uint8_t g_fade = (rb_g * g_light_brightness / 100 * tail_brightness) / 255;
                    uint8_t b_fade = (rb_b * g_light_brightness / 100 * tail_brightness) / 255;

                    lib_ws2812_set_key_color(r, c, r_fade, g_fade, b_fade);
                }
            }
            
            g_led_dirty = true;
            break;
        }
        
        // ================================================================
        default:
            break;
    }
}

void App_led_display_task(void) {
    if (g_led_dirty) {
        if (lib_ws2812_update() == 0) g_led_dirty = false;
    }
}

void App_set_light_config(uint8_t mode, uint8_t r, uint8_t g, uint8_t b, uint8_t br, uint8_t speed) {
    if (mode < LIGHT_MODE_MAX) {
        g_light_mode = (LightMode_t)mode;
    }
    g_light_r = r;
    g_light_g = g;
    g_light_b = b;
    g_light_brightness = (br > 100) ? 100 : br;
    g_light_speed = speed;

    ws2812_tick = 0;
    g_led_dirty = true;
}

void App_get_light_config(uint8_t *mode, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *br, uint8_t *speed) {
    *mode  = (uint8_t)g_light_mode;
    *r     = g_light_r;
    *g     = g_light_g;
    *b     = g_light_b;
    *br    = g_light_brightness;
    *speed = g_light_speed;
}
