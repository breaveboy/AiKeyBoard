#include "lib_hall_sensor.h"
#include "bsp_delay.h"
#include "App_debug.h"
// 当前正在采集的矩阵行，0~4。
volatile uint8_t g_current_row = 0;
// 一帧 5x14 数据采集完成标志，由按键任务清理并重启下一帧。
volatile uint8_t g_scan_complete = 0;
// 单行 14 路 ADC DMA 完成标志，由 DMA 中断置位。
volatile uint8_t g_adc_complete = 0;
#define ADC_DMA1_CH1_ALL_FLAGS (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CHTIF1 | DMA_IFCR_CTEIF1)
#define ADC_SCAN_TIMEOUT_MS 20U
static uint32_t g_adc_start_tick;
// 滤波后的整帧 ADC 数据，按键判断只读取这个数组。
uint16_t g_hall_adc_frame[ROW_COUNT][COL_COUNT] = {0};
uint16_t g_hall_adc_raw_frame[ROW_COUNT][COL_COUNT] = {0};
Key_t keys[ROW_COUNT][COL_COUNT];


const uint8_t key_mask[ROW_COUNT][COL_COUNT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1}
};


#define USE_NEW_FILTER

#if defined(USE_NEW_FILTER)
/* ================================================================
 * 新方案：噪声门 + 一阶 IIR
 * ================================================================ */
#define NOISE_GATE  3
#define SPIKE_GATE 80
#define IIR_SHIFT   2
static uint32_t ema_acc[ROW_COUNT][COL_COUNT];
static uint16_t last_out[ROW_COUNT][COL_COUNT];
//新的滤波
static uint16_t process_hall_filter(uint8_t row, uint8_t col, uint16_t new_raw){
    uint16_t cur = (uint16_t)(ema_acc[row][col] >> 4);

    int32_t delta = (int32_t)new_raw - (int32_t)cur;
    if (delta < 0) delta = -delta;

    if (delta <= NOISE_GATE) {
        return last_out[row][col];
    }

//    if (delta >= SPIKE_GATE) {
//        return last_out[row][col];
//    }

    int32_t diff = (int32_t)new_raw - (int32_t)cur;
    int64_t acc  = (int64_t)ema_acc[row][col] + ((int64_t)diff << 4 >> IIR_SHIFT);
    if (acc < 0) acc = 0;
    ema_acc[row][col] = (uint32_t)acc;

    uint16_t out = (uint16_t)(ema_acc[row][col] >> 4);
    last_out[row][col] = out;
    return out; 

}

static inline void hall_filter_calibration_init(uint8_t r, uint8_t c, uint16_t idle)
{
    ema_acc[r][c]  = (uint32_t)idle << 4;
    last_out[r][c] = idle;
}
#elif defined(USE_FILTER)
    /* ================================================================
     * 旧方案：中值滤波 + EMA + 迟滞死区
     * ================================================================ */
    #define EMA_SHIFT 3
    #define HYSTERESIS_DEADZONE 4
   

    static uint16_t raw_history[ROW_COUNT][COL_COUNT][3] = {0};
    static uint32_t ema_accumulator[ROW_COUNT][COL_COUNT] = {0};
    static uint16_t logical_output[ROW_COUNT][COL_COUNT] = {0};
     // 三点中值滤波
    static inline uint16_t fast_median(uint16_t a, uint16_t b, uint16_t c)
    {
        uint16_t temp;

        if (a > b) { temp = a; a = b; b = temp; }
        if (b > c) { temp = b; b = c; c = temp; }
        if (a > b) { temp = a; a = b; b = temp; }

        return b;
    }
   

    // 单键滤波链路：三点中值 -> EMA -> 迟滞死区。
    static uint16_t process_hall_filter(uint8_t row, uint8_t col, uint16_t new_raw)
    {
        raw_history[row][col][0] = raw_history[row][col][1];
        raw_history[row][col][1] = raw_history[row][col][2];
        raw_history[row][col][2] = new_raw;

        uint16_t median_val = fast_median(raw_history[row][col][0], raw_history[row][col][1], raw_history[row][col][2]);

        if (ema_accumulator[row][col] == 0) {
            ema_accumulator[row][col] = ((uint32_t)median_val << EMA_SHIFT);
        }
        ema_accumulator[row][col] += median_val - (ema_accumulator[row][col] >> EMA_SHIFT);
        uint16_t ema_val = ema_accumulator[row][col] >> EMA_SHIFT;

        int16_t delta = (int16_t)ema_val - (int16_t)logical_output[row][col];
        if (delta > HYSTERESIS_DEADZONE) {
            logical_output[row][col] = ema_val - HYSTERESIS_DEADZONE;
        } else if (delta < -HYSTERESIS_DEADZONE) {
            logical_output[row][col] = ema_val + HYSTERESIS_DEADZONE;
        }

        return logical_output[row][col];
    }

