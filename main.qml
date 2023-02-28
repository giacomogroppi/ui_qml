import QtQuick 2.15
import QtQuick.Controls 2.15

Window {
    width: 1024
    height: 680
    minimumHeight: 600
    minimumWidth: height
    visible: true
    title: qsTr("Writernote")


    StackView {
        id: stackViewMain
        anchors.fill: parent
        // pagina di scrittura
        //initialItem: "qrc:/ui/pageCanvas/MainWindow.qml"

        // pagina in cui vengono mostrati i file
        initialItem: "qrc:/ui/listOfFiles/MainWindowListFile.qml"
    }
}
