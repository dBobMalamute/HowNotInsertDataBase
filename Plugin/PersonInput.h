#ifndef PERSONINPUT_H
#define PERSONINPUT_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "Person.h"
#include "PeopleDataType.h"
#include "PersonArrayModel.h"

struct PersonInputAttributes : public IdeaAttributes
{
    PersonInputAttributes();
};

class PersonInput : public Idea
{
    Q_OBJECT
    Q_PROPERTY(Person* person READ person NOTIFY personChanged)
    Q_PROPERTY(bool personExists READ personExists WRITE setPersonExists NOTIFY personExistsChanged)

public:
    PersonInput();
    const IdeaAttributes attributes() override;

    QJsonObject save() const override;
    void load(QJsonObject const &p) override;

    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    Person *person() const;
    bool personExists() const;
    void setPersonExists(bool newPersonExists);

public slots:
    void clearPerson();
    void addPerson();

signals:
    void personChanged();
    void personExistsChanged();

private:
    std::shared_ptr<PeopleDataType> m_output;

    Person* m_person;
    PersonArrayModel *m_personModel = nullptr;

    bool m_personExists;
};

#endif // PERSONINPUT_H
