import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Popup {
    id: root

    /*RowLayout {
        BusyIndicator {
            id: busyIndicator
        }
        Label {
            id: labelMsg
            text: qsTr("Scaning");
            font.italic: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
        }
    }
    */

    contentItem: Label {
        color: "red"
        text: qsTr("This application is still <i><b>unstable</b></i>.<br>" +
                   "In <i><b>alpha</b></i> stage.")
        font.pointSize: 16
    }
}
