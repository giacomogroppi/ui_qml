import QtQuick 2.15
import QtQuick.Controls 2.12
import writernote.WQMLCanvasComponent 1.0

Item {
    id: canvas_surface

    Flickable {
        id: canvasSurface
        anchors.fill: parent
        //clip: true
        contentHeight: 0
        contentWidth: 0

        //boundsBehavior: Flickable.StopAtBounds

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
                acceptedDevices: PointerDevice.TouchScreen
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
