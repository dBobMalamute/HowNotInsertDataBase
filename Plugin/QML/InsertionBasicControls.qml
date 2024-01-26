import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    width: 140
    height: 200

    radius: 4
    border.color: "black"
    border.width: 4

    color: "grey"

    Text
    {
        text: "Speed: "
        font.pointSize: 12
        color: "#a6b0cb"
        x: 10
        y: 10
    }
    TextInput
    {
        font.pointSize: 12
        color: "#a6b0cb"
        text: idea.animationSpeed;
        x: 90
        y: 10
        selectByMouse: true;
        onEditingFinished:
        {
            idea.setAnimationSpeed(text);
        }
        validator: IntValidator{bottom: 20; top: 10000}
    }
    Button
    {
        text: "Pause"
        anchors.bottom: stepText.top
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked:
        {
            idea.setPaused(true);
        }
    }
    Button
    {
        id: stepText
        text: "Step"
        anchors.bottom: startText.top
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked:
        {
            idea.step();
        }
    }
    Button
    {
        id: startText
        text: "Start"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked:
        {
            idea.setPaused(false);
        }
    }
}
