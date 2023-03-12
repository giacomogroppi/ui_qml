import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {
    property int index: 0

    Rectangle {
        id: containerButtonSettings
        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }

        width: 150

        SettingsButton {
            id: buttonShowSettingsFile
            t: "Settings for file"
            anchors.top: parent.top
            onClicked: {
                index = 0
            }
        }

        SettingsButton {
            id: buttonShowSettingsPerformance
            t: "Settings for performance"
            anchors.top: buttonShowSettingsFile.bottom
            onClicked: {
                index = 1
            }
        }

    }

    Rectangle {
        id: containerSettingsOptions
        anchors {
            top: parent.top
            right: parent.right
            left: containerButtonSettings.right
            bottom: parent.bottom
        }

        SettingFile {
            anchors.fill: parent
            visible: index === 0
        }

        SettingsPerformance {
            anchors.fill: parent
            visible: index === 1
        }
    }
}
