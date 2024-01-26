#include <QQmlEngine>

#include "Plugin.h"

#include "PeopleDataType.h"

#include "PersonInput.h"
#include "DataBaseAfter.h"
#include "DataBaseBefore.h"
#include "MikeInput.h"
#include "MidgetInput.h"
#include "ChadInput.h"
#include "InsertionStartAtBeginning.h"
#include "InsertionSmart.h"

QString Plugin::PluginName()
{
    return "DataBaseInsertionVideo";
}

void Plugin::registerIdeas(std::shared_ptr<IdeaRegistry> ideaRegistry)
{
    ideaRegistry->registerIdea<PersonInput>();
    ideaRegistry->registerIdea<DataBaseBefore>();
    ideaRegistry->registerIdea<MikeInput>();

    ideaRegistry->registerIdea<ChadInput>();
    ideaRegistry->registerIdea<MidgetInput>();

    ideaRegistry->registerIdea<InsertionStartAtBeginning>();
    ideaRegistry->registerIdea<InsertionSmart>();
    ideaRegistry->registerIdea<DataBaseAfter>();

    qmlRegisterType(QUrl("qrc:/QML/StickFigure.qml"), "com.malamute.insertionLogs", 1, 0, "StickFigure");
}

void Plugin::registerDataTypeAttributes(std::shared_ptr<DataTypeRegistry> dataTypeRegistry)
{
    dataTypeRegistry->registerDataTypeAttributes<PeopleDataTypeAttributes>();
}
