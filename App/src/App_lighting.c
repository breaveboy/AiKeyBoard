#include "App_lighting.h"
#include "lib_hall_sensor.h"
#include "lib_ws2812.h"
#include <stdlib.h>  // 包含 abs 函数
bool g_led_dirty = false;
LightMode_t g_light_mode = LIGHT_MODE_OFF;
uint32_t ws2812_tick = 0; //原来的ws2812的计数器值
uint8_t g_light_r = 30;
uint8_t g_light_g = 180;
uint8_t g_light_b = 255;
uint8_t g_light_brightness = 100;
uint8_t g_light_speed = 10;
// 高精度的内部累加器
static uint32_t internal_tick_acc = 0;
extern volatile bool g_caps_lock_active; //大小锁


#include <string.h>


#define SNAKE_MAX_LEN 18

// 寻路 BFS 算法：找到从起点到终点的第一步方向
// 返回值：0-无路, 1-上, 2-下, 3-左, 4-右
static uint8_t snake_ai_get_direction(Pos_t start, Pos_t target, Pos_t *snake, uint8_t len) {
    int8_t parent[70]; // 5*14
    uint8_t queue[70];
    uint8_t head = 0, tail = 0;
    uint8_t s_idx = start.r * 14 + start.c;
    uint8_t t_idx = target.r * 14 + target.c;
    const int8_t dr[] = {-1, 1, 0, 0};
    const int8_t dc[] = {0, 0, -1, 1};
    uint8_t i;

    memset(parent, -1, sizeof(parent));
    queue[tail++] = s_idx;
    parent[s_idx] = s_idx;

    while (head < tail) {
        uint8_t curr = queue[head++];
        uint8_t r = curr / 14;
        uint8_t c = curr % 14;

        if (curr == t_idx) {
            uint8_t p = t_idx;
            while (parent[p] != s_idx) p = parent[p];
            if (p == s_idx - 14) return 1;
            if (p == s_idx + 14) return 2;
            if (p == s_idx - 1)  return 3;
            if (p == s_idx + 1)  return 4;
        }

        for (i = 0; i < 4; i++) {
            int8_t nr = r + dr[i];
            int8_t nc = c + dc[i];
            uint8_t n_idx = nr * 14 + nc;

            if (nr >= 0 && nr < 5 && nc >= 0 && nc < 14 && key_mask[nr][nc] != 0) {
                if (parent[n_idx] == -1) {
                    // 检查是否撞到自己（除掉尾巴，因为尾巴会移动）
                    bool is_body = false;
                    uint8_t j;
                    for (j = 0; j < len - 1; j++) {
                        if (snake[j].r == nr && snake[j].c == nc) { is_body = true; break; }
                    }
                    if (!is_body || n_idx == t_idx) {
                        parent[n_idx] = curr;
                        queue[tail++] = n_idx;
                    }
                }
            }
        }
    }
    return 0; // 没找到路
}





