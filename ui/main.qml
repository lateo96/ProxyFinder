import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

// My imports
import ProxyFinder 0.2

ApplicationWindow {
    id: appWindow
    visible: true
    width: 640
    height: 580
    title: Qt.application.name + ' ' + Qt.application.version

    Material.theme: preferences.theme

    //! Properties

    //! Backend
    ApplicationManager {
        id: appManager
        objectName: "appManager"
    }

    //! Functions
    function scan() {
        statusBarCustom.clearMessage()
        finder.initialAddress = general.proxyConfig.initialIP
        finder.finalAddress = general.proxyConfig.finalIP
        finder.port = ~~general.proxyConfig.port
        finder.maxThreads = advancedNetworkConfig.maxThreads
        finder.timeout = advancedNetworkConfig.timeout
        finder.requestType = advancedNetworkConfig.requestType
        finder.requestUrl = advancedNetworkConfig.requestUrl
        finder.start()
    }

    //! Events
    onClosing: {
        if (finder.scaning) {
            dialogConfirmExit.open()
            close.accepted = false
        }
    }

    //! Menu and status bars
    menuBar: MenuBar {
        property color iconColor: "transparent"
        Menu {
            title: qsTr("&Tools")
            MenuItem { text: qsTr("&Advanced network options"); enabled: !finder.scaning; icon.source: "qrc:/images/network-settings.svg"; icon.color: menuBar.iconColor; onTriggered: advancedNetworkConfig.open() }
            MenuItem { text: qsTr("&Preferences"); icon.source: "qrc:/images/preferences.svg"; icon.color: menuBar.iconColor; onTriggered: preferences.open() }
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
    General {
        id: general
        anchors.fill: parent
    }

    //! Dialogs
    AdvancedNetworkConfig {
        id: advancedNetworkConfig
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
    }

    Preferences {
        id: preferences
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
    }

    DialogStyleChooser {
        id: dialogStyleChooser
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
        visible: appManager.settings.firstTime && !networkUnavailable.visible

        onClosed: {
            dialogAlphaWarning.open()
        }
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
            general.proxyConfig.swapIPs()
            general.scan()
        }
    }

    PopupScaning {
        id: dialogAlphaWarning
        anchors.centerIn: Overlay.overlay
        visible: !appManager.settings.firstTime && !networkUnavailable.visible
        modal: true
        focus: true
    }

    NetworkOverlay {
        id: networkUnavailable
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
        visible: !appManager.settings.networkAvailable && appManager.settings.operatingSystem !== "Windows"

        onClosed: {
            dialogAlphaWarning.open()
        }
    }
}
