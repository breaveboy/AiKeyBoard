# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'MainWindows.ui'
##
## Created by: Qt User Interface Compiler version 6.11.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QButtonGroup, QHBoxLayout, QLabel,
    QPushButton, QSizePolicy, QSpacerItem, QTextEdit,
    QVBoxLayout, QWidget)
import source_rc

class Ui_MainWindowsForm(object):
    def setupUi(self, MainWindowsForm):
        if not MainWindowsForm.objectName():
            MainWindowsForm.setObjectName(u"MainWindowsForm")
        MainWindowsForm.resize(649, 500)
        self.verticalLayout = QVBoxLayout(MainWindowsForm)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.widget = QWidget(MainWindowsForm)
        self.widget.setObjectName(u"widget")
        self.widget.setStyleSheet(u"")
        self.horizontalLayout_2 = QHBoxLayout(self.widget)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.label = QLabel(self.widget)
        self.label.setObjectName(u"label")

        self.horizontalLayout_2.addWidget(self.label)

        self.horizontalSpacer = QSpacerItem(387, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_2.addItem(self.horizontalSpacer)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.top_btn = QPushButton(self.widget)
        self.top_btn.setObjectName(u"top_btn")
        icon = QIcon()
        icon.addFile(u":/svg/svg/top.svg", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        icon.addFile(u":/svg/svg/on_top.svg", QSize(), QIcon.Mode.Normal, QIcon.State.On)
        self.top_btn.setIcon(icon)
        self.top_btn.setIconSize(QSize(20, 20))
        self.top_btn.setCheckable(True)
        self.top_btn.setChecked(True)
        self.top_btn.setAutoExclusive(False)

        self.horizontalLayout.addWidget(self.top_btn)

        self.setting_btn = QPushButton(self.widget)
        self.setting_btn.setObjectName(u"setting_btn")
        icon1 = QIcon()
        icon1.addFile(u":/svg/svg/setting.svg", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        icon1.addFile(u":/svg/svg/on_setting.svg", QSize(), QIcon.Mode.Normal, QIcon.State.On)
        self.setting_btn.setIcon(icon1)
        self.setting_btn.setIconSize(QSize(20, 20))
        self.setting_btn.setCheckable(True)
        self.setting_btn.setChecked(False)
        self.setting_btn.setAutoExclusive(False)

        self.horizontalLayout.addWidget(self.setting_btn)

        self.cloase_btn = QPushButton(self.widget)
        self.cloase_btn.setObjectName(u"cloase_btn")
        icon2 = QIcon()
        icon2.addFile(u":/svg/svg/close.svg", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        icon2.addFile(u":/svg/svg/close.svg", QSize(), QIcon.Mode.Normal, QIcon.State.On)
        self.cloase_btn.setIcon(icon2)
        self.cloase_btn.setIconSize(QSize(20, 20))
        self.cloase_btn.setCheckable(True)
        self.cloase_btn.setAutoExclusive(False)

        self.horizontalLayout.addWidget(self.cloase_btn)


        self.horizontalLayout_2.addLayout(self.horizontalLayout)


        self.verticalLayout.addWidget(self.widget)

        self.widget_2 = QWidget(MainWindowsForm)
        self.widget_2.setObjectName(u"widget_2")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.widget_2.sizePolicy().hasHeightForWidth())
        self.widget_2.setSizePolicy(sizePolicy)
        self.widget_2.setLayoutDirection(Qt.LayoutDirection.LeftToRight)
        self.verticalLayout_5 = QVBoxLayout(self.widget_2)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.verticalLayout_4 = QVBoxLayout()
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.label_2 = QLabel(self.widget_2)
        self.label_2.setObjectName(u"label_2")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Preferred)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.label_2.sizePolicy().hasHeightForWidth())
        self.label_2.setSizePolicy(sizePolicy1)

        self.horizontalLayout_3.addWidget(self.label_2)

        self.horizontalSpacer_2 = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_2)


        self.verticalLayout_2.addLayout(self.horizontalLayout_3)

        self.input_edit = QTextEdit(self.widget_2)
        self.input_edit.setObjectName(u"input_edit")

        self.verticalLayout_2.addWidget(self.input_edit)


        self.verticalLayout_4.addLayout(self.verticalLayout_2)

        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.label_3 = QLabel(self.widget_2)
        self.label_3.setObjectName(u"label_3")

        self.horizontalLayout_4.addWidget(self.label_3)

        self.horizontalSpacer_3 = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_4.addItem(self.horizontalSpacer_3)


        self.verticalLayout_3.addLayout(self.horizontalLayout_4)

        self.output_edit = QTextEdit(self.widget_2)
        self.output_edit.setObjectName(u"output_edit")

        self.verticalLayout_3.addWidget(self.output_edit)


        self.verticalLayout_4.addLayout(self.verticalLayout_3)


        self.verticalLayout_5.addLayout(self.verticalLayout_4)


        self.verticalLayout.addWidget(self.widget_2)

        self.widget_3 = QWidget(MainWindowsForm)
        self.widget_3.setObjectName(u"widget_3")
        self.widget_3.setStyleSheet(u"")
        self.horizontalLayout_5 = QHBoxLayout(self.widget_3)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.horizontalSpacer_5 = QSpacerItem(92, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_5.addItem(self.horizontalSpacer_5)

        self.btn_c1 = QPushButton(self.widget_3)
        self.Ai_Btn_Group = QButtonGroup(MainWindowsForm)
        self.Ai_Btn_Group.setObjectName(u"Ai_Btn_Group")
        self.Ai_Btn_Group.addButton(self.btn_c1)
        self.btn_c1.setObjectName(u"btn_c1")
        sizePolicy1.setHeightForWidth(self.btn_c1.sizePolicy().hasHeightForWidth())
        self.btn_c1.setSizePolicy(sizePolicy1)
        self.btn_c1.setCheckable(True)
        self.btn_c1.setChecked(True)

        self.horizontalLayout_5.addWidget(self.btn_c1)

        self.btn_c2 = QPushButton(self.widget_3)
        self.Ai_Btn_Group.addButton(self.btn_c2)
        self.btn_c2.setObjectName(u"btn_c2")
        sizePolicy1.setHeightForWidth(self.btn_c2.sizePolicy().hasHeightForWidth())
        self.btn_c2.setSizePolicy(sizePolicy1)
        self.btn_c2.setCheckable(True)

        self.horizontalLayout_5.addWidget(self.btn_c2)

        self.btn_c3 = QPushButton(self.widget_3)
        self.Ai_Btn_Group.addButton(self.btn_c3)
        self.btn_c3.setObjectName(u"btn_c3")
        sizePolicy1.setHeightForWidth(self.btn_c3.sizePolicy().hasHeightForWidth())
        self.btn_c3.setSizePolicy(sizePolicy1)
        self.btn_c3.setCheckable(True)

        self.horizontalLayout_5.addWidget(self.btn_c3)

        self.btn_c6 = QPushButton(self.widget_3)
        self.Ai_Btn_Group.addButton(self.btn_c6)
        self.btn_c6.setObjectName(u"btn_c6")
        self.btn_c6.setCheckable(True)

        self.horizontalLayout_5.addWidget(self.btn_c6)

        self.btn_c4 = QPushButton(self.widget_3)
        self.Ai_Btn_Group.addButton(self.btn_c4)
        self.btn_c4.setObjectName(u"btn_c4")
        sizePolicy1.setHeightForWidth(self.btn_c4.sizePolicy().hasHeightForWidth())
        self.btn_c4.setSizePolicy(sizePolicy1)
        self.btn_c4.setCheckable(True)

        self.horizontalLayout_5.addWidget(self.btn_c4)

        self.btn_c5 = QPushButton(self.widget_3)
        self.Ai_Btn_Group.addButton(self.btn_c5)
        self.btn_c5.setObjectName(u"btn_c5")
        sizePolicy1.setHeightForWidth(self.btn_c5.sizePolicy().hasHeightForWidth())
        self.btn_c5.setSizePolicy(sizePolicy1)
        self.btn_c5.setCheckable(True)

        self.horizontalLayout_5.addWidget(self.btn_c5)

        self.horizontalSpacer_4 = QSpacerItem(92, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_5.addItem(self.horizontalSpacer_4)


        self.verticalLayout.addWidget(self.widget_3)

        self.verticalLayout.setStretch(0, 1)
        self.verticalLayout.setStretch(1, 8)
        self.verticalLayout.setStretch(2, 1)

        self.retranslateUi(MainWindowsForm)

        QMetaObject.connectSlotsByName(MainWindowsForm)
    # setupUi

    def retranslateUi(self, MainWindowsForm):
        MainWindowsForm.setWindowTitle(QCoreApplication.translate("MainWindowsForm", u"Form", None))
        self.label.setText(QCoreApplication.translate("MainWindowsForm", u"AI\u952e\u76d8", None))
        self.top_btn.setText("")
        self.setting_btn.setText("")
        self.cloase_btn.setText("")
        self.label_2.setText(QCoreApplication.translate("MainWindowsForm", u"\u8f93\u5165\u6587\u672c:", None))
        self.input_edit.setHtml(QCoreApplication.translate("MainWindowsForm", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", None))
        self.label_3.setText(QCoreApplication.translate("MainWindowsForm", u"\u8f93\u51fa\u6587\u672c:", None))
        self.btn_c1.setText(QCoreApplication.translate("MainWindowsForm", u"\u4ee3\u7801\u4f18\u5316", None))
        self.btn_c2.setText(QCoreApplication.translate("MainWindowsForm", u"\u8f85\u52a9\u7406\u89e3", None))
        self.btn_c3.setText(QCoreApplication.translate("MainWindowsForm", u"\u62a5\u9519\u5206\u6790", None))
        self.btn_c6.setText(QCoreApplication.translate("MainWindowsForm", u"\u6587\u6863\u6ce8\u91ca", None))
        self.btn_c4.setText(QCoreApplication.translate("MainWindowsForm", u"\u4e00\u952e\u66ff\u6362", None))
        self.btn_c5.setText(QCoreApplication.translate("MainWindowsForm", u"\u91cd\u65b0\u5f00\u59cb", None))
    # retranslateUi

