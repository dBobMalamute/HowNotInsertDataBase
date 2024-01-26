#ifndef DATABASEBEFORE_H
#define DATABASEBEFORE_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "PeopleDataType.h"
#include "PersonArrayModel.h"

struct DataBaseBeforeAttributes : public IdeaAttributes
{
    DataBaseBeforeAttributes();
};


class DataBaseBefore : public Idea
{
    Q_OBJECT

    Q_PROPERTY(int numPeople READ numPeople WRITE setNumPeople NOTIFY numPeopleChanged)
    Q_PROPERTY(PersonArrayModel* personModel READ personModel NOTIFY personModelChanged)

public:
    DataBaseBefore();
    const IdeaAttributes attributes() override;

    QJsonObject save() const override;
    void load(QJsonObject const &p) override;

    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    int numPeople() const;

    PersonArrayModel *personModel() const;

signals:
    void numPeopleChanged();
    void personModelChanged();

public slots:
    void setNumPeople(int newNumPeople);
    void generateNewData();

private:
    std::shared_ptr<PeopleDataType> m_output;

    int m_numPeople;
    PersonArrayModel *m_personModel = nullptr;
};

#endif // DATABASEBEFORE_H
