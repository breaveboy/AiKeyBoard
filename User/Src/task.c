#include "task.h"
volatile  uint32_t g_cnt = 0;

typedef void (*Task_Func)(void);

typedef struct {
	uint32_t count;
	uint32_t period;
	Task_Func func;
} Task_t;
static Task_t tasks[] = {
	
    {0, 1,  App_adkey_scan_task},   
    {0, 1,  App_usb_process_task},  

   
    {0, 3,  App_protocol_task},
  
    {0, 25, App_led_animation_task}, 
    {0, 30, App_led_display_task},   
};

static uint16_t task_cnt = sizeof(tasks) / sizeof(Task_t);
void Task_exec(void) {
	for(uint16_t i = 0; i < task_cnt; i++) {
		if(g_cnt - tasks[i].count >= tasks[i].period) {
			tasks[i].count = g_cnt;
			tasks[i].func();
		}
	}
}

void Task_update(void) {
	g_cnt++;
}
