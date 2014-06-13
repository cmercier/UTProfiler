#include "curriculum.h"

Curriculum::Curriculum():
    editStudent_(false),
    selectedDegree_(0)
{
    //student_ = new Student(); // a virer avec la connection

    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QVBoxLayout* l1 = new QVBoxLayout;

    // Modify Button
    QHBoxLayout* editLayout = new QHBoxLayout;
    QPushButton* edit = new QPushButton("Modifier");
    edit->setCheckable(true);
    edit->setChecked(false);
    QObject::connect(edit,SIGNAL(toggled(bool)),this,SLOT(editStudent(bool)));
    editLayout->addStretch();
    editLayout->addWidget(edit);
    l1->addLayout(editLayout);

    // Student
    studentLayout_ = new QHBoxLayout;
    l1->addLayout(studentLayout_);

    // Identity
    identityLayout_ = new QHBoxLayout;
    l1->addLayout(identityLayout_);

    // Equivalences
    equivalence_ = new QHBoxLayout;
    l1->addLayout(equivalence_);

    // Degrees
    degreesLayout_ = new QVBoxLayout;    
    l1->addLayout(degreesLayout_);    

    // Semesters
    uvLayout_ = new QHBoxLayout;
    l1->addLayout(uvLayout_);

    semestersLayout_ = new QVBoxLayout;
    QWidget* widget = new QWidget;
    widget->setLayout(semestersLayout_);
    semestersScrollArea_ = new QScrollArea;
    semestersScrollArea_->setWidget(widget);
    semestersScrollArea_->setWidgetResizable(true);

    // Delete UV
    deleteUvLayout_ = new QHBoxLayout;

    mainLayout->addLayout(l1);
    mainLayout->addWidget(semestersScrollArea_);
    mainLayout->addLayout(deleteUvLayout_);

    //generationView();
}

void Curriculum::addUV()
{
    if (semester_->text().isEmpty() || code_->currentIndex() == 0 || grade_->currentIndex() == 0)
        return;

    UVManager::instance().student()->addUV(code_->currentText(), semester_->text(), Uv::stringToGrade(grade_->currentText()));
    updateStudent();

}

void Curriculum::addDegree()
{
    UVManager::instance().student()->addDegree(selectedDegree_);
    updateStudent();
}

void Curriculum::deleteDegree()
{
    UVManager::instance().student()->deleteDegree(deleteDegree_->currentText());
    updateStudent();
}

void Curriculum::deleteUV()
{
    UVManager::instance().student()->deleteUV(deleteUVCodeUV_->currentText(), deleteUVSemester_->currentText());
    updateStudent();
}

void Curriculum::editStudent(bool edit)
{
    editStudent_ = edit;
    updateStudent();
}

void Curriculum::selectDegree(const QString &title)
{
   /*
     * If the user selects another option in a higher combo box, remove the sub combo boxes
     * For exemple, if the current state is : Branche -> GI -> SRI
     * and the user selects Tronc Commun instead
     * GI and SRI will be removed and the new state will be : Tronc Commun
     */
    selectedDegree_ = UVManager::instance().degreeWithTitle(title);
    int depth;
    selectedDegree_ ? depth = selectedDegree_->depth() : depth = 0;
    while(newDegreeLayout_->count() > depth + 2)
    {
        QLayoutItem* item = newDegreeLayout_->takeAt(newDegreeLayout_->count() - 1);
        newDegreeLayout_->removeItem(item);
        delete item->widget();
        delete item;
    }
    newDegreeLayout_->update();

    /*
     * Add the sub combo box if there is one
     * For exemple, if the user selects Branche
     * A new combo box will show with the options :
     * PCB, SRI, ...
     */
    QList<const Degree*> children = UVManager::instance().degreesWithParent(title);
    if(!children.isEmpty())
    {
        QComboBox* subDegree = new QComboBox;
        subDegree->insertItem(0,"Choix " + children.first()->type());

        for(int i = 0; i < children.size(); i++)
        {
            subDegree->insertItem(i + 1,children.at(i)->title());
        }

        newDegreeLayout_->addWidget(subDegree);
        QObject::connect(subDegree,SIGNAL(activated(QString)),this,SLOT(selectDegree(QString)));
    }
    newDegreeLayout_->addStretch(-1);

    QPushButton* addDegree = new QPushButton("Ajouter le cursus");
    addDegree->setCheckable(true);
    addDegree->setChecked(false);
    QObject::connect(addDegree,SIGNAL(clicked()),this,SLOT(addDegree()));
    newDegreeLayout_->addWidget(addDegree);
}

