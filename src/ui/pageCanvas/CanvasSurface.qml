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

        WCanvasComponent {
            id: canvas_surface_private
            anchors.margins: 10

            targetTouchArea: canvasSurface

            anchors.left: parent.left
            anchors.top: parent.top

            width: _controllerCanvas.widthObject
            height: _controllerCanvas.heigthObject

            onWidthChanged: {
                console.log("width change", width, "diventa", _controllerCanvas.widthObject);
            }

            TapHandler {
                acceptedDevices: PointerDevice.Stylus

                onPressedChanged: {
                    canvasSurface.interactive = false
                    //console.log("Pressed chang 1");
                    console.log("Press1 with pen: [x, y]", point.position)
                }

                onPointChanged: {
                    console.log("Press2 with pen: [x, y]", point.position)
                }

            }

            // The MouseArea fills the whole page
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    //_controllerCanvas.touchBegin(mouseX, mouseY)
                    //console.log("Pressed")
                }
                onReleased: {
                    //_controllerCanvas.touchEnd(mouseX, mouseY)
                    canvasSurface.interactive = true
                }
                onPositionChanged: {
                    //console.log("position changed " + mouseX +" "+ mouseY)
                    //_controllerCanvas.touchUpdate(mouseX, mouseY)
                }
                //onClicked: touchLog.text += "\nClicked"
            }

            TapHandler {
                acceptedDevices: PointerDevice.TouchScreen | PointerDevice.Mouse

                onPressedChanged: {
                    canvasSurface.interactive = true
                    console.log("Pressed change 2");
                }
            }
        }
    }
}
