import QtQuick 2.15
import QtMultimedia 5.15

Item
{
    id: root
    width: 1000;
    height: 300

    property int insertionIndex: 0;
    property int numPeople: 0;
    property double insertPersonHeight: 99999;

    Connections
    {
        target: idea
        function onSetupBefore(names, colors, heights)
        {
            let i = 0;
            let personRectComponent;
            let personRectObj;

            numPeople = names.length;
            root.width = (names.length) * 60 + 60 + 100
            for(i = 0; i < names.length; i++)
            {
                personRectComponent = Qt.createComponent("PersonRectangle.qml");
                personRectObj = personRectComponent.createObject(dataBaseVisualItem,
                                                                 {x: 30 + 60 * i,
                                                                     index: i,
                                                                     name: names[i],
                                                                     personOpacity: 0.0,
                                                                     personColor: colors[i],
                                                                     personHeight: heights[i]});
            }
        }

        function onClearAll()
        {
            let i;
            for(i = 0; i < dataBaseVisualItem.children.length; i++)
            {
                dataBaseVisualItem.children[i].destroy();
            }
            for(i = 0; i < toAddVisualItem.children.length; i++)
            {
                toAddVisualItem.children[i].destroy();
            }
        }

        function onNewPersonAdded(name, color, height, index)
        {
            insertionIndex = index;
            dataBaseVisualItem.makeAllInVisible();
            insertPersonHeight = height;

            for(let i = 0; i < toAddVisualItem.children.length; i++)
            {
                toAddVisualItem.children[i].destroy();
            }

            let personRectComponent;
            let personRectObj;
            personRectComponent = Qt.createComponent("PersonRectangle.qml");
            personRectObj = personRectComponent.createObject(toAddVisualItem,
                                                             {x: 0, opacity: 0.0,
                                                                 personOpacity: 0.0,
                                                                 name: name,
                                                                 personColor: color,
                                                                 personHeight: height});
            insertionLocationMarkers.setup(numPeople + 1);
            greenRuler.y = 170 - 180 * (height/ 2.5)
            botBrain.start();
        }
        function onPausedChanged(paused)
        {
            if(!paused)
            {
                botBrain.nextAction();
            }
        }

        function onOneStep()
        {
            botBrain.oneAction();
        }
    }

    Item
    {
        id: botBrain

        property bool setup: false;
        property bool found: false;
        property int searchIndex: 0;
        property int lowBound: 0;
        property int upBound: 0;

        function start()
        {
            setup = false;
            found = false;
            lowBound = -1;
            upBound = numPeople;
            searchIndex = -1;
            nextAction();
        }

        function nextAction()
        {
            if(idea.paused)
                return;

            oneAction();
        }

        function oneAction()
        {
            if(!idea.valid)
                return;

            if(setup === false)
            {
                startingAnimation.start();
                setup = true;
            }
            else if(!found)
            {
                searchIndex = Math.ceil((upBound + lowBound) / 2)
                searchAnimation.restart()

                if(idea.getHeight(searchIndex) > insertPersonHeight)
                {
                    upBound = searchIndex;
                }
                else
                {
                    lowBound = searchIndex;
                }
                if(upBound <= lowBound + 1)
                    found = true;
            }
            else
            {
                insertionAnimation.start();
            }
        }
    }
    SequentialAnimation
    {
        id: startingAnimation

        PauseAnimation{duration: 1 * idea.animationSpeed}
        ScriptAction{script: bot.x = 0;}
        ScriptAction{script: toAddVisualItem.makeVisible();}
        ScriptAction{script: toAddVisualItem.fadeIn()}
        ScriptAction{script: greenRuler.opacity = 1.0}
        PauseAnimation{duration: 10 * idea.animationSpeed}
        ScriptAction{script: botBrain.nextAction();}
    }

    SequentialAnimation
    {
        id: searchAnimation
        PauseAnimation
        {
            duration: 1 * idea.animationSpeed;
        }
        RotationAnimation
        {
            target: bot
            to: 90
            duration: 2 * idea.animationSpeed
            easing.type: Easing.InOutQuad
        }
        PropertyAnimation
        {
            target: bot
            property: "x"
            to: 130 + botBrain.searchIndex*60;
            duration: 2 * idea.animationSpeed;
            easing.type: Easing.InOutQuad
        }
        RotationAnimation
        {
            target: bot
            to: 0
            duration: 2 * idea.animationSpeed
            easing.type: Easing.InOutQuad
        }
        ScriptAction
        {
            script: dataBaseVisualItem.makeVisibleIndex(botBrain.searchIndex);
        }
        PauseAnimation
        {
            duration: 20 * idea.animationSpeed;
        }
        ScriptAction
        {
            script: if(botBrain.searchIndex > -1 && !botBrain.found)
                    {
                        if(idea.getHeight(botBrain.searchIndex) > insertPersonHeight)
                        {
                            insertionLocationMarkers.setNoAbove(botBrain.searchIndex);
                        }
                        else
                        {
                            insertionLocationMarkers.setNoBelow(botBrain.searchIndex);
                        }
                    }
        }
        PauseAnimation{duration: 1 * idea.animationSpeed;}
        ScriptAction{script: botBrain.nextAction();}
    }

    SequentialAnimation
    {
        id: insertionAnimation
        PauseAnimation{duration: 6 * idea.animationSpeed}
        ScriptAction
        {
            script: insertionLocationMarkers.validSpot(insertionIndex + 1)
        }
        ScriptAction
        {
            script: greenRuler.opacity = 0.0;
        }
        RotationAnimation
        {
            target: bot
            to: -90
            duration: 2 * idea.animationSpeed
            easing.type: Easing.InOutQuad
        }
        PropertyAnimation
        {
            target: bot
            property: "x"
            to: 0;
            duration: 8 * idea.animationSpeed;
            easing.type: Easing.InOutQuad
        }
        RotationAnimation
        {
            target: bot
            to: 0
            duration: 2 * idea.animationSpeed
            easing.type: Easing.InOutQuad
        }
        PauseAnimation{duration: (4 * idea.animationSpeed)}
        ScriptAction{script: puntSound.play()}
        ScriptAction{script: batAnimation.start()}
        PauseAnimation{duration: (150)}
        ScriptAction
        {
            script: toAddVisualItem.moveToIndex();
        }
        PauseAnimation{duration: 6 * idea.animationSpeed}
        ScriptAction
        {
            script: insertionLocationMarkers.deleteAll()
        }
        ScriptAction
        {
            script: dataBaseVisualItem.moveRight();
        }
        NumberAnimation
        {
            target: root
            property: "width"
            to: root.width + 60;
            duration: 10 * idea.animationSpeed;
        }
        PauseAnimation{duration: 30 * idea.animationSpeed}
        ScriptAction{script: idea.insertionAnimationCompleted();}
    }

    Item
    {
        id: insertionLocationMarkers
        visible: idea.valid;
        x: 100
        width: parent.width - 100
        height: 240;

        function setup(number)
        {
            insertionLocationMarkers.deleteAll();
            let component; let obj;
            for(let i = 0; i < number; i++)
            {
                component = Qt.createComponent("LocationMarker.qml");
                obj = component.createObject(insertionLocationMarkers, {x: 29 + 60*i, y: 200, index: i})
            }
        }
        function setNoAbove(index)
        {
            for(let i = 0; i < insertionLocationMarkers.children.length; i++)
            {
                if(insertionLocationMarkers.children[i].index > index)
                {
                    insertionLocationMarkers.children[i].setNo(true);
                }
            }
        }
        function setNoBelow(index)
        {
            for(let i = 0; i < insertionLocationMarkers.children.length; i++)
            {
                if(insertionLocationMarkers.children[i].index <= index)
                {
                    insertionLocationMarkers.children[i].setNo(true);
                }
            }
        }

        function validSpot(index)
        {
            for(let i = 0; i < insertionLocationMarkers.children.length; i++)
            {
                if(insertionLocationMarkers.children[i].index === index)
                    insertionLocationMarkers.children[i].setYes();
                else
                    insertionLocationMarkers.children[i].setNo();
            }
        }

        function deleteAll()
        {
            for(let i = 0; i < insertionLocationMarkers.children.length; i++)
            {
                insertionLocationMarkers.children[i].fadeOut();
            }
        }
    }

    Rectangle
    {
        id: track
        width: parent.width
        height: 50
        y: 250
        color: "grey"
        clip: true
        Row
        {
            anchors.fill: parent
            Repeater
            {
                model: (track.width / 200) + 1;
                Image
                {
                    source: "qrc:/Images/Road.png"

                }
            }
        }

    }
    Item
    {
        id: botBox
        anchors.fill: track
        z: 10
        Image
        {
            id: bot;
            source: "qrc:/Images/PinkBot.png"
        }
    }

    Item
    {
        id: dataBaseVisualItem
        x: 100
        width: parent.width - 100
        height: 200
        function moveRight()
        {
            for(let i = 0; i < dataBaseVisualItem.children.length; i++)
            {
                if(dataBaseVisualItem.children[i].index > insertionIndex)
                    dataBaseVisualItem.children[i].moveSixty();
            }
        }
        function makeVisibleIndex(index)
        {
            for(let i = 0; i < dataBaseVisualItem.children.length; i++)
            {
                if(dataBaseVisualItem.children[i].index === index)
                    dataBaseVisualItem.children[i].busyLoad();
            }
        }
        function makeAllInVisible()
        {
            for(let i = 0; i < dataBaseVisualItem.children.length; i++)
            {
                dataBaseVisualItem.children[i].personOpacity = 0;
            }
        }
    }
    Item
    {
        id: toAddVisualItem;
        anchors.fill: parent

        function fadeIn()
        {
            for(let i = 0; i < toAddVisualItem.children.length; i++)
            {
                toAddVisualItem.children[i].quickLoad();
            }
        }
        function makeVisible()
        {
            for(let i = 0; i < toAddVisualItem.children.length; i++)
            {
                toAddVisualItem.children[i].opacity = 1.0;
            }
        }

        function moveToIndex()
        {
            for(let i = 0; i < toAddVisualItem.children.length; i++)
            {
                toAddVisualItem.children[i].punt(190 + 60*root.insertionIndex)
            }
        }
    }

    Rectangle
    {
        id: greenRuler;
        opacity: 0.0;
        width: root.width - 22
        x: 2
        height: 2
        color: "green"
        Behavior on opacity
        {
            NumberAnimation {duration: 2 * idea.animationSpeed}
        }
    }

    Image
    {
        id: bat
        source: "qrc:/Images/Bat.png"
        x: 24
        y: 156
        z: 100
        transformOrigin: Item.Bottom;
        opacity: 0.0;

        SequentialAnimation
        {
            id: batAnimation;
            PropertyAction
            {
                target: bat
                property: "rotation"
                value: -135;
            }
            PropertyAnimation
            {
                target: bat
                to: 1.0;
                property: "opacity"
                duration: 1* idea.animationSpeed
            }
            RotationAnimation
            {
                target: bat
                to: 45
                duration: 3* idea.animationSpeed
                easing.type: Easing.InOutQuad;
            }
            PropertyAnimation
            {
                target: bat
                to: 0.0;
                property: "opacity"
                duration: 1* idea.animationSpeed
            }
        }
    }

    MediaPlayer
    {
        id: puntSound
        source: "qrc:/SoundEffects/PunchEffect.wav"
        volume: 1.0
    }
}