void Curriculum::updateUvs()
{
    deleteUVCodeUV_->clear();
    deleteUVCodeUV_->insertItem(0, "Choix de l'UV");

    Student* student = UVManager::instance().student();

    for(int i = 0; i < student->semesters().size(); i++)
    {
        if (student->semesters()[i]->title() == deleteUVSemester_->currentText())
        {
            QMapIterator<QString, Grade> it(student->semesters()[i]->uvs());
            while (it.hasNext()) {
                it.next();
                deleteUVCodeUV_->insertItem(i + 1, it.key());
            }
            return;
        }
    }
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
        QVBoxLayout* gradeCol = new QVBoxLayout;

        QMapIterator<QString, Grade> it(semester->uvs());
        while (it.hasNext()) {
            it.next();

            const Uv* uv = UVManager::instance().uvFromCode(it.key()) ;

            QLabel* code = new QLabel(uv->code());
            code->setFixedWidth(50);
            codeCol->addWidget(code);
            QLabel* title = new QLabel(uv->title());
            titleCol->addWidget(title);
            QLabel* credits = new QLabel(QString::number(uv->credits()));
            credits->setFixedWidth(50);
            creditsCol->addWidget(credits);
            QLabel* degree = new QLabel("To do");
            degree->setFixedWidth(100);
            degreeCol->addWidget(degree);
            QLabel* grade = new QLabel(Uv::gradeToString(it.value()));
            grade->setFixedWidth(50);
            gradeCol->addWidget(grade);
        }

        // Refresh uvs layout
        uvsLayout->addLayout(codeCol);
        uvsLayout->addLayout(titleCol);
        uvsLayout->addLayout(creditsCol);
        uvsLayout->addLayout(degreeCol);
        uvsLayout->addLayout(gradeCol);
        semesterBox->setLayout(uvsLayout);

        semestersLayout_->addWidget(semesterBox);
    }
    semestersLayout_->insertStretch(-1);
}

void Curriculum::saveQLineEdit()
{
    Student* student = UVManager::instance().student();
    // Sauvegarde des champs dans l'objet Student
    student->setEquivalenceCs(equivalenceCs_->text().toUInt());
    student->setEquivalenceTm(equivalenceTm_->text().toUInt());
    student->setEquivalenceTsh(equivalenceTsh_->text().toUInt());
    student->setEquivalenceSp(equivalenceSp_->text().toUInt());
    student->setFirstName(firstName_->text());
    student->setLastName(lastName_->text());
}

void Curriculum::updateStudent()
{    
    saveQLineEdit();
    generationView();
}

