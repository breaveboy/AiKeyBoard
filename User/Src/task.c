#include "task.h"

uint32_t g_cnt = 0;

typedef void (*Task_Func)();

typedef struct {
	uint32_t count;
	uint32_t period;
	Task_Func func;
} Task_t;

Task_t tasks[] = {
	{0, 20, App_usb_test_task},
	 
};

uint16_t task_cnt = sizeof(tasks) / sizeof(Task_t);

void Task_exec() {
	for(uint16_t i = 0; i < task_cnt; i++) {
		if(g_cnt - tasks[i].count >= tasks[i].period) {
			tasks[i].count = g_cnt;
			tasks[i].func();
		}
	}
}

void Task_update() {
	g_cnt++;
}
