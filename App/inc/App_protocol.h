#ifndef __APP_PROTOCOL_H__
#define __APP_PROTOCOL_H__


#include <stdbool.h>
#include <stdint.h>
#include <string.h>


//协议的基础定义
#define PROTOCOL_REPORT_ID   0x05  //包的报告头
#define PROTOCOL_PKT_SIZE    64    //包的大小
#define PROTOCOL_PKT_ACK_EP  0x82  //in端点
#define PROTOCOL_TIMEOUT_MS   50  //超时判断


/* HID包固定64字节：7字节头 + 56字节载荷 + 1字节校验 */
#define PROTOCOL_PAYLOAD_SIZE   56U
/* DATA载荷前4字节是固件偏移，因此实际固件数据最多52字节 */
#define OTA_DATA_MAX_SIZE       52U
#define OTA_VERSION_TEXT_SIZE   16U
#define OTA_PROTOCOL_VERSION    1U



/* ========================================================================= *
 *                       [主命令 CMD_ID 划分]
 * ========================================================================= */
/* --- 1. 系统与基础配置 (号段: 0x01 - 0x0F) --- */
typedef enum {
    CMD_SYS_PREPARE       = 0x01, // 驱动准备状态同步 (通信握手)
    CMD_SYS_INFO_W        = 0x02, // 写入键盘基础信息 (如自适应参考电压匹配)
    CMD_SYS_INFO_R        = 0x82, // 读取键盘基础信息 (固件版本/宏空间/轴体种类数)
    CMD_SYS_CFG_W         = 0x03, // 写入综合配置 (回报率/去抖/休眠/切换WinMac系统等)
    CMD_SYS_CFG_R         = 0x83, // 读取综合配置
    CMD_SYS_PROFILE_W     = 0x04, // 切换/设置当前板载配置层 (Profile 0-3)
    CMD_SYS_PROFILE_R     = 0x84, // 读取当前板载配置层
    CMD_SYS_RESET         = 0x05, // 键盘复位控制 (整机复位/按键复位/灯光复位)
    CMD_SYS_PRO_NAME_W    = 0x06, // 写入 Profile 名字 (上位机保存至设备)
    CMD_SYS_PRO_NAME_R    = 0x86, // 读取 Profile 名字
    CMD_SYS_OTA           = 0xF2  // 固件升级控制 (重启进Bootloader/发固件分片)
} SysCmdId_t;

/* --- 2. 按键与磁轴配置 (号段: 0x10 - 0x1F) --- */
typedef enum {
    CMD_KEY_MAP_W         = 0x10, // 写入单键常规键值映射 (Normal/FN等)
    CMD_KEY_MAP_R         = 0x90, // 读取单键常规键值映射
    
    CMD_KEY_MACRO_W       = 0x11, // 写入宏数据 (可变长分包数据)
    CMD_KEY_MACRO_R       = 0x91, // 读取宏数据
    
    CMD_KEY_ADV_W         = 0x12, // 写入高级按键功能 (DKS / MT / SOCD / MPT 等)
    CMD_KEY_ADV_R         = 0x92, // 读取高级按键功能
    
    CMD_KEY_TRAVEL_W      = 0x13, // 写入单键触发行程 (单位0.01mm)
    CMD_KEY_TRAVEL_R      = 0x93, // 读取单键触发行程
    
    CMD_KEY_CALIBRATION   = 0x94, // 磁轴校准流程交互 (开启/读最大最小ADC/结束)
    
    CMD_KEY_SWITCH_W      = 0x15, // 写入按键轴体类型
    CMD_KEY_SWITCH_R      = 0x95, // 读取按键轴体类型
    
    CMD_KEY_DEADZONE_W    = 0x16, // 写入按键安全区 (顶部/底部死区)
    CMD_KEY_DEADZONE_R    = 0x96, // 读取按键安全区 (顶部/底部死区)
    
    CMD_KEY_PHYSICAL_R    = 0x97, // 读取按键物理高度行程 (上位机用于动画)
    CMD_KEY_RT_REAL_R     = 0x98, // 读取按键实时行程和原始 AD 值
    
    CMD_KEY_RT_W          = 0x19, // 写入 RT(快速触发) 开关及灵敏度
    CMD_KEY_RT_R          = 0x99, // 读取 RT(快速触发) 开关及灵敏度
    
    CMD_KEY_NOISE_R       = 0x9A, // 读取按键噪音系数
    
    CMD_KEY_DEF_SW_W      = 0x1B, // 写入默认轴体类型
    CMD_KEY_DEF_SW_R      = 0x9B  // 读取默认轴体类型
} KeyCmdId_t;


