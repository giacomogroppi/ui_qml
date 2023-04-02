import QtQuick 2.15
import QtQuick.Controls 2.12
import writernote.WQMLCanvasComponent 1.0
import writernote.WQMLCanvasHandler 1.0

Item {
    id: canvas_surface

    Flickable {
        id: canvasSurface
        anchors.fill: parent
        //clip: true
        contentHeight: canvas_surface_private.height
        contentWidth: canvas_surface_private.width

        ScrollBar.vertical: ScrollBar {
            width: 40
            anchors.left: parent.right // adjust the anchor as suggested by derM
            policy: ScrollBar.AlwaysOn
        }

        ScrollBar.horizontal: ScrollBar {
            width: 40
            anchors.bottom: parent.bottom
            policy: ScrollBar.AlwaysOn
        }

        WCanvasComponent {
            id: canvas_surface_private
            anchors.margins: 10

            anchors.left: parent.left
            anchors.top: parent.top

            width: _controllerCanvas.widthObject
            height: _controllerCanvas.heigthObject

            xPosition: canvasSurface.originX
            yPosition: canvasSurface.originY

            onWidthChanged: {
                console.log("width change", width, "diventa", _controllerCanvas.widthObject);
            }
        }
    }

    WCanvasHandler {
        targetTouchArea: canvasSurface
    }
}
