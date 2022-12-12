import QtQuick 2.15
import writernote.WQMLItemListPreview 1.0

Rectangle {
    property int w: 200

    color: "#0000ff"

    ListView {
        anchors.fill: parent
        model: _controllerListPreview

        delegate: Rectangle {
            property int heigthItem: 260
            color: Qt.rgba(0.9,0.9,0.9)
            height: heigthItem
            width: parent.width

            Rectangle {
                anchors.fill: parent

                color: index % 2 === 1 ? "white" : "brown"

                Rectangle {
                    color: "red"
                    anchors {
                        top: parent.top
                        right: parent.right
                        left: parent.left
                        bottom: text_label.top
                    }

                    border.color: "black"
                    border.width: 2

                    WItemListPreview {
                        visible: false
                        id: imagePreview
                        width: parent.width - 20
                        indexObject: index
                        anchors.fill: parent
                    }
                }

                Rectangle {
                    id: text_label
                    anchors {
                        bottom: parent.bottom
                        left: parent.left
                        right: parent.right
                    }
                    color: "transparent"
                    height: 30

                    Text {
                        anchors.centerIn: parent

                        text: "Index: " + (index + 1)
                    }
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
}

