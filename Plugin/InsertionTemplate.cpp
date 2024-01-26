#include "InsertionTemplate.h"

InsertionTemplate::InsertionTemplate() :
    m_animationSpeed(250)
{

}

QJsonObject InsertionTemplate::save() const
{
    QJsonObject obj = Idea::save();
    obj["as"] = m_animationSpeed;
    return obj;
}

void InsertionTemplate::load(const QJsonObject &p)
{
    QJsonValue v = p["as"];
    if(!v.isUndefined())
    {
        m_animationSpeed = v.toInt();
        emit animationSpeedChanged();
    }

    Idea::load(p);
}

void InsertionTemplate::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber)
{
    auto n = std::dynamic_pointer_cast<PeopleDataType>(dataType);
    if(plugNumber == 0)
        m_dataBaseInput = n;
    else
        m_newPersonInput = n;

    validate();
}

std::shared_ptr<DataType> InsertionTemplate::dataOut(PlugNumber)
{
    return m_output;
}

void InsertionTemplate::insertionAnimationCompleted()
{
    emit newData(0);
    emit stopSpinningGear();
}

double InsertionTemplate::getHeight(int index)
{
    if(!valid())
        return 0.0;
    return m_dataBaseInput.lock()->model()->getHeights().at(index);

}

void InsertionTemplate::validate()
{
    auto n1 = m_dataBaseInput.lock();
    auto n2 = m_newPersonInput.lock();

    if(n1 && !n2)
    {
        emit clearAll();
        setStatus(IdeaStatus::StandBy, "Waiting for new data");
        setupBeforeInsertion();
    }
    else if(n1 && n2 && m_readyForInsertion)
    {
        setStatus(IdeaStatus::Working, "Workin");
        run();
    }
    else if(n1 && n2)
    {
        emit clearAll();
        setupBeforeInsertion();
        setStatus(IdeaStatus::Working, "Workin");
        run();
    }
    else
    {
        emit clearAll();
        m_readyForInsertion = false;
        setDefaultStatus();
    }
}

void InsertionTemplate::setupBeforeInsertion()
{
    m_readyForInsertion = true;
    auto n1 = m_dataBaseInput.lock();

    PersonArrayModel* model = n1->model();
    QList<QString> names = model->getNames();
    QList<QColor> colors = model->getColors();
    QList<double> heights = model->getHeights();

    emit setupBefore(names, colors, heights);
}

void InsertionTemplate::run()
{
    m_output = nullptr;
    emit newData(0);

    emit startSpinningGear();
    m_readyForInsertion = false;
    prepareVisual();

    auto n1 = m_dataBaseInput.lock();
    PersonArrayModel* model1 = n1->model();

    auto n2 = m_newPersonInput.lock();
    PersonArrayModel* model = n2->model();
    QList<QString> name = model->getNames();
    QList<QColor> color = model->getColors();
    QList<double> height = model->getHeights();

    QList<QString> newNames = model1->getNames();
    QList<QColor> newColors = model1->getColors();
    QList<double> newHeights = model1->getHeights();
    newNames.append(name);
    newColors.append(color);
    newHeights.append(height);

    PersonArrayModel* newModel = new PersonArrayModel(newNames,
                                                      newColors,
                                                      newHeights);
    m_output = std::make_shared<PeopleDataType>(newModel);
}

int InsertionTemplate::animationSpeed() const
{
    return m_animationSpeed;
}

void InsertionTemplate::setAnimationSpeed(int newAnimationSpeed)
{
    if (m_animationSpeed == newAnimationSpeed)
        return;
    m_animationSpeed = newAnimationSpeed;
    emit animationSpeedChanged();
}
