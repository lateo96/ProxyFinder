import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

ItemDelegate {
    id: root

    Rectangle {
        id: rectangleHighlight
        anchors.fill: parent
        color: model.modelData.httpStatusCode === 0 ? "#5041cd52" : "transparent"
        z: -1
    }

    Rectangle {
        id: rectangleCopied
        anchors.fill: parent
        color: Material.accent
        opacity: 0.0

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

        RowLayout {
            anchors.centerIn: parent
            spacing: 10

            Image {
                source: "qrc:/images/clipboard.svg"
                sourceSize: Qt.size(labelCopied.height, labelCopied.height)
            }

            Label {
                id: labelCopied
                text: qsTr("IP copied")
                font.pointSize: Qt.application.font.pointSize * 1.5
                color: Material.primaryHighlightedTextColor
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
            }
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
        rectangleCopied.flash()
    }
} // delegate (ItemDelegate)
