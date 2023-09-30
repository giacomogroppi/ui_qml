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

    property var viewFiles: Component = null;
    property var viewSettings: Component = null;
    property var viewCanvas: Component = null;

    id: mainRoot

    StackView {
        id: stackViewMain
        anchors.fill: parent
        initialItem: _controller.uiSelected
    }

    // list of files
    function showFiles() {
        if (viewFiles == null) {
            viewFiles = Qt.createComponent("qrc:/src/ui/listOfFiles/MainWindowListFile.qml");
        }

        stackViewMain.push(viewFiles);
        _controller.uiSelected = listOfFilesName
        console.log("call show Files");
    }

    function closeFiles() {
        stackViewMain.pop();
        console.log("Call close list of files");
    }

    // main options
    function showMain() {
        if (viewCanvas == null) {
            viewCanvas = Qt.createComponent("qrc:/src/ui/pageCanvas/MainWindow.qml")
        }

        stackViewMain.push(viewCanvas)
        _controller.uiSelected = mainName
        console.log("Call show main")
    }

    function closeMain() {
        stackViewMain.pop()
        console.log("Call close main")
    }

    // settings options
    function showSettings() {
        if (viewSettings == null) {
            viewSettings = Qt.createComponent("qrc:/src/ui/settings/Settings.qml")
        }
        stackViewMain.push(viewSettings)
        _controller.uiSelected = settingsName
        console.log("Call show settings");
    }

    function closeSettings() {
        stackViewMain.pop()
        console.log("Call close settings");
    }
}
