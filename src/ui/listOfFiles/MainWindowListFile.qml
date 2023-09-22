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
            id: containerFileAddress
            anchors.centerIn: parent

            Text{
                text: _controllerListFiles.dir_selected
                anchors.fill: parent
                font.pointSize: 16
            }
        }
    }

    Rectangle {
        id: listFiles

        width: 200

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

            RoundButton {
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
                    _controllerListFiles.createNewFolder("prova")
                }
            }
        }

        ListOfFolders {
            id: listOfFolders
            visible: _controllerListFolder.isVisible
            anchors {
                left: parent.left
                bottom: containerBottom.top
                top: toolBarListFile.bottom
            }
        }

        Rectangle {
            id: containerBottom
            height: 45
            anchors {
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            color: "yellow"

            RoundButton {
                id: buttonTrash
                radius: width / 2

                anchors.verticalCenter: parent.verticalCenter

                anchors {
                    right: parent.right
                }
            }

            RoundButton {
                id: buttonSettings
                radius: width / 2

                anchors.verticalCenter: parent.verticalCenter

                anchors {
                    right: buttonTrash.left
                }

                anchors.rightMargin: 5
            }
        }
    }

    ListOfFiles {
        id: listOfFiles
        anchors {
            right: parent.right
            left: listFiles.right
            top: address_box.bottom
            bottom: parent.bottom
        }
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
