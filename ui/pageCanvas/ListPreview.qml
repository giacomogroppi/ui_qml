import QtQuick

Rectangle {
    property int w: 200

    color: "#0000ff"

    ListView {
        anchors.fill: parent
        model: _controllerListPreview

        delegate: Rectangle {
            color: Qt.rgba(0.9,0.9,0.9)
            height: childrenRect.height
            width: parent.width

            Text {
                text: "nome: " + model.nome
                anchors.left: parent.left
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onDoubleClicked: {
                    if (mouse.button === Qt.LeftButton) {
                        _myModel.duplicateData(model.index);
                    } else if (mouse.button === Qt.RightButton) {
                        _myModel.removeData(model.index);
                    }
                }
            }
        }
    }
}


