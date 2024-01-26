#include "Person.h"

Person::Person(QObject *parent) : QObject{parent},
      m_height(1.0),
      m_name("Bob"),
      m_color()
{

}

double Person::height() const
{
    return m_height;
}

void Person::setHeight(double newHeight)
{
    if (qFuzzyCompare(m_height, newHeight))
        return;
    m_height = newHeight;
    emit heightChanged();
}

const QString &Person::name() const
{
    return m_name;
}

void Person::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

const QColor &Person::color() const
{
    return m_color;
}

void Person::setColor(const QColor &newColor)
{
    if (m_color == newColor)
        return;
    m_color = newColor;
    emit colorChanged();
}