#endif




// 关闭所有行，避免切行时串扰。
void ROW_ALL_OFF(void)
{
    CLR_IO(GPIOA, GPIO_PIN_8);
    CLR_IO(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
}

// 选择一行进入采样状态，行信号低电平有效。
void select_row(uint8_t index)
{
    ROW_ALL_OFF();
    //Bsp_Delay_Us(ROW_OFF_DEADTIME_US);
    switch (index) {
    case 0: SET_IO(GPIOA, GPIO_PIN_8); break;
    case 1: SET_IO(GPIOC, GPIO_PIN_9); break;
    case 2: SET_IO(GPIOC, GPIO_PIN_8); break;
    case 3: SET_IO(GPIOC, GPIO_PIN_7); break;
    case 4: SET_IO(GPIOC, GPIO_PIN_6); break;
    default: break;
    

    }
    Bsp_Delay_Us(ROW_ON_SETTLING_US);
}

// 霍尔采集层初始化：只负责 GPIO、ADC、DMA，不做按键业务判断。
void lib_hall_sensor_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    ROW_ALL_OFF();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    ROW_ALL_OFF();  

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
                          GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    bsp_adc_dma_init();
}

// DMA 中断只置完成标志，数据处理放在任务里完成。
void DMA1_Channel1_IRQHandler(void)
{   
    uint32_t isr=DMA1->ISR;
    App_debug_dma_tick(
        (isr & DMA_ISR_TEIF1) != 0U
    );
    DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS; //完成寄存器清空
    DMA1_Channel1->CCR &= ~DMA_CCR_EN;   //dma1_chanel1通用配置寄存器开关
    if (isr & DMA_ISR_TEIF1) {
        // 标记错误并重新启动扫描
        g_adc_complete = 1;
        return;
    }
    if(isr&DMA_ISR_TCIF1){
        g_adc_complete = 1;
    }
}

