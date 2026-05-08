import logging
import os
import sys
from logging.handlers import RotatingFileHandler

class LogManager:
    """
    工业级日志管理器
    负责初始化配置、自动创建目录、定义多级处理器和格式化器
    """
    
    # 默认格式定义
    CONSOLE_FORMAT = "%(levelname)-8s | %(message)s"
    FILE_FORMAT = "%(asctime)s [%(name)s] %(levelname)-8s [%(filename)s:%(lineno)d] %(message)s"
    DATE_FORMAT = "%Y-%m-%d %H:%M:%S"
    
    @classmethod
    def setup(cls, log_dir: str = "logs", log_name: str = "keyboard.log", level=logging.DEBUG):
        """
        静态方法：一键初始化全局日志环境
        """
        # 1. 创建日志目录
        if not os.path.exists(log_dir):
            os.makedirs(log_dir)

        # 2. 配置根记录器 (Root Logger)
        root_logger = logging.getLogger()
        root_logger.setLevel(level)
        
        # 清除旧的 Handler，防止重复打印
        if root_logger.hasHandlers():
            root_logger.handlers.clear()

        # 3. 创建控制台处理器 (Console Handler)
        # 工业标准：屏幕只看 INFO 以上，保持整洁
        console_handler = logging.StreamHandler(sys.stdout)
        console_handler.setLevel(logging.INFO)
        console_handler.setFormatter(logging.Formatter(cls.CONSOLE_FORMAT))

        # 4. 创建文件滚动处理器 (Rotating File Handler)
        # 工业标准：记录所有细节，5MB一个文件，保留10个，确保不会撑爆硬盘
        log_path = os.path.join(log_dir, log_name)
        file_handler = RotatingFileHandler(
            log_path, 
            maxBytes=5 * 1024 * 1024, 
            backupCount=10, 
            encoding="utf-8"
        )
        file_handler.setLevel(logging.DEBUG)
        file_handler.setFormatter(logging.Formatter(cls.FILE_FORMAT, datefmt=cls.DATE_FORMAT))

        # 5. 装载处理器
        root_logger.addHandler(console_handler)
        root_logger.addHandler(file_handler)

        logging.info("--- Log System Initialized (Industrial Class Version) ---")