import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import com.malamute.insertionLogs 1.0
import QtQuick.Controls.Material 2.12


Item
{
    id: root
    width: Math.max(600, idea.numPeople * 60)
    height: 200

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
}
