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
    {0, 1,  App_protocol_task},
    {0, 1, App_ota_task},
    {0, 25, App_led_animation_task},
    {0, 5,  App_led_display_task},
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


///////////////////////////////键盘的实现流程/////////////////////////////
////adc的采集 lib_hall_sensor_task======>存放在lib_hall_sensor_task
///进行三阶滤波 process_hall_filter======》process_hall_filter
///环境补偿update_baseline_tracking======》当按键处于“未按下”状态时，计算当前采样值（cur_adc）与存储基准（idele_adc）的偏差 diff
///算法逻辑层process_key_logic
////业务转换层


