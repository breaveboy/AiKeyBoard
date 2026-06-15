import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: window
    width: 1102
    height: 660
    minimumWidth: 1102
    minimumHeight: 560
    visible: true
    title: currentPage === 0
        ? "AiKeyBoard 运行日志"
        : currentPage === 1
            ? "AiKeyBoard ADC监控"
            : "AiKeyBoard OTA升级"
    color: "#030712"

    property int currentPage: 0

    Component.onCompleted: DebugBackend.setActive(true)
    onClosing: DebugBackend.setActive(false)

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 54
            color: "#080D14"
            border.color: "#1E293B"

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 18
                anchors.rightMargin: 18
                spacing: 8

                Text {
                    text: "AiKeyBoard"
                    color: Theme.text
                    font.family: Theme.fontFamily
                    font.pixelSize: 16
                    font.bold: true
                }

                Item { Layout.fillWidth: true }

                NavButton {
                    text: "运行日志"
                    selected: window.currentPage === 0
                    onClicked: window.openPage(0)
                }

                NavButton {
                    text: "ADC监控"
                    selected: window.currentPage === 1
                    onClicked: window.openPage(1)
                }

                NavButton {
                    text: "OTA升级"
                    selected: window.currentPage === 2
                    onClicked: window.openPage(2)
                }
            }
        }

        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: window.currentPage

            DebugPage {}
            AdcPage {}
            OtaPage {}
        }
    }

    function openPage(index) {
        if (currentPage === index)
            return
        DebugBackend.setActive(index !== 2)
        if (index !== 2)
            OtaBackend.closeConnection()
        currentPage = index
    }

    component NavButton: Button {
        id: control
        property bool selected: false

        implicitWidth: 104
        implicitHeight: 34

        contentItem: Text {
            text: control.text
            color: control.selected ? "#FFFFFF" : "#94A3B8"
            font.family: Theme.fontFamily
            font.pixelSize: 13
            font.bold: control.selected
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            radius: 5
            color: control.selected ? Theme.blue : "transparent"
            border.color: control.selected ? Theme.blue : "#334155"
        }
    }
}
