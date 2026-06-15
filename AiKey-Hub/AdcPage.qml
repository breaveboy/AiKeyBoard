import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: Theme.panel
    property int selectedIndex: 0
    property int selectedRaw: DebugBackend.adcRaw.length > selectedIndex
        ? DebugBackend.adcRaw[selectedIndex] : 0
    property int selectedFiltered: DebugBackend.adcFiltered.length > selectedIndex
        ? DebugBackend.adcFiltered[selectedIndex] : 0
    readonly property int rowLabelWidth: 54
    readonly property int cellWidth: 62
    readonly property int cellSpacing: 6
    readonly property int tableWidth: rowLabelWidth + 14 * cellWidth + 14 * cellSpacing

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 14

        RowLayout {
            Layout.fillWidth: true

            ColumnLayout {
                spacing: 3

                Text {
                    text: "ADC矩阵监控"
                    color: Theme.text
                    font.family: Theme.fontFamily
                    font.pixelSize: 20
                    font.bold: true
                }

                Text {
                    text: "每个格子同时显示 原始ADC / 滤波ADC"
                    color: Theme.muted
                    font.family: Theme.fontFamily
                    font.pixelSize: 12
                }

                Text {
                    Layout.maximumWidth: 720
                    text: "ADC文件：" + DebugBackend.adcFile
                    color: Theme.dimText
                    font.family: Theme.fontFamily
                    font.pixelSize: 11
                    elide: Text.ElideMiddle
                }
            }

            Item { Layout.fillWidth: true }

            Text {
                text: DebugBackend.adcStatus
                color: DebugBackend.adcStatus === "ADC数据正常"
                    ? "#22C55E"
                    : Theme.warning
                font.family: Theme.fontFamily
                font.pixelSize: 12
            }

            Button {
                text: DebugBackend.adcDisplayPaused ? "继续ADC" : "暂停ADC"
                focusPolicy: Qt.NoFocus
                onClicked: DebugBackend.toggleAdcDisplayPause()
            }

            Button {
                text: "记录快照"
                focusPolicy: Qt.NoFocus
                onClicked: DebugBackend.recordAdcSnapshot()
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 8
            color: "#080D14"
            border.color: "#334155"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 14
                spacing: 10

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 48
                    radius: 5
                    color: "#101722"
                    border.color: "#253044"

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 14
                        anchors.rightMargin: 14

                        Text {
                            text: "选中 R" + Math.floor(root.selectedIndex / 14)
                                + " C" + (root.selectedIndex % 14)
                            color: Theme.text
                            font.family: Theme.fontFamily
                            font.bold: true
                        }

                        Item { Layout.fillWidth: true }

                        Text {
                            text: "原始 " + root.selectedRaw
                                + "   滤波 " + root.selectedFiltered
                                + "   差值 " + (root.selectedRaw - root.selectedFiltered)
                            color: "#93C5FD"
                            font.family: "Consolas"
                            font.pixelSize: 13
                        }
                    }
                }

                Flickable {
                    id: tableFlick
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    contentWidth: root.tableWidth
                    contentHeight: tableColumn.implicitHeight
                    clip: true
                    boundsBehavior: Flickable.StopAtBounds

                    ScrollBar.horizontal: ScrollBar {
                        policy: ScrollBar.AsNeeded
                    }

                    Column {
                        id: tableColumn
                        width: root.tableWidth
                        spacing: 8

                        Row {
                            spacing: root.cellSpacing

                            LabelCell {
                                width: root.rowLabelWidth
                                height: 36
                                text: "行/列"
                                accent: true
                            }

                            Repeater {
                                model: 14

                                LabelCell {
                                    width: root.cellWidth
                                    height: 36
                                    text: "C" + index
                                }
                            }
                        }

                        Repeater {
                            model: 5

                            Row {
                                id: rowDelegate
                                required property int index
                                spacing: root.cellSpacing

                                LabelCell {
                                    width: root.rowLabelWidth
                                    height: 58
                                    text: "R" + rowDelegate.index
                                    accent: true
                                }

                                Repeater {
                                    model: 14

                                    AdcCell {
                                        required property int index
                                        width: root.cellWidth
                                        height: 58
                                        property int dataIndex: rowDelegate.index * 14 + index
                                        rawValue: DebugBackend.adcRaw.length > dataIndex
                                            ? DebugBackend.adcRaw[dataIndex] : 0
                                        filteredValue: DebugBackend.adcFiltered.length > dataIndex
                                            ? DebugBackend.adcFiltered[dataIndex] : 0
                                        selected: root.selectedIndex === dataIndex
                                        onClicked: root.selectedIndex = dataIndex
                                    }
                                }
                            }
                        }
                    }
                }

                Text {
                    Layout.fillWidth: true
                    text: DebugBackend.adcFrameReady
                        ? "完整矩阵约每200毫秒刷新一次。数值为0的格子可能是无效键位。"
                        : "尚未收到完整ADC矩阵。请确认MCU已烧录包含F3/10~14和F3/20~24命令的新固件。"
                    color: Theme.dimText
                    font.family: Theme.fontFamily
                    font.pixelSize: 11
                    horizontalAlignment: Text.AlignRight
                }
            }
        }
    }

    component LabelCell: Rectangle {
        property alias text: label.text
        property bool accent: false

        radius: 4
        color: accent ? "#172554" : "#111827"

        Text {
            id: label
            anchors.centerIn: parent
            color: accent ? "#93C5FD" : Theme.muted
            font.family: Theme.fontFamily
            font.pixelSize: 11
            font.bold: true
        }
    }

    component AdcCell: Rectangle {
        signal clicked()
        property int rawValue: 0
        property int filteredValue: 0
        property bool selected: false

        radius: 5
        color: rawValue === 0 && filteredValue === 0 ? "#111827" : "#101C2C"
        border.width: selected ? 2 : 1
        border.color: selected
            ? Theme.blue
            : (rawValue === 0 && filteredValue === 0 ? "#1F2937" : "#334155")

        Column {
            anchors.centerIn: parent
            spacing: 2

            Text {
                text: "原 " + rawValue
                color: rawValue === 0 ? Theme.dimText : "#F8FAFC"
                font.family: "Consolas"
                font.pixelSize: 11
                font.bold: true
            }

            Text {
                text: "滤 " + filteredValue
                color: filteredValue === 0 ? Theme.dimText : "#93C5FD"
                font.family: "Consolas"
                font.pixelSize: 11
                font.bold: true
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: parent.clicked()
        }
    }
}
