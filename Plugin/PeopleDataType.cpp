#include "PeopleDataType.h"

PeopleDataTypeAttributes::PeopleDataTypeAttributes()
{
    m_name = "People";
    m_abbreviation = "";
}

DataTypeAttributes PeopleDataType::getAttributes()
{
    return Magic<PeopleDataTypeAttributes>::cast();
}

PersonArrayModel *PeopleDataType::model() const
{
    return m_model;
}

PeopleDataType::PeopleDataType(PersonArrayModel *model)
{
    m_model = model;
}

