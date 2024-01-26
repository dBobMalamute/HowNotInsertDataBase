#ifndef PERSONFACTORY_H
#define PERSONFACTORY_H

#define MAXHEIGHT 2.0
#define MINHEIGHT 1.0


#include "Person.h"

class PersonFactory
{
public:
    static PersonFactory& getInstance()
    {
        static PersonFactory instance;
        return instance;
    }

    QList<Person*> generatePeople(int n);
    Person* getGreenGuy();

private:
    PersonFactory();

    QStringList names;
    int m_namesIter;

public:
    PersonFactory(PersonFactory const&) = delete;
    void operator=(PersonFactory const &) = delete;
};

#endif // PERSONFACTORY_H
