#include "PersonInput.h"
#include "PersonFactory.h"
#include <QVariant>

PersonInputAttributes::PersonInputAttributes()
{
    m_listName = "Person Input";
    m_displayName = "";
    m_iconPath = "qrc:/Icons/PersonInput.png";

    m_dataTypesOut.push_back(Magic<PeopleDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/PersonInputDisplay.qml";
}

const IdeaAttributes PersonInput::attributes()
{
    return Magic<PersonInputAttributes>::cast();
}

PersonInput::PersonInput()
{
    m_person = PersonFactory::getInstance().getGreenGuy();
    setPersonExists(true);
    setStatus(IdeaStatus::Working, "Working");

    m_personModel = new PersonArrayModel();
    m_personModel->addPerson(m_person);
    m_output = std::make_shared<PeopleDataType>(m_personModel);
    emit newData(0);
}

QJsonObject PersonInput::save() const
{
    QJsonObject ideaJson = Idea::save();
    if(m_person && m_personExists)
    {
        ideaJson["n"] = m_person->name();
        ideaJson["h"] = m_person->height();
        ideaJson["pc"] = m_person->color().name();
    }
    if(!m_personExists)
    {
        ideaJson["np"] = false;
    }
    return ideaJson;
}

void PersonInput::load(const QJsonObject &p)
{
    QJsonValue v = p["n"];
    if(!v.isUndefined())
    {
        delete m_person;
        m_person = new Person();
        m_person->setName(v.toString());
        v = p["h"];
        m_person->setHeight(v.toDouble());
        v = p["pc"];
        m_person->setColor(v.toString());
        emit personChanged();
        emit personExistsChanged();
    }
    v = p["np"];
    if(!v.isUndefined())
    {
        clearPerson();
    }

    Idea::load(p);
}

std::shared_ptr<DataType> PersonInput::dataOut(PlugNumber)
{
    return m_output;
}

Person *PersonInput::person() const
{
    return m_person;
}

bool PersonInput::personExists() const
{
    return m_personExists;
}

void PersonInput::setPersonExists(bool newPersonExists)
{
    if (m_personExists == newPersonExists)
        return;
    m_personExists = newPersonExists;
    emit personExistsChanged();
}

void PersonInput::clearPerson()
{
    if(m_personExists == true)
    {
        setDefaultStatus();
        setPersonExists(false);
    }
}

void PersonInput::addPerson()
{
    if(m_personExists)
    {
        m_person = PersonFactory::getInstance().getGreenGuy();
        emit personChanged();
    }
    else
    {
        m_person = PersonFactory::getInstance().getGreenGuy();
        setStatus(IdeaStatus::Working, "Working");
        emit personChanged();
        setPersonExists(true);
    }

    m_personModel->clear();
    m_personModel->addPerson(m_person);
    m_output = std::make_shared<PeopleDataType>(m_personModel);
    emit newData(0);
}
