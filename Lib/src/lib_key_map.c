/*
 * lib_key_map.c - 61键键盘映射表
 * 
 * 功能：
 * - 将 (行,列) 坐标转换为 HID 键码
 * - 支持修饰键识别
 */

#include "lib_key_map.h"
#include "lib_hall_sensor.h"

// ==========================================================
//  修饰键映射表
//  标记每个位置是否是修饰键 (0=普通键, 1=修饰键)
// ==========================================================
const uint8_t key_modifier_map[MATRIX_ROWS_COUNT][ADC_CHANNELS_COUNT] = {
    // Row 0 - 无修饰键
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // Row 1 - 无修饰键
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // Row 2 - 无修饰键
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // Row 3 - LShift(0,0), RShift(0,13)
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    // Row 4 - LCtrl(1,0), LWin(1,1), LAlt(1,2), RAlt(1,10), RWin(1,11), Menu(1,12)
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}
};

// ==========================================================
//  61键 HID 键码映射表
//  根据用户提供的布局配置
// ==========================================================
const uint8_t key_map[MATRIX_ROWS_COUNT][ADC_CHANNELS_COUNT] = {
    // ROW0: ESC, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
    {0x29, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x2A},
    // ROW1: Tab, Q, W, E, R, T, Y, U, I, O, P, [, ], \
    {0x2B, 0x14, 0x1A, 0x08, 0x15, 0x17, 0x1C, 0x18, 0x0C, 0x12, 0x13, 0x2F, 0x30, 0x31},
    // ROW2: Caps, A, S, D, F, G, H, J, K, L, ;, ', (空), Enter
    {0x39, 0x04, 0x16, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x33, 0x34, 0x00, 0x28},
    // ROW3: LShift, (空), Z, X, C, V, B, N, M, ,, ., /, (空), RShift
    {0xE1, 0x00, 0x1D, 0x1B, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38, 0x00, 0xE5},
    // ROW4: LCtrl, LWin, LAlt, (空), (空), (空), Space, (空), (空), (空), RAlt, RWin, Menu, Fn
    {0xE0, 0xE3, 0xE2, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0xE6, 0xE7, 0x65, 0xFF}
};

// ==========================================================
//  函数实现
// ==========================================================

/**
 * @brief  获取指定位置的 HID 键码
 * @param  row: 行索引 (0-4)
 * @param  col: 列索引 (0-13)
 * @return HID 键码，无效返回 HID_KEY_NONE
 */
uint8_t lib_key_get_code(uint8_t row, uint8_t col)
{
    if (row >= MATRIX_ROWS_COUNT || col >= ADC_CHANNELS_COUNT) {
        return HID_KEY_NONE;
    }
    if (!lib_hall_is_key_valid(row, col)) {
        return HID_KEY_NONE;
    }
    return key_map[row][col];
}

/**
 * @brief  检查指定位置是否是修饰键
 * @param  row: 行索引 (0-4)
 * @param  col: 列索引 (0-13)
 * @return true-是修饰键, false-不是
 */
bool lib_key_is_modifier(uint8_t row, uint8_t col)
{
    if (row >= MATRIX_ROWS_COUNT || col >= ADC_CHANNELS_COUNT) {
        return false;
    }
    if (!lib_hall_is_key_valid(row, col)) {
        return false;
    }
    return key_modifier_map[row][col] != 0;
}

/**
 * @brief  获取修饰键的掩码
 * @param  row: 行索引 (0-4)
 * @param  col: 列索引 (0-13)
 * @return 修饰键掩码 (HID_MOD_xxx)，不是修饰键返回 0
 */
uint8_t lib_key_get_modifier_mask(uint8_t row, uint8_t col)
{
    if (!lib_key_is_modifier(row, col)) {
        return 0;
    }
    uint8_t code = key_map[row][col];
    switch (code) {
        case 0xE0: return HID_MOD_LEFT_CTRL;
        case 0xE1: return HID_MOD_LEFT_SHIFT;
        case 0xE2: return HID_MOD_LEFT_ALT;
        case 0xE3: return HID_MOD_LEFT_GUI;
        case 0xE4: return HID_MOD_RIGHT_CTRL;
        case 0xE5: return HID_MOD_RIGHT_SHIFT;
        case 0xE6: return HID_MOD_RIGHT_ALT;
        case 0xE7: return HID_MOD_RIGHT_GUI;
        default: return 0;
    }
}
