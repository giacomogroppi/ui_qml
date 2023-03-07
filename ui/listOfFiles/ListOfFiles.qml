import QtQuick 2.15

Rectangle {
    ListView {
        anchors.fill: parent
        model: _controllerListFiles

        delegate: Rectangle {
            width: parent.width
            height: 50
            color: index % 2 === 0 ? "white" : "brown"

            border.color: "black"

            Text {
                anchors.fill: parent
                text: model.name_file
            }
        }
    }
}
