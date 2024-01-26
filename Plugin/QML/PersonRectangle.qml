import QtQuick 2.15
import com.malamute.insertionLogs 1.0
import QtQuick.Controls 2.15

Item
{
    id: root
    property int index: 0;
    property color personColor : "#000000"
    property string name : "name"
    property double personHeight : 1.0
    property double personOpacity: 1.0;
    property double finalX: 0.0;

    width: 60
    height: 200

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true;

    }
    Label
    {
        id: nullWords
        opacity: parent.opacity;
        anchors.centerIn: parent
        font.pointSize: 10
        font.bold: true
        font.family: "inconsolata"

        text: "";

        ToolTip.delay: 1000;
        ToolTip.timeout: 5000;
        ToolTip.visible: mouseArea.containsMouse;
        ToolTip.text: "Height\n" + parseFloat(1.2*personHeight).toFixed(3);
    }

    Rectangle
    {
        id: backgroundRect
        width: parent.width - 4;
        height: 192
        anchors.centerIn: parent
        color: "#000000"
    }

    StickFigure
    {
        id: stickFigure
        anchors.bottom: nameText.top
        anchors.bottomMargin: 4
        anchors.horizontalCenter: parent.horizontalCenter
        scale: personHeight / 2.5;
        stickColor: personColor;
        opacity: personOpacity
    }

    Text
    {
        id: nameText;
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.horizontalCenter: parent.horizontalCenter
        text: name
        font.bold: true;
        font.pointSize: 14
        color: personColor;
        opacity: 1.0
    }
    BusyIndicator
    {
        id: busyIndicator
        anchors.centerIn: parent
        width: parent.width;
        running: false
    }

    function busyLoad()
    {
        busyLoadAnimation.start();
    }

    function quickLoad()
    {
        personOpacity = 1.0;
    }

    SequentialAnimation
    {
        id: busyLoadAnimation
        ScriptAction
        {
            script: busyIndicator.running = true;
        }
        PauseAnimation
        {
            duration: 18 * idea.animationSpeed
        }
        ScriptAction
        {
            script: busyIndicator.running = false;
        }
        ScriptAction
        {
            script: personOpacity = 1.0;
        }
    }
    function moveThirty()
    {
        move30toRightAnimation.start();
    }
    NumberAnimation
    {
        id: move30toRightAnimation
        duration: 10 * idea.animationSpeed
        target: root
        property: "x"
        to: root.x + 30
    }
    function moveSixty()
    {
        move60toRightAnimation.start();
    }
    NumberAnimation
    {
        id: move60toRightAnimation
        duration: 10 * idea.animationSpeed
        target: root
        property: "x"
        to: root.x + 60
    }
    function punt(x)
    {
        finalX = x;
        puntAnimation.start();
    }
    SequentialAnimation
    {
        id: puntAnimation;
        ParallelAnimation
        {
            NumberAnimation
            {
                target: root
                property: "x"
                to: finalX / 2
                duration: 15 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: root
                property: "y"
                to: -300
                duration: 15 * idea.animationSpeed
                easing.type: Easing.OutQuad
            }
            NumberAnimation
            {
                target: root
                property: "rotation"
                to: 360
                duration: 15 * idea.animationSpeed
            }
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: root
                property: "x"
                to: finalX
                duration: 15 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: root
                property: "y"
                to: 0
                duration: 15 * idea.animationSpeed
                easing.type: Easing.InQuad
            }
            NumberAnimation
            {
                target: root
                property: "rotation"
                to: 720
                duration: 15 * idea.animationSpeed
            }
        }
    }

    Behavior on personOpacity
    {
        NumberAnimation{duration: 2 * idea.animationSpeed}
    }
}
