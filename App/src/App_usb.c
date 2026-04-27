/**
 * @file App_usb.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-04-27
 * 
 * @copyright Copyright (c) 2026
 * - 管理内容 ：把 App_key 算出来的键值打包成 8 字节的 HID 报文，调用发送接口。同时接收电脑发来的 CapsLock 灯状态，反馈给 App_lighting 。
 *  - 完善点 ：解决了“IN 和 OUT 端点”的管理问题。
 */