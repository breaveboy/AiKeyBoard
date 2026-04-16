#include "bsp_gpio.h"

// 行端口映射表
static const GPIO_TypeDef* row_ports[MATRIX_ROWS_COUNT] = {
    ROW1_PORT, ROW2_PORT, ROW3_PORT, ROW4_PORT, ROW5_PORT
};

// 行引脚映射表
static const uint16_t row_pins[MATRIX_ROWS_COUNT] = {
    ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN, ROW5_PIN
};

void bsp_key_matrix_row_init(void)
{
    GPIO_InitTypeDef GPIO_Init = {0};

    // 使能行控制引脚所在端口的时钟
    RCC_ROW_PORT_CLK_ENABLE();

    // 配置为推挽输出模式
    GPIO_Init.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull  = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_Init.Pin   = ROW_ALL_PINS;
    HAL_GPIO_Init((GPIO_TypeDef*)ROW_ALL_PORT, &GPIO_Init);

    // 初始状态：所有行拉高（关闭）
    bsp_key_matrix_row_all_set(GPIO_PIN_SET);
}

void bsp_key_matrix_row_set(uint8_t row_idx, GPIO_PinState state)
{
    // 检查行索引是否有效
    if (row_idx < MATRIX_ROWS_COUNT) {
        HAL_GPIO_WritePin((GPIO_TypeDef*)row_ports[row_idx], row_pins[row_idx], state);
    }
}

void bsp_key_matrix_row_all_set(GPIO_PinState state)
{
    // 批量设置所有行的电平
    HAL_GPIO_WritePin((GPIO_TypeDef*)ROW_ALL_PORT, ROW_ALL_PINS, state);
}

void bsp_key_matrix_row_select(uint8_t row_idx)
{
    // 先把所有行拉高
    bsp_key_matrix_row_all_set(GPIO_PIN_SET);
    // 再拉低选中的行
    if (row_idx < MATRIX_ROWS_COUNT) {
        bsp_key_matrix_row_set(row_idx, GPIO_PIN_RESET);
    }
}

void bsp_led_en_init(void)
{
    GPIO_InitTypeDef GPIO_Init = {0};

    // 使能 GPIOB 时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // 配置 LED_EN 引脚为推挽输出
    GPIO_Init.Pin = LED_EN_PIN;
    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LED_EN_PORT, &GPIO_Init);

    // 初始状态：拉低（关闭 LED）
    bsp_led_en_set(GPIO_PIN_RESET);
}

void bsp_led_en_set(GPIO_PinState state)
{
    // 设置 LED 使能引脚电平
    HAL_GPIO_WritePin(LED_EN_PORT, LED_EN_PIN, state);
}