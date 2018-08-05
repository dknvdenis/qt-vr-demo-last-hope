import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    property var settings
    title: qsTr("Scene settings")

    function save() {
        settings.scene_sphereRadius = radius.text
        settings.scene_zNear = zNear.text
        settings.scene_zFar = zFar.text
        settings.scene_width = sceneWidth.text
        settings.scene_height = sceneHeight.text
    }

    GridLayout {
        columns: 2
        rowSpacing: 5
        columnSpacing: 5
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            Layout.row: 1
            Layout.column: 1
            text: "Sphere radius"
        }
        TextField {
            id: radius
            Layout.row: 1
            Layout.column: 2
            text: settings.scene_sphereRadius
            validator: IntValidator { bottom: 1; top: 10000; }
            selectByMouse: true
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.IBeamCursor
                acceptedButtons: Qt.NoButton
            }
        }

        Label {
            Layout.row: 3
            Layout.column: 1
            text: "zNear"
        }
        TextField {
            id: zNear
            Layout.row: 3
            Layout.column: 2
            text: settings.scene_zNear
            validator: RegExpValidator { regExp: /[0-9]+\.[0-9]+/ }
            selectByMouse: true
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.IBeamCursor
                acceptedButtons: Qt.NoButton
            }
        }

        Label {
            Layout.row: 4
            Layout.column: 1
            text: "zFar"
        }
        TextField {
            id: zFar
            Layout.row: 4
            Layout.column: 2
            text: settings.scene_zFar
            validator: RegExpValidator { regExp: /[0-9]+\.[0-9]+/ }
            selectByMouse: true
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.IBeamCursor
                acceptedButtons: Qt.NoButton
            }
        }

        Label {
            Layout.row: 6
            Layout.column: 1
            text: "Width"
        }
        TextField {
            id: sceneWidth
            Layout.row: 6
            Layout.column: 2
            text: settings.scene_width
            validator: IntValidator { bottom: 1; top: 10000; }
            selectByMouse: true
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.IBeamCursor
                acceptedButtons: Qt.NoButton
            }
        }

        Label {
            Layout.row: 7
            Layout.column: 1
            text: "Height"
        }
        TextField {
            id: sceneHeight
            Layout.row: 7
            Layout.column: 2
            text: settings.scene_height
            validator: IntValidator { bottom: 1; top: 10000; }
            selectByMouse: true
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.IBeamCursor
                acceptedButtons: Qt.NoButton
            }
        }
    }
}
