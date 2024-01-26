#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QColor>

class Person : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit Person(QObject *parent = nullptr);

    double height() const;
    void setHeight(double newHeight);

    const QString &name() const;
    void setName(const QString &newName);

    const QColor &color() const;
    void setColor(const QColor &newColor);

signals:
    void heightChanged();
    void nameChanged();

    void colorChanged();

private:
    double m_height;
    QString m_name;
    QColor m_color;
};

#endif // PERSON_H
