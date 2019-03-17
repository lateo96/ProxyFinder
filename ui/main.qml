import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

// My imports
import ProxyFinder 0.2

ApplicationWindow {
    id: appWindow
    visible: true
    width: 640
    height: 580
    title: Qt.application.name + ' ' + Qt.application.version

    //! Properties
    property int status: finder.status
    onStatusChanged: {
        switch (status) {
        case 0: // ReadyFirstTime
            console.log('ReadyFirstTime')
            break
        case 1: // GettingAddresses
            console.log('GettingAddresses')
            break
        case 2: // SettingCheckers
            console.log('SettingCheckers')
            progress.Material.accent = Material.Green
            break
        case 3: // Scaning
            console.log('Scaning')
            progress.noAnimate = true
            progress.value = 0
            progress.noAnimate = false
            progress.Material.accent = appWindow.Material.accent
            break
        case 4: // FinishedAndReady
            console.log('FinishedAndReady')
            finished()
            break
        case 5: // AbortedAndReady
            console.log('AbortedAndReady')
        }
    }

    //! Backend
    ApplicationManager {
        id: appManager
        objectName: "appManager"
    }

    //! Functions
    function scan() {
        statusBarCustom.clearMessage()
        finder.initialAddress = groupBoxConfigureProxy.initialIP
        finder.finalAddress = groupBoxConfigureProxy.finalIP
        finder.port = ~~groupBoxConfigureProxy.port
        finder.maxThreads = advancedNetworkConfig.maxThreads
        finder.timeout = advancedNetworkConfig.timeout
        finder.requestType = advancedNetworkConfig.requestType
        finder.requestUrl = advancedNetworkConfig.requestUrl
        finder.start()
    }

    //! Signals
    signal finished()

    //! Events
    onClosing: {
        if (finder.scaning) {
            dialogConfirmExit.open()
            close.accepted = false
        }
    }

    onFinished: {
        //statusBarCustom.showMessage("qrc:/images/done-green.svg", qsTr("Done!"), 10000)
        appWindow.alert(0)
    }

    //! Menu and status bars
    menuBar: MenuBar {
        property color iconColor: "transparent"
        Menu {
            title: qsTr("&Tools")
            MenuItem { text: qsTr("&Advanced network options"); enabled: !finder.scaning; icon.source: "qrc:/images/network-settings.svg"; icon.color: menuBar.iconColor; onTriggered: advancedNetworkConfig.open() }
            MenuSeparator { }
            MenuItem { text: qsTr("&Quit"); icon.source: "qrc:/images/close.svg"; icon.color: menuBar.iconColor; onTriggered: appWindow.close() }
        }
        Menu {
            title: qsTr("&Help")
            MenuItem { id: app; text: qsTr("&Proxy finder"); icon.source: "qrc:/images/appIcon.svg"; icon.color: menuBar.iconColor; onTriggered: dialogAbout.open() }
            MenuItem { text: qsTr("&Qt"); icon.source: "qrc:/images/qt_logo_green_rgb_256x256.png"; icon.color: menuBar.iconColor; onTriggered: dialogAboutQt.open() }
        }
        Menu {
            title: qsTr("&Language")
            MenuItem { text: qsTr("&English"); icon.source: "qrc:/images/en.svg"; icon.color: "transparent" }
            MenuItem { text: qsTr("&Spanish"); icon.source: "qrc:/images/es.svg"; icon.color: "transparent"; enabled: false }
        }
    }

    // Built with Qt logo
    Image {
        anchors.top: parent.top
        anchors.topMargin: -menuBar.height + 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        z: 2
        source: "qrc:/images/Built_with_Qt_RGB_logo.svg"
        sourceSize: Qt.size(menuBar.height, menuBar.height - 16)
        fillMode: Image.PreserveAspectFit

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                dialogAboutQt.open()
            }
        }
    }

    footer: CustomStatusBar {
        id: statusBarCustom
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
                id: groupBoxConfigureProxy
                enabled: !finder.running
                clip: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
            }

            ButtonScan {
                id: buttonScan
                text: qsTr("Scan")
                highlighted: true
                enabled: !finder.running && groupBoxConfigureProxy.valid
                Layout.fillWidth: true

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

            ProgressBar {
                id: progress
                indeterminate: buttonScan.enabled
                Material.accent: !groupBoxConfigureProxy.valid ? Material.Pink : appWindow.Material.accent
                Layout.fillWidth: true

                property bool noAnimate: false

                Behavior on value { NumberAnimation { duration: progress.noAnimate ? 0 : 100 } }

                Timer {
                    id: timerProgressUpdater
                    interval: 100
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

    //! Dialogs
    AdvancedNetworkConfig {
        id: advancedNetworkConfig
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
    }

    DialogAbout {
        id: dialogAbout
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
    }

    DialogAboutQt {
        id: dialogAboutQt
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
    }

    // TODO: Auto-closing this dialog is done when the "SCAN" button is enabled,
    // and it shouldn't be implemented there.
    DialogConfirmExit {
        id: dialogConfirmExit
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true

        onAccepted: {
            // FIX: The app crashes
            finder.clean()
            finder.terminate()
            appWindow.close()
        }
    }

    DialogReorderIPs {
        id: dialogReorderIPs
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true

        onAccepted: {
            groupBoxConfigureProxy.swapIPs()
            scan()
        }
    }

    PopupScaning {
        anchors.centerIn: Overlay.overlay
        //        visible: true
        modal: true
        focus: true
    }
}
