import QtQuick 2.15
import QtQuick.Controls 2.12
import writernote.WQMLCanvasComponentStroke 1.0
import writernote.WQMLCanvasHandler 1.0
import writernote.WQMLCanvasComponentPage 1.0

Item {
    id: canvas_surface

    /*
    Flickable {
        id: canvasSurface
        anchors.fill: parent
        contentHeight: 1000
        contentWidth: 1000

        // Y  position
        onContentYChanged: {
            if (contentY >= 0.)
                _controllerCanvas.positionY = contentY;
        }

        // X  position
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

        ListView {
            anchors.fill: parent
            model: _controllerCanvas
            clip: false
            visible: true

            width: 1000
            height: 1000

            delegate: Rectangle {
                height: 1000
                width: 1000

                Rectangle {
                    anchors {
                        top: parent.top
                        right: parent.right
                        left: parent.left
                    }

                    WCanvasComponent {
                        id: canvas_surface_private
                        anchors.margins: 10

                        anchors.left: parent.left
                        anchors.top: parent.top

                        index: index

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
                }
            }
        }

        WCanvasHandler {
            targetTouchArea: canvasSurface
            heightObject: canvasSurface.height
            widthObject:  canvasSurface.width

            xOriginPosition: canvas_surface_private.x - canvasSurface.x
            yOriginPosition: canvas_surface_private.y - canvasSurface.y
        }
    }*/


    ListView {
        id: containerCanvas
        anchors.fill: parent
        model: _controllerCanvas
        clip: true
        //visible: true

        delegate: Rectangle {
            width: 1000
            height: 1414

            //visible: true
            visible: index === 0

            WCanvasComponentPage {
                anchors.margins: 10

                anchors.left: parent.left
                anchors.top: parent.top

                indexDrawer: index

                height: parent.height
                width: parent.width
                //width: _controllerCanvas.widthObject * canvasSurface.scale
                //height: _controllerCanvas.heigthObject * canvasSurface.scale

                xPosition: canvasSurface.originX
                yPosition: canvasSurface.originY

                onWidthChanged: {
                    console.log("width change", width, "diventa", _controllerCanvas.widthObject);
                }
            }

            WCanvasComponent {
                anchors.margins: 10

                anchors.left: parent.left
                anchors.top: parent.top

                height: parent.height
                width: parent.width
                //width: _controllerCanvas.widthObject * canvasSurface.scale
                //height: _controllerCanvas.heigthObject * canvasSurface.scale

                xPosition: canvasSurface.originX
                yPosition: canvasSurface.originY

                onWidthChanged: {
                    console.log("width change", width, "diventa", _controllerCanvas.widthObject);
                }
            }
        }
    }

    WCanvasHandler {
        targetTouchArea: containerCanvas

        heightObject: containerCanvas.height
        widthObject:  containerCanvas.width

        xOriginPosition: 10
        yOriginPosition: 10
    }
}
