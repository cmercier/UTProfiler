
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

    // Add degree
    QPushButton* addDegreeButton = new QPushButton("Ajouter un cursus");
    addDegreeButton->setCheckable(true);
    QObject::connect(addDegreeButton,SIGNAL(clicked(bool)),this,SLOT(showAddDegreePanel(bool)));
    QHBoxLayout* addDegreeLayout = new QHBoxLayout;
    addDegreeLayout->addWidget(addDegreeButton);
    addDegreeLayout->insertStretch(-1);
    createAddDegreePanel();
    addDegreePanel_->setVisible(false);
    QVBoxLayout* v3 = new QVBoxLayout;
    v3->addLayout(addDegreeLayout);
    v3->addWidget(addDegreePanel_);
    mainLayout->addLayout(v3);

    // Edit degree
    QLabel* editDegreeLabel = new QLabel("Modifier un cursus");
    editDegree_comboBox_ = new QComboBox;
    editDegree_comboBox_->setInsertPolicy(QComboBox::InsertAlphabetically);
    QObject::connect(editDegree_comboBox_,SIGNAL(activated(QString)),this,SLOT(editDegree(QString)));
    QHBoxLayout* editDegreeLayout = new QHBoxLayout;
    editDegreeLayout->addWidget(editDegreeLabel);
    editDegreeLayout->addWidget(editDegree_comboBox_);
    editDegreeLayout->insertStretch(-1);
    createEditDegreePanel();
    editDegreePanel_->setVisible(false);
    QVBoxLayout* v4 = new QVBoxLayout;
    v4->addLayout(editDegreeLayout);
    v4->addWidget(editDegreePanel_);
    mainLayout->addLayout(v4);

    // Remove degree
    QLabel* removeDegreeLabel = new QLabel("Supprimer un cursus :");
    removeDegree_comboBox_ = new QComboBox;
    removeDegree_remove_ = new QPushButton("Supprimer");
    removeDegree_remove_->setVisible(false);
    QObject::connect(removeDegree_comboBox_,SIGNAL(activated(QString)),this,SLOT(showRemoveDegreeButton(QString)));
    QObject::connect(removeDegree_remove_,SIGNAL(clicked()),this,SLOT(removeDegree()));
    QHBoxLayout* h1 = new QHBoxLayout;
    h1->addWidget(removeDegreeLabel);
    h1->addWidget(removeDegree_comboBox_);
    h1->addWidget(removeDegree_remove_);
    h1->insertStretch(-1);
    mainLayout->addLayout(h1);

    updateForms();

    mainLayout->insertStretch(-1);
}

void Admin::addDegree()
{
    if(addDegree_name_->text().isEmpty())
    {
        QMessageBox::warning(this,"Information manquante","Veuillez indiquer un nom pour la formation.");
        return;
    }

   Degree* degree = new Degree;
   degree->setTitle(addDegree_name_->text());
   for(int i = 0; i < addDegree_uvsBoxes_.size(); i++)
   {
       if(addDegree_uvsBoxes_.at(i)->isChecked())
            degree->addUv(UTManager::instance().uvFromCode(addDegree_uvsBoxes_.at(i)->text()));
   }

   if(addDegree_parent_->currentIndex() > 0)
   {
       degree->setParent(UTManager::instance().degreeWithTitle(addDegree_parent_->currentText()));
   }

   for(int i = 0; i < addDegree_criteria_.size(); i++)
   {
       degree->setQuota(addDegree_criteria_.at(i)->text(),addDegree_criteria_.at(i)->value());
   }

   UTManager::instance().addDegree(degree);

   QMessageBox::information(this,"","Le cursus a été ajouté.");

   showAddDegreePanel(false);
   updateForms();
   addDegree_name_->setText("");

   for(int i = 0; i < addDegree_criteria_.size(); i++)
   {
       addDegree_criteria_[i]->setValue(0);
   }
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
        uv->setCategory(addUv_category_->currentText());
        uv->setCode(addUv_code_->text());
        uv->setCredits(addUv_credits_->value());
        uv->setFall(addUv_fall_->isChecked());
        uv->setSpring(addUv_spring_->isChecked());
        uv->setTitle(addUv_title_->text());
        UTManager::instance().addUv(uv);

        showAddUvPanel(false);
        QMessageBox::information(this,"","Uv ajoutée.",QMessageBox::Ok);
    }
}

