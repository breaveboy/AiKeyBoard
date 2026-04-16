#include "bsp_tim.h"

TIM_HandleTypeDef TimHandle;

extern void Task_update(void);

void bsp_tim_init(void)
{
    RCC_TIM6_CLK_ENABLE();
    TimHandle.Instance = TASK_TIM_INSTANCE;
    TimHandle.Init.Period            = TASK_TIM_PERIOD;
    TimHandle.Init.Prescaler         = TASK_TIM_PRESCALER;
    TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
    TimHandle.Init.RepetitionCounter = 0;
    TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&TimHandle);

    HAL_NVIC_SetPriority(TASK_TIM_IRQ, 3, 0);
    HAL_NVIC_EnableIRQ(TASK_TIM_IRQ);
    HAL_TIM_Base_Start_IT(&TimHandle);
}

void TASK_TIM_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TimHandle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TASK_TIM_INSTANCE) {
        Task_update();
    }
}
