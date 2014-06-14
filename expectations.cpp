#include "expectations.h"
#include <QDebug>
#include "utilities.h"

Expectations::Expectations():
    selectedDegree_(0)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    // Select or create expectations
    exp_ = new Expectation;
    QLabel* expSelectLabel = new QLabel("Mes prévisions :");
    expSelect_ = new QComboBox;
    expSelect_->setInsertPolicy(QComboBox::InsertAlphabetically);
    expSelect_->setFixedWidth(150);
    QObject::connect(expSelect_,SIGNAL(activated(QString)),this,SLOT(updateExp()));
    QObject::connect(expSelect_,SIGNAL(activated(QString)),this,SLOT(createExpPanel()));
    QPushButton* deleteExp = new QPushButton("Supprimer la prévision");
    QObject::connect(deleteExp,SIGNAL(clicked()),this,SLOT(deleteExp()));

    QHBoxLayout* h1 = new QHBoxLayout;
    h1->addWidget(expSelectLabel);
    h1->addWidget(expSelect_);
    h1->addWidget(deleteExp);
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

    // Save button
    QPushButton* validate = new QPushButton("Sauvegarder la prévision");
    QObject::connect(validate,SIGNAL(clicked()),this,SLOT(validateExp()));
    mainLayout->addWidget(validate);

    // Generation button
    QPushButton* generate = new QPushButton("Générer la prévision");
    QObject::connect(generate,SIGNAL(clicked()),this,SLOT());
    mainLayout->addWidget(generate);

    // Semestres générés
    semestersLayout_ = new QVBoxLayout;
    QWidget* widget = new QWidget;
    widget->setLayout(semestersLayout_);
    semestersScrollArea_ = new QScrollArea;
    semestersScrollArea_->setWidget(widget);
    semestersScrollArea_->setWidgetResizable(true);

    mainLayout->addWidget(semestersScrollArea_);
}

void Expectations::addWantedDegree()
{
   if (selectedDegree_ != 0)
       exp_->addDegree(selectedDegree_);

    saveDatas();
    createExpPanel();
}

void Expectations::addSemester()
{
    Semester* s = new Semester;
    s->setTitle(seasonBox_->currentText() + yearBox_->text());
    exp_->addSemester(s);
    createExpPanel();
}