/* --- 3. 灯光系统配置 (号段: 0x20 - 0x2F) --- */
typedef enum {
    CMD_LIGHT_WRITE_CFG   = 0x20, // 写入配置 (模式/颜色/亮度/速度等，与系统配置共用)
    CMD_LIGHT_READ_CFG    = 0xA0, // 读取配置
    
    CMD_LIGHT_WRITE_CUST  = 0x21, // 写入自定义按键灯效 (游戏模式)
    CMD_LIGHT_READ_CUST   = 0xA1, // 读取自定义按键灯效
    
    CMD_LIGHT_MUSIC_MAIN  = 0x22, // 音乐律动实时推流 (主键区)
    CMD_LIGHT_READ_REAL   = 0xA2, // 读取当前物理输出的实时灯色
} LightCmdId_t;


/* --- 4. 冒泡主动上报 (特殊的统一状态) --- */
typedef enum {
    CMD_BUBBLE_RPT        = 0xFE  // [中断上报] MCU 主动上报事件给PC
} BubbleCmdId_t;











/* ========================================================================= *
 *                       [子命令 CMD_PARAM 划分]
 * ========================================================================= */
/* --- 1. 系统参数 SysCmdParam (配合 CMD_SYS_CFG_W / R 使用) --- */
typedef enum {
    SPARAM_DEBOUNCE       = 0x00, // 按键去抖次数
    SPARAM_OS_SWITCH      = 0x01, // 切换 Win/Mac 系统
    SPARAM_TAP_DELAY      = 0x02, // Tap层延迟时间
    SPARAM_SLEEP_LV1      = 0x03, // 一级休眠时间
    SPARAM_SLEEP_LV2      = 0x04, // 二级休眠时间
    SPARAM_WIN_LOCK       = 0x05, // Win键锁定开关
    SPARAM_KEY_LOCK       = 0x06, // 全键盘锁定开关
    SPARAM_POLLING_RATE   = 0x07, // USB 回报率 (1000Hz/8000Hz)
    SPARAM_NKRO_SW        = 0x08, // 全键无冲/按键连击开关
    SPARAM_AUTO_CALIB     = 0x09, // 磁轴自适应校准开关
    SPARAM_DEBOUNCE_MODE  = 0x0A, // 磁轴去抖模式 (按下和松开的判定逻辑)
    SPARAM_DEBOUNCE_TIME  = 0x0B, // 磁轴去抖绝对时间 (单位us)
    SPARAM_LOW_POWER      = 0x0C  // 低功耗模式开关
} SysCmdParam_t;
/* --- 2. 按键层级 KeyLayerParam (配合几乎所有 KeyCmd 使用) --- */
// 提示：设置键值、设置RT、设置行程时，Param 通常代表设置的是哪个"逻辑层"
typedef enum {
    KPARAM_LAYER_NORMAL   = 0x00, // 普通层 (Normal Layer)
    KPARAM_LAYER_FN1      = 0x01, // FN1层
    KPARAM_LAYER_FN2      = 0x02, // FN2层
    KPARAM_LAYER_TAP      = 0x03, // Tap层 (短按触发层)
    KPARAM_LAYER_WIN_MAC  = 0x04  // 系统专属层 (区分 Win表 和 Mac表)
} KeyLayerParam_t;


