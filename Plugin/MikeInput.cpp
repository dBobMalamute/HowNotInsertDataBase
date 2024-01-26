#include "MikeInput.h"

MikeInputAttributes::MikeInputAttributes()
{
    m_listName = "Mike Input";
    m_displayName = "";
    m_iconPath = "qrc:/Icons/MikeInput.png";

    m_dataTypesOut.push_back(Magic<PeopleDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/PersonInputDisplay.qml";
}

const IdeaAttributes MikeInput::attributes()
{
    return Magic<MikeInputAttributes>::cast();
}

MikeInput::MikeInput()
{
    m_person = new Person();
    m_person->setColor(0x10dede);
    m_person->setHeight(1.7);
    m_person->setName("Mike");
    setPersonExists(true);
    setStatus(IdeaStatus::Working, "Working");

    m_personModel = new PersonArrayModel();
    m_personModel->addPerson(m_person);
    m_output = std::make_shared<PeopleDataType>(m_personModel);
    emit newData(0);
}

QJsonObject MikeInput::save() const
{
    QJsonObject ideaJson = Idea::save();
    if(!m_personExists)
    {
        ideaJson["np"] = false;
    }
    return ideaJson;
}

void MikeInput::load(const QJsonObject &p)
{
    QJsonValue v = p["np"];
    if(!v.isUndefined())
    {
        clearPerson();
    }
    Idea::load(p);
}

std::shared_ptr<DataType> MikeInput::dataOut(PlugNumber)
{
    return m_output;
}

Person *MikeInput::person() const
{
    return m_person;
}

bool MikeInput::personExists() const
{
    return m_personExists;
}

void MikeInput::setPersonExists(bool newPersonExists)
{
    if (m_personExists == newPersonExists)
        return;
    m_personExists = newPersonExists;
    emit personExistsChanged();
}

void MikeInput::clearPerson()
{
    if(m_personExists == true)
    {
        setDefaultStatus();
        setPersonExists(false);
    }
}

void MikeInput::addPerson()
{
    if(m_personExists)
    {
        m_person = new Person();
        m_person->setColor(0x10dede);
        m_person->setHeight(1.7);
        m_person->setName("Mike");
        emit personChanged();
    }
    else
    {
        m_person = new Person();
        m_person->setColor(0x10dede);
        m_person->setHeight(1.7);
        m_person->setName("Mike");
        setStatus(IdeaStatus::Working, "Working");
        emit personChanged();
        setPersonExists(true);
    }

    m_personModel->clear();
    m_personModel->addPerson(m_person);
    m_output = std::make_shared<PeopleDataType>(m_personModel);
    emit newData(0);
}
