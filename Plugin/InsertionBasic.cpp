#include "InsertionBasic.h"

InsertionBasicAttributes::InsertionBasicAttributes()
{
    m_listName = "Insertion Basic";
    m_displayName = "Insert Guy\nInto Database";
    m_iconPath = "qrc:/Icons/InsertionBasic.png";

    m_dataTypesIn.push_back(Magic<PeopleDataTypeAttributes>::cast().id());
    m_dataTypesIn.push_back(Magic<PeopleDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<PeopleDataTypeAttributes>::cast().id());

    //m_embeddedQMLPath = ":/QML/InsertionBasic.qml";
    m_gear = true;

    //m_minimizable = true;

    //m_externalQMLPaths << ":/QML/InsertionBasicControls.qml";
    //m_externalQMLLocations.push_back({true, false, 10,0});
}

const IdeaAttributes InsertionBasic::attributes()
{
    return Magic<InsertionBasicAttributes>::cast();
}

void InsertionBasic::run()
{
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
    emit newData(0);
}

void InsertionBasic::prepareVisual()
{
    emit stopSpinningGear();
}

InsertionBasic::InsertionBasic() : InsertionTemplate()
{

}
