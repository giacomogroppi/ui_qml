import QtQuick 2.15
import QtQuick.Controls 2.12

RoundButton {
    required property string t
    property int h: 30
    property int w: 150

    text: t
    height: h
    width: w
    radius: width / 2
}