/* --- 3. 灯光参数 LightCmdParam (配合 CMD_LIGHT_WRITE_CFG 使用) --- */
typedef enum {
    LPARAM_ALL_SET        = 0x00, // 综合设置 (模式+颜色+亮度+速度)
    LPARAM_MODE_ONLY      = 0x01, // 仅切换模式
    LPARAM_COLOR_ONLY     = 0x02, // 仅切换颜色
    LPARAM_BRIGHT_ONLY    = 0x03, // 仅切换亮度
    LPARAM_SPEED_ONLY     = 0x04, // 仅切换速度
    LPARAM_DIRECTION      = 0x05, // 切换灯效方向
    LPARAM_MAIN_SWITCH    = 0x06, // 主背光/边灯/Logo 总开关
    LPARAM_OVERLAY_SWITCH = 0x07  // 叠加层(响应层)总开关
} LightCmdParam_t;



/* --- 4. 冒泡上报参数 BubbleCmdParam (配合 CMD_BUBBLE_RPT 使用) --- */
typedef enum {
    BPARAM_DONGLE_CONN    = 0x01, // 2.4G 接收器连接状态变化
    BPARAM_BATTERY_LVL    = 0x02, // 电池电量/充放电状态变化
    BPARAM_OS_SWITCH      = 0x03, // 用户快捷键切换 Win/Mac 时的通知
    BPARAM_AI_KEY_TRIG    = 0x04, // 【核心】AI自定义按键被触发，通知上位机唤醒大模型
    BPARAM_PROFILE_SW     = 0x05, // 快捷键切换 Profile 层通知
    BPARAM_DATA_CHANGED   = 0x06, // 键盘内部数据变化，提示驱动重新读取 (如免驱改键后)
} BubbleCmdParam_t;
////////////////////////////////////////////////////////ota相关////////////////////////////////
/* OTA操作命令 */
typedef enum {
    OTA_PARAM_QUERY  = 0x00, /* 查询当前状态和接收进度 */
    OTA_PARAM_BEGIN  = 0x01, /* 开始新的固件传输 */
    OTA_PARAM_DATA   = 0x02, /* 发送固件分片 */
    OTA_PARAM_END    = 0x03, /* 结束传输并校验完整固件 */
    OTA_PARAM_ABORT  = 0x04, /* 取消当前升级 */
    OTA_PARAM_REBOOT = 0x05  /* 重启进入Bootloader升级 */
} OtaCmdParam_t;

/* OTA运行状态 */
typedef enum {
    OTA_STATE_IDLE      = 0x00, /* 当前没有升级任务 */
    OTA_STATE_RECEIVING = 0x01, /* 正在接收固件 */
    OTA_STATE_VERIFYING = 0x02, /* 正在校验固件 */
    OTA_STATE_READY     = 0x03, /* 固件有效，可以重启 */
    OTA_STATE_ERROR     = 0x04  /* 升级失败 */
} OtaState_t;

/* OTA命令执行结果 */
typedef enum {
    OTA_STATUS_OK              = 0x00, /* 成功 */
    OTA_STATUS_INVALID_COMMAND = 0x01, /* 未知命令 */
    OTA_STATUS_INVALID_LENGTH  = 0x02, /* payload长度错误 */
    OTA_STATUS_INVALID_STATE   = 0x03, /* 当前状态不允许执行 */
    OTA_STATUS_INVALID_IMAGE   = 0x04, /* 固件参数无效 */
    OTA_STATUS_OFFSET_MISMATCH = 0x05, /* 分片偏移错误 */
    OTA_STATUS_FLASH_ERROR     = 0x06, /* Flash操作失败 */
    OTA_STATUS_CRC_ERROR       = 0x07, /* 固件CRC32错误 */
    OTA_STATUS_BUSY            = 0x08, /* 设备忙 */
    OTA_STATUS_INTERNAL_ERROR  = 0x09  /* 内部错误 */
} OtaStatus_t;

