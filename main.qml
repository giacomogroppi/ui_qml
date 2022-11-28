import QtQuick
import QtQuick.Controls 6.3

Window {
    width: 1024
    height: 680
    minimumHeight: 600
    minimumWidth: height
    title: qsTr("Writernote")

    StackView {
        id: stackViewMain
        anchors.fill: parent
        initialItem: "qrc:/ui/pageCanvas/MainWindow.qml"
    }
}