void Admin::createAddDegreePanel()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    addDegreePanel_ = new QWidget;
    addDegreePanel_->setLayout(mainLayout);
    int labelWidth = 40;

    // Name
    QLabel* nameLabel = new QLabel("Nom : ");
    nameLabel->setFixedWidth(labelWidth);
    addDegree_name_ = new QLineEdit;
    QHBoxLayout* nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(addDegree_name_);
    nameLayout->insertStretch(-1);
    mainLayout->addLayout(nameLayout);

    QHBoxLayout* h1 = new QHBoxLayout;

    // Add uv
    QLabel* addDegreeLabel = new QLabel("Uvs :");
    addDegreeLabel->setFixedWidth(labelWidth);
    QHBoxLayout* addDegreeLayout = new QHBoxLayout;
    addDegreeLayout->addWidget(addDegreeLabel);
    addDegree_scrollArea_ = new QScrollArea;
    QWidget* saw = new QWidget;
    addDegree_uvs_layout_ = new QVBoxLayout;
    saw->setLayout(addDegree_uvs_layout_);
    addDegree_scrollArea_->setWidgetResizable(true);
    addDegree_scrollArea_->setFixedWidth(110);
    addDegree_scrollArea_->setWidget(saw);
    addDegreeLayout->addWidget(addDegree_scrollArea_);
    //addDegreeLayout->insertStretch(-1);
    h1->addLayout(addDegreeLayout);

    // Add criterias
    QGroupBox* addCriteriaBox = new QGroupBox("Critères");
    QVBoxLayout* v1 = new QVBoxLayout;
    addCriteriaBox->setLayout(v1);

    QStringList categories = Uv::categories_;
    foreach(QString cat,categories)
    {
        QLabel* label = new QLabel(cat);
        label->setFixedWidth(labelWidth);
        QSpinBox* box = new QSpinBox;
        box->setMinimum(0);
        box->setValue(0);
        QHBoxLayout* h = new QHBoxLayout;
        h->addWidget(label);
        h->addWidget(box);
        v1->addLayout(h);
        addDegree_criteria_.push_back(box);
    }

        // Parent degree
    QLabel* parentDegreeLabel = new QLabel("Inclure la formation dans :");
    v1->addWidget(parentDegreeLabel);
    addDegree_parent_ = new QComboBox;
    addDegree_parent_->setInsertPolicy(QComboBox::InsertAlphabetically);
    v1->addWidget(addDegree_parent_);

    v1->insertStretch(-1);
    h1->addWidget(addCriteriaBox);
    h1->insertStretch(-1);

    mainLayout->addLayout(h1);

    // Submit
    QPushButton* submit = new QPushButton("Ajouter");
    QObject::connect(submit,SIGNAL(clicked()),this,SLOT(addDegree()));
    mainLayout->addWidget(submit);
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
    QStringList categories = Uv::categories_;
    foreach(QString cat,categories)
    {
        addUv_category_->addItem(cat);
    }

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

