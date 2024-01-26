#ifndef INSERTIONSMART_H
#define INSERTIONSMART_H

#include "InsertionTemplate.h"

struct InsertionSmartAttributes : public IdeaAttributes
{
    InsertionSmartAttributes();
};

class InsertionSmart : public InsertionTemplate
{
    Q_OBJECT
    Q_PROPERTY(bool paused READ paused WRITE setPaused NOTIFY pausedChanged FINAL)

public:
    InsertionSmart();
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

#endif // INSERTIONSMART_H
