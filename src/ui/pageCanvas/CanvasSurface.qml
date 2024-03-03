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
        width: 245
        height: 45
        modal: true

        background: Rectangle {
            color: "transparent"
            border.color: "transparent"
        }

        function showObject() {
            console.log("popupOptions show with index " + index + " x " + x + " y " + y)
            popupOptions.isVisible = true
        }

        id: popupOptions
        visible: true

        Rectangle {
            anchors.fill: parent

            //property var fontButtons: Font { family: "Helvetica"; pointSize: 13; bold: true }
            property var fontFamily: string = "Helvetica"
            property var fontSize: 13
            property var fontColor: "black"

            // TODO: add controll action
            Row {
                id: private_row_popup_canvas
                anchors.fill: parent

                spacing: 1
                Button {
                    //text: "Copy"
                    contentItem: Text {
                            text: "copy"
                            opacity: 1.0
                            font: fontFamily
                            color: fontColor
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }
                    onClicked: console.log("Option 1 clicked")
                }
                Button {
                    text: "Delete"
                    onClicked: console.log("Option 2 clicked")
                }
                Button {
                    text: "Paste"
                    onClicked: console.log("Option 3 clicked")
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
