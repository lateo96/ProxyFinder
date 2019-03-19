import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtQuick.Templates 2.12 as T

Popup {
    id: root

    closePolicy: Popup.NoAutoClose
    Material.theme: Material.Light

    background: Rectangle {
        radius: 2
        color: "transparent"
    }

    T.Overlay.modal: Rectangle {
        color: Material.theme === Material.Light ? "#DD000000" : "#DDFFFFFF"
        Behavior on opacity { NumberAnimation { duration: 150 } }
    }

    T.Overlay.modeless: Rectangle {
        color: Material.theme === Material.Light ? "#DD000000" : "#DDFFFFFF"
        Behavior on opacity { NumberAnimation { duration: 150 } }
    }

    Label {
        id: subMessage
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 100
        Material.theme: parent.Material.theme === Material.Light ? Material.Dark : Material.Light
        text: qsTr("Waiting for network...")
        font.pointSize: 14
        font.italic: true
        color: Material.color(Material.Pink)
    }

    RowLayout {
        anchors.centerIn: parent
        spacing: 250

        Image {
            id: imageUser
            source: "qrc:/images/network-pc.svg"
            sourceSize: "64x64"
        }

        Image {
            id: imageNetwork
            source: "qrc:/images/network-online.svg"
            sourceSize: "64x64"
        }
    }

    Image {
        id: imageLineUpLeft
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 0
        source: "qrc:/images/line.svg"
        sourceSize: "64x64"
    }
    Image {
        id: imageLineBottomRight
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 9
        source: "qrc:/images/line.svg"
        sourceSize: "64x64"
    }

    Image {
        id: imageCross
        anchors.centerIn: parent
        source: "qrc:/images/close.svg"
        sourceSize: "24x24"
    }

    SequentialAnimation {
        running: true
        loops: Animation.Infinite
        ParallelAnimation {
            NumberAnimation { target: imageLineUpLeft; duration: 200; property: "anchors.horizontalCenterOffset"; from: -100; to: -65 }
            NumberAnimation { target: imageLineUpLeft; duration: 200; property: "opacity"; from: 0.0; to: 1.0 }
            NumberAnimation { target: imageLineBottomRight; duration: 200; property: "anchors.horizontalCenterOffset"; from: 100; to: 65 }
            NumberAnimation { target: imageLineBottomRight; duration: 200; property: "opacity"; from: 0.0; to: 1.0 }
        }
        ParallelAnimation {
            NumberAnimation { target: imageLineUpLeft; duration: 200; property: "anchors.horizontalCenterOffset"; from: -65; to: -30 }
            NumberAnimation { target: imageLineUpLeft; duration: 200; property: "opacity"; from: 1.0; to: 0.0 }
            NumberAnimation { target: imageLineBottomRight; duration: 200; property: "anchors.horizontalCenterOffset"; from: 65; to: 30 }
            NumberAnimation { target: imageLineBottomRight; duration: 200; property: "opacity"; from: 1.0; to: 0.0 }
            SequentialAnimation {
                ParallelAnimation {
                    NumberAnimation { target: imageCross; duration: 100; property: "opacity"; from: 0.0; to: 1.0 }
                    NumberAnimation { target: imageCross; duration: 100; property: "scale"; from: 0.8; to: 1.0 }
                }
                ParallelAnimation {
                    NumberAnimation { target: imageCross; duration: 100; property: "opacity"; from: 1.0; to: 0.0 }
                    NumberAnimation { target: imageCross; duration: 100; property: "scale"; from: 1.0; to: 0.8 }
                }
            } // SequentialAnimation
        } // ParallelAnimation
        PropertyAction { target: imageLineUpLeft; property: "anchors.horizontalCenterOffset"; value: -100 }
    } // SequentialAnimation
}
