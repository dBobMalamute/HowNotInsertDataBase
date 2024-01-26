#ifndef PEOPLEDATATYPE_H
#define PEOPLEDATATYPE_H

#include "../MalamuteCore/InheritedClasses/DataType.h"
#include "PersonArrayModel.h"

struct PeopleDataTypeAttributes : public DataTypeAttributes
{
    PeopleDataTypeAttributes();
};

class PeopleDataType : public DataType
{
public:
    PeopleDataType(PersonArrayModel* model);

    DataTypeAttributes getAttributes() override;   
    PersonArrayModel *model() const;

private:
    PersonArrayModel* m_model;
};

#endif // PEOPLEDATATYPE_H
