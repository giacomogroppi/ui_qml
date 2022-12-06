import QtQuick 2.15

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
                text: model.nome +" "+ model.cognome +" "+ model.eta

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


