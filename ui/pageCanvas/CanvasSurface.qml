import QtQuick 2.15
import QtQuick.Controls 2.12
import writernote.WQMLCanvasComponent 1.0

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

        //boundsBehavior: Flickable.DragAndOvershootBounds

//        Text {
//            anchors.left: parent.left
//            anchors.top: parent.top
//
//            text: _controllerCanvas.heigthObject ? ("height: " + _controllerCanvas.heigthObject) : "ciao"
//            font.pixelSize: 100
//        }

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
                acceptedDevices: PointerDevice.Stylus
                onTapped: {
                    canvasSurface.interactive = false
                    console.log("right clicked 1")
                }
                onLongPressed: {
                    canvasSurface.interactive = false
                    console.log("Long press 1");
                }

                onPressedChanged: {
                    canvasSurface.interactive = false
                    console.log("Pressed chang 1");
                }

                onCanceled: {
                    canvasSurface.interactive = false
                    console.log("Cancellato 1");
                }
            }

            TapHandler {
                acceptedDevices: PointerDevice.TouchScreen | PointerDevice.Mouse
                onTapped: {
                    canvasSurface.interactive = true
                    console.log("right clicked 2")
                }
                onLongPressed: {
                    canvasSurface.interactive = true
                    console.log("Long press 2");
                }

                onPressedChanged: {
                    canvasSurface.interactive = true
                    console.log("Pressed change 2");
                }

                onCanceled: {
                    canvasSurface.interactive = true
                    console.log("Cancellato 2");
                }
            }
        }
    }
}
