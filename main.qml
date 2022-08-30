import QtQuick
import QtQuick.Controls
import mymod

Window {
    visible: true
    width: 800
    height: 600
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Hello World")
    color: "#F6F6F6"

    TextField {
        anchors.centerIn: parent
        width: 400
        height: 400
        text:"hello, 世界！"
    }
    TextBalloon {
            anchors.right: parent.right
            height: 220
            text: "hello, 世界！"
            width: 220
        }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5;height:960;width:1400}
}
##^##*/

