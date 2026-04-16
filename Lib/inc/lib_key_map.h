#ifndef __LIB_KEY_MAP_H__
#define __LIB_KEY_MAP_H__

#include "py32f4xx_hal.h"
#include "stdbool.h"
#include "bsp_board.h"
#include <stdint.h>

// ==========================================================
//  HID 键盘键码定义
//  参考：USB HID Usage Tables 1.12
// ==========================================================
// 修饰键 (Modifier Keys) - Byte 0
#define HID_MOD_LEFT_CTRL     (1 << 0)
#define HID_MOD_LEFT_SHIFT    (1 << 1)
#define HID_MOD_LEFT_ALT      (1 << 2)
#define HID_MOD_LEFT_GUI      (1 << 3)
#define HID_MOD_RIGHT_CTRL    (1 << 4)
#define HID_MOD_RIGHT_SHIFT   (1 << 5)
#define HID_MOD_RIGHT_ALT     (1 << 6)
#define HID_MOD_RIGHT_GUI     (1 << 7)

// 普通键码 (Keycodes) - Byte 2-7
#define HID_KEY_NONE           0x00
#define HID_KEY_A              0x04
#define HID_KEY_B              0x05
#define HID_KEY_C              0x06
#define HID_KEY_D              0x07
#define HID_KEY_E              0x08
#define HID_KEY_F              0x09
#define HID_KEY_G              0x0A
#define HID_KEY_H              0x0B
#define HID_KEY_I              0x0C
#define HID_KEY_J              0x0D
#define HID_KEY_K              0x0E
#define HID_KEY_L              0x0F
#define HID_KEY_M              0x10
#define HID_KEY_N              0x11
#define HID_KEY_O              0x12
#define HID_KEY_P              0x13
#define HID_KEY_Q              0x14
#define HID_KEY_R              0x15
#define HID_KEY_S              0x16
#define HID_KEY_T              0x17
#define HID_KEY_U              0x18
#define HID_KEY_V              0x19
#define HID_KEY_W              0x1A
#define HID_KEY_X              0x1B
#define HID_KEY_Y              0x1C
#define HID_KEY_Z              0x1D

#define HID_KEY_1              0x1E
#define HID_KEY_2              0x1F
#define HID_KEY_3              0x20
#define HID_KEY_4              0x21
#define HID_KEY_5              0x22
#define HID_KEY_6              0x23
#define HID_KEY_7              0x24
#define HID_KEY_8              0x25
#define HID_KEY_9              0x26
#define HID_KEY_0              0x27

#define HID_KEY_ENTER          0x28
#define HID_KEY_ESCAPE         0x29
#define HID_KEY_BACKSPACE      0x2A
#define HID_KEY_TAB            0x2B
#define HID_KEY_SPACE          0x2C

#define HID_KEY_MINUS          0x2D
#define HID_KEY_EQUAL          0x2E
#define HID_KEY_LEFT_BRACKET   0x2F
#define HID_KEY_RIGHT_BRACKET  0x30
#define HID_KEY_BACKSLASH      0x31
#define HID_KEY_NONUS_HASH     0x32
#define HID_KEY_SEMICOLON      0x33
#define HID_KEY_APOSTROPHE     0x34
#define HID_KEY_GRAVE          0x35
#define HID_KEY_COMMA          0x36
#define HID_KEY_DOT            0x37
#define HID_KEY_SLASH          0x38
#define HID_KEY_CAPS_LOCK      0x39

#define HID_KEY_F1             0x3A
#define HID_KEY_F2             0x3B
#define HID_KEY_F3             0x3C
#define HID_KEY_F4             0x3D
#define HID_KEY_F5             0x3E
#define HID_KEY_F6             0x3F
#define HID_KEY_F7             0x40
#define HID_KEY_F8             0x41
#define HID_KEY_F9             0x42
#define HID_KEY_F10            0x43
#define HID_KEY_F11            0x44
#define HID_KEY_F12            0x45

#define HID_KEY_PRINT_SCREEN   0x46
#define HID_KEY_SCROLL_LOCK    0x47
#define HID_KEY_PAUSE          0x48
#define HID_KEY_INSERT         0x49
#define HID_KEY_HOME           0x4A
#define HID_KEY_PAGE_UP        0x4B
#define HID_KEY_DELETE         0x4C
#define HID_KEY_END            0x4D
#define HID_KEY_PAGE_DOWN      0x4E

#define HID_KEY_RIGHT          0x4F
#define HID_KEY_LEFT           0x50
#define HID_KEY_DOWN           0x51
#define HID_KEY_UP             0x52

#define HID_KEY_NUM_LOCK       0x53
#define HID_KEY_KP_DIVIDE      0x54
#define HID_KEY_KP_MULTIPLY    0x55
#define HID_KEY_KP_SUBTRACT    0x56
#define HID_KEY_KP_ADD         0x57
#define HID_KEY_KP_ENTER       0x58
#define HID_KEY_KP_1           0x59
#define HID_KEY_KP_2           0x5A
#define HID_KEY_KP_3           0x5B
#define HID_KEY_KP_4           0x5C
#define HID_KEY_KP_5           0x5D
#define HID_KEY_KP_6           0x5E
#define HID_KEY_KP_7           0x5F
#define HID_KEY_KP_8           0x60
#define HID_KEY_KP_9           0x61
#define HID_KEY_KP_0           0x62
#define HID_KEY_KP_DOT         0x63

#define HID_KEY_NONUS_BACKSLASH 0x64
#define HID_KEY_APPLICATION    0x65
#define HID_KEY_POWER          0x66
#define HID_KEY_KP_EQUAL       0x67

// ==========================================================
//  5x14 按键矩阵到 HID 键码的映射表
//  用户在此处根据实际键盘布局修改
// ==========================================================

// 修饰键映射表 (用于判断某个键是否是修饰键)
extern const uint8_t key_modifier_map[MATRIX_ROWS_COUNT][ADC_CHANNELS_COUNT];

// 普通键映射表
extern const uint8_t key_map[MATRIX_ROWS_COUNT][ADC_CHANNELS_COUNT];

// ==========================================================
//  函数声明
// ==========================================================

/**
 * @brief  获取指定位置的 HID 键码
 * @param  row: 行索引 (0-4)
 * @param  col: 列索引 (0-13)
 * @return HID 键码，无按键返回 HID_KEY_NONE
 */
uint8_t lib_key_get_code(uint8_t row, uint8_t col);

/**
 * @brief  检查指定位置是否是修饰键
 * @param  row: 行索引 (0-4)
 * @param  col: 列索引 (0-13)
 * @return true-是修饰键, false-不是
 */
bool lib_key_is_modifier(uint8_t row, uint8_t col);

/**
 * @brief  获取修饰键的掩码
 * @param  row: 行索引 (0-4)
 * @param  col: 列索引 (0-13)
 * @return 修饰键掩码 (HID_MOD_xxx)，不是修饰键返回 0
 */
uint8_t lib_key_get_modifier_mask(uint8_t row, uint8_t col);

#endif
