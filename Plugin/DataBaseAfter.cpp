#include "DataBaseAfter.h"

DataBaseAfterAttributes::DataBaseAfterAttributes()
{
    m_listName = "DataBase After";
    m_displayName = "DataBase After";
    m_iconPath = "qrc:/Icons/DataBaseAfter.png";

    m_dataTypesIn.push_back(Magic<PeopleDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/DataBaseAfter.qml";
    m_minimizedQMLPath = "";
    m_minimizedName = "DataBase\nAfter";
}

const IdeaAttributes DataBaseAfter::attributes()
{
    return Magic<DataBaseAfterAttributes>::cast();
}

DataBaseAfter::DataBaseAfter() :
    m_numPeople(10)
{

}

QJsonObject DataBaseAfter::save() const
{
    QJsonObject obj = Idea::save();

    return obj;
}

void DataBaseAfter::load(const QJsonObject &p)
{

    Idea::load(p);
}

void DataBaseAfter::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto m = std::dynamic_pointer_cast<PeopleDataType>(dataType);
    m_input = m;

    validate();
}

int DataBaseAfter::numPeople() const
{
    return m_numPeople;
}

void DataBaseAfter::setNumPeople(int newNumPeople)
{
    if (m_numPeople == newNumPeople)
        return;
    m_numPeople = newNumPeople;
    emit numPeopleChanged();
}

PersonArrayModel *DataBaseAfter::personModel() const
{
    return m_personModel;
}

void DataBaseAfter::validate()
{
    auto n = m_input.lock();
    if(n)
    {
        setStatus(IdeaStatus::Working, "Working");
        m_personModel = n->model();
        setNumPeople(m_personModel->rowCount(QModelIndex()));
        emit personModelChanged();
    }
    else
    {
        setDefaultStatus();
        m_personModel = nullptr;
        setNumPeople(10);
        emit personModelChanged();
    }
}