void Expectations::createExpPanel()
{
    Utilities::clearLayout(expLayout_);

    // Name
    QLabel* nameLabel = new QLabel("Nom :");
    name_ = new QLineEdit(exp_->name());
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
    const QList<Degree*> &degrees = UTManager::instance().degrees();
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
    wantedDegrees->setLayout(v1);
    for(int i = 0; i < exp_->degrees().size(); i++)
    {
        const Degree* degree = exp_->degrees()[i];
        QHBoxLayout* degreesLayout = new QHBoxLayout;
        getParentDegree(degreesLayout, degree);
        degreesLayout->insertStretch(-1);
        v1->addLayout(degreesLayout);
    }
    QHBoxLayout* deleteDegreeLayout = new QHBoxLayout;
    deleteDegree_ = new QComboBox;

    deleteDegree_->insertItem(0, "Choix du cursus");
    for(int i = 0; i < exp_->degrees().size(); i++)
    {
        deleteDegree_->insertItem(i + 1, exp_->degrees().at(i)->title());
    }

    QPushButton* deleteDegreeButton = new QPushButton("Supprimer le cursus");
    QObject::connect(deleteDegreeButton,SIGNAL(clicked()),this,SLOT(deleteDegree()));

    deleteDegreeLayout->addWidget(deleteDegree_);
    deleteDegreeLayout->insertStretch(-1);
    deleteDegreeLayout->addWidget(deleteDegreeButton);

    v1->addLayout(deleteDegreeLayout);

    v1->insertStretch(-1);

    QHBoxLayout* h4 = new QHBoxLayout;
    h4->addLayout(h2);
    h4->addLayout(h3);
    h4->insertStretch(-1);
    h4->addWidget(wantedDegrees);
    expLayout_->addLayout(h4);


    // Add semester
    QGroupBox* addSemesterBox = new QGroupBox;
    QVBoxLayout* v2 = new QVBoxLayout;
    addSemesterBox->setLayout(v2);
        // semester
    QLabel* seasonLabel = new QLabel("Semestre :");
    seasonBox_ = new QComboBox;
    seasonBox_->addItem("P");
    seasonBox_->addItem("A");
    QHBoxLayout* h6 = new QHBoxLayout;
    h6->addWidget(seasonLabel);
    h6->addWidget(seasonBox_);
        // date
    QLabel* yearLabel = new QLabel("Année :");
    yearBox_ = new QSpinBox;
    yearBox_->setValue(14);
    // button add
    QPushButton* addSemester = new QPushButton("Ajouter le semestre");
    QObject::connect(addSemester,SIGNAL(clicked()),this,SLOT(addSemester()));
    h6->addWidget(yearLabel);
    h6->addWidget(yearBox_);
    h6->addWidget(addSemester);
    h6->insertStretch(-1);

    v2->addLayout(h6);

    for(int i = 0; i < exp_->semesters().size(); i++)
    {
        QLabel* semester = new QLabel(exp_->semesters().at(i)->title());
        QHBoxLayout* h = new QHBoxLayout;
        h->addWidget(semester);
        h->insertStretch(-1);
        v2->addLayout(h);
    }

    semestersBox_ = new QComboBox;
    for(int i = 0; i < exp_->semesters().size(); i++)
    {
        semestersBox_->addItem(exp_->semesters().at(i)->title());
    }
    QPushButton* deleteSemester = new QPushButton("Supprimer le semestre");
    QObject::connect(deleteSemester,SIGNAL(clicked()),this,SLOT(deleteSemester()));
    QHBoxLayout* h7 = new QHBoxLayout;
    h7->addWidget(semestersBox_);
    h7->addWidget(deleteSemester);
    h7->insertStretch(-1);
    v2->addLayout(h7);


    expLayout_->addWidget(addSemesterBox);

    expLayout_->insertStretch(-1);

    updateWantedUvs();
    updateUnwantedUvs();
    loadSemesters();
}

void Expectations::getParentDegree(QHBoxLayout* degreeLayout, const Degree* degree)
{
    QLabel* degreeTitleLabel;

    if(degree->parent() != 0)
    {
        degreeTitleLabel = new QLabel("->  " + degree->title());
        getParentDegree(degreeLayout, degree->parent());
    }
    else
    {
        degreeTitleLabel = new QLabel(degree->title());
    }

    degreeLayout->addWidget(degreeTitleLabel);
}

void Expectations::deleteDegree()
{
    exp_->deleteDegree(deleteDegree_->currentText());
    createExpPanel();
}

void Expectations::deleteExp()
{
    if (expSelect_->currentIndex() == 0)
        return;

    UTManager::instance().student()->deleteExp(exp_);
    updateExpComboBox();
    updateExp();
    createExpPanel();
}

void Expectations::deleteSemester()
{
    exp_->deleteSemester(semestersBox_->currentText());
    createExpPanel();
}

void Expectations::saveDatas()
{
    // Nom
    exp_->setName(name_->text());

    // Listes d'uvs
    exp_->clearUvs();

    for(int i = 0; i < unwantedUvsLayout_->count() - 1; i++)
    {
        QCheckBox* cb = dynamic_cast<QCheckBox*>(unwantedUvsLayout_->itemAt(i)->widget());
        if (cb->isChecked())
        {
            const Uv *uv = UTManager::instance().uvFromCode(cb->text());
            if(uv)
                exp_->addRejectedUv(uv);
        }
    }

    for(int i = 0; i < wantedUvsLayout_->count() - 1; i++)
    {

        QCheckBox* cb = dynamic_cast<QCheckBox*>(wantedUvsLayout_->itemAt(i)->widget());
        if (cb->isChecked())
        {
            const Uv *uv = UTManager::instance().uvFromCode(cb->text());
            if(uv)
                exp_->addRequiredUv(uv);
        }
    }
}

