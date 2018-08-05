import QtQuick 2.9

import VrDemo 1.0

VRView {
    property var settings
    property string title: qsTr("VR scene")

    scene_sphereRadius: settings.scene_sphereRadius
    scene_zNear: settings.scene_zNear
    scene_zFar: settings.scene_zFar
    scene_width: settings.scene_width
    scene_height: settings.scene_height

    vr_k1: settings.vr_k1
    vr_k2: settings.vr_k2
    vr_meshRows: settings.vr_meshRows
    vr_meshCols: settings.vr_meshCols
}
