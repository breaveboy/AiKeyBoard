#include "task.h"
volatile  uint32_t g_cnt = 0;

typedef void (*Task_Func)(void);

typedef struct {
	uint32_t count;
	uint32_t period;
	Task_Func func;
} Task_t;
//任务数组
static Task_t tasks[] = {
	{0, 1, App_adkey_scan_task},
	{0, 1, App_display_task},
	//{0, 1, App_logic_handler_task},
	//{0, 20,App_usb_test_task },
	//{0, 2, App_ws2812_breath_task },
};
//任务个数
static uint16_t task_cnt = sizeof(tasks) / sizeof(Task_t);
void Task_exec(void) {
	for(uint16_t i = 0; i < task_cnt; i++) {
		if(g_cnt - tasks[i].count >= tasks[i].period) {
			tasks[i].count = g_cnt;
			tasks[i].func();
		}
	}
}
//计数器
void Task_update(void) {
	g_cnt++;
}
