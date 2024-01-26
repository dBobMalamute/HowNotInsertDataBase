import QtQuick 2.15
import QtQuick.Controls 2.15
import com.malamute.insertionLogs 1.0
import QtQuick.Controls.Material 2.12

Item
{
    id: root
    width: 140
    height: 260

    Rectangle
    {
        color: "black"
        radius: 10
        anchors.top: parent.top;
        anchors.topMargin: 6
        width: parent.width
        height: 200
    }

    StickFigure
    {
        visible: idea.personExists;
        anchors.bottom: nameText.top
        anchors.bottomMargin: 4
        anchors.horizontalCenter: parent.horizontalCenter
        scale: idea.person.height / 2.5;
        stickColor: idea.person.color;
    }
    Text
    {
        visible: idea.personExists;
        id: nameText;
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 64
        anchors.horizontalCenter: parent.horizontalCenter
        text: idea.person.name
        font.bold: true;
        font.pointSize: 14
        color: idea.person.color;
    }
    Button
    {
        id: addButton
        anchors.bottom: clearButton.top
        anchors.bottomMargin: -8
        anchors.horizontalCenter: parent.horizontalCenter
        height: 36
        width: parent.width -4
        text: "New"

        onClicked:
        {
            idea.addPerson();
        }

        font.capitalization: Font.MixedCase
        font.family: "verdana"
        font.bold: true;
        font.pointSize: 12
        Material.background: idea.outPortLabelColors[0]
        Material.foreground: "#1a1a1a"
    }
    Button
    {
        id: clearButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -4
        anchors.horizontalCenter: parent.horizontalCenter
        height: 36
        width: parent.width - 4
        text: "Clear"

        onClicked:
        {
            idea.clearPerson();
        }

        font.capitalization: Font.MixedCase
        font.family: "verdana"
        font.bold: true;
        font.pointSize: 12
        Material.background: Material.Grey
        Material.foreground: "#1a1a1a"
    }
}
