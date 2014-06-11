
#include "admin.h"

Admin::Admin()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

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
    editUv_comboBox_ = new QComboBox;
    editUv_comboBox_->setInsertPolicy(QComboBox::InsertAlphabetically);
    QHBoxLayout* editUvLayout = new QHBoxLayout;
    editUvLayout->addWidget(editUvLabel);
    editUvLayout->addWidget(editUv_comboBox_);
    editUvLayout->insertStretch(-1);
    createEditUvPanel();
    editUvPanel_->setVisible(false);
    QObject::connect(editUv_comboBox_,SIGNAL(activated(QString)),SLOT(editUv(QString)));
    QVBoxLayout* v2 = new QVBoxLayout;
    v2->addLayout(editUvLayout);
    v2->addWidget(editUvPanel_);
    mainLayout->addLayout(v2);

    // Remove Uv
    QLabel* removeUvLabel = new QLabel("Supprimer une Uv");
    removeUv_comboBox_ = new QComboBox;
    removeUv_comboBox_->setInsertPolicy(QComboBox::InsertAlphabetically);
    QObject::connect(removeUv_comboBox_,SIGNAL(activated(QString)),this,SLOT(showRemoveUvButton(QString)));
    removeUv_remove_ = new QPushButton("Supprimer");
    removeUv_remove_->setVisible(false);
    QObject::connect(removeUv_remove_,SIGNAL(clicked()),this,SLOT(removeUv()));
    QHBoxLayout* removeUvLayout = new QHBoxLayout;
    removeUvLayout->addWidget(removeUvLabel);
    removeUvLayout->addWidget(removeUv_comboBox_);
    removeUvLayout->addWidget(removeUv_remove_);
    removeUvLayout->insertStretch(-1);
    mainLayout->addLayout(removeUvLayout);

    updateUvLists();

    mainLayout->insertStretch(-1);
}

void Admin::addUv()
{
    if(
            addUv_category_->currentText().isEmpty()
            || addUv_code_->text().isEmpty()
            || addUv_title_->text().isEmpty()
            )
        QMessageBox::warning(this,"Formulaire incomplet","Veuillez renseigner tous les champs.",QMessageBox::Ok);
    else
    {
        Uv* uv = new Uv;
        uv->setCategory(Uv::stringToCategory(addUv_category_->currentText()));
        uv->setCode(addUv_code_->text());
        uv->setCredits(addUv_credits_->value());
        uv->setFall(addUv_fall_->isChecked());
        uv->setSpring(addUv_spring_->isChecked());
        uv->setTitle(addUv_title_->text());
        UVManager::instance().addUv(uv);

        showAddUvPanel(false);
        QMessageBox::information(this,"","Uv ajoutée.",QMessageBox::Ok);
    }
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
    addUv_code_ = new QLineEdit;
    addUv_code_->setMaxLength(4);
    addUv_code_->setFixedWidth(50);
    QHBoxLayout* codeLayout = new QHBoxLayout;
    codeLayout->addWidget(codeLabel);
    codeLayout->addWidget(addUv_code_);
    codeLayout->insertStretch(-1);
    mainLayout->addLayout(codeLayout);

    // Title
    QLabel * titleLabel = new QLabel("Intitulé : ");
    titleLabel->setFixedWidth(labelWidth);
    addUv_title_ = new QLineEdit;
    QHBoxLayout* titleLayout = new QHBoxLayout;
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(addUv_title_);
    titleLayout->insertStretch(-1);
    mainLayout->addLayout(titleLayout);

    // Credits
    QLabel* creditsLabel = new QLabel("Crédits : ");
    creditsLabel->setFixedWidth(labelWidth);
    addUv_credits_ = new QSpinBox;
    addUv_credits_->setMinimum(0);
    addUv_credits_->setValue(6);
    addUv_credits_->setSingleStep(1);
    QHBoxLayout* creditsLayout = new QHBoxLayout;
    creditsLayout->addWidget(creditsLabel);
    creditsLayout->addWidget(addUv_credits_);
    creditsLayout->insertStretch(-1);
    mainLayout->addLayout(creditsLayout);

    // Category
    QLabel* categoryLabel = new QLabel("Catégorie : ");
    categoryLabel->setFixedWidth(labelWidth);
    addUv_category_ = new QComboBox;
    addUv_category_->addItem("CS");
    addUv_category_->addItem("TM");
    addUv_category_->addItem("TSH");
    addUv_category_->addItem("SP");
    QHBoxLayout* categoryLayout = new QHBoxLayout;
    categoryLayout->addWidget(categoryLabel);
    categoryLayout->addWidget(addUv_category_);
    categoryLayout->insertStretch(-1);
    mainLayout->addLayout(categoryLayout);

    // Season
    QLabel* seasonLabel = new QLabel("Ouverture : ");
    addUv_spring_ = new QCheckBox("Printemps");
    addUv_spring_->setChecked(true);
    addUv_fall_ = new QCheckBox("Automne");
    addUv_fall_->setChecked(true);
    QHBoxLayout* seasonLayout = new QHBoxLayout;
    seasonLayout->addWidget(seasonLabel);
    seasonLayout->addWidget(addUv_spring_);
    seasonLayout->addWidget(addUv_fall_);
    seasonLayout->insertStretch(-1);
    mainLayout->addLayout(seasonLayout);

    // Submit
    QPushButton* submit = new QPushButton("Ajouter");
    mainLayout->addWidget(submit);
    QObject::connect(submit,SIGNAL(clicked()),this,SLOT(addUv()));
}

