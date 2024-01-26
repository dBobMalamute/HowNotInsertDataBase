#ifndef INSERTIONTEMPLATE_H
#define INSERTIONTEMPLATE_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "PeopleDataType.h"

class InsertionTemplate : public Idea
{
    Q_OBJECT

    Q_PROPERTY(int animationSpeed READ animationSpeed WRITE setAnimationSpeed NOTIFY animationSpeedChanged)

public:
    InsertionTemplate();

    QJsonObject save() const override;
    void load(QJsonObject const &p) override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    int animationSpeed() const;

signals:
    void setupBefore(QList<QString> names, QList<QColor> colors, QList<double> heights);
    void clearAll();

    void animationSpeedChanged();

public slots:
    void setAnimationSpeed(int newAnimationSpeed);
    void insertionAnimationCompleted();
    double getHeight(int index);

protected:
    std::weak_ptr<PeopleDataType> m_dataBaseInput;
    std::weak_ptr<PeopleDataType> m_newPersonInput;

    std::shared_ptr<PeopleDataType> m_output;

    void validate();
    void setupBeforeInsertion();
    virtual void run();
    virtual void prepareVisual() = 0;

    bool m_readyForInsertion = false;
    int m_animationSpeed;


};

#endif // INSERTIONTEMPLATE_H
