#include "lib_ws2812.h"
#include "bsp_gpio.h"
#include <string.h>
#include <stdlib.h>

#define INVALID_INDEX  0xFFU
//dma搬运的数组值
  uint8_t g_ws2812_tx_buffer[WS2812_TX_BUFFER_SIZE];
  ws2812_color_t g_ws2812_colors[WS2812_LED_NUM];
static const uint8_t g_key_to_led_map[MATRIX_ROWS_COUNT][ADC_CHANNELS_COUNT]={
	   // 第一行
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13},
     // 第二行：最左是 27，最右是 14
    {27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14},
    {28,29,30,31,32,33,34,35,36,37,38,39,INVALID_INDEX,40},
     // 第四行：最左是 52，接下来是无效位... 最右是 41
    {52, INVALID_INDEX, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, INVALID_INDEX, 41},
		// 第五行
    {53,54,55,INVALID_INDEX,INVALID_INDEX,INVALID_INDEX,56,INVALID_INDEX,INVALID_INDEX,INVALID_INDEX,57,58,59,60}
};  

//字节转化为spi的字节高字节先发送 dma从低字节进行搬运
static void ws2812_encode_byte(uint8_t value, uint8_t *dst)
{
    for (uint8_t bit = 0; bit < 8U; bit++) {
        dst[bit] = ((value & (0x80U >> bit)) != 0U) ? WS_BIT_1 : WS_BIT_0;
    }
}

//设置index位置的spi值
static void ws2812_encode_pixel(uint16_t led_index)
{
    uint16_t offset = led_index * WS2812_BITS_PER_LED;
	  //获取index值的颜色值
    ws2812_color_t *color = &g_ws2812_colors[led_index];
	//color转为spi的数值存起来
    ws2812_encode_byte(color->g, &g_ws2812_tx_buffer[offset + 0U]);
    ws2812_encode_byte(color->r, &g_ws2812_tx_buffer[offset + 8U]);
    ws2812_encode_byte(color->b, &g_ws2812_tx_buffer[offset + 16U]);
}




void lib_ws2812_init(void)
{   
    bsp_spi_dma_init();

	  ///清空数值
    memset(g_ws2812_tx_buffer, 0, sizeof(g_ws2812_tx_buffer));
    memset(g_ws2812_colors, 0, sizeof(g_ws2812_colors));

    for (uint16_t i = 0; i < WS2812_LED_NUM; i++) {
        ws2812_encode_pixel(i);
    }

    bsp_led_en_set(GPIO_PIN_SET);
}
//ws2812的颜色值
bool lib_ws2812_set_pixel(uint16_t led_index, uint8_t r, uint8_t g, uint8_t b)
{
    if (led_index >= WS2812_LED_NUM) {
        return false;
    }
		//rgb进行存储
    g_ws2812_colors[led_index].r = r;
    g_ws2812_colors[led_index].g = g;
    g_ws2812_colors[led_index].b = b;
		//存入spi数组中
    ws2812_encode_pixel(led_index);
    return true;
}
//设置按键的颜色值
bool lib_ws2812_set_key_color(uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b)
{   
	  //判断范围
    if ((row >= MATRIX_ROWS_COUNT) || (col >= ADC_CHANNELS_COUNT)) {
        return false;
    }

    if (g_key_to_led_map[row][col] == INVALID_INDEX) {
        return false;
    }
    
    return lib_ws2812_set_pixel(g_key_to_led_map[row][col], r, g, b);
}
void lib_ws2812_set_all(uint8_t r, uint8_t g, uint8_t b)
{
    for (uint16_t i = 0; i < WS2812_LED_NUM; i++) {
        (void)lib_ws2812_set_pixel(i, r, g, b);
    }
}