void App_led_animation_task(void) {
    static uint8_t speed_prescaler = 0;

    if (bsp_spi_dma_is_busy()) {
        return;
    }
   

    // --- 第二部分：背景动画限速器 ---
    uint8_t target_delay = 11 - (g_light_speed > 10 ? 10 : g_light_speed);
    if (++speed_prescaler < target_delay) {
        return;
    }
    speed_prescaler = 0;
    
    
    
    // --- 第三部分：背景动画 ---
    uint8_t cur_r = (g_light_r * g_light_brightness) / 100;
    uint8_t cur_g = (g_light_g * g_light_brightness) / 100;
    uint8_t cur_b = (g_light_b * g_light_brightness) / 100;
    
    
//    uint8_t speed_idx=g_light_speed;
//    if(speed_idx<1) speed_idx=1;
//    if(speed_idx>5) speed_idx=5;
//    //每帧固定执行
//    internal_tick_acc+=SPEED_STEP_MAP[speed_idx-1];
//    //将内部累加器/10给业务的tick
//    // 3. 将内部高精度累加器，除以 10 转换给业务使用的 tick
//    ws2812_tick = internal_tick_acc / 10;
//    uint8_t cur_r = (g_light_r * g_light_brightness) / 100;
//    uint8_t cur_g = (g_light_g * g_light_brightness) / 100;
//    uint8_t cur_b = (g_light_b * g_light_brightness) / 100;

   

    switch (g_light_mode) {
        case LIGHT_MODE_OFF:
            lib_ws2812_set_all(0, 0, 0);
            g_led_dirty = true;
            break;
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
       
       
        case LIGHT_MODE_BOUNCE_MARQUEE:  //???????
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
     
        case LIGHT_MODE_SNAKE_MARQUEE:  //??????
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
       
       case LIGHT_MODE_CYBER_SNAKE:
        {
            static Pos_t snake[SNAKE_MAX_LEN];
            static uint8_t snake_len = 4;
            static Pos_t food = {2, 7};
            static bool needs_init = true;
            static uint16_t snake_logic_gate = 0; 
            
            // --- 新增：用于存储“下一跳”位置的变量，实现平滑预测 ---
            static Pos_t next_head_pos; 

            uint8_t i, dir;
            ws2812_tick++; 

            if (needs_init) {
                snake_len = 4;
                for (i = 0; i < snake_len; i++) {
                    snake[i].r = 0; snake[i].c = snake_len - 1 - i;
                }
                food.r = 3; food.c = 10;
                needs_init = false;
                snake_logic_gate = 0;
                // 初始化预测位置
                next_head_pos = snake[0]; 
            }

            // 1. 计算当前的插值比例 (0 ~ 255)
            // 当 gate 为 0 时，比例为 0；当 gate 接近 7 时，比例接近 255
            uint16_t fraction = (snake_logic_gate * 255) / 7;

            if (++snake_logic_gate >= 7) { 
                snake_logic_gate = 0;

                // 物理位移逻辑 (保持不变)
                dir = snake_ai_get_direction(snake[0], food, snake, snake_len);
                if (dir == 0) { /* 挣扎逻辑... */ }

                Pos_t real_next_head = snake[0];
                if (dir == 1) real_next_head.r--;
                else if (dir == 2) real_next_head.r++;
                else if (dir == 3) real_next_head.c--;
                else if (dir == 4) real_next_head.c++;
                else { needs_init = true; }

                if (!needs_init) {
                    if (key_mask[real_next_head.r][real_next_head.c] == 0) { needs_init = true; }
                    else {
                        for (i = 0; i < snake_len - 1; i++) {
                            if (real_next_head.r == snake[i].r && real_next_head.c == snake[i].c) { needs_init = true; break; }
                        }
                    }
                }

                if (!needs_init) {
                    if (real_next_head.r == food.r && real_next_head.c == food.c) {
                        if (snake_len < SNAKE_MAX_LEN) snake_len++;
                        // 生成新食物
                        uint32_t seed = ws2812_tick + g_hall_adc_frame[0][0];
                        for (i = 0; i < 70; i++) {
                            uint8_t tr = (seed + i * 3) % 5;
                            uint8_t tc = (seed + i * 7) % 14;
                            if (key_mask[tr][tc] != 0) { food.r = tr; food.c = tc; break; }
                        }
                    }
                    for (i = snake_len - 1; i > 0; i--) { snake[i] = snake[i - 1]; }
                    snake[0] = real_next_head;
                }
                
                // 物理位移完成后，立即计算“下一跳”用于渲染预览
                dir = snake_ai_get_direction(snake[0], food, snake, snake_len);
                next_head_pos = snake[0];
                if (dir == 1) next_head_pos.r--;
                else if (dir == 2) next_head_pos.r++;
                else if (dir == 3) next_head_pos.c--;
                else if (dir == 4) next_head_pos.c++;
            }

            // --- 2. 滑丝渲染逻辑 ---
            lib_ws2812_set_all(0, 0, 0);

            // A. 渲染食物 (呼吸灯)
            uint8_t food_val = 160 + (abs((int)(ws2812_tick % 40) - 20) * 4);
            lib_ws2812_set_key_color(food.r, food.c, (food_val * g_light_brightness / 100), 0, 0);

            // B. 渲染蛇身 (常规部分，第1节到倒数第2节)
            for (i = 1; i < snake_len - 1; i++) {
                uint8_t fade = 255 - (i * (180 / snake_len));
                lib_ws2812_set_key_color(snake[i].r, snake[i].c, 
                    (80 * fade / 255) * g_light_brightness / 100, 0, (255 * fade / 255) * g_light_brightness / 100);
            }

            // C. 蛇尾滑丝：最后一节逐渐变暗
            {
                uint8_t last_idx = snake_len - 1;
                uint8_t tail_fade = (255 - (last_idx * (180 / snake_len))) * (255 - fraction) / 255;
                lib_ws2812_set_key_color(snake[last_idx].r, snake[last_idx].c, 
                    (80 * tail_fade / 255) * g_light_brightness / 100, 0, (255 * tail_fade / 255) * g_light_brightness / 100);
            }

            // D. 蛇头滑丝：当前头保持亮，目标头逐渐变亮
            // 当前头
            lib_ws2812_set_key_color(snake[0].r, snake[0].c, 0, (255 * g_light_brightness / 100), (255 * g_light_brightness / 100));
            // 目标头 (渐入)
            if (!(next_head_pos.r == snake[0].r && next_head_pos.c == snake[0].c)) {
                uint8_t head_in = (fraction * 255) / 255; // 0 -> 255
                lib_ws2812_set_key_color(next_head_pos.r, next_head_pos.c, 0, 
                    (head_in * g_light_brightness / 100), (head_in * g_light_brightness / 100));
            }

            g_led_dirty = true;
            break;
        }
        
        
        default:
            break;
    }


    // ========== 【新增代码：最后一步强行覆盖 CapsLock 灯】 ==========
    if(g_caps_lock_active){
        lib_ws2812_set_pixel(28, 255, 200, 200);
        //lib_ws2812_set_key_color(2, 0, 255, 255, 255);
         g_led_dirty = true; // 强制触发硬件刷新
    
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
