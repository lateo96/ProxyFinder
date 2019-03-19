import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

// My imports
import ProxyFinder 0.2

Page {
    id: root

    property alias proxyConfig: proxyConfig    
    property int status: finder.status
    onStatusChanged: {
        switch (status) {
        case 0: // ReadyFirstTime
            break
        case 1: // GettingAddresses
            break
        case 2: // SettingCheckers
            progress.Material.accent = Material.Green
            break
        case 3: // Scaning
            progress.noAnimate = true
            progress.value = 0
            progress.noAnimate = false
            progress.Material.accent = appWindow.Material.accent
            break
        case 4: // FinishedAndReady
            finished()
            progress.noAnimate = true
            progress.value = 0
            progress.noAnimate = false
            break
        case 5: // AbortedAndReady
        }
    }

    //! Functions
    function scan() {
        statusBarCustom.clearMessage()
        finder.initialAddress = proxyConfig.initialIP
        finder.finalAddress = proxyConfig.finalIP
        finder.port = ~~proxyConfig.port
        finder.maxThreads = advancedNetworkConfig.maxThreads
        finder.timeout = advancedNetworkConfig.timeout
        finder.requestType = advancedNetworkConfig.requestType
        finder.requestUrl = advancedNetworkConfig.requestUrl
        finder.start()
    }

    //! Signals
    signal finished()

    onFinished: {
        //statusBarCustom.showMessage("qrc:/images/done-green.svg", qsTr("Done!"), 10000)
        appWindow.alert(0)
    }

    //! Content
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 30

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 20

            ProxyConfig {
                id: proxyConfig
                enabled: !finder.running
                clip: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
            }

            Item { // to add later graphics effects
                Layout.fillWidth: true
                height: buttonScan.height
                ButtonScan {
                    id: buttonScan
                    anchors.fill: parent
                    text: qsTr("Scan")
                    highlighted: true
                    enabled: !finder.running && proxyConfig.valid

                    onClicked: {
                        if (finder.addressesAreInverted()) {
                            dialogReorderIPs.open()
                        } else {
                            scan()
                        }
                    }

                    onEnabledChanged: {
                        if (enabled && dialogConfirmExit.visible) {
                            dialogConfirmExit.close()
                        }
                    }
                } // ButtonScan
            } // Item

            ProgressBar {
                id: progress
                indeterminate: buttonScan.enabled && !networkUnavailable.visible
                Layout.fillWidth: true

                property bool noAnimate: false

                Behavior on value { NumberAnimation { duration: progress.noAnimate ? 0 : 100 } }

                Timer {
                    id: timerProgressUpdater
                    interval: finder.scaning ? 250 : 100
                    repeat: true
                    running: finder.running

                    onTriggered: {
                        progress.value = finder.progress
                        statusBarCustom.progressTotal = finder.progressTotal
                        statusBarCustom.progressPartial = finder.progressPartial
                    }
                }
            } // ProgressBar
        } // ColumnLayout


        Label {
            id: headerLabel
            text: qsTr("Report")
            font.pointSize: Qt.application.font.pointSize * 2
            Layout.fillWidth: true
        }


        Report {
            id: report
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    } // ColumnLayout (root)
}
