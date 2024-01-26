#include "PersonArrayModel.h"

PersonArrayModel::PersonArrayModel(QObject *parent) : QAbstractListModel(parent)
{

}

PersonArrayModel::PersonArrayModel(QList<QString> names, QList<QColor> colors, QList<double> heights, QObject *parent) :
    QAbstractListModel(parent)
{

    for(int i = 0; i < names.length(); i++)
    {
        m_people.append(new Person);
        m_people[i]->setName(names.at(i));
        m_people[i]->setColor(colors.at(i));
        m_people[i]->setHeight(heights.at(i));
    }

    std::sort(m_people.begin(), m_people.end(), [](Person* a, Person* b)
    {
        return a->height() < b->height();
    });
}

int PersonArrayModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_people.size();
}

QVariant PersonArrayModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_people.count())
        return QVariant();

    Person* person = m_people.at(index.row());
    if(role == NameRole)
        return QVariant(person->name());
    if(role == HeightRole)
        return QVariant(person->height());
    if(role == ColorRole)
        return QVariant(person->color());
    return QVariant();
}

bool PersonArrayModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Person* person = m_people.at(index.row());
    bool somethingChanged = false;

    switch (role)
    {
    case NameRole:
    {
        if(person->name() != value.toString())
        {
            person->setName(value.toString());
            somethingChanged = true;
        }
    }
        break;
    case HeightRole:
    {
        if(person->height() != value.toDouble())
        {
            person->setHeight(value.toDouble());
            somethingChanged = true;
        }
    }
        break;
    case ColorRole:
    {
        if(person->color() != value.toString())
        {
            person->setColor(value.toString());
            somethingChanged = true;
        }
    }
    }
    if(somethingChanged)
    {
        emit dataChanged(index,index,QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PersonArrayModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> PersonArrayModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[HeightRole] = "height";
    roles[ColorRole] = "color";

    return roles;
}

void PersonArrayModel::addPerson(Person *person)
{

    beginInsertRows(QModelIndex(), m_people.size(), m_people.size());
    m_people.append(person);
    endInsertRows();

}

void PersonArrayModel::AddPerson(int num)
{
    if (m_people.size() == 0)
    {
        beginInsertRows(QModelIndex(), 0, num - 1);
        m_people = PersonFactory::getInstance().generatePeople(num);
        endInsertRows();
    }
}

void PersonArrayModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_people.size() - 1);
    for(int i = 0; i < m_people.size(); i++)
        delete m_people.at(i);
    m_people.clear();
    endRemoveRows();
}

QList<QString> PersonArrayModel::getNames() const
{
    QList<QString> names;
    names.reserve(m_people.size());
    for(int i = 0; i < m_people.size(); i++)
    {
        names.append(m_people.at(i)->name());
    }
    return names;
}

QList<QColor> PersonArrayModel::getColors() const
{
    QList<QColor> colors;
    colors.reserve(m_people.size());
    for(int i = 0; i < m_people.size(); i++)
    {
        colors.append(m_people.at(i)->color());
    }
    return colors;
}

QList<double> PersonArrayModel::getHeights() const
{
    QList<double> heights;
    heights.reserve(m_people.size());
    for(int i = 0; i < m_people.size(); i++)
    {
        heights.append(m_people.at(i)->height());
    }
    return heights;
}
