#ifndef INSERTIONBASIC_H
#define INSERTIONBASIC_H

#include "InsertionTemplate.h"

struct InsertionBasicAttributes : public IdeaAttributes
{
    InsertionBasicAttributes();
};

class InsertionBasic : public InsertionTemplate
{
    Q_OBJECT

public:
    InsertionBasic();
    const IdeaAttributes attributes() override;

signals:
    void newPersonAdded(QString name, QColor color, double height, int index);

private:
    void run() override;
    void prepareVisual() override;
};

#endif // INSERTIONBASIC_H
