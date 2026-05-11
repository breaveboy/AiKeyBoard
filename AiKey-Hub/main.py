
# 导入必要的模块
import sys
import threading
import time
import pyperclip
import platform
# 判断windows平台
if platform.system() == 'Windows':
    import win32gui

# qt相关导入
from PySide6.QtWidgets import QApplication, QWidget
from PySide6.QtCore import QObject, Signal, Qt, QPoint
from pynput import mouse, keyboard

# 界面相关导入
from ui.Ui_MainWindows import Ui_MainWindowsForm
from core.ai_assistant import DeepSeekAssistant,SystemPrompt
from core.text_selector import TextSelector
import config


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindowsForm()
        self.ui.setupUi(self)
        self.setWindowFlag(Qt.WindowStaysOnTopHint)
        self.setWindowFlag(Qt.FramelessWindowHint)
        self.init_ui()
        
    def init_ui(self):
        self._isTracking = False
        self.ui.input_edit.setFocus()
        # --- AI助手和剪贴板集成 ---
        MY_API_KEY = config.key_api
        MY_BASE_URL = config.base_url
        # 初始化
        self.ai_assistant = DeepSeekAssistant(api_key=MY_API_KEY, base_url=MY_BASE_URL)
        self.text_selector = TextSelector(assistant=self.ai_assistant, main_window=self, exclude_rect=self._get_window_geometry())

        # 连接信号到槽
        self.text_selector.selected_text_signal.connect(self.update_input_edit)
        self.text_selector.start_ai_response_signal.connect(self.clear_output_edit) # Connect new signal
        self.ai_assistant.ai_response_signal.connect(self.append_output_edit) # Change to append

        # 启动文本选择监听器（在单独线程中）
        self.selector_thread = threading.Thread(target=self.text_selector.start_listening, daemon=True)
        self.selector_thread.start()
        # 连接信号与槽
        self.ui.top_btn.toggled.connect(self.toggle_topmost)
        self.ui.cloase_btn.clicked.connect(self.close)
        self.ui.btn_c1.clicked.connect(lambda:self.on_btn1_clicked())
        self.ui.btn_c2.clicked.connect(lambda:self.on_btn2_clicked())
        self.ui.btn_c3.clicked.connect(lambda:self.on_btn3_clicked())
        self.ui.btn_c4.clicked.connect(lambda:self.on_btn4_clicked())
        self.ui.btn_c5.clicked.connect(lambda:self.on_btn5_clicked())
        self.ui.btn_c6.clicked.connect(lambda:self.on_btn6_clicked())
    
   

    
    # 使用新的提示词
    def on_btn1_clicked(self):
        # 代码优化
        code_optimization_prompt = SystemPrompt["CODE_OPTIMIZATION"]
        self.ai_assistant.change_prompt(code_optimization_prompt)
        
   
        

    def on_btn2_clicked(self):
        # 辅助理解
        auxiliary_understanding_prompt = SystemPrompt["AUXILIARY_UNDERSTANDING"]
        self.ai_assistant.change_prompt(auxiliary_understanding_prompt)
       
    
    def on_btn3_clicked(self):
        # 报错分析
        error_analysis_prompt = SystemPrompt["ERROR_ANALYSIS"]
        self.ai_assistant.change_prompt(error_analysis_prompt)
       
      
    
    def on_btn4_clicked(self):
        output_text = self.ui.output_edit.toPlainText()
        if output_text:
            # 使用新线程运行替换逻辑，避免阻塞 UI 线程导致卡顿
            threading.Thread(target=self.text_selector.replace_selected_text, args=(output_text,), daemon=True).start()
            
      
    def on_btn5_clicked(self):
        # 重新开始/重新发送 AI 请求
        input_text = self.ui.input_edit.toPlainText()
        if input_text:
            self.clear_output_edit()
            # 在新线程中运行，避免阻塞界面
            threading.Thread(target=self.ai_assistant.ask_ai, args=(input_text,), daemon=True).start()
        else:
            self.append_output_edit("错误：输入框为空，无法重新发送请求。\n")
    def on_btn6_clicked(self):
        # 文档注释
        doc_comment_prompt = SystemPrompt["DOC_COMMENT"]
        self.ai_assistant.change_prompt(doc_comment_prompt)
        
    
          



    def _get_window_geometry(self):
        geom = self.geometry()
        return (geom.x(), geom.y(), geom.width(), geom.height())

    def moveEvent(self, event):
        super().moveEvent(event)
        self.text_selector.exclude_rect = self._get_window_geometry()

    def resizeEvent(self, event):
        super().resizeEvent(event)
        self.text_selector.exclude_rect = self._get_window_geometry()

    def update_input_edit(self, text):
        self.ui.input_edit.setText(text)

    def clear_output_edit(self):
        self.ui.output_edit.clear()

    def append_output_edit(self, text):
        self.ui.output_edit.insertPlainText(text)

    def toggle_topmost(self, checked):
        if checked:
            self.setWindowFlag(Qt.WindowStaysOnTopHint, True)
        else:
            self.setWindowFlag(Qt.WindowStaysOnTopHint, False)
        self.show()
        
      
    

    _startPos = None
    _endPos = None

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self._isTracking = True
            self._startPos = QPoint(event.position().x(), event.position().y())

    def mouseMoveEvent(self, event):
        if self._isTracking:
            self._endPos = QPoint(event.position().x(), event.position().y())
            self.move(self.pos() + self._endPos - self._startPos)

    def mouseReleaseEvent(self, event):
        if event.button() == Qt.LeftButton:
            self._isTracking = False
            self._startPos = None
            self._endPos = None

    def closeEvent(self, event):
        # 确保在窗口关闭时停止监听线程
        self.text_selector.stop_listening()
        super().closeEvent(event)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    
    # 加载 QSS 样式表
    try:
        with open("qss/style.qss", "r", encoding="utf-8") as f:
            _style = f.read()
            app.setStyleSheet(_style)
    except FileNotFoundError:
        print("Error: qss/style.qss not found.")

    # 实例化主窗口
    main_window = MainWindow()
    main_window.show()
    sys.exit(app.exec())