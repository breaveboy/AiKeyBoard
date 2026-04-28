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
	// 1. 核心输入/输出：1ms 周期
    {0, 1,  App_adkey_scan_task},   // 获取霍尔传感器物理值
    {0, 1,  App_usb_process_task},    // 计算并向电脑发送USB报告

    // 2. 内部业务逻辑：10ms 周期
    {0, 10, App_led_logic_task},     // 响应 Fn+Light 等切换指令

    // 3. 灯光视觉效果：25ms-30ms 周期
    {0, 25, App_led_animation_task}, // 演算灯光颜色数据
    {0, 30, App_led_display_task},   // 通过SPI-DMA物理刷新灯珠
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
