#include "DataBaseBefore.h"

DataBaseBeforeAttributes::DataBaseBeforeAttributes()
{
    m_listName = "DataBase Before";
    m_displayName = "DataBase Before";
    m_iconPath = "qrc:/Icons/DataBaseBefore.png";

    m_dataTypesOut.push_back(Magic<PeopleDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/DataBaseBefore.qml";
    m_minimizedQMLPath = ":/QML/DataBaseBeforeMinimized.qml";
    m_minimizedName = "DataBase\nBefore";
    m_startMinimized = false;
}

const IdeaAttributes DataBaseBefore::attributes()
{
    return Magic<DataBaseBeforeAttributes>::cast();
}

DataBaseBefore::DataBaseBefore() :
    m_numPeople(15)
{
    m_personModel = new PersonArrayModel();
    m_personModel->AddPerson(15);
    setStatus(IdeaStatus::Working, "Working");
    m_output = std::make_shared<PeopleDataType>(m_personModel);
    emit newData(0);
}

QJsonObject DataBaseBefore::save() const
{
    QJsonObject ideaJson = Idea::save();
    ideaJson["np"] = m_numPeople;
    QJsonArray heightsArray;
    QJsonArray namesArray;
    QJsonArray colorsArray;

    for(int i = 0; i < m_numPeople; i++)
    {
        heightsArray.append(m_personModel->getHeights().at(i));
        namesArray.append(m_personModel->getNames().at(i));
        colorsArray.append(m_personModel->getColors().at(i).name());
    }
    ideaJson["ha"] = heightsArray;
    ideaJson["na"] = namesArray;
    ideaJson["ca"] = colorsArray;

    return ideaJson;
}

void DataBaseBefore::load(const QJsonObject &p)
{
    QJsonValue v = p["np"];
    if(!v.isUndefined())
    {
        m_numPeople = v.toInt();
    }
    v = p["ha"];
    if(!v.isUndefined())
    {
        QJsonArray heightsArray = v.toArray();
        v = p["na"];
        QJsonArray namesArray = v.toArray();
        v = p["ca"];
        QJsonArray colorsArray = v.toArray();

        m_personModel->clear();;
        for(int i = 0; i < m_numPeople; i++)
        {
            Person* person = new Person();
            person->setHeight(heightsArray.at(i).toDouble());
            person->setName(namesArray.at(i).toString());
            person->setColor(colorsArray.at(i).toString());
            m_personModel->addPerson(person);
            m_output = std::make_shared<PeopleDataType>(m_personModel);
            emit newData(0);
        }
    }

    Idea::load(p);
}

std::shared_ptr<DataType> DataBaseBefore::dataOut(PlugNumber)
{
    return m_output;
}

int DataBaseBefore::numPeople() const
{
    return m_numPeople;
}

void DataBaseBefore::setNumPeople(int newNumPeople)
{
    if (m_numPeople == newNumPeople)
        return;
    m_numPeople = newNumPeople;
    emit numPeopleChanged();
}

void DataBaseBefore::generateNewData()
{
    m_personModel->clear();
    m_personModel->AddPerson(m_numPeople);
    m_output = std::make_shared<PeopleDataType>(m_personModel);
    emit newData(0);
}

PersonArrayModel *DataBaseBefore::personModel() const
{
    return m_personModel;
}
