#include "InsertionStartAtBeginning.h"

InsertionStartAtBeginningAttributes::InsertionStartAtBeginningAttributes()
{
    m_listName = "Insertion. Inefficient";
    m_displayName = "Insertion. Will Result in \"educational\" videos made about you";

    //m_displayName = "Insertion. Inefficient";

    m_iconPath = "qrc:/Icons/InsertionStartAtBeginning.png";

    m_dataTypesIn.push_back(Magic<PeopleDataTypeAttributes>::cast().id());
    m_dataTypesIn.push_back(Magic<PeopleDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<PeopleDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/InsertionStartAtBeginning.qml";
    m_minimizedQMLPath = "";
    m_minimizedName = "Insertion";
    m_gear = true;

    m_externalQMLPaths << ":/QML/InsertionBasicControls.qml";
    m_externalQMLLocations.push_back({true, false, 10,0});
}

const IdeaAttributes InsertionStartAtBeginning::attributes()
{
    return Magic<InsertionStartAtBeginningAttributes>::cast();
}

InsertionStartAtBeginning::InsertionStartAtBeginning() : InsertionTemplate()
{
    m_paused = false;
}

void InsertionStartAtBeginning::prepareVisual()
{
    auto n1 = m_dataBaseInput.lock();
    PersonArrayModel* model1 = n1->model();
    QList<double> heights = model1->getHeights();

    auto n2 = m_newPersonInput.lock();
    PersonArrayModel* model = n2->model();
    QList<QString> name = model->getNames();
    QList<QColor> color = model->getColors();
    QList<double> height = model->getHeights();

    //Find position.
    auto loc = std::lower_bound(heights.begin(), heights.end(), height.at(0));

    emit newPersonAdded(name.at(0), color.at(0), height.at(0), std::distance(heights.begin(),loc) - 1);
}

bool InsertionStartAtBeginning::paused() const
{
    return m_paused;
}

void InsertionStartAtBeginning::setPaused(bool newPaused)
{
    if (m_paused == newPaused)
        return;
    m_paused = newPaused;
    emit pausedChanged();
}

void InsertionStartAtBeginning::step()
{
    m_paused = true;
    emit oneStep();
}

