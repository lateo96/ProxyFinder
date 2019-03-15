import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

ItemDelegate {
    id: root

    Label {
        id: labelCopied
        anchors.fill: parent
        text: qsTr("IP copied")
        font.pointSize: Qt.application.font.pointSize * 1.5
        color: Material.primaryHighlightedTextColor
        opacity: 0.0
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter

        background: Rectangle {
            color: Material.accent
        }

        SequentialAnimation on opacity {
            id: animationCopy
            running: false
            NumberAnimation { to: 1.0; duration: 300 }
            PauseAnimation  { duration: 800 }
            NumberAnimation { to: 0.0; duration: 500 }
        }

        function flash() {
            animationCopy.start()
        }
    }

    contentItem: RowLayout {
        Label {
            id: labelIP
            text: model.modelData.hostName
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            Layout.preferredWidth: internalLabelIPWidth
        }
        Label {
            id: labelCode
            text: model.modelData.httpStatusCode
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            Layout.preferredWidth: internalLabelCodeWidth
        }
        Label {
            id: labelPhrase
            text: model.modelData.httpReasonPhrase
            Layout.fillWidth: true
        }
    } // contentItem (RowLayout)

    onClicked: {
        appManager.toClipboard(labelIP.text)
        labelCopied.flash()
    }
} // delegate (ItemDelegate)
