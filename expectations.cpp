#include "expectations.h"

Expectations::Expectations()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    // Select or create expectations
    QLabel* expSelectLabel = new QLabel("Mes prévisions :");
    expSelect_ = new QComboBox;
    expSelect_->setInsertPolicy(QComboBox::InsertAlphabetically);
    expSelect_->setFixedWidth(150);
    QHBoxLayout* h1 = new QHBoxLayout;
    h1->addWidget(expSelectLabel);
    h1->addWidget(expSelect_);
    h1->insertStretch(-1);
    mainLayout->addLayout(h1);

    // Exp panel
    expScrollArea_ = new QScrollArea;
    expScrollArea_->setWidgetResizable(true);
    QWidget* w = new QWidget;
    expScrollArea_->setWidget(w);
    expLayout_ = new QVBoxLayout;
    w->setLayout(expLayout_);
    mainLayout->addWidget(expScrollArea_);

    mainLayout->insertStretch(-1);

    createExpPanel();
}

void Expectations::addWantedDegree()
{

}

void Expectations::createExpPanel()
{
    // Name
    QLabel* nameLabel = new QLabel("Nom :");
    name_ = new QLineEdit;
    QHBoxLayout* h1 = new QHBoxLayout;
    h1->addWidget(nameLabel);
    h1->addWidget(name_);
    h1->insertStretch(-1);
    expLayout_->addLayout(h1);

    // Uvs the student wishes to do
    QLabel* wantedUvsLabel = new QLabel("Uvs voulues :");
    QScrollArea* wantedUvsScroll = new QScrollArea;
    QWidget* w1 = new QWidget;
    wantedUvsScroll->setWidget(w1);
    wantedUvsScroll->setFixedWidth(110);
    wantedUvsScroll->setWidgetResizable(true);
    wantedUvsLayout_ = new QVBoxLayout;
    w1->setLayout(wantedUvsLayout_);
    QHBoxLayout* h2 = new QHBoxLayout;
    h2->addWidget(wantedUvsLabel);
    h2->addWidget(wantedUvsScroll);

    // Uvs the student does not wish to do
    QLabel* unwantedUvsLabel = new QLabel("Uvs non voulues :");
    QScrollArea* unwantedUvsScroll = new QScrollArea;
    QWidget* w2 = new QWidget;
    unwantedUvsScroll->setWidget(w2);
    unwantedUvsScroll->setFixedWidth(110);
    unwantedUvsScroll->setWidgetResizable(true);
    unwantedUvsLayout_ = new QVBoxLayout;
    w2->setLayout(unwantedUvsLayout_);
    QHBoxLayout* h3 = new QHBoxLayout;
    h3->addWidget(unwantedUvsLabel);
    h3->addWidget(unwantedUvsScroll);

    // Degrees the students wishes to enroll in
    QGroupBox* wantedDegrees = new QGroupBox("Formations envisagées");
    degreesBox_ = new QComboBox;
    const QList<Degree*> &degrees = UVManager::instance().degrees();
    degreesBox_->insertItem(0,"Choix " + degrees.first()->type());
    int count = 1;
    for(int i = 0; i < degrees.size(); i++)
    {
        if(!degrees.at(i)->parent())
        {
            degreesBox_->insertItem(count,degrees.at(i)->title());
            count++;
        }
    }
    QObject::connect(degreesBox_,SIGNAL(activated(QString)),this,SLOT(selectDegree(QString)));
    degreeLayout_ = new QHBoxLayout;
    degreeLayout_->addWidget(degreesBox_);
    degreeLayout_->insertStretch(-1);
    QPushButton* addDegreeButton = new QPushButton("Ajouter");
    QObject::connect(addDegreeButton,SIGNAL(clicked()),this,SLOT(addWantedDegree()));
    QHBoxLayout* h5 = new QHBoxLayout;
    h5->addWidget(addDegreeButton);
    h5->insertStretch(-1);
    QVBoxLayout* v1 = new QVBoxLayout;
    v1->addLayout(degreeLayout_);
    v1->addLayout(h5);
    v1->insertStretch(-1);
    wantedDegrees->setLayout(v1);

    QHBoxLayout* h4 = new QHBoxLayout;
    h4->addLayout(h2);
    h4->addLayout(h3);
    h4->insertStretch(-1);
    h4->addWidget(wantedDegrees);
    expLayout_->addLayout(h4);

    /*
    // Add semester
    QGroupBox* addSemesterBox = new QGroupBox;
    QVBoxLayout* v1 = new QVBoxLayout;
    addSemesterBox->setLayout(v1);
        // semester
    QLabel* seasonLabel = new QLabel("Semestre :");
    QComboBox* seasonBox = new QComboBox;
    seasonBox->addItem("Printemps");
    seasonBox->addItem("Automne");
    QHBoxLayout* h2 = new QHBoxLayout;
    h2->addWidget(seasonLabel);
    h2->addWidget(seasonBox);
        // date
    QLabel* yearLabel = new QLabel("Année :");
    QSpinBox* yearBox = new QSpinBox;
    yearBox->setValue(14);
    h2->addWidget(yearLabel);
    h2->addWidget(yearBox);
    h2->insertStretch(-1);
    v1->addLayout(h2);

    expLayout_->addWidget(addSemesterBox);
    */
    expLayout_->insertStretch(-1);

    updateWantedUvs();
    updateUnwantedUvs();
}

