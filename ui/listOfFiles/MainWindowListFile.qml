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
        id: listFiles

        width: 300

        anchors {
            top: address_box.bottom
            left: parent.left
            bottom: parent.bottom
        }

        Rectangle {
            id: toolBarListFile
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
            height: 30
            color: "yellow"

            RoundButton {
                text: "+"

                anchors {
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }

                anchors.topMargin: 2
                anchors.bottomMargin: 2
                anchors.rightMargin: 5

                width: height

                background: Rectangle {
                    color: "#3F51B5"
                    border.width: 0
                    radius: width / 2
                }

                onClicked: {
                    console.log("New folder button")
                }
            }
        }

        ListOfFiles {
            visible: true
            anchors {
                left: parent.left
                bottom: parent.bottom
                top: toolBarListFile.bottom
            }
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
