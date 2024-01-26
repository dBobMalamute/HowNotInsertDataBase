#ifndef INSERTIONSTARTATBEGINNING_H
#define INSERTIONSTARTATBEGINNING_H

#include "InsertionTemplate.h"

struct InsertionStartAtBeginningAttributes : public IdeaAttributes
{
    InsertionStartAtBeginningAttributes();
};

class InsertionStartAtBeginning : public InsertionTemplate
{
    Q_OBJECT
    Q_PROPERTY(bool paused READ paused WRITE setPaused NOTIFY pausedChanged FINAL)

public:
    InsertionStartAtBeginning();
    const IdeaAttributes attributes() override;

    bool paused() const;

signals:
    void newPersonAdded(QString name, QColor color, double height, int index);
    void pausedChanged();
    void oneStep();

public slots:
    void setPaused(bool newPaused);
    void step();

private:
    void prepareVisual() override;
    bool m_paused;

};

#endif // INSERTIONSTARTATBEGINNING_H