void Expectations::selectDegree(const QString &title)
{
    selectedDegree_ = UVManager::instance().degreeWithTitle(title);
    int depth;
    selectedDegree_ ? depth = selectedDegree_->depth() : depth = 0;
    while(degreeLayout_->count() > depth + 2)
    {
        QLayoutItem* item = degreeLayout_->takeAt(degreeLayout_->count() - 1);
        degreeLayout_->removeItem(item);
        delete item->widget();
        delete item;
    }
    degreeLayout_->update();

    QList<const Degree*> children = UVManager::instance().degreesWithParent(title);
    if(!children.isEmpty())
    {
        QComboBox* subDegree = new QComboBox;
        subDegree->insertItem(0,"Choix " + children.first()->type());

        for(int i = 0; i < children.size(); i++)
        {
            subDegree->insertItem(i + 1,children.at(i)->title());
        }

        degreeLayout_->addWidget(subDegree);
        QObject::connect(subDegree,SIGNAL(activated(QString)),this,SLOT(selectDegree(QString)));
    }

    degreeLayout_->insertStretch(-1);
}

void Expectations::updateExpComboBox()
{
    expSelect_->clear();

    Student* student = UVManager::instance().student();
    if(!student)
        return;

    const QList<Expectation*> &exp = student->exp();
    for(int i = 0; i < exp.size(); i++)
    {
        expSelect_->addItem(exp.at(i)->name());
    }

    expSelect_->insertItem(0,"Nouvelle prévision");
    expSelect_->setCurrentIndex(0);
}

void Expectations::updateExpPanel()
{
}

void Expectations::updateUnwantedUvs()
{
    QList<const Uv*> uvs = UVManager::instance().uvs();
    Utilities::clearLayout(unwantedUvsLayout_);

    for(int i = 0; i < uvs.size(); i++)
    {
        QString code = uvs.at(i)->code();
        QCheckBox* uv = new QCheckBox(code);
        uv->setChecked(false);
        unwantedUvsLayout_->addWidget(uv);
    }

    unwantedUvsLayout_->insertStretch(-1);
}

void Expectations::updateWantedUvs()
{
    QList<const Uv*> uvs = UVManager::instance().uvs();
    Utilities::clearLayout(wantedUvsLayout_);

    for(int i = 0; i < uvs.size(); i++)
    {
        QString code = uvs.at(i)->code();
        QCheckBox* uv = new QCheckBox(code);
        uv->setChecked(false);
        wantedUvsLayout_->addWidget(uv);
    }

    wantedUvsLayout_->insertStretch(-1);
}
