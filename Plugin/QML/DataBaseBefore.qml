import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import com.malamute.insertionLogs 1.0
import QtQuick.Controls.Material 2.12


Item
{
    id: root
    width: Math.max(200, idea.numPeople * 60)
    height: 226

    RowLayout
    {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 200
        ListView
        {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            model: idea.personModel;
            orientation: ListView.Horizontal;
            delegate: Item
            {
                width: 60
                height: 200
                Rectangle
                {
                    width: parent.width - 2;
                    height: 192
                    anchors.centerIn: parent
                    color: "black"
                }

                StickFigure
                {
                    anchors.bottom: nameText.top
                    anchors.bottomMargin: 4
                    anchors.horizontalCenter: parent.horizontalCenter
                    scale: model.height / 2.5;
                    stickColor: model.color;
                }
                Text
                {
                    id: nameText;
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 4
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: model.name
                    font.bold: true;
                    font.pointSize: 14
                    color: model.color;
                }
            }
        }
    }

    Rectangle
    {
        height: 28
        radius: 4
        width: addButton.width + 8 + countRectangle.width;
        y: 197
        x: 200
        color: "black"

        Row
        {
            height: 36
            y: -4
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            spacing: 4
            Button
            {
                id: addButton
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
                y: 6
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
    }
}
