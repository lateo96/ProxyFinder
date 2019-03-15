import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

GroupBox {
    id: root

    property alias initialIP: textFieldInitialIP.text
    property alias finalIP: textFieldFinalIP.text
    property alias port: textFieldPort.text

    property bool valid: validInitialIP && validFinalIP && validPort

    property bool validInitialIP: finder.validInitialAddress && (initialIP.split('.').length === 4)
    property bool validFinalIP: finder.validFinalAddress && (finalIP.split('.').length === 4)
    property bool validPort: port > 0x0000 && port <= 0xFFFF

    label: SwitchDelegate {
        id: switchConfigureProxy
        text: qsTr("Configure proxy")
        enabled: !checked || valid

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            cursorShape: Qt.PointingHandCursor
        }

        Component.onCompleted: {
            checked = !valid
        }
    }

    contentItem: RowLayout {
        enabled: switchConfigureProxy.checked
        spacing: 20

        ColumnLayout {
            Layout.fillWidth: true
            Label {
                text: qsTr("Initial IP")
                Material.foreground: (validInitialIP ? root.Material.foreground : Material.Pink)
            }
            CustomTextField {
                id: textFieldInitialIP
                placeholderText: "IP"
//                text: "10.8.6.0"
                selectByMouse: true
                Layout.fillWidth: true

                Material.accent: (validInitialIP ? root.Material.accent : Material.Pink)
                Material.foreground: (validInitialIP ? root.Material.foreground : Material.Pink)

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
                Material.foreground: (validFinalIP ? root.Material.foreground : Material.Pink)
            }
            CustomTextField {
                id: textFieldFinalIP
                placeholderText: "IP"
//                text: "10.8.9.0"
                selectByMouse: true
                Layout.fillWidth: true

                Material.accent: (validFinalIP ? root.Material.accent : Material.Pink)
                Material.foreground: (validFinalIP ? root.Material.foreground : Material.Pink)

                onTextChanged: {
                    text = text.trim()
                    finder.finalAddress = text
                }

                Component.onCompleted: {
                    finder.finalAddress = text
                }
            } // ColumnLayout
        }
        ColumnLayout {
            Label {
                text: qsTr("Port")
                Material.foreground: (validPort ? root.Material.foreground : Material.Pink)
            }
            CustomTextField {
                id: textFieldPort
                placeholderText: "PORT"
//                text: "3128"
                selectByMouse: true
                inputMethodHints: Qt.ImhDigitsOnly

                Material.accent: (validPort ? root.Material.accent : Material.Pink)
                Material.foreground: (validPort ? root.Material.foreground : Material.Pink)

                onTextChanged: {
                    text = text.trim()
                    finder.port = ~~text
                }

                Component.onCompleted: {
                    finder.port = ~~text
                }
            }
        } // ColumnLayoutS
    } // contenrItem (RowLayout)
} // GroupBox
