import QtQuick 2.15

Item
{
    id: root;
    property int index: -1
    opacity: 0.01

    function setYes()
    {
        image2.source = "qrc:/Images/Yes.png"
        line2.color = "#10aa10"
        switchAnimation.start();
    }
    function setNo(delay)
    {
        image2.source = "qrc:/Images/No.png"
        line2.color = "#cb1212"
        if(!delay)
            switchAnimation.start();
        else
            delaySwitchAnimation.start();
    }
    function fadeOut()
    {
        fadeOutAnimation.start();
    }

    Image
    {
        id: image;
        x: - width/2
        source: "qrc:/Images/Unknown.png";
    }
    Image
    {
        id: image2
        x: -width/2
        opacity: 0.0;
    }

    Rectangle
    {
        id: line2

        opacity: 0.0;
        y: -100
        height: 100
        width: 2
        x: -1
        color: "#982198"
    }

    Rectangle
    {
        id: line
        y: -100
        height: 100
        width: 2
        x: -1
        color: "#982198"
    }

    Component.onCompleted:
    {
        fadeInAnimation.start();
    }
    PropertyAnimation
    {
        id: fadeInAnimation
        target: root
        property: "opacity"
        to: 1.0
        duration: 3*idea.animationSpeed;
    }
    SequentialAnimation
    {
        id: fadeOutAnimation
        PropertyAnimation
        {
            target: root
            property: "opacity"
            to: 0.0
            duration: 10*idea.animationSpeed;
        }
        ScriptAction
        {
            script: root.destroy();
        }
    }

    SequentialAnimation
    {
        id: delaySwitchAnimation
        PauseAnimation
        {
            duration: 5*idea.animationSpeed
        }
        ScriptAction
        {
            script: switchAnimation.start();
        }
    }

    SequentialAnimation
    {
        id: switchAnimation
        ParallelAnimation
        {
            PropertyAnimation
            {
                target: line
                property: "opacity"
                to: 0.0;
                duration: 1*idea.animationSpeed
            }
            PropertyAnimation
            {
                target: image
                property: "opacity"
                to: 0.0;
                duration: 1*idea.animationSpeed
            }
        }
        ParallelAnimation
        {
            PropertyAnimation
            {
                target: line2
                property: "opacity"
                to: 1.0;
                duration: 1*idea.animationSpeed
            }
            PropertyAnimation
            {
                target: image2
                property: "opacity"
                to: 1.0;
                duration: 1*idea.animationSpeed
            }
        }
    }
}
