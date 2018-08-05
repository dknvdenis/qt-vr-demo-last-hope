import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    property var settings
    title: qsTr("VR settings")

    function save() {
        settings.vr_k1 = k1.text
        settings.vr_k2 = k2.text
        settings.vr_meshRows = rows.text
        settings.vr_meshCols = cols.text
    }

    GridLayout {
        columns: 2
        rowSpacing: 5
        columnSpacing: 5
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            Layout.row: 3
            Layout.column: 1
            text: "K1"
        }
        TextField {
            id: k1
            Layout.row: 3
            Layout.column: 2
            text: settings.vr_k1
            validator: RegExpValidator { regExp: /-*[0-9]+\.[0-9]+/ }
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
            text: "K2"
        }
        TextField {
            id: k2
            Layout.row: 4
            Layout.column: 2
            text: settings.vr_k2
            validator: RegExpValidator { regExp: /-*[0-9]+\.[0-9]+/ }
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
            text: "Mesh rows"
        }
        TextField {
            id: rows
            Layout.row: 6
            Layout.column: 2
            text: settings.vr_meshRows
            validator: IntValidator { bottom: 2; top: 1000; }
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
            text: "Mesh cols"
        }
        TextField {
            id: cols
            Layout.row: 7
            Layout.column: 2
            text: settings.vr_meshCols
            validator: IntValidator { bottom: 2; top: 1000; }
            selectByMouse: true
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.IBeamCursor
                acceptedButtons: Qt.NoButton
            }
        }
    }
}
