import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Dialog {
    id: root

    standardButtons: Dialog.Yes | Dialog.No
    contentItem: RowLayout {
        BusyIndicator {
            id: busyIndicator
        }
        Label {
            id: labelMsg
            text: qsTr("Scaning in progress. <b>Abort?</b>");
            font.italic: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
        }
    }
}
