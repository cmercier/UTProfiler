#include "expectations.h"
#include <QDebug>
#include "utilities.h"

Expectations::Expectations()
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

    // Validation button
    QPushButton* validate = new QPushButton("Valider");
    QObject::connect(validate,SIGNAL(clicked()),this,SLOT(validateExp()));
    mainLayout->addWidget(validate);

    mainLayout->insertStretch(-1);
}

void Expectations::addWantedDegree()
{
    exp_->addDegree(selectedDegree_);

    saveDatas();
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
    wantedDegrees->setLayout(v1);
    for(int i = 0; i < exp_->degrees().size(); i++)
    {
        const Degree* degree = exp_->degrees()[i];

        QHBoxLayout* degreesLayout = new QHBoxLayout;

        getParentDegree(degreesLayout, degree);

        degreesLayout->insertStretch(-1);

        v1->addLayout(degreesLayout);

    }
    v1->insertStretch(-1);

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

void Expectations::saveDatas()
{
    // Nom
    exp_->setName(name_->text());

    // Listes d'uvs
    exp_->clearUvs();

    for(int i = 0; i < unwantedUvsLayout_->count() - 1; i++)
    {
        QCheckBox* cb = dynamic_cast<QCheckBox*>(unwantedUvsLayout_->takeAt(i)->widget());
        if (cb->isChecked())
        {
            qDebug() << "add rejected";
            const Uv *uv = UVManager::instance().uvFromCode(cb->text());
            if(uv)
                exp_->addRejectedUv(uv);
        }
    }

    for(int i = 0; i < wantedUvsLayout_->count() - 1; i++)
    {
        QCheckBox* cb = dynamic_cast<QCheckBox*>(wantedUvsLayout_->takeAt(i)->widget());
        if (cb->isChecked())
        {
            qDebug() << "add required";
            const Uv *uv = UVManager::instance().uvFromCode(cb->text());
            if(uv)
                exp_->addRequiredUv(uv);
        }
    }

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

void Expectations::updateExp()
{
    if (expSelect_->currentIndex() == 0)
    {
        exp_ = new Expectation;
        return;
    }

    // Maj de l'exp courant
    Student* student = UVManager::instance().student();

    for (int i = 0; i < student->exp().size(); i++)
    {
        if (expSelect_->currentText() == student->exp().at(i)->name())
            exp_ = student->exp().at(i);
    }
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

    createExpPanel();
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
    QList<const Uv*> uvs = UVManager::instance().uvs();
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
        UVManager::instance().student()->addExp(exp_);

    saveDatas();
    updateExpComboBox();
}


