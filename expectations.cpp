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

void Expectations::createExpPanel()
{
    QLabel* nameLabel = new QLabel("Nom :");
    name_ = new QLineEdit;
    QHBoxLayout* h1 = new QHBoxLayout;
    h1->addWidget(nameLabel);
    h1->addWidget(name_);
    h1->insertStretch(-1);
    expLayout_->addLayout(h1);

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
    expLayout_->insertStretch(-1);
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
