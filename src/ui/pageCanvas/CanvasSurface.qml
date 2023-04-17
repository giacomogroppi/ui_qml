import QtQuick 2.15
import QtQuick.Controls 2.12
import writernote.WQMLCanvasComponent 1.0
import writernote.WQMLCanvasHandler 1.0

Item {
    id: canvas_surface

    Flickable {
        id: canvasSurface
        anchors.fill: parent
        contentHeight: canvas_surface_private.height
        contentWidth: canvas_surface_private.width

        /**
          * Y  position
        */
        onContentYChanged: {
            if (contentY >= 0.)
                _controllerCanvas.positionY = contentY;
        }

        /**
          * X  position
        */
        onContentXChanged: {
            if (contentX >= 0.)
                _controllerCanvas.positionX = contentX;
        }

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


            /*PinchArea{
                id: pinchArea

                anchors.fill: canvas_surface_private

                pinch.maximumScale: 2.
                pinch.minimumScale: 1.

                property real original_pinch;

                onPinchStarted: {
                    original_pinch = canvasSurface.scale

                    console.log("Original scale: " + original_pinch)
                }

                onPinchUpdated: {
                    var center_x = pinch.center.x - canvasSurface.contentX
                    var center_y = pinch.center.y - canvasSurface.contentY
                    var content_width = canvasSurface.contentWidth * pinch.scale
                    var content_height = canvasSurface.contentHeight * pinch.scale

                    //console.log(center_x + " " + center_y + " pinch scale: " + pinch.scale);

                    var original_center = pinch.startCenter
                    var new_center = pinch.center

                    var new_position_center_x = original_center.x - new_center.x
                    var new_position_center_y = original_center.y - new_center.y

                    new_position_center_x *= (pinch.scale - original_pinch)
                    new_position_center_y *= (pinch.scale - original_pinch)

                    console.log(pinch.scale)
                    if (pinch.scale >= 2. || pinch.scale <= 0.5)
                        return;

                    canvasSurface.scale = pinch.scale
                    canvasSurface.contentX = Math.max(0, new_position_center_x)
                    canvasSurface.contentY = Math.max(0, new_position_center_y)
                }

                onPinchFinished: {
                    if (canvasSurface.contentX <= 0.) {
                        canvasSurface.contentX = 0.;
                    }

                    if (canvasSurface.contentY <= 0.) {
                        canvasSurface.contentY = 0.;
                    }
                }
            }*/

            WCanvasComponent {
                id: canvas_surface_private
                anchors.margins: 10

                anchors.left: parent.left
                anchors.top: parent.top

                width: 1000
                height: 1000
                //width: _controllerCanvas.widthObject * canvasSurface.scale
                //height: _controllerCanvas.heigthObject * canvasSurface.scale

                xPosition: canvasSurface.originX
                yPosition: canvasSurface.originY

                onWidthChanged: {
                    console.log("width change", width, "diventa", _controllerCanvas.widthObject);
                }
            }

            /*Timer {
                interval: 15
                running: true
                repeat: true
                onTriggered: {
                    console.log("Timer end");
                    canvas_surface_private.requestPaint()
                }
            }

            Canvas {
                id: canvas_surface_private
                anchors.left: parent.left
                anchors.top: parent.top

                height: 500
                width: 500

                property int variable: 0

                onPaint: {
                    var ctx = getContext("2d");
                    ctx.fillStyle = Qt.rgba(1, 1, 1, 1);
                    ctx.fillRect(0, 0, width, height);
                    //ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
                    //ctx.fillRect(0, 0, variable, variable);

                    //console.log(variable)
                    if (variable > width)
                        variable = 0;
                    variable ++;

                    //var img = new Image();
                    var image = _controllerToolBar.getPixmap(); // ottieni il QPixmap dal tuo oggetto C++
                    //image.src = pixmap.toImage(); // converte il QPixmap in un QImage

                    console.log("Image" + image);
                    for(var m in image) {
                        console.log("Has property" + m);
                    }


                    ctx.drawImage(image, 0, 0); // disegna l'immagine sul canvas
                }
            }*/

            WCanvasHandler {
                targetTouchArea: canvasSurface
                heightObject: canvas_surface_private.height
                widthObject:  canvas_surface_private.width

                xOriginPosition: canvas_surface_private.x - canvasSurface.x
                yOriginPosition: canvas_surface_private.y - canvasSurface.y

            }
        }
}
