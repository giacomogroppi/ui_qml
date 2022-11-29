import QtQuick
import ControllerList 1.0

Rectangle {
    property int w: 100

    color: "#0000ff"

    ControllerList {
        id: listPreview
    }

    Repeater {
        model: listPreview.numPage
        anchors.fill: parent

        Rectangle {
            width: w
            height: 200

            color: "#0000ff"

            Text {
                id: prova
                text: listPreview.at(index)
            }
        }
    }
}


