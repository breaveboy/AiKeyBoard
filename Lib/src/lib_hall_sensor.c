#include "lib_hall_sensor.h"

// 静态私有变量
static hall_config_t hall_keys[MATRIX_ROWS_COUNT][ADC_CHANNELS_COUNT];
static key_data_t   key_state[MATRIX_ROWS_COUNT][ADC_CHANNELS_COUNT];
//定义键盘的矩阵排布
static void _hall_map_init(void) {
    for (uint8_t r = 0; r < MATRIX_ROWS_COUNT; r++) {
        for (uint8_t c = 0; c < ADC_CHANNELS_COUNT; c++) {
            bool valid = true;
            
            // 第一二行 (row 0, 1): 全满，默认有效
            // 第三行 (row 2): 缺 12 (只有0-11, 13)
            if (r == 2 && c == 12) valid = false;
            // 第四行 (row 3): 缺 1, 12 (只有0, 2-11, 13)
            if (r == 3 && (c == 1 || c == 12)) valid = false;
            // 第五行 (row 4): 不需要 3, 4, 5, 7, 8, 9
            if (r == 4 && (c == 3 || c == 4 || c == 5 || c == 7 || c == 8 || c == 9)) {
                valid = false;
            }
            
            hall_keys[r][c].is_valid = valid;
            
            // 默认校准参数初始化
            hall_keys[r][c].min_adc = HALL_CALIB_DEFAULT_MIN;
            hall_keys[r][c].max_adc = HALL_CALIB_DEFAULT_MAX;
            hall_keys[r][c].range   = HALL_CALIB_DEFAULT_MAX - HALL_CALIB_DEFAULT_MIN;
            
            // 按键状态初始化
            key_state[r][c].state = KEY_STATE_RELEASED;
            key_state[r][c].debounce_cnt = 0;
            key_state[r][c].last_depth = 0;
            key_state[r][c].was_pressed = false;
        }
    }
}

void lib_hall_init(void) {
    _hall_map_init();
}

bool lib_hall_is_key_valid(uint8_t row, uint8_t col) {
    if (row >= MATRIX_ROWS_COUNT || col >= ADC_CHANNELS_COUNT) return false;
    return hall_keys[row][col].is_valid;
}

uint16_t lib_hall_get_depth(uint8_t row, uint8_t col) {
    if (!lib_hall_is_key_valid(row, col)) return 0;
    uint32_t raw_adc = g_adc_raw_matrix[row][col];
    hall_config_t *cfg = &hall_keys[row][col];
	  //判断adc的采集按键的数值是不是在范围内
    if (raw_adc <= cfg->min_adc) return 0;
    if (raw_adc >= cfg->max_adc) return HALL_DEPTH_MAX;
    return (uint16_t)((raw_adc - cfg->min_adc) * HALL_DEPTH_MAX / cfg->range);
}

void lib_hall_scan_all(void) {
    for (uint8_t r = 0; r < MATRIX_ROWS_COUNT; r++) {
        for (uint8_t c = 0; c < ADC_CHANNELS_COUNT; c++) {
					  //无效按键退出
            if (!lib_hall_is_key_valid(r, c)) continue;
            //获取按键的深度
            uint16_t depth = lib_hall_get_depth(r, c); //计算当前的深度
            key_data_t *k = &key_state[r][c];
					  // 根据深度判定当前是否有“按下趋势”或“抬起趋势”
            bool is_pressed_now = (depth >= HALL_THRESHOLD_PRESS);
            bool is_released_now = (depth <= HALL_THRESHOLD_RELEASE);
            // 记录上一时刻的状态，用于后面判断“刚刚按下”的一瞬间
            k->was_pressed = (k->state == KEY_STATE_PRESSED);

            switch (k->state) {
                case KEY_STATE_RELEASED:
									  
                    if (is_pressed_now) {
                        k->state = KEY_STATE_DEBOUNCE_PRESS;
                        k->debounce_cnt = 0;
                    }
                    break;

                case KEY_STATE_DEBOUNCE_PRESS:  //（按下）
                    if (is_pressed_now) {
                        k->debounce_cnt++;
                        if (k->debounce_cnt >= HALL_DEBOUNCE_CNT) {
                            k->state = KEY_STATE_PRESSED;
                        }
                    } else {
                        k->state = KEY_STATE_RELEASED;
                    }
                    break;

                case KEY_STATE_PRESSED:  //状态：已按下
                    if (is_released_now) {
                        k->state = KEY_STATE_DEBOUNCE_RELEASE;
                        k->debounce_cnt = 0;
                    }
                    break;

                case KEY_STATE_DEBOUNCE_RELEASE:
                    if (is_released_now) {
                        k->debounce_cnt++;
                        if (k->debounce_cnt >= HALL_DEBOUNCE_CNT) {
                            k->state = KEY_STATE_RELEASED;
                        }
                    } else {
                        k->state = KEY_STATE_PRESSED;
                    }
                    break;
            }
            k->last_depth = depth;
        }
    }
}

bool lib_hall_is_pressed(uint8_t row, uint8_t col) {
    if (!lib_hall_is_key_valid(row, col)) return false;
    return (key_state[row][col].state == KEY_STATE_PRESSED);
}


bool lib_hall_just_pressed(uint8_t row, uint8_t col) {
    if (!lib_hall_is_key_valid(row, col)) return false;
    key_data_t *k = &key_state[row][col];
    return (k->state == KEY_STATE_PRESSED) && (!k->was_pressed);
}

bool lib_hall_just_released(uint8_t row, uint8_t col) {
    if (!lib_hall_is_key_valid(row, col)) return false;
    key_data_t *k = &key_state[row][col];
    return (k->state == KEY_STATE_RELEASED) && (k->was_pressed);
}
