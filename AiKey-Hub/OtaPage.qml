import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Rectangle {
    id: root
    color: Theme.panel

    /* ---------- 文件选择对话框 ---------- */
    FileDialog {
        id: fileDialog
        title: "选择固件文件"
        nameFilters: ["固件文件 (*.bin)"]
        defaultSuffix: "bin"

        onAccepted: function () {
            OtaBackend.selectFile(String(fileDialog.selectedFile))
        }
    }

    Rectangle {
        width: 128
        height: 36
        color: Theme.panel

        Text {
            anchors.centerIn: parent
            text: "OTA升级"
            color: Theme.text
            font.family: Theme.fontFamily
            font.pixelSize: 14
            font.bold: true
        }
    }

    Item {
        anchors.fill: parent
        anchors.topMargin: 58
        anchors.leftMargin: 16
        anchors.rightMargin: 28
        anchors.bottomMargin: 32

        RowLayout {
            anchors.fill: parent
            spacing: 16

            /* ============= 左侧：固件信息 ============= */
            Rectangle {
                Layout.preferredWidth: 330
                Layout.fillHeight: true
                radius: 8
                color: "#080D14"
                border.color: "#334155"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 18

                    Text {
                        text: "固件升级"
                        color: Theme.text
                        font.family: Theme.fontFamily
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        Layout.fillWidth: true
                        text: "选择本地固件包并将键盘升级到新版本。升级过程中请保持设备连接。"
                        color: Theme.muted
                        font.family: Theme.fontFamily
                        font.pixelSize: 13
                        wrapMode: Text.WordWrap
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 200
                        radius: 8
                        color: "#101722"
                        border.color: "#253044"

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 20
                            spacing: 12

                            VersionInfo {
                                label: "设备状态"
                                value: OtaBackend.deviceState
                            }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 1
                                color: "#253044"
                            }
                            VersionInfo {
                                label: "当前固件"
                                value: OtaBackend.currentVersion
                            }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 1
                                color: "#253044"
                            }
                            VersionInfo {
                                label: "可用版本"
                                value: OtaBackend.availableVersion
                            }
                        }
                    }

                    Item { Layout.fillHeight: true }
                }
            }

            /* ============= 右侧：升级操作 ============= */
            Rectangle {
                Layout.preferredWidth: 500
                Layout.fillHeight: true
                radius: 8
                color: "#080D14"
                border.color: "#334155"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 18

                    Text {
                        text: "升级操作"
                        color: Theme.text
                        font.family: Theme.fontFamily
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        text: "固件文件"
                        color: Theme.muted
                        font.family: Theme.fontFamily
                        font.pixelSize: 13
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 12

                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 42
                            radius: 5
                            color: Theme.field
                            border.color: "#39465A"

                            Text {
                                anchors.fill: parent
                                anchors.leftMargin: 14
                                anchors.rightMargin: 14
                                verticalAlignment: Text.AlignVCenter
                                text: OtaBackend.firmwareFile.length > 0
                                    ? OtaBackend.firmwareFile
                                    : "请选择 .bin 固件文件"
                                color: OtaBackend.firmwareFile.length > 0
                                    ? Theme.text
                                    : Theme.dimText
                                font.family: Theme.fontFamily
                                font.pixelSize: 13
                                elide: Text.ElideMiddle
                            }
                        }

                        AppButton {
                            Layout.preferredWidth: 104
                            Layout.preferredHeight: 42
                            text: "选择文件"
                            active: true
                            onClicked: fileDialog.open()
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 118
                        radius: 8
                        color: "#101722"
                        border.color: "#253044"

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 18
                            spacing: 10

                            RowLayout {
                                Layout.fillWidth: true

                                Text {
                                    text: "升级进度"
                                    color: Theme.text
                                    font.family: Theme.fontFamily
                                    font.pixelSize: 14
                                    font.bold: true
                                }

                                Item { Layout.fillWidth: true }

                                Text {
                                    text: Math.round(OtaBackend.progress * 100) + "%"
                                    color: Theme.muted
                                    font.family: Theme.fontFamily
                                    font.pixelSize: 13
                                }
                            }

                            ProgressBar {
                                id: upgradeProgress
                                Layout.fillWidth: true
                                Layout.preferredHeight: 8
                                value: OtaBackend.progress

                                background: Rectangle {
                                    radius: 4
                                    color: "#283140"
                                }

                                contentItem: Item {
                                    Rectangle {
                                        width: parent.width
                                               * upgradeProgress.visualPosition
                                        height: parent.height
                                        radius: 4
                                        color: Theme.blue
                                    }
                                }
                            }

                            Text {
                                text: OtaBackend.statusText
                                color: Theme.dimText
                                font.family: Theme.fontFamily
                                font.pixelSize: 12
                                elide: Text.ElideRight
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 12

                        Item { Layout.fillWidth: true }

                        AppButton {
                            Layout.preferredWidth: 112
                            Layout.preferredHeight: 38
                            text: "检查更新"
                            normalColor: Theme.key
                            borderColor: "#465268"
                            enabled: !OtaBackend.busy
                            onClicked: OtaBackend.checkUpdate()
                        }

                        AppButton {
                            Layout.preferredWidth: 128
                            Layout.preferredHeight: 38
                            text: "开始升级"
                            active: true
                            enabled: !OtaBackend.busy
                            onClicked: OtaBackend.startUpgrade()
                        }
                    }

                    Text {
                        Layout.fillWidth: true
                        text: "注意：升级期间请勿关闭应用、断开键盘或拔出数据线。"
                        color: Theme.warning
                        font.family: Theme.fontFamily
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignRight
                        wrapMode: Text.WordWrap
                    }

                    Item { Layout.fillHeight: true }
                }
            }

            Item { Layout.fillWidth: true }
        }
    }

    /* ================== 子组件 ================== */

    component VersionInfo: ColumnLayout {
        property string label: ""
        property string value: ""

        Layout.fillWidth: true
        spacing: 6

        Text {
            text: label
            color: Theme.muted
            font.family: Theme.fontFamily
            font.pixelSize: 12
        }

        Text {
            text: value
            color: Theme.text
            font.family: Theme.fontFamily
            font.pixelSize: 16
            font.bold: true
        }
    }

    component AppButton: Button {
        id: control

        property bool active: false
        property color normalColor: active ? Theme.blue : Theme.field
        property color borderColor: active ? Theme.blue : "#465268"

        font.family: Theme.fontFamily
        font.pixelSize: 13

        contentItem: Text {
            text: control.text
            color: control.enabled ? Theme.text : Theme.dimText
            font: control.font
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            radius: 5
            color: !control.enabled
                ? Theme.field
                : control.down
                    ? Qt.darker(control.normalColor, 1.15)
                    : control.normalColor
            border.color: control.enabled ? control.borderColor : "#1E293B"
        }
    }
}
