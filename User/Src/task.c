#include "task.h"
#include "lib_hall_sensor.h"

volatile uint32_t g_cnt = 0;

typedef void (*Task_Func)(void);

typedef struct {
    uint32_t count;
    uint32_t period;
    Task_Func func;
} Task_t;

// 简易任务表：period 为 0 的任务每次主循环都执行，用来快速推进 ADC 状态机。
static Task_t tasks[] = {
    {0, 0,  lib_hall_sensor_task},     // ADC 行采集任务
    {0, 1,  App_adkey_scan_task},      // 整帧按键判断任务
    {0, 1,  App_usb_process_task},     // 标准键盘 HID 发送任务
    {0, 3,  App_protocol_task},
    {0, 25, App_led_animation_task},
    {0, 30, App_led_display_task},
};

static uint16_t task_cnt = sizeof(tasks) / sizeof(Task_t);

// 主循环调度入口，由 main() 不断调用。
void Task_exec(void)
{
    for (uint16_t i = 0; i < task_cnt; i++) {
        if (tasks[i].period == 0) {
            tasks[i].func();
            continue;
        }

        if (g_cnt - tasks[i].count >= tasks[i].period) {
            tasks[i].count = g_cnt;
            tasks[i].func();
        }
    }
}

void Task_update(void)
{
    g_cnt++;
}
