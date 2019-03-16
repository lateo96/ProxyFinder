import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Dialog {
    id: root

    title: qsTr("Warning")
    standardButtons: Dialog.Yes | Dialog.No

    RowLayout {
        spacing: 20

        Image {
            source: "qrc:/images/warning.svg"
            sourceSize: "64x64"
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        }
        Label {
            id: labelMsg
            text: qsTr("The final IP address must be greater or equal than the " +
                       "initial IP address in order to scan. <b><i>Swap them?</i></b>");
            wrapMode: Label.WordWrap
            Layout.fillWidth: true
            Layout.preferredWidth: 200
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        }
    } // Layout
}
