import QtQuick 2.15
import QtQuick.Controls 2.12
import writernote.WQMLItemListPreview 1.0

Rectangle {
    property int w: 200

    color: "#0000ff"

    width: w

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

                    Button {
                        id: buttonShowProperty
                        anchors {
                            left: imagePreview.left
                            bottom: imagePreview.bottom
                        }

                        anchors.margins: 2

                        height: 25
                        width: height
                        background: Rectangle {
                            anchors.fill: parent
                            color: "yellow"
                        }

                        Rectangle {
                            anchors.fill: parent

                            Text {
                                anchors.centerIn: parent
                                text: "."
                                font.bold: true
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                            onClicked: (mouse)=> {
                                onClicked: {
                                    console.log("tua madre")
                                    popupOptions.showObject(index, mouse.x, mouse.y)
                                }
                            }
                        }

                        Popup {
                            property int indexObject: -1

                            function showObject(index, x, y) {
                                console.log("popupOptions show with index " + index + " x " + x + " y " + y)
                                popupOptions.indexObject = index
                                popupOptions.visible = true
                                popupOptions.x = x
                                popupOptions.y = y
                            }

                            id: popupOptions

                            Rectangle {
                                Button {
                                    id: buttonAddPage
                                }
                                Button {
                                    id: buttonRemovePage
                                }
                                Button {
                                    id: buttonCopyPage
                                }
                            }
                        }
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

                //MouseArea {
                //    anchors.fill: parent
                //    acceptedButtons: Qt.LeftButton | Qt.RightButton
                //    onDoubleClicked: {
                //        if (mouse.button === Qt.LeftButton) {
                //            _myModel.duplicateData(model.index);
                //        } else if (mouse.button === Qt.RightButton) {
                //            _myModel.removeData(model.index);
                //        }
                //    }
                //}
            }
        }
    }
}