void Curriculum::generationView()
{
    // Refresh
    Utilities::clearLayout(semestersLayout_);
    Utilities::clearLayout(studentLayout_);
    Utilities::clearLayout(degreesLayout_);
    Utilities::clearLayout(identityLayout_);
    Utilities::clearLayout(equivalence_);
    Utilities::clearLayout(uvLayout_);
    Utilities::clearLayout(deleteUvLayout_);

    Student* student = UVManager::instance().student();

    // Student
    QLabel* studentLabel = new QLabel("Etudiant (login) : ");
    studentLabel->setFixedWidth(80);
    login_ = new QLabel(student->login());

    studentLayout_->addWidget(studentLabel);
    studentLayout_->addWidget(login_);
    studentLayout_->insertStretch(-1);

    // Identity
    QLabel* identityLabel = new QLabel("Identité :");
    identityLabel->setFixedWidth(80);
    firstName_ = new QLineEdit(student->firstName());
    firstName_->setReadOnly(!editStudent_);
    firstName_->setFixedWidth(100);
    lastName_ = new QLineEdit(student->lastName());
    lastName_->setReadOnly(!editStudent_);
    lastName_->setFixedWidth(100);
    identityLayout_->addWidget(identityLabel);
    identityLayout_->addWidget(firstName_);
    identityLayout_->addWidget(lastName_);
    identityLayout_->insertStretch(-1);

    // Equivalences
    QLabel* equivalenceLabel = new QLabel("Equivalences :");
    equivalenceLabel->setFixedWidth(80);
    QLabel* equivalenceCsLabel = new QLabel("CS :");
    QLabel* equivalenceTmLabel = new QLabel("TM :");
    QLabel* equivalenceTshLabel = new QLabel("TSH :");
    QLabel* equivalenceSpLabel = new QLabel("SP :");
    equivalenceCs_ = new QLineEdit(QString::number(student->equivalenceCs()));
    equivalenceTm_ = new QLineEdit(QString::number(student->equivalenceTm()));
    equivalenceTsh_ = new QLineEdit(QString::number(student->equivalenceTsh()));
    equivalenceSp_ = new QLineEdit(QString::number(student->equivalenceSp()));
    equivalenceCs_->setFixedWidth(50);
    equivalenceTm_->setFixedWidth(50);
    equivalenceTsh_->setFixedWidth(50);
    equivalenceSp_->setFixedWidth(50);
    equivalenceCs_->setReadOnly(!editStudent_);
    equivalenceTm_->setReadOnly(!editStudent_);
    equivalenceTsh_->setReadOnly(!editStudent_);
    equivalenceSp_->setReadOnly(!editStudent_);
    equivalence_->addWidget(equivalenceLabel);
    equivalence_->addWidget(equivalenceCsLabel);
    equivalence_->addWidget(equivalenceCs_);
    equivalence_->addWidget(equivalenceTmLabel);
    equivalence_->addWidget(equivalenceTm_);
    equivalence_->addWidget(equivalenceTshLabel);
    equivalence_->addWidget(equivalenceTsh_);
    equivalence_->addWidget(equivalenceSpLabel);
    equivalence_->addWidget(equivalenceSp_);
    equivalence_->insertStretch(-1);


    // Degrees
    QLabel* degreeLabel = new QLabel("Cursus :");
    degreeLabel->setFixedWidth(80);
    newDegreeLayout_ = new QHBoxLayout;
    newDegreeLayout_->addWidget(degreeLabel);
    degreesLayout_->addLayout(newDegreeLayout_);

    if (editStudent_)
    {
        selectedDegree_ = 0;
        const QList<Degree*> &degrees = UVManager::instance().degrees();

        degree_ = new QComboBox;
        QObject::connect(degree_,SIGNAL(activated(QString)),this,SLOT(selectDegree(QString)));

        while (degree_->count() != 0)
            degree_->removeItem(0);

        degree_->insertItem(0,"Choix " + degrees.first()->type());
        int count = 1;
        for(int i = 0; i < degrees.size(); i++)
        {
            if(!degrees.at(i)->parent())
            {
                degree_->insertItem(count,degrees.at(i)->title());
                count++;
            }
        }

        QPushButton* addDegree = new QPushButton("Ajouter le cursus");
        QObject::connect(addDegree,SIGNAL(toggled(bool)),this,SLOT(editStudent(bool)));

        newDegreeLayout_->addWidget(degree_);
        newDegreeLayout_->addStretch(-1);
        newDegreeLayout_->addWidget(addDegree);
    }
    else
        newDegreeLayout_->addStretch(-1);

    for(int i = 0; i <student->degrees().size(); i++)
    {
        const Degree* degree = student->degrees()[i];

        QHBoxLayout* degreeLayout = new QHBoxLayout;

        getParentDegree(degreeLayout, degree);

        degreeLayout->insertStretch(-1);

        degreesLayout_->addLayout(degreeLayout);

    }

    if(editStudent_)
    {
        QHBoxLayout* deleteDegreeLayout = new QHBoxLayout;
        deleteDegree_ = new QComboBox;

        deleteDegree_->insertItem(0, "Choix du cursus");
        for(int i = 0; i < student->degrees().size(); i++)
        {
            deleteDegree_->insertItem(i + 1, student->degrees()[i]->title());
        }

        QPushButton* deleteDegreeButton = new QPushButton("Supprimer le cursus");
        QObject::connect(deleteDegreeButton,SIGNAL(clicked()),this,SLOT(deleteDegree()));

        deleteDegreeLayout->addWidget(deleteDegree_);
        deleteDegreeLayout->insertStretch(-1);
        deleteDegreeLayout->addWidget(deleteDegreeButton);

        degreesLayout_->addLayout(deleteDegreeLayout);
    }

    // Semesters

    // Add UV
    if (editStudent_)
    {
        QLabel* uvLabel = new QLabel("UV : ");
        uvLabel->setFixedWidth(80);
        QPushButton* addUV = new QPushButton("Ajouter l'UV");

        code_ = new QComboBox;
        code_->insertItem(0, "Choix de l'UV");
        QList<const Uv*> uvs;
        uvs = UVManager::instance().uvs();
        for (int i = 0; i < uvs.size(); i++)
        {
            code_->insertItem(i + 1, uvs[i]->code());
        }

        QLabel* semesterLabel = new QLabel("Semestre : ");
        semester_ = new QLineEdit;
        semester_->setFixedWidth(50);

        grade_ = new QComboBox;
        grade_->insertItem(0, "Choix de la note");
        for (int i = A; i <= EC; i++)
        {
            grade_->insertItem(i + 1, Uv::gradeToString(static_cast<Grade>(i)));
        }

        QObject::connect(addUV,SIGNAL(clicked()),this,SLOT(addUV()));

        uvLayout_->addWidget(uvLabel);
        uvLayout_->addWidget(code_);
        uvLayout_->addWidget(semesterLabel);
        uvLayout_->addWidget(semester_);
        uvLayout_->addWidget(grade_);
        uvLayout_->insertStretch(-1);
        uvLayout_->addWidget(addUV);
    }

    // Delete UV
    if(editStudent_)
    {
        deleteUVCodeUV_ = new QComboBox;
        deleteUVSemester_ = new QComboBox;
        QObject::connect(deleteUVSemester_,SIGNAL(activated(QString)),this,SLOT(updateUvs()));
        deleteUVSemester_->insertItem(0, "Choix du semestre");

        for(int i = 0; i < student->semesters().size(); i++)
        {
            deleteUVSemester_->insertItem(i + 1, student->semesters()[i]->title());
        }

        QPushButton* deleteUvButton = new QPushButton("Supprimer l'UV");
        QObject::connect(deleteUvButton,SIGNAL(clicked()),this,SLOT(deleteUV()));


        deleteUvLayout_->addWidget(deleteUVSemester_);
        deleteUvLayout_->addWidget(deleteUVCodeUV_);
        deleteUvLayout_->insertStretch(-1);
        deleteUvLayout_->addWidget(deleteUvButton);
    }

    loadSemesters(student);
}
