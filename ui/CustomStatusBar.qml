import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Page {
    id: root

    //! Properties
    property int progressTotal: 0
    property int progressPartial: 0
    property string messageImageSource;
    property string message;

    //! Functions
    function showMessage(imageSrc, messageToShow, timeout) {
        messageImageSource = imageSrc
        message = messageToShow
        rowLayoutMessage.clearMessage(timeout)
    }

    function clearMessage() {
        rowLayoutMessage.clearMessage(0)
    }

    implicitHeight: rowLayoutRoot.implicitHeight + topPadding + bottomPadding
    leftPadding: 10
    rightPadding: 10

    Material.background: !groupBoxConfigureProxy.valid ? Material.Pink : parent.Material.background

    RowLayout {
        id: rowLayoutRoot
        RowLayout {
            id: rowLayoutStatus
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft
            Layout.preferredWidth: 150

            Label {
                text: qsTr("Status:")
                horizontalAlignment: Label.AlignLeft | Label.AlignVCenter
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            }
            Label {
                id: labelStatus
                text: finder.gettingAddresses ? qsTr("Initializing") :
                                                finder.settingCheckers ? qsTr("Addressing") :
                                                                         finder.scaning ? qsTr("Scaning") :
                                                                                          !groupBoxConfigureProxy.valid ? qsTr("Invalid") : qsTr("Ready")
                horizontalAlignment: Label.AlignLeft | Label.AlignVCenter
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            }
        } // RowLayout

        RowLayout {
            id: rowLayoutProgress
            visible: finder.running
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft

            Label {
                text: qsTr("Progress:")
                horizontalAlignment: Label.AlignLeft | Label.AlignVCenter
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            }
            Label {
                id: labelProgress
                text: progressPartial + '/' + progressTotal
                horizontalAlignment: Label.AlignLeft | Label.AlignVCenter
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            }
        } // RowLayout

        RowLayout {
            id: rowLayoutMessage
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft

            function clearMessage(timeout) {
                if (timerClearMsg.running) {
                    timerClearMsg.stop()
                }
                if (timeout > 0) {
                    timerClearMsg.interval = timeout
                    timerClearMsg.start()
                }
            }

            Timer {
                id: timerClearMsg

                onTriggered: {
                    message = ""
                    messageImageSource = ""
                }
            }

            Image {
                id: image
                source: messageImageSource
                sourceSize: Qt.size(root.implicitHeight, root.implicitHeaderHeight);
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            }
            Label {
                id: labelMessage
                text: message
                horizontalAlignment: Label.AlignLeft | Label.AlignVCenter
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            }
        } // RowLayout
    } // RowLayout
}