void Admin::createEditUvPanel()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    editUvPanel_ = new QWidget;
    editUvPanel_->setLayout(mainLayout);
    int labelWidth = 60;

    // Code
    QLabel * codeLabel = new QLabel("Code : ");
    codeLabel->setFixedWidth(labelWidth);
    editUv_code_ = new QLineEdit;
    editUv_code_->setMaxLength(4);
    editUv_code_->setFixedWidth(50);
    QHBoxLayout* codeLayout = new QHBoxLayout;
    codeLayout->addWidget(codeLabel);
    codeLayout->addWidget(editUv_code_);
    codeLayout->insertStretch(-1);
    mainLayout->addLayout(codeLayout);

    // Title
    QLabel * titleLabel = new QLabel("Intitulé : ");
    titleLabel->setFixedWidth(labelWidth);
    editUv_title_ = new QLineEdit;
    QHBoxLayout* titleLayout = new QHBoxLayout;
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(editUv_title_);
    titleLayout->insertStretch(-1);
    mainLayout->addLayout(titleLayout);

    // Credits
    QLabel* creditsLabel = new QLabel("Crédits : ");
    creditsLabel->setFixedWidth(labelWidth);
    editUv_credits_ = new QSpinBox;
    editUv_credits_->setMinimum(0);
    editUv_credits_->setValue(6);
    editUv_credits_->setSingleStep(1);
    QHBoxLayout* creditsLayout = new QHBoxLayout;
    creditsLayout->addWidget(creditsLabel);
    creditsLayout->addWidget(editUv_credits_);
    creditsLayout->insertStretch(-1);
    mainLayout->addLayout(creditsLayout);

    // Category
    QLabel* categoryLabel = new QLabel("Catégorie : ");
    categoryLabel->setFixedWidth(labelWidth);
    editUv_category_ = new QComboBox;
    editUv_category_->addItem("CS");
    editUv_category_->addItem("TM");
    editUv_category_->addItem("TSH");
    editUv_category_->addItem("SP");
    QHBoxLayout* categoryLayout = new QHBoxLayout;
    categoryLayout->addWidget(categoryLabel);
    categoryLayout->addWidget(editUv_category_);
    categoryLayout->insertStretch(-1);
    mainLayout->addLayout(categoryLayout);

    // Season
    QLabel* seasonLabel = new QLabel("Ouverture : ");
    editUv_spring_ = new QCheckBox("Printemps");
    editUv_spring_->setChecked(true);
    editUv_fall_ = new QCheckBox("Automne");
    editUv_fall_->setChecked(true);
    QHBoxLayout* seasonLayout = new QHBoxLayout;
    seasonLayout->addWidget(seasonLabel);
    seasonLayout->addWidget(editUv_spring_);
    seasonLayout->addWidget(editUv_fall_);
    seasonLayout->insertStretch(-1);
    mainLayout->addLayout(seasonLayout);

    // Submit
    QPushButton* submit = new QPushButton("Modifier");
    mainLayout->addWidget(submit);
    QObject::connect(submit,SIGNAL(clicked()),this,SLOT(editUv()));
}

void Admin::removeUv()
{
    UVManager::instance().removeUv(removeUv_comboBox_->currentText());
    updateUvLists();
    removeUv_remove_->setVisible(false);
    QMessageBox::information(this,"","Uv supprimée.",QMessageBox::Ok);
}

void Admin::editUv()
{
    if(
            editUv_category_->currentText().isEmpty()
            || editUv_code_->text().isEmpty()
            || editUv_title_->text().isEmpty()
            )
        QMessageBox::warning(this,"Formulaire incomplet","Veuillez renseigner tous les champs.",QMessageBox::Ok);
    else
    {
        Uv* uv = new Uv;
        uv->setCategory(Uv::stringToCategory(editUv_category_->currentText()));
        uv->setCode(editUv_code_->text());
        uv->setCredits(editUv_credits_->value());
        uv->setFall(editUv_fall_->isChecked());
        uv->setSpring(editUv_spring_->isChecked());
        uv->setTitle(editUv_title_->text());
        UVManager::instance().addUv(uv);

        showEditUvPanel(false);
        QMessageBox::information(this,"","Uv modifiée.",QMessageBox::Ok);
    }
}

void Admin::editUv(QString code)
{
    editUv_uv_ = UVManager::instance().uvFromCode(code);

    editUv_category_->setCurrentText(Uv::categoryToString(editUv_uv_->category()));
    editUv_code_->setText(editUv_uv_->code());
    editUv_credits_->setValue(editUv_uv_->credits());
    editUv_spring_->setChecked(editUv_uv_->spring());
    editUv_fall_->setChecked(editUv_uv_->fall());
    editUv_title_->setText(editUv_uv_->title());

    showEditUvPanel(true);
}

void Admin::showAddUvPanel(bool show)
{
    addUvPanel_->setVisible(show);
}

void Admin::showEditUvPanel(bool show)
{
    editUvPanel_->setVisible(show);
}

void Admin::showRemoveUvButton(QString code)
{
    if(UVManager::instance().uvFromCode(code))
        removeUv_remove_->setVisible(true);
    else
        removeUv_remove_->setVisible(false);
}

void Admin::updateUvLists()
{
    QList<const Uv*> uvs = UVManager::instance().uvs();

    editUv_comboBox_->clear();
    removeUv_comboBox_->clear();

    for(int i = 0; i < uvs.size(); i++)
    {
        QString code = uvs.at(i)->code();
        editUv_comboBox_->addItem(code);
        removeUv_comboBox_->addItem(code);
    }

    editUv_comboBox_->insertItem(0,"Selectionnez une Uv...");
    editUv_comboBox_->setCurrentIndex(0);
    removeUv_comboBox_->insertItem(0,"Selectionnez une Uv...");
    removeUv_comboBox_->setCurrentIndex(0);
}
