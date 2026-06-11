import QtQuick
import QtQuick.Controls

Window {
    width: 920
    height: 600
    visible: true
    title: "OTA 升级"
    color: "#030712"

    OtaPage {
        anchors.fill: parent
    }
}
