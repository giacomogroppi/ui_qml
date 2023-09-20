import QtQuick 2.15
import QtQuick.Controls 2.15

Window {
    width: 1024
    height: 680
    minimumHeight: 600
    minimumWidth: height
    visible: true
    title: qsTr("Writernote")

    /**
      * unfortunatly we can't read the enum defined in Controller
      * so we need to replicate it here
    */
    readonly property string mainName: "Main"
    readonly property string settingsName: "Settings"
    readonly property string listOfFilesName: "ListFiles"

    id: mainRoot

    StackView {
        id: stackViewMain
        anchors.fill: parent
        initialItem: _controller.uiSelected
    }

    // list of files
    function showFiles() {
        var newView = Qt.createComponent("qrc:/src/ui/listOfFiles/MainWindowListFile.qml");
        stackViewMain.push(newView);
        _controller.uiSelected = listOfFilesName
        console.log("call show Files");
    }

    function closeFiles() {
        stackView.pop();
        console.log("Call close list of files");
    }

    // main options
    function showMain() {
        var newView = Qt.createComponent("qrc:/src/ui/pageCanvas/MainWindow.qml")
        stackViewMain.push(newView)
        _controller.uiSelected = ""
        console.log("Call show main")
    }

    function closeMain() {
        stackViewMain.pop()
        console.log("Call close main")
    }

    // settings options
    function showSettings() {
        stackViewMain.push(Qt.createComponent("qrc:/src/ui/settings/Settings.qml"))
        console.log("Call show settings");
    }

    function closeSettings() {
        stackViewMain.pop()
        console.log("Call close settings");
    }
}
