import QtQuick
import QtQuick.Controls 2.12
import TextBalloon 1.0

Item {
    id: canvas_surface

    ScrollView {
        id: canvasSurface
        anchors.fill: parent
        clip: true

        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        Image {
            id: img_id_canvas_private
            source: "image://_controllerCanvas/prova"
            fillMode: Image.PreserveAspectFit

            function updateImg() {
                var last_source = img_id_canvas_private.source
                img_id_canvas_private.source = ""
                img_id_canvas_private.source = last_source
            }
        }

        scale: .99
    }
}
