import QtQuick 2.15
import QtQuick.Controls 2.12
import com.github.giacomogroppi.writernoteqt.WQMLCanvasComponent 1.0

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

            text: Disegnatore.heigthObject ? Disegnatore.heigthObject : "ciao"
            font.pixelSize: 400
        }

        WCanvasComponent {
            id: canvas_surface_private
            anchors.margins: 10

            anchors.left: parent.left
            anchors.top: parent.top

            width: CanvasSurface.widthObject + 100
            //height: CanvasSurface.heigthObject
            //width: 5000
            height: 5000

            onWidthChanged: {
                console.log("width change", width, "diventa", Disegnatore.widthObject);
            }
        }
    }
}
