import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 800 * settings.scene_width / settings.scene_height
    height: 800
    title: qsTr("Qt VR demo")

    QtObject {
        id: settings

        property int scene_sphereRadius: 9000
        property real scene_zNear: 1.5
        property real scene_zFar: 10000
        property real scene_width: 2960
        property real scene_height: 1440

        property real vr_k1: 0.244
        property real vr_k2: 0.421
        property int vr_meshRows: 26
        property int vr_meshCols: 26
    }

    header: ToolBar {
        width: toolButton.implicitWidth
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.currentItem.save()
                    stackView.pop()
                    stackView.replace("Vr.qml", { "settings": settings })
                } else {
                    drawer.open()
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Scene settings")
                width: parent.width
                onClicked: {
                    stackView.push("SceneSettings.qml", { "settings": settings })
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("VR settings")
                width: parent.width
                onClicked: {
                    stackView.push("VrSettings.qml", { "settings": settings })
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        Component.onCompleted: stackView.push("Vr.qml", { "settings": settings })
    }
}
