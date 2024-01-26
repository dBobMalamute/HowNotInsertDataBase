import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import com.malamute.insertionLogs 1.0
import QtQuick.Controls.Material 2.12


Item
{
    id: root
    width: 140
    height: 60

    Button
    {
        id: addButton
        anchors.horizontalCenter: parent.horizontalCenter
        height: 36
        text: "New"
        onClicked:
        {
            idea.generateNewData();
        }

        font.capitalization: Font.MixedCase
        font.family: "verdana"
        font.bold: true;
        font.pointSize: 12
        Material.background: idea.outPortLabelColors[0]
        Material.foreground: "#1a1a1a"
    }
    Rectangle
    {
        id: countRectangle;
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 2
        color: "#4c53c0"
        width: 140
        height: 24
        radius: 2
        Text
        {
            text: "People: "
            font.pointSize: 12
            font.family: "verdana"
            font.bold: true;

            x: 10
            anchors.verticalCenter: parent.verticalCenter
        }
        TextInput
        {
            font.pointSize: 12
            font.underline: true;
            font.family: "verdana"
            font.bold: true;

            text: idea.numPeople;
            x: 90
            anchors.verticalCenter: parent.verticalCenter
            selectByMouse: true;
            onEditingFinished:
            {
                idea.setNumPeople(text);
                idea.generateNewData();
            }
            validator: IntValidator{bottom: 1.0; top: 1000}
        }
    }
}
