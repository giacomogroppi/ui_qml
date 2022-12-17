import QtQuick 2.15
import QtQuick.Controls 2.12
import writernote.WQMLCanvasComponent 1.0

Item {
    id: canvas_surface

    ScrollView {
        id: canvasSurface
        anchors.fill: parent
        clip: true

        ScrollBar.horizontal.interactive: true
        ScrollBar.vertical.interactive: true

        contentHeight: canvas_surface_private.height
        contentWidth: canvas_surface_private.width

        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        Text {
            anchors.left: parent.left
            anchors.top: parent.top

            text: _controllerCanvas.heigthObject ? _controllerCanvas.heigthObject : "ciao"
            font.pixelSize: 100
        }

        WCanvasComponent {
            id: canvas_surface_private
            anchors.margins: 10

            anchors.left: parent.left
            anchors.top: parent.top

            width: _controllerCanvas.widthObject
            height: _controllerCanvas.heigthObject

            onWidthChanged: {
                console.log("width change", width, "diventa", _controllerCanvas.widthObject);
            }

            TapHandler {
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onTapped: console.log("scroll action")
            }

            TapHandler {
                //acceptedDevices: PointerDevice.Mouse | PointerDevice.Stylus
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onTapped: console.log("right clicked")
            }
        }
    }
}
