import QtQuick 2.15

Rectangle {
    ListView {
        anchors.fill: parent
        model: _controllerListFilesFolder

        delegate: Rectangle {
            width: parent.width
            height: 100
            color: index % 2 === 0 ? "white" : "brown"

            border.color: "black"

            Text {
                anchors.fill: parent
                text: model.path
            }
        }
    }
}