void Admin::createEditDegreePanel()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    editDegreePanel_ = new QWidget;
    editDegreePanel_->setLayout(mainLayout);
    int labelWidth = 40;

    // Name
    QLabel* nameLabel = new QLabel("Nom : ");
    nameLabel->setFixedWidth(labelWidth);
    editDegree_name_ = new QLineEdit;
    QHBoxLayout* nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(editDegree_name_);
    nameLayout->insertStretch(-1);
    mainLayout->addLayout(nameLayout);

    QHBoxLayout* h1 = new QHBoxLayout;

    // Add uv
    QLabel* editDegreeLabel = new QLabel("Uvs :");
    editDegreeLabel->setFixedWidth(labelWidth);
    QHBoxLayout* editDegreeLayout = new QHBoxLayout;
    editDegreeLayout->addWidget(editDegreeLabel);
    editDegree_scrollArea_ = new QScrollArea;
    QWidget* saw = new QWidget;
    editDegree_uvs_layout_ = new QVBoxLayout;
    saw->setLayout(editDegree_uvs_layout_);
    editDegree_scrollArea_->setWidgetResizable(true);
    editDegree_scrollArea_->setFixedWidth(110);
    editDegree_scrollArea_->setWidget(saw);
    editDegreeLayout->addWidget(editDegree_scrollArea_);
    //editDegreeLayout->insertStretch(-1);
    h1->addLayout(editDegreeLayout);

    // Add criterias
    QGroupBox* addCriteriaBox = new QGroupBox("Critères");
    QVBoxLayout* v1 = new QVBoxLayout;
    addCriteriaBox->setLayout(v1);

    QStringList categories = Uv::categories_;
    foreach(QString cat,categories)
    {
        QLabel* label = new QLabel(cat);
        label->setFixedWidth(labelWidth);
        QSpinBox* box = new QSpinBox;
        box->setMinimum(0);
        box->setValue(0);
        QHBoxLayout* h = new QHBoxLayout;
        h->addWidget(label);
        h->addWidget(box);
        v1->addLayout(h);
        editDegree_criteria_.push_back(box);
    }

        // Parent degree
    QLabel* parentDegreeLabel = new QLabel("Inclure la formation dans :");
    v1->addWidget(parentDegreeLabel);
    editDegree_parent_ = new QComboBox;
    editDegree_parent_->setInsertPolicy(QComboBox::InsertAlphabetically);
    v1->addWidget(editDegree_parent_);

    v1->insertStretch(-1);
    h1->addWidget(addCriteriaBox);
    h1->insertStretch(-1);

    mainLayout->addLayout(h1);

    // Submit
    QPushButton* submit = new QPushButton("Modifier");
    QObject::connect(submit,SIGNAL(clicked()),this,SLOT(editDegree()));
    mainLayout->addWidget(submit);
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
    QStringList categories = Uv::categories_;
    editUv_category_ = new QComboBox;
    foreach(QString cat,categories)
    {
        editUv_category_->addItem(cat);
    }
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

void Admin::editDegree(QString)
{
    Degree* deg = UTManager::instance().degreeWithTitle(editDegree_comboBox_->currentText());
    if(deg)
    {
        QStringList categories = Uv::categories_;
        for(int i = 0; i < categories.size(); i++)
        {
            editDegree_criteria_[i]->setValue(deg->quota(categories.at(i)));
        }

        editDegree_name_->setText(deg->title());

        editDegreePanel_->setVisible(true);
    }
    else
        editDegreePanel_->setVisible(false);
}

void Admin::editDegree()
{
    if(editDegree_name_->text().isEmpty())
    {
        QMessageBox::warning(this,"Information manquante","Veuillez indiquer un nom pour la formation.");
        return;
    }

   Degree* degree = new Degree;
   degree->setTitle(editDegree_name_->text());
   for(int i = 0; i < editDegree_uvsBoxes_.size(); i++)
   {
       if(editDegree_uvsBoxes_.at(i)->isChecked())
            degree->addUv(UTManager::instance().uvFromCode(editDegree_uvsBoxes_.at(i)->text()));
   }

   if(editDegree_parent_->currentIndex() > 0)
   {
       degree->setParent(UTManager::instance().degreeWithTitle(editDegree_parent_->currentText()));
   }

   QStringList cat = Uv::categories_;
   for(int i = 0; i < editDegree_criteria_.size(); i++)
   {
       degree->setQuota(cat.at(i),editDegree_criteria_.at(i)->value());
   }

   UTManager::instance().addDegree(degree);

   QMessageBox::information(this,"","Le cursus a été modifié.");

   editDegreePanel_->setVisible(false);
   updateForms();
   editDegree_name_->setText("");

   for(int i = 0; i < editDegree_criteria_.size(); i++)
   {
       editDegree_criteria_[i]->setValue(0);
   }
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
        uv->setCategory(editUv_category_->currentText());
        uv->setCode(editUv_code_->text());
        uv->setCredits(editUv_credits_->value());
        uv->setFall(editUv_fall_->isChecked());
        uv->setSpring(editUv_spring_->isChecked());
        uv->setTitle(editUv_title_->text());
        UTManager::instance().addUv(uv);

        showEditUvPanel(false);
        QMessageBox::information(this,"","Uv modifiée.",QMessageBox::Ok);
    }
}

