import QtQuick 2.15
import QtQuick.Controls 2.12

Item {
    Rectangle {
        id: address_box

        height: 40

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        color: "brown"

        Rectangle {
            id: containterFolderAddress
        }

        Rectangle {
            id: containerFileAddress
            Text{

            }
        }
    }

    Rectangle {
        id: toolBarListFiles

        width: 300

        anchors {
            top: address_box.bottom
            left: parent.left
            bottom: parent.bottom
        }

        ListOfFiles {
            anchors.fill: toolBarListFiles
        }
    }

    Rectangle {
        id: addFileContainer
    }

    RoundButton {
        id: button_add_file

        text: "New File"
        anchors {
            bottom: parent.bottom
            right: parent.right
        }

        anchors.margins: 10

        radius: width/2
        onClicked: {
            console.log("Button clicked")
            _controller.newFile()
        }
    }
}
