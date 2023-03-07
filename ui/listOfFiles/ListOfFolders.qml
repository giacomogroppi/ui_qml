import QtQuick 2.15

ListView {
    model: _controllerListFilesFolder

    height: parent.height
    width: parent.width

    anchors.fill: parent

    delegate: Rectangle {
        width: parent.width
        height: 40
        color: index % 2 === 0 ? "white" : "brown"

        border.color: "black"

        Text {
            anchors {
                left: parent.left
                top: parent.top
                right: parent.right
            }

            text: model.folder_name
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("ListOfFolders click on " + index)
                _controllerListFilesFolder.click(index)
            }
        }
    }
}

