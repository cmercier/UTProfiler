
#include "admin.h"

Admin::Admin()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    QList<const Uv*> uvs = UVManager::instance().uvs();

    // Add Uv
    QPushButton* addUvButton = new QPushButton("Ajouter une Uv");
    addUvButton->setCheckable(true);
    QHBoxLayout* addUvLayout = new QHBoxLayout;
    addUvLayout->addWidget(addUvButton);
    addUvLayout->insertStretch(-1);
    createAddUvPanel();
    addUvPanel_->setVisible(false);
    QObject::connect(addUvButton,SIGNAL(toggled(bool)),this,SLOT(showAddUvPanel(bool)));
    QVBoxLayout* v1 = new QVBoxLayout;
    v1->addLayout(addUvLayout);
    v1->addWidget(addUvPanel_);
    mainLayout->addLayout(v1);

    // Edit Uv
    QLabel* editUvLabel = new QLabel("Modifier une Uv");
    QComboBox* editUvComboBox = new QComboBox;
    editUvComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    QHBoxLayout* editUvLayout = new QHBoxLayout;
    editUvLayout->addWidget(editUvLabel);
    editUvLayout->addWidget(editUvComboBox);
    editUvLayout->insertStretch(-1);
    mainLayout->addLayout(editUvLayout);

    // Delete Uv
    QLabel* deleteUvLabel = new QLabel("Supprimer une Uv");
    QComboBox* deleteUvComboBox = new QComboBox;
    deleteUvComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    QHBoxLayout* deleteUvLayout = new QHBoxLayout;
    deleteUvLayout->addWidget(deleteUvLabel);
    deleteUvLayout->addWidget(deleteUvComboBox);
    deleteUvLayout->insertStretch(-1);
    mainLayout->addLayout(deleteUvLayout);

    for(int i = 0; i < uvs.size(); i++)
    {
        QString code = uvs.at(i)->code();
        editUvComboBox->addItem(code);
        deleteUvComboBox->addItem(code);
    }

    editUvComboBox->insertItem(0,"Selectionnez une Uv...");
    editUvComboBox->setCurrentIndex(0);
    deleteUvComboBox->insertItem(0,"Selectionnez une Uv...");
    deleteUvComboBox->setCurrentIndex(0);

    mainLayout->insertStretch(-1);
}

void Admin::createAddUvPanel()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    addUvPanel_ = new QWidget;
    addUvPanel_->setLayout(mainLayout);
    int labelWidth = 60;

    // Code
    QLabel * codeLabel = new QLabel("Code : ");
    codeLabel->setFixedWidth(labelWidth);
    QLineEdit* codeEdit = new QLineEdit;
    codeEdit->setMaxLength(4);
    codeEdit->setFixedWidth(50);
    QHBoxLayout* codeLayout = new QHBoxLayout;
    codeLayout->addWidget(codeLabel);
    codeLayout->addWidget(codeEdit);
    codeLayout->insertStretch(-1);
    mainLayout->addLayout(codeLayout);

    // Title
    QLabel * titleLabel = new QLabel("Intitulé : ");
    titleLabel->setFixedWidth(labelWidth);
    QLineEdit* titleEdit = new QLineEdit;
    QHBoxLayout* titleLayout = new QHBoxLayout;
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(titleEdit);
    titleLayout->insertStretch(-1);
    mainLayout->addLayout(titleLayout);

    // Credits
    QLabel* creditsLabel = new QLabel("Crédits : ");
    creditsLabel->setFixedWidth(labelWidth);
    QSpinBox* creditsBox = new QSpinBox;
    creditsBox->setMinimum(0);
    creditsBox->setValue(6);
    creditsBox->setSingleStep(1);
    QHBoxLayout* creditsLayout = new QHBoxLayout;
    creditsLayout->addWidget(creditsLabel);
    creditsLayout->addWidget(creditsBox);
    creditsLayout->insertStretch(-1);
    mainLayout->addLayout(creditsLayout);

    // Category
    QLabel* categoryLabel = new QLabel("Catégorie : ");
    categoryLabel->setFixedWidth(labelWidth);
    QComboBox* categoryBox = new QComboBox;
    categoryBox->addItem("CS");
    categoryBox->addItem("TM");
    categoryBox->addItem("TSH");
    categoryBox->addItem("SP");
    QHBoxLayout* categoryLayout = new QHBoxLayout;
    categoryLayout->addWidget(categoryLabel);
    categoryLayout->addWidget(categoryBox);
    categoryLayout->insertStretch(-1);
    mainLayout->addLayout(categoryLayout);

    // Season
    QLabel* seasonLabel = new QLabel("Ouverture : ");
    QCheckBox* spring = new QCheckBox("Printemps");
    spring->setChecked(true);
    QCheckBox* fall = new QCheckBox("Automne");
    fall->setChecked(true);
    QHBoxLayout* seasonLayout = new QHBoxLayout;
    seasonLayout->addWidget(seasonLabel);
    seasonLayout->addWidget(spring);
    seasonLayout->addWidget(fall);
    seasonLayout->insertStretch(-1);
    mainLayout->addLayout(seasonLayout);
}

void Admin::showAddUvPanel(bool show)
{
    addUvPanel_->setVisible(show);
}

