import QtQuick 2.15

Item
{
    property color stickColor: "green"

    id: figureRect
    width: 80
    height: 180
    transformOrigin: Item.Bottom

    Rectangle
    {
        id: head
        anchors.horizontalCenter: parent.horizontalCenter
        y: 0
        width: 60
        height: 60
        radius: width / 2;
        color: "#1a1a1a"
        border.width: 5
        border.color: stickColor

        Rectangle
        {
            color: stickColor
            width: 8
            height: width
            radius: width
            x: 16
            y: 20
        }
        Rectangle
        {
            color: stickColor
            width: 8
            height: width
            radius: width / 2
            x: 36
            y: 20
        }

        Rectangle
        {
            color: stickColor
            width: 14
            height: 2
            radius: 2
            x: 30 - width/2
            y: 43
        }
    }
    Rectangle
    {
        id: body
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: head.bottom
        width: 8
        height: 70
        color: stickColor
        antialiasing: true;
    }
    Rectangle
    {
        id: arm1
        x: 53.5
        y: 59
        width: 6
        height: 50
        rotation: -45
        color: stickColor
        antialiasing: true;
    }
    Rectangle
    {
        id: arm2
        x: 21
        y: 59
        width: 6
        height: 50
        rotation: 45
        color: stickColor
        antialiasing: true;
    }
    Rectangle
    {
        id: leg1
        x: 53.5
        y: 115
        width: 6
        height: 70
        rotation: -30
        color: stickColor
        antialiasing: true;
    }
    Rectangle
    {
        id: leg2
        x: 21
        y: 115
        width: 6
        height: 70
        rotation: 30
        color: stickColor
        antialiasing: true;
    }
}
