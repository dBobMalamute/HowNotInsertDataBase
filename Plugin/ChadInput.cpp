#include "ChadInput.h"
#include "PersonFactory.h"

ChadInputAttributes::ChadInputAttributes()
{
    m_listName = "Chad Input";
    m_displayName = "";
    m_iconPath = "qrc:/Icons/ChadInput.png";

    m_dataTypesOut.push_back(Magic<PeopleDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/PersonInputDisplay.qml";
}

const IdeaAttributes ChadInput::attributes()
{
    return Magic<ChadInputAttributes>::cast();
}

ChadInput::ChadInput()
{
    m_person = new Person();
    m_person->setColor("red");
    m_person->setHeight(3.1);
    m_person->setName("CHAD!");
    setPersonExists(true);
    setStatus(IdeaStatus::Working, "Working");

    m_personModel = new PersonArrayModel();
    m_personModel->addPerson(m_person);
    m_output = std::make_shared<PeopleDataType>(m_personModel);
    emit newData(0);
}

QJsonObject ChadInput::save() const
{
    QJsonObject ideaJson = Idea::save();
    if(!m_personExists)
    {
        ideaJson["np"] = false;
    }
    return ideaJson;
}

void ChadInput::load(const QJsonObject &p)
{
    QJsonValue v = p["np"];
    if(!v.isUndefined())
    {
        clearPerson();
    }
    Idea::load(p);
}

std::shared_ptr<DataType> ChadInput::dataOut(PlugNumber)
{
    return m_output;
}

Person *ChadInput::person() const
{
    return m_person;
}

bool ChadInput::personExists() const
{
    return m_personExists;
}

void ChadInput::setPersonExists(bool newPersonExists)
{
    if (m_personExists == newPersonExists)
        return;
    m_personExists = newPersonExists;
    emit personExistsChanged();
}

void ChadInput::clearPerson()
{
    if(m_personExists == true)
    {
        setDefaultStatus();
        setPersonExists(false);
    }
}

void ChadInput::addPerson()
{
    if(m_personExists)
    {
        m_person = new Person();
        m_person->setColor("red");
        m_person->setHeight(3.1);
        m_person->setName("CHAD!");
        emit personChanged();
    }
    else
    {
        m_person = new Person();
        m_person->setColor("red");
        m_person->setHeight(3.1);
        m_person->setName("CHAD!");
        setStatus(IdeaStatus::Working, "Working");
        emit personChanged();
        setPersonExists(true);
    }

    m_personModel->clear();
    m_personModel->addPerson(m_person);
    m_output = std::make_shared<PeopleDataType>(m_personModel);
    emit newData(0);
}