void lib_hall_sensor_calibration_oled(void){
    printf("adc——init");
    g_adc_complete=0;
    g_scan_complete=0;
    g_current_row=0;
    memset(g_hall_adc_frame, 0, sizeof(g_hall_adc_frame));
    for(uint8_t r=0;r<ROW_COUNT;r++){
        select_row(r);
        //Bsp_Delay_Us(SETTLING_TIME_US);
        /////////////三次采集数据//////////
        uint32_t col_sums[COL_COUNT]={0};
        for(int i=0;i<3;i++){
            g_adc_complete=0;
            bsp_adc_dma_start();
            while (!g_adc_complete); //没有采集完成卡死
            for (uint8_t c = 0; c < COL_COUNT; c++){
               col_sums[c] += gADCxConvertedData[c]; // 累加第 i 次的读数
            }
            Bsp_Delay_Us(10); // 采样
        }
        ////////////计算平均值并进行初始化赋值/////////////
        for(uint8_t c=0;c<COL_COUNT;c++){
            //计算三次的平均值
            uint16_t average_idle = (uint16_t)(col_sums[c] / 3);
            //////给按键复制
            keys[r][c].idele_adc=average_idle;
            g_hall_adc_frame[r][c]=average_idle;
            // 3. 设定其他参数
            keys[r][c].drift_cnt = 0;
            keys[r][c].actuation_point = 250;    //350 200
            keys[r][c].top_deadzone = 150;     // 建议死区从 80 稍微调高到 100
            keys[r][c].bottom_deadzone = 1000;
            keys[r][c].rt_press_sens = 50;
            keys[r][c].rt_release_sens = 50;
            keys[r][c].is_pressed = 0;
            keys[r][c].in_rt_cycle = 0;
            keys[r][c].max_offset = 0;
            keys[r][c].min_offset = 0;
            
            #if defined(USE_NEW_FILTER)
            hall_filter_calibration_init(r, c, average_idle);
            #elif defined(USE_FILTER)
            // 4. 同步更新滤波器状态，防止运行第一秒时数值跳变
            raw_history[r][c][0] = average_idle;
            raw_history[r][c][1] = average_idle;
            raw_history[r][c][2] = average_idle;
            ema_accumulator[r][c] = ((uint32_t)average_idle << EMA_SHIFT);
            logical_output[r][c] = average_idle;
            #endif
            
        }

    
    }
    g_scan_complete = 0;
    g_current_row = 0;
    ROW_ALL_OFF();

}
/////////////五次中值/////////////////////
static uint16_t median5(uint16_t values[5])
{
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = i + 1; j < 5; j++) {
            if (values[i] > values[j]) {
                uint16_t temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }

    // 排序后第3个数就是中值
    return values[2];
}
void lib_hall_sensor_calibration(void){
    g_adc_complete=0;
    g_scan_complete=0;
    g_current_row=0;
    //进行5次中值滤波
    static uint16_t adc_samples[ROW_COUNT][COL_COUNT][5] ={0};
    for(uint8_t sample=0;sample<5;sample++){
        for(uint8_t r=0;r<ROW_COUNT;r++){
            select_row(r);
           
            g_adc_complete=0;
            //开始采集
            bsp_adc_dma_start();
            while(!g_adc_complete);
            for(uint8_t c = 0; c < COL_COUNT; c++){
                adc_samples[r][c][sample]=gADCxConvertedData[c];
            }
        
        }
     
    }
   // 对每个按键的5次数据取中值
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
          if (key_mask[r][c] == 0) {
                g_hall_adc_frame[r][c] = 0;
                continue;
            }
          uint16_t values[5];
           for (uint8_t i = 0; i < 5; i++) {
                values[i] = adc_samples[r][c][i];
            }
            uint16_t median_idle = median5(values);
            keys[r][c].idele_adc = median_idle;
            g_hall_adc_frame[r][c] = median_idle;

            keys[r][c].drift_cnt = 0;
            keys[r][c].actuation_point = 250;
            keys[r][c].top_deadzone = 150;
            keys[r][c].bottom_deadzone = 1000;
            keys[r][c].rt_press_sens = 50;
            keys[r][c].rt_release_sens = 50;
            keys[r][c].is_pressed = 0;
            keys[r][c].in_rt_cycle = 0;
            keys[r][c].max_offset = 0;
            keys[r][c].min_offset = 0;
            #if defined(USE_NEW_FILTER)
            hall_filter_calibration_init(r, c, median_idle);
            #elif defined(USE_FILTER)
                raw_history[r][c][0] = median_idle;
                raw_history[r][c][1] = median_idle;
                raw_history[r][c][2] = median_idle;
                ema_accumulator[r][c] =
                    (uint32_t)median_idle << EMA_SHIFT;
                logical_output[r][c] = median_idle;
            #endif
        }
    
    }
    
    
    g_adc_complete = 0;
    g_scan_complete = 0;
    g_current_row = 0;
   ROW_ALL_OFF();


}









// 从第 0 行开始启动一整帧扫描。
void lib_hall_sensor_start_scan(void)
{
    g_adc_complete = 0;
    g_scan_complete = 0;
    g_current_row = 0;

    select_row(g_current_row);
    //Bsp_Delay_Us(SETTLING_TIME_US);
    g_adc_start_tick = HAL_GetTick();
    bsp_adc_dma_start();
}

// 当前帧被 App_key 消费后，重新启动下一帧采集。任务中循环调用的函数
void lib_hall_sensor_release_frame(void)
{
    if (g_scan_complete) {
        lib_hall_sensor_start_scan();
    }
}