/* ========================================================================= *
 *                       [AI 专属动作 (填入 Payload)]
 * ========================================================================= */
typedef enum{
    AI_ACT_TRIGGER  =0x01, //触发和唤醒AI
    AI_ACT_CONFIRM  =0x02, //确定AI的结果
    AI_ACT_CANCEL   =0x03, //取消或关闭AI界面
}AiAction_t;




/* ========================================================================= *
 *                           [数据包结构体与强转载荷]
 * ========================================================================= */
/*
 * 所有通过USB传输的结构体统一按1字节对齐。
 * push保存原有对齐设置，末尾pop负责恢复，避免影响其他模块。
 */
#pragma pack(push, 1)

//定义命令的结构体
//64-8=56个数据有效区
typedef struct{
	uint8_t report_id;     //报告id   byte0
	uint8_t cmd_id;       //命令参数
	uint8_t cmd_param;    //命令参数
	uint8_t reserved;     //预留字节
    uint8_t total_pkts;    //总包数
    uint8_t cur_pkt;       //当前包数
	uint8_t data_len;      //有效数据长度
	uint8_t payload[56];    //数据区
	uint8_t crc;             //前面字段的校验和
}Packet_t;

// 定义 payload 解析强转结构体 (对应 LPARAM_ALL_SET 综合设置)
typedef struct {
    uint8_t mode_idx;     // 模式序号 (0-19)
    uint8_t color_idx;    // 颜色序号 (0-7)
    uint8_t r;            // 红色值
    uint8_t g;            // 绿色值
    uint8_t b;            // 蓝色值
    uint8_t brightness;   // 亮度 (0-100 或 0-4 档位)
    uint8_t speed;        // 速度 (0-39)
} Payload_LightAll_t;

// 定义 payload 解析强转结构体 (对应 LPARAM_COLOR_ONLY 仅切换颜色)
typedef struct {
    uint8_t color_idx;    // 主颜色序号
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t layer;        // 层级
} Payload_LightColor_t;

/* BEGIN命令：上位机发送固件基本信息，固定28字节 */
typedef struct {
    uint32_t image_size;                    /* 固件文件实际长度 */
    uint32_t image_crc32;                   /* 完整固件CRC32 */
    uint32_t image_version;                 /* 数字版本号 */
    uint8_t version_text[OTA_VERSION_TEXT_SIZE]; /* 显示版本，如"1.2.0" */
} Payload_OtaBegin_t;

/* DATA命令：4字节偏移 + 最多52字节固件数据 */
typedef struct {
    uint32_t offset;                        /* 数据相对固件起点的偏移 */
    uint8_t data[OTA_DATA_MAX_SIZE];        /* 固件分片数据 */
} Payload_OtaData_t;

/* END命令：再次确认固件大小和CRC，固定8字节 */
typedef struct {
    uint32_t image_size;
    uint32_t image_crc32;
} Payload_OtaEnd_t;

/* 所有OTA命令统一响应，固定20字节 */
typedef struct {
    uint8_t protocol_version; /* OTA协议版本 */
    uint8_t state;            /* OtaState_t */
    uint8_t status;           /* OtaStatus_t */
    uint8_t reserved;
    uint32_t max_image_size;  /* 下载区最大容量 */
    uint32_t received_size;   /* 已确认接收长度，也是下一包offset */
    uint32_t image_crc32;     /* 当前目标固件CRC */
    uint32_t image_version;   /* 当前目标版本 */
} Payload_OtaResponse_t;

#pragma pack(pop)



//////////////////定义函数接口
uint8_t App_protocol_sum(uint8_t *buf);
bool App_protocol_send_packet(const Packet_t *packet);
void App_protocol_task(void);
void App_protocol_on_rx(uint8_t *buf, uint32_t len); 





#endif
