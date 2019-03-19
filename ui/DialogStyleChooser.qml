import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Dialog {
    id: root

    title: qsTr("Configure the style")
    standardButtons: Dialog.Close

    ColumnLayout {
        id: rowLayoutTheme
        anchors.fill: parent
        spacing: 20

        Image {
            source: "qrc:/images/appIcon.svg"
            sourceSize: Qt.size(64, 64)
            fillMode: Image.PreserveAspectFit

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
        }

        Rectangle {
            height: 1
            color: Material.color(Material.Grey)
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.fillWidth: true

            RadioButton {
                id: radioButtonLightTheme
                text: qsTr("Light")
                checked: appWindow.Material.theme === Material.Light

                onCheckedChanged: {
                    if (checked && appWindow.Material.theme !== Material.Light) {
                        preferences.theme = Material.Light
                    }
                }
            }

            RadioButton {
                id: radioButtonDarkTheme
                text: qsTr("Dark")
                checked: appWindow.Material.theme === Material.Dark

                onCheckedChanged: {
                    if (checked && appWindow.Material.theme !== Material.Dark) {
                        preferences.theme = Material.Dark
                    }
                }
            }
        } // RowLayout
    } // ColumnLayout
} // Dialog
