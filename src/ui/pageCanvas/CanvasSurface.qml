import QtQuick 2.15
import QtQuick.Controls 2.12
import writernote.WQMLCanvasComponentStroke 1.0
import writernote.WQMLCanvasHandler 1.0
import writernote.WQMLCanvasComponentPage 1.0

Item {
    id: canvas_surface

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
        }
    }

    WCanvasComponentStroke {
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

    Popup {
        width: 100
        height: 30*3

        function showObject() {
            console.log("popupOptions show with index " + index + " x " + x + " y " + y)
            popupOptions.isVisible = true
        }

        id: popupOptions
        visible: true

        Rectangle {
            anchors.fill: parent
            Button {
                id: buttonAddPage
                text: "Add page"
                height: parent.height / 3
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
            }
            Button {
                id: buttonRemovePage
                text: "Remove page"
                height: parent.height / 3
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: buttonAddPage.bottom
            }
            Button {
                id: buttonCopyPage
                text: "Copy page"
                height: parent.height / 3
                anchors.top: buttonRemovePage.bottom
                anchors.left: parent.left
                anchors.right: parent.right
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
