import QtQuick 2.15
import QtQuick.Controls 2.12

ListView {
    model: _controllerListFilesFolder

    height: parent.height
    width: parent.width

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

            pressAndHoldInterval: 400
            onPressAndHold: menu.popup()

            Menu {
                id: menu

                MenuItem {
                    text: "Elimina"
                    onTriggered: {
                        console.log("ListOfFolders function not implemented")
                    }
                }

                MenuItem {
                    text: "Rinomina"
                    onTriggered: {
                        console.log("ListOfFolders function not implemented")
                    }
                }
            }
        }
    }
}