void Admin::editUv(QString code)
{
    editUv_uv_ = UTManager::instance().uvFromCode(code);
    if(!editUv_uv_)
    {
        showEditUvPanel(false);
        return;
    }

    editUv_category_->setCurrentText(editUv_uv_->category());
    editUv_code_->setText(editUv_uv_->code());
    editUv_credits_->setValue(editUv_uv_->credits());
    editUv_spring_->setChecked(editUv_uv_->spring());
    editUv_fall_->setChecked(editUv_uv_->fall());
    editUv_title_->setText(editUv_uv_->title());

    showEditUvPanel(true);
}

void Admin::removeDegree()
{
    UTManager::instance().removeDegree(removeDegree_comboBox_->currentText());
    updateForms();
    removeDegree_remove_->setVisible(false);
    QMessageBox::information(this,"","Cursus supprimé.",QMessageBox::Ok);
}

void Admin::removeUv()
{
    UTManager::instance().removeUv(removeUv_comboBox_->currentText());
    updateForms();
    removeUv_remove_->setVisible(false);
    QMessageBox::information(this,"","Uv supprimée.",QMessageBox::Ok);
}

void Admin::showAddDegreePanel(bool show)
{
    addDegreePanel_->setVisible(show);
}

void Admin::showAddUvPanel(bool show)
{
    addUvPanel_->setVisible(show);
}

void Admin::showEditDegreePanel(QString title)
{
    editDegreePanel_->setVisible(UTManager::instance().degreeWithTitle(title));
}

void Admin::showEditUvPanel(bool show)
{
    editUvPanel_->setVisible(show);
}

void Admin::showRemoveDegreeButton(QString title)
{
    if(UTManager::instance().degreeWithTitle(title))
        removeDegree_remove_->setVisible(true);
    else
        removeDegree_remove_->setVisible(false);
}

void Admin::showRemoveUvButton(QString code)
{
    if(UTManager::instance().uvFromCode(code))
        removeUv_remove_->setVisible(true);
    else
        removeUv_remove_->setVisible(false);
}

void Admin::updateForms()
{
    QList<const Uv*> uvs = UTManager::instance().uvs();

    editUv_comboBox_->clear();
    removeUv_comboBox_->clear();
    removeDegree_comboBox_->clear();
    Utilities::clearLayout(addDegree_uvs_layout_);
    Utilities::clearLayout(editDegree_uvs_layout_);

    for(int i = 0; i < uvs.size(); i++)
    {
        QString code = uvs.at(i)->code();
        editUv_comboBox_->addItem(code);
        removeUv_comboBox_->addItem(code);

        QCheckBox* addDegreeUv = new QCheckBox(code);
        addDegreeUv->setChecked(false);
        addDegree_uvs_layout_->addWidget(addDegreeUv);
        addDegree_uvsBoxes_.push_back(addDegreeUv);

        QCheckBox* editDegreeUv = new QCheckBox(code);
        editDegreeUv->setChecked(false);
        editDegree_uvs_layout_->addWidget(editDegreeUv);
        editDegree_uvsBoxes_.push_back(editDegreeUv);
    }

    editUv_comboBox_->insertItem(0,"Selectionnez une Uv...");
    editUv_comboBox_->setCurrentIndex(0);
    editDegree_comboBox_->insertItem(0,"Selectionnez un cursus...");
    editDegree_comboBox_->setCurrentIndex(0);
    removeUv_comboBox_->insertItem(0,"Selectionnez une Uv...");
    removeUv_comboBox_->setCurrentIndex(0);

    const QList<Degree*> &degrees = UTManager::instance().degrees();
    for(int i = 0; i < degrees.size(); i++)
    {
        addDegree_parent_->addItem(degrees.at(i)->title());
        removeDegree_comboBox_->addItem(degrees.at(i)->title());
        editDegree_parent_->addItem(degrees.at(i)->title());
        editDegree_comboBox_->addItem(degrees.at(i)->title());
    }

    addDegree_parent_->insertItem(0,"Parent...");
    addDegree_parent_->setCurrentIndex(0);

    editDegree_parent_->insertItem(0,"Parent...");
    editDegree_parent_->setCurrentIndex(0);

    removeDegree_comboBox_->insertItem(0,"Selectionner un cursus...");
    removeDegree_comboBox_->setCurrentIndex(0);
}