// ADC 采集任务：一次 DMA 完成只处理一行，五行完成后交给按键任务。
void lib_hall_sensor_task(void)
{
    if (g_scan_complete) {
        return;
    }

    if (!g_adc_complete) {
        if ((HAL_GetTick() - g_adc_start_tick) < ADC_SCAN_TIMEOUT_MS) {
            return;
        }

        App_debug_capture_adc_timeout(g_current_row);
        DMA1_Channel1->CCR &= ~DMA_CCR_EN;
        DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
        g_adc_complete = 0;
        select_row(g_current_row);
        g_adc_start_tick = HAL_GetTick();
        bsp_adc_dma_start();
        return;
    }

    g_adc_complete = 0;

    for (uint8_t c = 0; c < COL_COUNT; c++) {
        if (key_mask[g_current_row][c] == 0) {
            g_hall_adc_raw_frame[g_current_row][c] = 0;
            g_hall_adc_frame[g_current_row][c] = 0;
            continue;
        }

        g_hall_adc_raw_frame[g_current_row][c] = gADCxConvertedData[c];
        // 这里只写入滤波 ADC 帧，不在采集层判断按下/松开。
        g_hall_adc_frame[g_current_row][c] = process_hall_filter(g_current_row, c, gADCxConvertedData[c]);
    }

    g_current_row++;
    if (g_current_row >= ROW_COUNT) {
        g_current_row = 0;
        g_scan_complete = 1;
        /* 已经完成5行ADC扫描 */
        App_debug_frame_tick();
        ROW_ALL_OFF();
        return;
    }

    select_row(g_current_row);
    //Bsp_Delay_Us(SETTLING_TIME_US);
    g_adc_start_tick = HAL_GetTick();
    bsp_adc_dma_start();
}


#if 0
////////上电时初始key的状态
// 上电校准：逐行采样一次，初始化每个键的 idle_adc 和滤波器状态。
// 上电校准：逐行采样一次，初始化每个键的 idle_adc 和滤波器状态。
//  fn和普通按键的初始化数值是不一样的
void lib_hall_sensor_calibration_oled(void)
{
    g_adc_complete = 0;
    g_scan_complete = 0;
    g_current_row = 0;
    memset(g_hall_adc_frame, 0, sizeof(g_hall_adc_frame));

    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        select_row(r);
        Bsp_Delay_Us(SETTLING_TIME_US);

        g_adc_complete = 0;
        bsp_adc_dma_start();

        while (!g_adc_complete) {
        }

        g_adc_complete = 0;

        for (uint8_t c = 0; c < COL_COUNT; c++) {
            uint16_t idle = gADCxConvertedData[c]; //原始的adc的数值，没有滤波

            g_hall_adc_frame[r][c] = idle;
            keys[r][c].idele_adc = idle;
            keys[r][c].drift_cnt = 0;
            keys[r][c].actuation_point = 350; 
            keys[r][c].top_deadzone = 80;
            keys[r][c].bottom_deadzone = 1050;
            keys[r][c].rt_press_sens = 50;
            keys[r][c].rt_release_sens = 50;
            keys[r][c].is_pressed = 0;
            keys[r][c].in_rt_cycle = 0;
            keys[r][c].max_offset = 0;
            keys[r][c].min_offset = 0;

            raw_history[r][c][0] = idle;
            raw_history[r][c][1] = idle;
            raw_history[r][c][2] = idle;
            ema_accumulator[r][c] = ((uint32_t)idle << EMA_SHIFT);
            logical_output[r][c] = idle;
        }
    }   

    g_scan_complete = 0;
    g_current_row = 0;
    ROW_ALL_OFF();
    //printf("Calibration OK!\r\n");
}

void lib_hall_sensor_calibration(void) {
    printf("Calibration Start...\r\n");
    g_scan_complete = 0;
    g_current_row = 0;
    memset(g_adc_raw_col, 0, sizeof(g_adc_raw_col));

    select_row(0);
    Bsp_Delay_Us(100); // 校准给更长稳定时间
    bsp_adc_dma_start();

    while(!g_scan_complete); // 等待三轮扫完

    for(uint8_t r = 0; r < ROW_COUNT; r++) {
        for(uint8_t c = 0; c < COL_COUNT; c++) {
            keys[r][c].idele_adc = g_adc_raw_col[r][c] / SCAN_ROUNDS;
            g_adc_raw_col[r][c] = 0; // 必须清零累加器！
					  keys[r][c].drift_cnt = 0; // 【加这一句，保证初始化清零】
            keys[r][c].actuation_point = 350;
            keys[r][c].top_deadzone = 80;
            keys[r][c].bottom_deadzone = 1050;
            keys[r][c].rt_press_sens = 50;
            keys[r][c].rt_release_sens = 50;
            keys[r][c].is_pressed = 0;
        }
    }
    
    // 关键复位：确保 main 启动正常
    g_scan_complete = 0;
    g_current_row = 0;
    printf("Calibration OK!\r\n");
}


