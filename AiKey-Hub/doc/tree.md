MyProject/
├── main.py                # 程序入口（启动主窗口）
├── config.py              # 全局配置文件（存储 HAL 端口、AI 参数、灯光状态等）
│
├── ui/                    # 专门放 Qt Designer 生成的 .ui 文件
│   ├── main_window.ui     # 主窗口
│   ├── setting_hal.ui     # HAL 设置页
│   ├── setting_light.ui   # 灯光设置页
│   ├── setting_ai.ui      # AI 设置页
│   ├── float_icon.ui      # 悬浮小图标
│   └── float_panel.ui     # 悬浮弹出的大面板
│
├── views/                 # 存放 UI 对应的逻辑代码（Python 类）
│   ├── __init__.py
│   ├── main_view.py       # 处理主窗口逻辑
│   ├── settings_view.py   # 处理那三个设置页的切换逻辑
│   └── float_view.py      # 处理悬浮窗、大小窗口切换逻辑
│
├── core/                  # 存放核心业务功能模块（跟 UI 无关）
│   ├── __init__.py
│   ├── hal_handler.py     # 串口通信、底层硬件交互逻辑
│   ├── light_controller.py# 灯光控制协议
│   └── ai_engine.py       # AI 划线、图像处理算法
│
├── qss/                   # 资源文件夹
│   ├── svg/             # 图标（小窗口用的图标）
│   ├── png/            # 背景图
│   └── style.qss          # 皮肤样式表
│
└── utils/                 # 工具类
    └── clip_monitor.py    # 剪贴板监控或其他通用工具