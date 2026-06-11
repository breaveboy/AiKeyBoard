import logging
import sys
from pathlib import Path

from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine

from ota_backend import OtaBackend

# ========================================================================
#  日志配置：控制台输出
# ========================================================================
logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s [%(levelname)s] %(name)s: %(message)s",
    datefmt="%H:%M:%S",
    stream=sys.stdout,
)
app = QGuiApplication(sys.argv)
engine = QQmlApplicationEngine()

# ========================================================================
#  主题变量（被 OtaPage.qml 消费）
# ========================================================================
mock_theme = {
    "panel": "#0F172A",
    "text": "#F8FAFC",
    "muted": "#64748B",
    "dimText": "#475569",
    "field": "#1E293B",
    "blue": "#3B82F6",
    "key": "#0EA5E9",
    "warning": "#F59E0B",
    "fontFamily": "Microsoft YaHei",
}
engine.rootContext().setContextProperty("Theme", mock_theme)

# ========================================================================
#  OTA 升级后端（暴露给 QML 调用）
# ========================================================================
ota_backend = OtaBackend()
engine.rootContext().setContextProperty("OtaBackend", ota_backend)
logging.getLogger(__name__).info("OtaBackend 已注册到 QML 上下文")

qml_file = Path(__file__).resolve().with_name("main.qml")
logging.getLogger(__name__).info("加载 QML: %s", qml_file)
engine.load(qml_file)

if not engine.rootObjects():
    logging.getLogger(__name__).critical("QML 加载失败，没有 rootObjects")
    sys.exit(-1)

sys.exit(app.exec())