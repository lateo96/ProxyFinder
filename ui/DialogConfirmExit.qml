import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Dialog {
    id: root

    title: qsTr("Confirm exit")
    standardButtons: Dialog.Yes | Dialog.No

    RowLayout {
        spacing: 10
        BusyIndicator {
            id: busyIndicator
            Material.accent: "#FB0000"
            implicitWidth: 128
            implicitHeight: implicitWidth

            Image {
                anchors.centerIn: parent
                source: "qrc:/images/close.svg"
                sourceSize: "48x48"
            }
        }
        Label {
            id: labelMsg
            text: qsTr("Scaning in progress. <b>Abort?</b>");
            font.italic: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
        }
    } // RowLayout
}
