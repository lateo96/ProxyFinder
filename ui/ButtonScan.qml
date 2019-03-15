import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.12

Button {
    id: root

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton
        cursorShape: Qt.PointingHandCursor
    }

    background: Rectangle {
        implicitWidth: 64
        implicitHeight: root.Material.buttonHeight
        //        height: width

        radius: width/2
        color: !root.enabled ? root.Material.buttonDisabledColor :
                               root.highlighted ? root.Material.highlightedButtonColor : root.Material.buttonColor

        // The layer is disabled when the button color is transparent so you can do
        // Material.background: "transparent" and get a proper flat button without needing
        // to set Material.elevation as well
        layer.enabled: root.enabled && root.Material.buttonColor.a > 0
        layer.effect: ElevationEffect {
            elevation: root.Material.elevation
        }

        Ripple {
            clipRadius: parent.radius
            width: parent.width
            height: parent.height
            anchor: root
            active: root.down || root.visualFocus || root.hovered
            color: root.Material.rippleColor
        }

    } // background (Rectangle)

    BusyIndicator {
        id: busyIndicatorScaning
        anchors.centerIn: parent
        visible: finder.scaning
    }

} // Button
