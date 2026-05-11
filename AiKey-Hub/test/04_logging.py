import logging
print("正在初始化日志系统...")
# 默认是warning级别，下面的日志不会显示
logging.basicConfig(filename="test.log", filemode='w', level=logging.DEBUG,encoding='utf-8', format='%(levelname)s:%(name)s:%(message)s')
logging.debug("这是一个调试级别的日志，通常用于开发阶段，记录详细的内部状态信息。")
logging.info("这是一个信息级别的日志，适合记录程序的正常运行状态和重要事件。")
logging.warning("这是一个警告级别的日志，表示可能出现的问题，但程序仍然可以继续运行。")
logging.error("这是一个错误级别的日志，表示程序遇到了严重问题，可能无法继续运行。")
logging.critical("这是一个严重级别的日志，表示程序遇到了无法恢复的错误，通常会导致程序崩溃。")
logger = logging.getLogger(__name__)
logger.info("日志系统初始化完成！")