void Expectations::selectDegree(const QString &title)
{
    selectedDegree_ = UTManager::instance().degreeWithTitle(title);
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

    QList<const Degree*> children = UTManager::instance().degreesWithParent(title);
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

void Expectations::updateExp()
{
    if (expSelect_->currentIndex() == 0)
    {
        exp_ = new Expectation;
        return;
    }

    // Maj de l'exp courant
    Student* student = UTManager::instance().student();

    for (int i = 0; i < student->exp().size(); i++)
    {
        if (expSelect_->currentText() == student->exp().at(i)->name())
            exp_ = student->exp().at(i);
    }
}

void Expectations::updateExpComboBox()
{
    expSelect_->clear();

    Student* student = UTManager::instance().student();
    if(!student)
        return;

    const QList<Expectation*> &exp = student->exp();
    for(int i = 0; i < exp.size(); i++)
    {
        expSelect_->addItem(exp.at(i)->name());
    }

    expSelect_->insertItem(0,"Nouvelle prévision");
    expSelect_->setCurrentIndex(0);

    createExpPanel();
}

void Expectations::updateExpPanel()
{
}

void Expectations::updateUnwantedUvs()
{
    QList<const Uv*> uvs = UTManager::instance().uvs();
    Utilities::clearLayout(unwantedUvsLayout_);

    for(int i = 0; i < uvs.size(); i++)
    {
        QString code = uvs.at(i)->code();
        QCheckBox* uv = new QCheckBox(code);
        if (exp_->rejectedUvs().contains(uvs.at(i)))
            uv->setChecked(true);
        else
            uv->setChecked(false);
        unwantedUvsLayout_->addWidget(uv);
    }

    unwantedUvsLayout_->insertStretch(-1);
}

void Expectations::updateWantedUvs()
{
    QList<const Uv*> uvs = UTManager::instance().uvs();
    Utilities::clearLayout(wantedUvsLayout_);

    for(int i = 0; i < uvs.size(); i++)
    {
        QString code = uvs.at(i)->code();
        QCheckBox* uv = new QCheckBox(code);
        if (exp_->requiredUvs().contains(uvs.at(i)))
            uv->setChecked(true);
        else
            uv->setChecked(false);
        wantedUvsLayout_->addWidget(uv);
    }

    wantedUvsLayout_->insertStretch(-1);
}

void Expectations::validateExp()
{
    if (expSelect_->currentIndex() == 0)
        UTManager::instance().student()->addExp(exp_);

    saveDatas();
    updateExpComboBox();
    updateExp();
    createExpPanel();
}

void Expectations::loadSemesters() const
{
    Utilities::clearLayout(semestersLayout_);
    // Create semesters
    for(int i = 0; i < exp_->semesters().size(); i++)
    {
        const Semester* semester = exp_->semesters().at(i);
        QGroupBox* semesterBox = new QGroupBox(semester->title());

        // Create and populate new uvs layout
        QHBoxLayout* uvsLayout = new QHBoxLayout;
        QVBoxLayout* codeCol = new QVBoxLayout;
        QVBoxLayout* titleCol = new QVBoxLayout;
        QVBoxLayout* creditsCol = new QVBoxLayout;

        QMapIterator<QString, Grade> it(semester->uvs());
        while (it.hasNext()) {
            it.next();

            const Uv* uv = UTManager::instance().uvFromCode(it.key()) ;

            QLabel* code = new QLabel(uv->code());
            code->setFixedWidth(50);
            codeCol->addWidget(code);
            QLabel* title = new QLabel(uv->title());
            titleCol->addWidget(title);
            QLabel* credits = new QLabel(QString::number(uv->credits()));
            credits->setFixedWidth(50);
            creditsCol->addWidget(credits);
        }

        // Refresh uvs layout
        uvsLayout->addLayout(codeCol);
        uvsLayout->addLayout(titleCol);
        uvsLayout->addLayout(creditsCol);
        semesterBox->setLayout(uvsLayout);

        semestersLayout_->addWidget(semesterBox);
    }
    semestersLayout_->insertStretch(-1);
}


