#include "lib_ws2812.h"
#include "bsp_gpio.h"
#include <string.h>


#define INVALID_INDEX  0xFFU
//dma搬运的数组值
static uint8_t g_ws2812_tx_buffer[WS2812_TX_BUFFER_SIZE];
static ws2812_color_t g_ws2812_colors[WS2812_LED_NUM];

static const uint8_t g_key_to_led_map[MATRIX_ROWS_COUNT][ADC_CHANNELS_COUNT] = {
    // 第一行：14颗灯，从右到左 (0在最右)
    {13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0},
    
    // 第二行：14颗灯，从右到左 (14在最右)
    {27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14},
    
    // 第三行：注意 INVALID 的位置也要随按键物理位置对应
    {40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, INVALID_INDEX,28},
    
    // 第四行：
    {52, INVALID_INDEX, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, INVALID_INDEX, 41},
    
    // 第五行：
    {60, 59, 58, 57, INVALID_INDEX, INVALID_INDEX, INVALID_INDEX, 56, INVALID_INDEX, INVALID_INDEX, INVALID_INDEX, 55, 54, 53}
   
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
	  ///清空数值
    memset(g_ws2812_tx_buffer, 0, sizeof(g_ws2812_tx_buffer));
    memset(g_ws2812_colors, 0, sizeof(g_ws2812_colors));

    for (uint16_t i = 0; i < WS2812_LED_NUM; i++) {
        ws2812_encode_pixel(i);
    }

    bsp_led_en_set(GPIO_PIN_SET);
}

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
void lib_ws2812_update(void)
{
    (void)bsp_spi_dma_send(g_ws2812_tx_buffer, (uint16_t)sizeof(g_ws2812_tx_buffer));
}
//清楚所有的灯光
void lib_ws2812_clear(void)
{   
    lib_ws2812_set_all(0U, 0U, 0U);
    lib_ws2812_update();
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
