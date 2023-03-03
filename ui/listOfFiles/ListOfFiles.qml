import QtQuick 2.15

Rectangle {
    ListView {
        anchors.fill: parent
        model: _controllerListFilesFolder

        delegate: Rectangle {
            width: 100
            color: index % 2 === 0 ? "blue" : "red"


            Text {
                anchors.fill: parent
                text: model.path
            }
        }
    }
}
