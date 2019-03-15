import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Page {
    id: root

    property real internalLabelIPWidth: 150
    property real internalLabelCodeWidth: 50

    header: ColumnLayout {

        RowLayout {
            Layout.topMargin: -20

            Label {
                text: qsTr("Proxy IP")
                font.pointSize: 9
                Layout.leftMargin: 16 // spacing property of ItemDelegate (see Qt source code)
                Layout.preferredWidth: internalLabelIPWidth
            }
            Label {
                text: qsTr("Code")
                font.pointSize: 9
                Layout.preferredWidth: internalLabelCodeWidth
            }
            Label {
                text: qsTr("Reason phrase")
                font.pointSize: 9
                Layout.fillWidth: true
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: "#DDDDDD"
        }
    }

    ScrollView {
        id: scrollView
        anchors.fill: parent
        clip: true

        background: Image {
            fillMode: Image.PreserveAspectCrop
            source: "qrc:/images/qt_background.png"
        }

        ListView {
            id: list
            width: parent.width
            model: 0

            delegate: ReportDelegate {
                width: root.width
            }

            Timer {
                id: timerReportUpdater
                interval: 500
                repeat: true
                running: finder.scaning

                onRunningChanged: {
                    list.model = finder.reportModel
                }

                onTriggered: {
                    list.model = finder.reportModel
                }
            }
        } // ListView
    } // ScrollView
}
