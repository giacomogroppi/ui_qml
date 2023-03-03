import QtQuick 2.15
import QtQuick.Controls 2.12

Item {
    Rectangle {
        id: toolBarListFiles

        width: 300

        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }

        ListOfFiles {
            anchors.fill: toolBarListFiles
        }
    }

    Rectangle {
        id: address
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
        id: listFolderListFiles
    }

    Rectangle {
        id: listOfFiles
    }
}
