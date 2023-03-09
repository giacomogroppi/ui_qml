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
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                text : model.name_file
            }

            Text {
                text: model.last_mod
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _controllerListFiles.clickFile(index)
                }
            }
        }
    }
}
