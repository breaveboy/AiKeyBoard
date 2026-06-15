import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    color: Theme.panel

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 14

        RowLayout {
            Layout.fillWidth: true

            ColumnLayout {
                spacing: 3

                Text {
                    text: "键盘运行日志"
                    color: Theme.text
                    font.family: Theme.fontFamily
                    font.pixelSize: 20
                    font.bold: true
                }

                Text {
                    text: "通过 Custom HID 读取扫描、DMA、按键和 USB 状态"
                    color: Theme.muted
                    font.family: Theme.fontFamily
                    font.pixelSize: 12
                }

                Text {
                    Layout.maximumWidth: 560
                    text: "日志文件：" + DebugBackend.logFile
                    color: Theme.dimText
                    font.family: Theme.fontFamily
                    font.pixelSize: 11
                    elide: Text.ElideMiddle
                }
            }

            Item { Layout.fillWidth: true }

            Text {
                text: "设备：" + DebugBackend.connection
                color: DebugBackend.connection === "已连接" ? "#22C55E" : Theme.warning
                font.family: Theme.fontFamily
                font.pixelSize: 13
            }

            Button {
                text: DebugBackend.displayPaused ? "继续显示" : "暂停显示"
                onClicked: DebugBackend.toggleDisplayPause()
            }

            Button {
                text: "清除日志"
                onClicked: DebugBackend.clearLog()
            }

            Button {
                text: "清除计数"
                enabled: DebugBackend.connection === "已连接"
                onClicked: DebugBackend.clearCounters()
            }
        }

        GridLayout {
            Layout.fillWidth: true
            columns: 5
            columnSpacing: 10
            rowSpacing: 10

            MetricCard { title: "运行时间"; value: DebugBackend.uptime }
            MetricCard { title: "主循环"; value: DebugBackend.mainCount }
            MetricCard { title: "DMA中断"; value: DebugBackend.dmaCount }
            MetricCard { title: "扫描帧"; value: DebugBackend.frameCount }
            MetricCard { title: "按键变化"; value: DebugBackend.keyChangeCount }
            MetricCard { title: "USB提交"; value: DebugBackend.usbCount }
            MetricCard { title: "当前行"; value: DebugBackend.currentRow }
            MetricCard { title: "运行状态"; value: DebugBackend.stateFlags }
            MetricCard {
                Layout.columnSpan: 2
                title: "最近错误"
                value: DebugBackend.errorText
                valueColor: DebugBackend.errorText === "无" ? "#22C55E" : "#EF4444"
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 8
            color: "#080D14"
            border.color: "#334155"

            ScrollView {
                anchors.fill: parent
                anchors.margins: 10

                TextArea {
                    text: DebugBackend.logText
                    readOnly: true
                    selectByMouse: true
                    color: "#CBD5E1"
                    selectionColor: Theme.blue
                    font.family: "Consolas"
                    font.pixelSize: 12
                    wrapMode: TextEdit.NoWrap
                    background: null
                    onTextChanged: cursorPosition = length
                }
            }
        }
    }

    component MetricCard: Rectangle {
        property string title: ""
        property string value: ""
        property color valueColor: Theme.text

        Layout.fillWidth: true
        Layout.preferredHeight: 78
        radius: 7
        color: "#101722"
        border.color: "#253044"

        Column {
            anchors.fill: parent
            anchors.margins: 12
            spacing: 7

            Text {
                text: parent.parent.title
                color: Theme.muted
                font.family: Theme.fontFamily
                font.pixelSize: 11
            }

            Text {
                width: parent.width
                text: parent.parent.value
                color: parent.parent.valueColor
                font.family: Theme.fontFamily
                font.pixelSize: 15
                font.bold: true
                elide: Text.ElideRight
            }
        }
    }
}
