#ifndef PERSONARRAYMODEL_H
#define PERSONARRAYMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include "Person.h"
#include "PersonFactory.h"

class PersonArrayModel : public QAbstractListModel
{
    Q_OBJECT
    enum Roles
    {
        NameRole = Qt::UserRole + 1,
        HeightRole,
        ColorRole
    };

public:
    explicit PersonArrayModel(QObject *parent = nullptr);

    PersonArrayModel(QList<QString> names, QList<QColor> colors, QList<double> heights, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addPerson(Person* person);
    Q_INVOKABLE void AddPerson(int num);
    Q_INVOKABLE void clear();

    QList<QString> getNames() const;
    QList<QColor> getColors() const;
    QList<double> getHeights() const;

signals:

private:
    QList<Person*> m_people;
};



#endif // PERSONARRAYMODEL_H
