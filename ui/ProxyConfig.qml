import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.12

GroupBox {
    id: root

    //! Properties
    property alias initialIP: textFieldInitialIP.text
    property alias finalIP: textFieldFinalIP.text
    property alias port: textFieldPort.text

    property bool valid: validInitialIP && validFinalIP && validPort

    property bool validInitialIP: finder.validInitialAddress && (initialIP.split('.').length === 4)
    property bool validFinalIP: finder.validFinalAddress && (finalIP.split('.').length === 4)
    property bool validPort: port > 0x0000 && port <= 0xFFFF

    readonly property color accentColorOk: Material.accent
    readonly property color accentColorError: Material.color(Material.Pink)
    readonly property color foregroundColorOk: Material.foreground
    readonly property color foregroundColorError: Material.color(Material.Pink)

    //! Property handlers
    onValidChanged: {
        // ProgressBar
        progress.Material.accent = valid ? appWindow.Material.accent : Material.Pink
    }

    //! Functions
    function swapIPs() {
        var hold = initialIP
        initialIP = finalIP
        finalIP = hold
    }

    // UI
    label: SwitchDelegate {
        id: switchConfigureProxy
        text: qsTr("Configure proxy")
        enabled: !checked || valid

        property color foregroundColor: enabled ? foregroundColorOk : Material.hintTextColor
        Behavior on foregroundColor { ColorAnimation { duration: 250; easing.type: Easing.OutQuart } }
        Material.foreground: foregroundColor

        indicator: SwitchIndicator {
            x: switchConfigureProxy.text ? (switchConfigureProxy.mirrored ? switchConfigureProxy.leftPadding : switchConfigureProxy.width - width - switchConfigureProxy.rightPadding) : switchConfigureProxy.leftPadding + (switchConfigureProxy.availableWidth - width) / 2
            y: switchConfigureProxy.topPadding + (switchConfigureProxy.availableHeight - height) / 2
            control: switchConfigureProxy

            Rectangle {
                width: parent.width
                height: 14
                radius: height / 2
                y: parent.height / 2 - height / 2
                color: parent.control.enabled ? (parent.control.checked ? parent.control.Material.switchCheckedTrackColor : parent.control.Material.switchUncheckedTrackColor)
                                       : parent.control.Material.switchDisabledTrackColor
                Behavior on color { ColorAnimation { duration: 250; easing.type: Easing.OutQuart } }
                z: -1
            }

            Behavior on handle.color { ColorAnimation { duration: 250; easing.type: Easing.OutQuart } }
        } // SwitchIndicator

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            cursorShape: Qt.PointingHandCursor
        }

        Component.onCompleted: {
            checked = !valid
        }
    } // label: SwitchDelegate

    contentItem: RowLayout {
        enabled: switchConfigureProxy.checked
        spacing: 20

        ColumnLayout {
            Layout.fillWidth: true
            Label {
                text: qsTr("Initial IP")
                property color foregroundColor: validInitialIP ? foregroundColorOk : foregroundColorError
                Behavior on foregroundColor { ColorAnimation { duration: 250; easing.type: Easing.OutQuart } }
                Material.foreground: foregroundColor
            }
            CustomTextField {
                id: textFieldInitialIP
                placeholderText: "IP"
                text: appManager.settings.initialAddress
                selectByMouse: true
                Layout.fillWidth: true

                property color accentColor: validInitialIP ? accentColorOk : accentColorError
                property color foregroundColor: validInitialIP ? foregroundColorOk : foregroundColorError

                Behavior on accentColor { ColorAnimation { duration: 250; easing.type: Easing.OutQuart } }
                Behavior on foregroundColor { ColorAnimation { duration: 250; easing.type: Easing.OutQuart } }

                Material.accent: accentColor
                Material.foreground: foregroundColor

                onTextChanged: {
                    text = text.trim()
                    finder.initialAddress = text
                }

                Component.onCompleted: {
                    finder.initialAddress = text
                }
            }
        } // ColumnLayout
        ColumnLayout {
            Layout.fillWidth: true
            Label {
                text: qsTr("Final IP")
                property color foregroundColor: validFinalIP ? foregroundColorOk : foregroundColorError
                Behavior on foregroundColor { ColorAnimation { duration: 250; easing.type: Easing.OutQuart } }
                Material.foreground: foregroundColor
            }
            CustomTextField {
                id: textFieldFinalIP
                placeholderText: "IP"
                text: appManager.settings.finalAddress
                selectByMouse: true
                Layout.fillWidth: true

                property color accentColor: validFinalIP ? accentColorOk : accentColorError
                property color foregroundColor: validFinalIP ? foregroundColorOk : foregroundColorError

                Material.accent: accentColor
                Material.foreground: foregroundColor

                Behavior on accentColor { ColorAnimation { duration: 250; easing.type: Easing.OutQuart } }
                Behavior on foregroundColor { ColorAnimation { duration: 250; easing.type: Easing.OutQuart } }

                onTextChanged: {
                    text = text.trim()
                    finder.finalAddress = text
                }

                Component.onCompleted: {
                    finder.finalAddress = text
                }
            } // CustomTextField
        } // ColumnLayout
        ColumnLayout {
            Label {
                text: qsTr("Port")
                property color foregroundColor: validPort ? foregroundColorOk : foregroundColorError
                Behavior on foregroundColor { ColorAnimation { duration: 250; easing.type: Easing.OutQuart } }
                Material.foreground: foregroundColor
            }
            CustomTextField {
                id: textFieldPort
                placeholderText: "PORT"
                text: appManager.settings.port
                selectByMouse: true
                inputMethodHints: Qt.ImhDigitsOnly

                property color accentColor: validPort ? accentColorOk : accentColorError
                property color foregroundColor: validPort ? foregroundColorOk : foregroundColorError

                Material.accent: accentColor
                Material.foreground: foregroundColor

                onTextChanged: {
                    if (text === "") {
                        return
                    } else if (text === "0") {
                        text = ""
                        return
                    }
                    text = text.trim()
                    finder.port = text === "" ? 0 : ~~text
                }

                Component.onCompleted: {
                    finder.port = text === "" ? 0 : ~~text
                }
            } // CustomTextField
        } // ColumnLayoutS
    } // contenrItem (RowLayout)
} // GroupBox