//进行数据搬运
uint8_t lib_ws2812_update(void)
{
    return (uint8_t)bsp_spi_dma_send(g_ws2812_tx_buffer, (uint16_t)sizeof(g_ws2812_tx_buffer));
}
//清楚所有的灯光
void lib_ws2812_clear(void)
{   
    lib_ws2812_set_all(0U, 0U, 0U);
    lib_ws2812_update();
}
//hsb转为rgb
static uint8_t hsv_to_rgb_helper(uint8_t phase, uint8_t t) {
    if (t < 43) {
        return (uint8_t)((t * 6) / 255.0f * 255);
    } else if (t < 128) {
        return 255;
    } else if (t < 171) {
        return (uint8_t)(((171 - t) * 6) / 255.0f * 255);
    } else {
        return 0;
    }
}
///word keil vscode 记事本
void hsv_to_rgb(uint16_t hue, uint8_t *r, uint8_t *g, uint8_t *b) {
    uint8_t phase = hue / 43;
    uint8_t t = hue % 43;
    t = t * 6;

    switch (phase) {
        case 0: *r = 255; *g = t; *b = 0; break;
        case 1: *r = 255 - t; *g = 255; *b = 0; break;
        case 2: *r = 0; *g = 255; *b = t; break;
        case 3: *r = 0; *g = 255 - t; *b = 255; break;
        case 4: *r = t; *g = 0; *b = 255; break;
        default: *r = 255; *g = 0; *b = 255 - t; break;
    }
}
// 呼吸模式优化版 - 更快、更符合人体感官
void lib_ws2812_breath_mode(uint32_t tick) {
    static const uint8_t colors[5][3] = {
        {2, 10, 50},    // 紫蓝色
        {255, 10, 10},  // 红色
        {10, 50, 255},  // 绿色
        {10, 10, 50},   // 蓝色
        {50, 40, 10}    // 橙色
    };

    // 1. 缩短周期：原来总长10000，现在改为5000（每种颜色1000，呼吸更轻快）
    // 如果觉得还是慢，可以把 5000 改为 3000
    uint32_t total_cycle = 1000; 
    uint32_t color_period = total_cycle / 5; // 每种颜色占 1000

    uint32_t color_cycle = tick % total_cycle;
    uint8_t color_index = color_cycle / color_period;
    uint32_t phase = color_cycle % color_period;

    uint32_t raw_brightness;

    // 2. 构造 0 -> 255 -> 0 的原始亮度
    uint32_t half_period = color_period / 2;
    if (phase < half_period) {
        raw_brightness = (phase * 255) / half_period;
    } else {
        raw_brightness = ((color_period - phase) * 255) / half_period;
    }

    // 这会让灯光在低亮度时过渡极其细腻，高亮度时自然饱满，消除闪烁感
    uint8_t sensory_brightness = (uint8_t)((raw_brightness * raw_brightness) >> 8);

    // 4. 计算最终输出颜色
    uint8_t r = (colors[color_index][0] * sensory_brightness) / 255;
    uint8_t g = (colors[color_index][1] * sensory_brightness) / 255;
    uint8_t b = (colors[color_index][2] * sensory_brightness) / 255;

    lib_ws2812_set_all(r, g, b);
  
}
//彩虹模式
void lib_ws2812_rainbow_mode(uint32_t tick) {
    uint16_t base_hue = (tick * 2) % 256;

    for (uint16_t i = 0; i < WS2812_LED_NUM; i++) {
        uint16_t hue = (base_hue + (i * 4)) % 256;  //i*4
        uint8_t r, g, b;
        hsv_to_rgb(hue, &r, &g, &b);
        lib_ws2812_set_pixel(i, r, g, b);
    }
}
 
// 碰撞波纹模式
void lib_ws2812_collide_ripple_mode(uint32_t tick) {
    // 1. 定义动画周期 (约 2 秒一个循环)sss
    uint32_t cycle = tick % 80; 
    
    // 清空画布，因为这个模式需要每帧重新计sss算
    lib_ws2812_set_all(0, 0, 0);

    // 碰撞中心点（60% 键盘约在第 2 行，第 6-7 列）
    const int center_r = 2;
    const int center_c = 6;
    const int max_dist_to_center = center_r + center_c; // 约 8-9 步

    for (uint8_t r = 0; r < 5; r++) {
        for (uint8_t c = 0; c < 14; c++) {
            if (g_key_to_led_map[r][c] == INVALID_INDEX) continue;

            uint8_t red = 0, green = 0, blue = 0;

            // --- 阶段 A: 流星对撞 (cycle 0 - 20) ---
            if (cycle < 20) {
                // 流星 A: 从左上 (0,0) 出发
                int distA = r + c; // 当前点距离左上的距离
                int posA = cycle;  // 流星头部的当前位置
                if (distA <= posA && distA > posA - 3) { // 长度为 3 的拖尾
                    blue = 255 / (posA - distA + 1);
                    green = blue / 2;
                }

                // 流星 B: 从右下 (4,13) 出发
                int distB = (4 - r) + (13 - c);
                int posB = cycle;
                if (distB <= posB && distB > posB - 3) {
                    red = 255 / (posB - distB + 1);
                    green = red / 4;
                }
            } 
            // --- 阶段 B: 碰撞波纹 (cycle 21 - 60) ---
            else if (cycle >= 20 && cycle < 60) {
                int ripple_tick = cycle - 20;
                // 计算当前点到中心的距离
                int dist_to_center = abs(r - center_r) + abs(c - center_c);
                
                // 波纹扩散：距离等于当前 tick 的点亮起
                int ripple_radius = ripple_tick / 2; // 控制波纹扩散速度
                
                if (dist_to_center == ripple_radius) {
                    // 波纹颜色：青色 (Cyan)
                    uint8_t fade = 255 - (ripple_tick * 4); // 随时间变暗
                    green = fade;
                    blue = fade;
                } else if (dist_to_center == ripple_radius - 1) {
                    // 波纹拖尾
                    uint8_t fade = 120 - (ripple_tick * 2);
                    green = fade;
                    blue = fade;
                }
            }

            // 如果有颜色，则写入硬件缓冲区
            if (red > 0 || green > 0 || blue > 0) {
                lib_ws2812_set_key_color(r, c, red, green, blue);
            }
        }
    }
}







