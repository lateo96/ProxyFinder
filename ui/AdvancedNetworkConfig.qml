import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Dialog {
    id: root

    property alias maxThreads: spinBoxMaxThreads.value
    property alias timeout: spinBoxTimeout.value
    property alias requestType: comboBoxRequestType.currentIndex
    property alias requestUrl: textFieldRequestUrl.text

    enum RequestType { HTTP, HTTPS, FTP }

    title: qsTr("Advanced network options")
    standardButtons: Dialog.Close

    GridLayout {
        columns: 2
        rowSpacing: 20
        columnSpacing: 25

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Label {
                text: qsTr("Timeout") + " <i>" + qsTr("(ms)") + "</i>"
            }
            SpinBox {
                id: spinBoxTimeout
                editable: true
                from: 100
                to: 10000
                value: appManager.settings.timeout
                stepSize: 100
                Layout.fillWidth: true

                onValueChanged: {
                    finder.timeout = value
                }
            }
        } // ColumnLayout

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Label {
                text: qsTr("Max threads")
            }
            SpinBox {
                id: spinBoxMaxThreads
                editable: true
                from: 1
                to: 1000
                value: appManager.settings.maxThreads
                stepSize: 100
                Layout.fillWidth: true

                onValueChanged: {
                    finder.maxThreads = value
                }
            }
        } // ColumnLayout

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Label {
                text: qsTr("Request type")
            }
            ComboBox {
                id: comboBoxRequestType
                model: ["HTTP", "HTTPS", "FTP"]
                currentIndex: appManager.settings.requestType
                Layout.fillWidth: true

                onCurrentIndexChanged: {
                    finder.requestType = currentIndex
                }
            }
        } // ColumnLayout
        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Label {
                text: qsTr("Request URL")
            }
            RowLayout {
                Label {
                    text: comboBoxRequestType.currentText.toLowerCase() + "://"
                    enabled: false
                }
                CustomTextField {
                    id: textFieldRequestUrl
                    placeholderText: "google.com"
                    text: appManager.settings.requestUrl
                    selectByMouse: true
                    Layout.fillWidth: true

                    onTextChanged: {
                        finder.requestUrl = text
                    }
                }
            }
        } // ColumnLayout
    } // GridLayout
}
