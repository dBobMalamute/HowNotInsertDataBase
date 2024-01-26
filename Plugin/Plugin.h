#ifndef INSERTIONLOGARITHMS_H
#define INSERTIONLOGARITHMS_H

#include "../MalamuteCore/InheritedClasses/MalamutePlugin.h"

class Plugin : public MalamutePlugin
{
    Q_OBJECT

public:
    QString PluginName() override;
    void registerIdeas(std::shared_ptr<IdeaRegistry> ideaRegistry) override;
    void registerDataTypeAttributes(std::shared_ptr<DataTypeRegistry> dataTypeRegistry) override;
};


#endif // INSERTIONLOGARITHMS_H