// 炫彩跑马灯模式
void lib_ws2812_dazzle_marquee_mode(uint32_t tick) {
    const uint8_t total_keys = 70; // 5 * 14
    const uint8_t tail_length = 16; // 拖尾长度

    // 1. 确定当前车头位置 (0-69)
    // 这里的速度可以调，tick * 1 是普通速度，tick * 2 是快速
    uint16_t head_pos = tick % total_keys;

    // 清空画布
    lib_ws2812_set_all(0, 0, 0);

    for (uint8_t r = 0; r < 5; r++) {
        for (uint8_t c = 0; c < 14; c++) {
            if (g_key_to_led_map[r][c] == INVALID_INDEX) continue;

            // 2. 将二维坐标转为一维线性索引
            uint16_t current_idx = r * 14 + c;

            // 3. 计算当前点距离车头的距离 (考虑循环越界)
            int16_t dist;
            if (head_pos >= current_idx) {
                dist = head_pos - current_idx;
            } else {
                // 如果车头已经转回到开头，而尾巴还在末尾
                dist = head_pos + total_keys - current_idx;
            }

            // 4. 如果该点在拖尾范围内
            if (dist < tail_length) {
                // 计算色调：(车头位置 * 4) 决定了基础颜色，(dist * 8) 决定了尾巴的彩虹过渡
                uint16_t hue = (tick * 4 + dist * 8) % 256;
                
                uint8_t rv, gv, bv;
                hsv_to_rgb(hue, &rv, &gv, &bv);

                // 5. 计算亮度衰减：越靠近尾部越暗
                // 亮度 = 255 * (剩余长度 / 总长度)
                uint8_t brightness = (255 * (tail_length - dist)) / tail_length;

                // 最终颜色应用亮度
                rv = (rv * brightness) / 255;
                gv = (gv * brightness) / 255;
                bv = (bv * brightness) / 255;

                lib_ws2812_set_key_color(r, c, rv, gv, bv);
            }
        }
    }
}






















#if 0
void ws28_encode_byte(uint8_t val,uint8_t* dst){
	for(uint8_t i=0 ;i<8;i++){
		dst[i]=((val&(0x80>>i))!=0)?WS_BIT_1:WS_BIT_0;
	
	}
}
void ws28_encode_index(uint16_t led_index){
    uint16_t offset=led_index*24;
		//获取index位置的数值
		ws2812_color_t *color=&g_ws2812_colors[led_index];
	  //grb进行转换
	  ws28_encode_byte(color->g,&g_ws2812_tx_buffer[offset]);
		ws28_encode_byte(color->g,&g_ws2812_tx_buffer[offset+8]);
		ws28_encode_byte(color->g,&g_ws2812_tx_buffer[offset+16]);

}

/* lib_ws2812.c - WS2812 LED library implementation placeholder */
#include "lib_ws2812.h"
#include "string.h"

//设置ws2812的现存数据
typedef struct{
  uint8_t r;
	uint8_t g;
	uint8_t b;
}color_t;




//设置每一行的物理长度
static const uint8_t row_lens[5]={14,14,13,12,8};
//每一行的索引值
static const uint16_t row_offsets[5]={0,14,28};

uint8_t g_led_buffer[24];
//  按照 G/R/B 的顺序发送。
void lib_ws2812_set_color(uint8_t num,uint16_t index, color_t color_data){
	//判断是不是在范围内
   //转为grb
	uint32_t data=color_data.g|color_data.r|color_data.b;
	uint16_t start_pos = index * 24;
	//转为spi的数值[][][]
	for (uint8_t i = 0; i < num; i++)
	{
		for (uint8_t j = 0;j < 24; j++){
				//是0=ws_bit0;
				if((data>>j)&0x01){
					g_led_buffer[i][start_pos+(23-j)]=WS_BIT_0;
				}else{

					g_led_buffer[i][start_pos + (23 - j)] = WS_BIT_0;
				}
				//是1=ws_bit1
		}
	}
	//发送res码
	
	
	
	
}
void lib_ws2812_update(void){


	
	
}
void lib_ws2812_clear(void){




}
#endif
