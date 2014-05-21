#include "curriculum.h"

Curriculum::Curriculum()
{
    // pour tester
    Student* student = UVManager::instance().students()[0];

    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QVBoxLayout* l1 = new QVBoxLayout;

    // Student
    QLabel* studentLabel = new QLabel("Etudiant (login) : ");
    QLabel* login_ = new QLabel(student->login());

    QHBoxLayout* studentLayout_ = new QHBoxLayout;
    studentLayout_->addWidget(studentLabel);
    studentLayout_->addWidget(login_);
    studentLayout_->insertStretch(-1);
    l1->addLayout(studentLayout_);

    //QObject::connect(student_,SIGNAL(activated(QString)),this,SLOT(selectDegree(QString)));


    // Identity
    QLabel* identityLabel = new QLabel("Identité :");
    firstName_ = new QLineEdit(student->firstName());
    lastName_ = new QLineEdit(student->lastName());
    QHBoxLayout* l2 = new QHBoxLayout;
    l2->addWidget(identityLabel);
    l2->addWidget(firstName_);
    l2->addWidget(lastName_);
    l1->addLayout(l2);

    // Equivalences
    QLabel* equivalenceLabel = new QLabel("Equivalences :");
    equivalenceCs_ = new QLineEdit(QString::number(student->equivalenceCs()));
    equivalenceTm_ = new QLineEdit(QString::number(student->equivalenceTm()));
    equivalenceTsh_ = new QLineEdit(QString::number(student->equivalenceTsh()));
    equivalenceSp_ = new QLineEdit(QString::number(student->equivalenceSp()));
    equivalence_ = new QHBoxLayout;
    equivalence_->addWidget(equivalenceLabel);
    equivalence_->addWidget(equivalenceCs_);
    equivalence_->addWidget(equivalenceTm_);
    equivalence_->addWidget(equivalenceTsh_);
    equivalence_->addWidget(equivalenceSp_);

    l1->addLayout(equivalence_);

    // Degrees
    degreesLayout_ = new QVBoxLayout;
    QLabel* degreeLabel = new QLabel("Cursus :");
    degreesLayout_->addWidget(degreeLabel);
    for(int i = 0; i <student->degrees().size(); i++)
    {
        const Degree* degree = student->degrees()[i];

        QHBoxLayout* degreeLayout = new QHBoxLayout;

        getParentDegree(degreeLayout, degree);

        degreeLayout->insertStretch(-1);
        degreesLayout_->addLayout(degreeLayout);

    }
    l1->addLayout(degreesLayout_);

    // Semesters
    semestersLayout_ = new QVBoxLayout;
    QWidget* widget = new QWidget;
    widget->setLayout(semestersLayout_);
    semestersScrollArea_ = new QScrollArea;
    semestersScrollArea_->setWidget(widget);
    semestersScrollArea_->setWidgetResizable(true);
    loadSemesters(student);

    mainLayout->addLayout(l1);
    mainLayout->addWidget(semestersScrollArea_);
}

void Curriculum::getParentDegree(QHBoxLayout* degreeLayout, const Degree* degree)
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

void Curriculum::loadSemesters(const Student* student) const
{
    // Create semesters
    for(int i = 0; i < student->semesters().size(); i++)
    {
        const Semester* semester = student->semesters()[i];
        QGroupBox* semesterBox = new QGroupBox(semester->title());

        // Create and populate new uvs layout
        QHBoxLayout* uvsLayout = new QHBoxLayout;
        QVBoxLayout* codeCol = new QVBoxLayout;
        QVBoxLayout* titleCol = new QVBoxLayout;
        QVBoxLayout* creditsCol = new QVBoxLayout;
        QVBoxLayout* degreeCol = new QVBoxLayout;

        for(int i = 0; i < semester->uvs().size(); i++)
        {
            const Uv* uv = semester->uvs()[i];

            QLabel* code = new QLabel(uv->code());
            code->setFixedWidth(50);
            codeCol->addWidget(code);
            QLabel* title = new QLabel(uv->title());
            titleCol->addWidget(title);
            QLabel* credits = new QLabel(QString::number(uv->credits()));
            credits->setFixedWidth(50);
            creditsCol->addWidget(credits);
            QLabel* degree = new QLabel("a faire");
            degree->setFixedWidth(100);
            degreeCol->addWidget(degree);
        }

        // Refresh uvs layout
        uvsLayout->addLayout(codeCol);
        uvsLayout->addLayout(titleCol);
        uvsLayout->addLayout(creditsCol);
        uvsLayout->addLayout(degreeCol);
        semesterBox->setLayout(uvsLayout);

        semestersLayout_->addWidget(semesterBox);
    }
    semestersLayout_->insertStretch(-1);
}
