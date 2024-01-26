#include "MidgetInput.h"
#include "PersonFactory.h"

MidgetInputAttributes::MidgetInputAttributes()
{
    m_listName = "Midget Input";
    m_displayName = "";
    m_iconPath = "qrc:/Icons/MidgetInput.png";

    m_dataTypesOut.push_back(Magic<PeopleDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/PersonInputDisplay.qml";
}

const IdeaAttributes MidgetInput::attributes()
{
    return Magic<MidgetInputAttributes>::cast();
}

MidgetInput::MidgetInput()
{
    m_person = new Person();
    m_person->setColor("orange");
    m_person->setHeight(0.5);
    m_person->setName("ting");
    setPersonExists(true);
    setStatus(IdeaStatus::Working, "Working");

    m_personModel = new PersonArrayModel();
    m_personModel->addPerson(m_person);
    m_output = std::make_shared<PeopleDataType>(m_personModel);
    emit newData(0);
}

QJsonObject MidgetInput::save() const
{
    QJsonObject ideaJson = Idea::save();
    if(!m_personExists)
    {
        ideaJson["np"] = false;
    }
    return ideaJson;
}

void MidgetInput::load(const QJsonObject &p)
{
    QJsonValue v = p["np"];
    if(!v.isUndefined())
    {
        clearPerson();
    }
    Idea::load(p);
}

std::shared_ptr<DataType> MidgetInput::dataOut(PlugNumber)
{
    return m_output;
}

Person *MidgetInput::person() const
{
    return m_person;
}

bool MidgetInput::personExists() const
{
    return m_personExists;
}

void MidgetInput::setPersonExists(bool newPersonExists)
{
    if (m_personExists == newPersonExists)
        return;
    m_personExists = newPersonExists;
    emit personExistsChanged();
}

void MidgetInput::clearPerson()
{
    if(m_personExists == true)
    {
        setDefaultStatus();
        setPersonExists(false);
    }
}

void MidgetInput::addPerson()
{
    if(m_personExists)
    {
        m_person = new Person();
        m_person->setColor("orange");
        m_person->setHeight(0.5);
        m_person->setName("ting");
        emit personChanged();
    }
    else
    {
        m_person = new Person();
        m_person->setColor("orange");
        m_person->setHeight(0.5);
        m_person->setName("ting");
        setStatus(IdeaStatus::Working, "Working");
        emit personChanged();
        setPersonExists(true);
    }

    m_personModel->clear();
    m_personModel->addPerson(m_person);
    m_output = std::make_shared<PeopleDataType>(m_personModel);
    emit newData(0);
}