// ADC 采集任务：一次 DMA 完成只处理一行，五行完成后交给按键任务。
void lib_hall_sensor_task(void) {
    static uint16_t scan_watchdog = 0;
    if (g_scan_complete == 1) {
        for(uint8_t r = 0; r < ROW_COUNT; r++) {
            for (uint8_t c = 0; c < COL_COUNT; c++) {
				//跳出无效的按键
                if (key_mask[r][c] == 0) {
                    g_adc_raw_col[r][c] = 0;
                    continue;
                }
                
				//进行三次滤波
                uint16_t avg_adc = g_adc_raw_col[r][c] / SCAN_ROUNDS;
                g_adc_raw_col[r][c] = 0; // 处理完即清零
                Key_t *k = &keys[r][c];		
				// === 【这里是关键！】在算逻辑之前，先进行动态追踪 ===
                update_baseline_tracking(k, avg_adc);
								
				//执行按键的逻辑
                process_key_logic(k, avg_adc);
            }
        }

        // 3. 一波逻辑处理结束，重启新的一波扫描
        scan_watchdog = 0;
        g_scan_complete = 0;
        g_scan_round = 0;
        g_current_row = 0;
        select_row(0);
        Bsp_Delay_Us(SETTLING_TIME_US);
        bsp_adc_dma_start();
    } else {
        // DMA看门狗：超过100ms未完成扫描则强制重启
        if (++scan_watchdog > 20) {
            scan_watchdog = 0;
            g_scan_complete = 0;
            g_scan_round = 0;
            g_current_row = 0;
            select_row(0);
            Bsp_Delay_Us(SETTLING_TIME_US);
            bsp_adc_dma_start();
        }
    }
}

//14次普通扫描： 14 × (63us高 + 22us低) = 1190 us
//第15次扫描+数据处理发送： 约2us高 + 830us长低 = 832 us
//当前总周期： 1190 + 832 = 2022 us（约 2 毫秒）
// 核心中断：链式触发逻辑  5*3会产生15中断=1.17ms。单次adc的采集是66.0us
#define ADC_DMA1_CH1_ALL_FLAGS (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CHTIF1 | DMA_IFCR_CTEIF1)
// DMA 中断只置完成标志，数据处理放在任务里完成。
void DMA1_Channel1_IRQHandler(void) {
	
	  GPIOA->BSRR = GPIO_PIN_9;
    if(DMA1->ISR & (DMA_ISR_TCIF1 | DMA_ISR_TEIF1)) {
        DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
        DMA1_Channel1->CCR &= ~DMA_CCR_EN;

        if(DMA1->ISR & DMA_ISR_TEIF1) {
            // DMA传输错误，无条件重启扫描链
            g_scan_complete = 0;
            g_scan_round = 0;
            g_current_row = 0;
            select_row(0);
            Bsp_Delay_Us(SETTLING_TIME_US);
            bsp_adc_dma_start();
            GPIOA->BRR = (uint32_t)GPIO_PIN_9;
            return;
        }

        // 1. 数据累加
        for(uint8_t c = 0; c < COL_COUNT; c++) {
            g_adc_raw_col[g_current_row][c] += gADCxConvertedData[c];
        }

        // 2. 状态机：切换行或轮次
        g_current_row++;
        if(g_current_row < ROW_COUNT) {
            select_row(g_current_row);
            Bsp_Delay_Us(SETTLING_TIME_US);
            bsp_adc_dma_start();
        } else {
            g_current_row = 0;
            g_scan_round++;
            if(g_scan_round < SCAN_ROUNDS) {
                select_row(0);
                Bsp_Delay_Us(SETTLING_TIME_US);
                bsp_adc_dma_start();
            } else {
                g_scan_complete = 1; // 标记扫描全结束，等待 task 处理
            }
        }
    }
		GPIOA->BRR = (uint32_t)GPIO_PIN_9;
}
#endif
