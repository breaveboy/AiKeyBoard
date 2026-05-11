import time
import threading
import pyperclip
from PySide6.QtCore import QObject, Signal, Qt
from PySide6.QtWidgets import QApplication
from pynput import mouse, keyboard
from core.ai_assistant import DeepSeekAssistant

# ================= 文本选择监听类 =================
class TextSelector(QObject):
    selected_text_signal = Signal(str)
    start_ai_response_signal = Signal() # New signal
    
    def __init__(self, assistant: DeepSeekAssistant, main_window, exclude_rect=None):
        super().__init__()
        self.assistant = assistant
        self.main_window = main_window
        self.selected_text = ""
        self.is_processing = False
        self.kb_controller = keyboard.Controller()
        self.mouse_ctrl = mouse.Controller() # 初始化鼠标控制器
        self.click_start_pos = None
        self.click_start_time = None
        self.listener = None
        self.keyboard_listener = None
        self.exclude_rect = exclude_rect # (x, y, width, height)
        self.mode = "replace"  # "replace" 或 "paste"
    def on_click(self, x, y, button, pressed):
        # 检查点击是否在排除区域内
        if self.exclude_rect:
            ex_x, ex_y, ex_w, ex_h = self.exclude_rect
            if ex_x <= x <= ex_x + ex_w and ex_y <= y <= ex_y + ex_h:
                # 点击在主窗口内，不处理
                return

        if button == mouse.Button.left:
            if pressed:
                self.click_start_pos = (x, y)
                self.click_start_time = time.time()
            else:
                if self.is_processing:
                    return
                
                if self.click_start_pos and self.click_start_time:
                    distance = ((x - self.click_start_pos[0])**2 + (y - self.click_start_pos[1])**2)**0.5
                    time_diff = time.time() - self.click_start_time

                    if distance > 5 and time_diff > 0.1:
                        # 开启新线程去处理，避免阻塞鼠标监听
                        threading.Thread(target=self.process_selection, daemon=True).start()
    def ctrl_c(self):
        with self.kb_controller.pressed(keyboard.Key.ctrl):
            self.kb_controller.press('c')
            self.kb_controller.release('c')
    def ctrl_v(self):
        with self.kb_controller.pressed(keyboard.Key.ctrl):
            self.kb_controller.press('v')
            self.kb_controller.release('v')
    def paste_at_mouse(self):
        self.mouse_ctrl.click(mouse.Button.left, 1)
        time.sleep(0.1)
        self.ctrl_v()

    def process_selection(self):
        if self.is_processing:
            return
        if QApplication.activeWindow() == self.main_window:
            return
        self.is_processing = True
        try:
            # 获取当前剪贴板内容作为备份
            old_clipboard = pyperclip.paste()
            
            # 模拟 Ctrl+C
            self.ctrl_c()
            # 给剪贴板一点时间去更新内容
            time.sleep(0.15) # 稍微减少一点延迟
           
            new_text = pyperclip.paste()
               
            print(f"✅ 获取文本: {new_text}")
            # 只要获取到了非空文本就触发，不再强制要求与旧内容不同（因为用户可能重复选择）
            if new_text and new_text.strip():
                self.selected_text = new_text
                self.selected_text_signal.emit(self.selected_text)
                self.start_ai_response_signal.emit() # 在询问 AI 前发出信号以清空输出框
                self.assistant.ask_ai(self.selected_text)
            else:
                # 如果没获取到新内容，还原剪贴板
                pyperclip.copy(old_clipboard)

        finally:
            time.sleep(0.3) # 减少处理后的锁定时间
            self.is_processing = False
    # 实现一个替换选中文本的方法
    def replace_selected_text(self, new_text):
        if not new_text:
            print("AI返回为空")
            return
        
        # 1. 写入剪贴板
        pyperclip.copy(new_text)
        time.sleep(0.05) # 减小延迟
        
        # 2. 直接替换鼠标放置的位置（回显焦点并粘贴）
        if self.click_start_pos:
            # 记录当前鼠标位置（即按钮位置）以便之后可能恢复
            current_mouse_pos = self.mouse_ctrl.position
            
            # 移动到最初划词的位置并点击，使原应用重新获得焦点
            self.mouse_ctrl.position = self.click_start_pos
            self.mouse_ctrl.click(mouse.Button.left, 1)
            time.sleep(0.05) # 减小延迟
            
            # 3. 执行粘贴动作
            if self.mode == "replace":
                self.ctrl_v()
            elif self.mode == "paste":
                self.paste_at_mouse()
            
            # 4. 将鼠标移回原位，方便用户继续操作
            self.mouse_ctrl.position = current_mouse_pos
            
            print("🎉 已完成直接替换")
        else:
            # 如果没有记录到位置，回退到原来的隐藏/显示逻辑
            self.main_window.hide()
            time.sleep(0.2)
            self.ctrl_v()
            self.main_window.show()
            print("🎉 已完成替换 (由于未记录位置，使用了窗口隐藏逻辑)")
    

    def start_listening(self):
        print(">>> 监听中... 选中任何文本后松开左键即可触发 AI 分析 (按 ESC 退出)")
        self.listener = mouse.Listener(on_click=self.on_click)
        self.listener.start()
        
        def on_press(key):
            if key == keyboard.Key.esc:
                self.stop_listening()
                return False
        
        self.keyboard_listener = keyboard.Listener(on_press=on_press)
        self.keyboard_listener.start()
        # self.keyboard_listener.join()

    def stop_listening(self):
        if self.listener: self.listener.stop()
        if self.keyboard_listener: self.keyboard_listener.stop()
        print("\n程序已退出")
    