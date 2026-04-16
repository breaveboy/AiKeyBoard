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
void lib_ws2812_set_color(uint16_t index, color_t color){
	



}
void lib_ws2812_update(void){


	
	
}
void lib_ws2812_clear(void){




}