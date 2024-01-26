#ifndef DATABASEAFTER_H
#define DATABASEAFTER_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "PeopleDataType.h"

struct DataBaseAfterAttributes : public IdeaAttributes
{
    DataBaseAfterAttributes();
};

class DataBaseAfter : public Idea
{
    Q_OBJECT

    Q_PROPERTY(int numPeople READ numPeople WRITE setNumPeople NOTIFY numPeopleChanged)
    Q_PROPERTY(PersonArrayModel* personModel READ personModel NOTIFY personModelChanged)

public:
    DataBaseAfter();
    const IdeaAttributes attributes() override;

    QJsonObject save() const override;
    void load(QJsonObject const &p) override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;

    int numPeople() const;
    void setNumPeople(int newNumPeople);

    PersonArrayModel *personModel() const;

signals:
    void numPeopleChanged();
    void personModelChanged();

private:
    std::weak_ptr<PeopleDataType> m_input;
    void validate();

    int m_numPeople;
    PersonArrayModel *m_personModel = nullptr;
};



#endif // DATABASEAFTER_H
