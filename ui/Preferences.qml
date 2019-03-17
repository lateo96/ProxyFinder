import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Dialog {
    id: root

    readonly property string style: "Material"
    property int theme: appManager.settings.theme
    onThemeChanged: {
        appManager.settings.theme = theme
    }

    title: qsTr("Preferences")

    GroupBox {
        id: groupBoxStyle
        title: qsTr("Style")
        anchors.fill: parent

        ColumnLayout {
            id: columnLayoutTheme
            anchors.fill: parent

            RowLayout {
                enabled: !checkBoxSystemTheme.checked
                Layout.fillWidth: true

                RadioButton {
                    id: radioButtonLightTheme
                    text: qsTr("Light")
                    checked: appWindow.Material.theme === Material.Light

                    onCheckedChanged: {
                        if (checked && appWindow.Material.theme !== Material.Light) {
                            theme = Material.Light
                        }
                    }
                }

                RadioButton {
                    id: radioButtonDarkTheme
                    text: qsTr("Dark")
                    checked: appWindow.Material.theme === Material.Dark

                    onCheckedChanged: {
                        if (checked && appWindow.Material.theme !== Material.Dark) {
                            theme = Material.Dark
                        }
                    }
                }
            } // RowLayout

            CheckBox {
                id: checkBoxSystemTheme
                text: qsTr("Use system theme")
                checked: theme === Material.System

                onCheckedChanged: {
                    if (checked) {
                        theme = Material.System
                    }
                }

                Layout.fillWidth: true
            }
        } // ColumnLayout
    } // GroupBox
} // Popup
