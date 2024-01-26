#include "PersonFactory.h"
#include <QRandomGenerator>


QList<Person *> PersonFactory::generatePeople(int n)
{
    QList<Person*> people;
    people.reserve(n);

    for(int i = 0; i < n; i++)
    {
        double height = MINHEIGHT + QRandomGenerator::global()->generateDouble() *
               (MAXHEIGHT - MINHEIGHT);

        if(m_namesIter == names.length() - 1)
            m_namesIter = 0;
        else
            m_namesIter++;
        QString name = names.at(m_namesIter);
        Person* newPerson = new Person();
        newPerson->setHeight(height);
        newPerson->setName(name);
        int rRand = QRandomGenerator::global()->bounded(100);
        int gRand = QRandomGenerator::global()->bounded(100);
        int bRand = QRandomGenerator::global()->bounded(55);
        newPerson->setColor(QColor(75 + rRand,75 +gRand,200+bRand));
        people.push_back(newPerson);
    }

    std::sort(people.begin(), people.end(), [](Person* a, Person* b)
    {
        return a->height() < b->height();
    });

    return people;
}

Person *PersonFactory::getGreenGuy()
{
    double height = MINHEIGHT + QRandomGenerator::global()->generateDouble() *
           (MAXHEIGHT - MINHEIGHT);
    int nameRand = QRandomGenerator::global()->bounded(names.length());
    QString name = names.at(nameRand);
    Person* newPerson = new Person();
    newPerson->setHeight(height);
    newPerson->setName(name);
    newPerson->setColor(QColor(54,232,54));

    return newPerson;
}

PersonFactory::PersonFactory()
{
    names.append("Ren");
    names.append("John");
    names.append("Jim");
    names.append("Jake");
    names.append("Joe");
    names.append("JJ");
    names.append("Dave");
    names.append("Sam");
    names.append("Mark");
    names.append("Bob");
    names.append("Yani");
    names.append("Tim");
    names.append("Alex");
    names.append("Dale");
    names.append("Tom");
    names.append("Eli");
    names.append("Chen");
    names.append("Ben");
    names.append("Jack");
    names.append("Ron");
    names.append("Wei");
    names.append("Bo");
    m_namesIter = 0;
}
