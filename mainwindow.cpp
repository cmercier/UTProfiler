#include "mainwindow.h"

MainWindow::MainWindow():
    selectedDegree_(0)
{
    try
    {
        UVManager::instance().loadUvs("UV_UTC.xml");
        UVManager::instance().loadDegrees("formations.xml");
    }
    catch(UTProfilerException e)
    {
        qDebug() << e.getInfo();
    }

    createStackedWidget();
}

void MainWindow::clearLayout(QLayout *layout)
{
    if(layout)
    {
        QLayoutItem* item;
        while( (item = layout->takeAt(0)) )
        {
            if(item->layout())
            {
                clearLayout(item->layout());
                delete item->layout();
            }
            if(item->widget())
                delete item->widget();

            delete item;
        }
    }
}

void MainWindow::createCatalog()
{
    catalog_ = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    catalog_->setLayout(mainLayout);

    QVBoxLayout* l1 = new QVBoxLayout;

    // Degree
    QLabel* degreeLabel = new QLabel("Formation : ");
    degree_ = new QComboBox;
    const QList<Degree*> &degrees = UVManager::instance().degrees();
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
    QObject::connect(degree_,SIGNAL(activated(QString)),this,SLOT(selectDegree(QString)));
    degreeLayout_ = new QHBoxLayout;
    degreeLayout_->addWidget(degreeLabel);
    degreeLayout_->addWidget(degree_);
    degreeLayout_->insertStretch(-1);
    l1->addLayout(degreeLayout_);

    // Season
    QLabel* seasonLabel = new QLabel("Semestre : ");
    spring_ = new QCheckBox("Printemps");
    spring_->setChecked(true);
    fall_ = new QCheckBox("Automne");
    fall_->setChecked(true);
    QHBoxLayout* l2 = new QHBoxLayout;
    l2->addWidget(seasonLabel);
    l2->addWidget(spring_);
    l2->addWidget(fall_);
    l2->insertStretch(-1);
    l1->addLayout(l2);

    // Category
    QLabel* categoryLabel = new QLabel("Catégorie : ");
    cs_ = new QCheckBox("CS");
    cs_->setChecked(true);
    tm_ = new QCheckBox("TM");
    tm_->setChecked(true);
    tsh_ = new QCheckBox("TSH");
    tsh_->setChecked(true);
    sp_ = new QCheckBox("SP");
    sp_->setChecked(true);
    QHBoxLayout* l3 = new QHBoxLayout;
    l3->addWidget(categoryLabel);
    l3->addWidget(cs_);
    l3->addWidget(tm_);
    l3->addWidget(tsh_);
    l3->addWidget(sp_);
    l3->insertStretch(-1);
    l1->addLayout(l3);

    // Uvs
    uvsLayout_ = new QHBoxLayout;
    QWidget* widget = new QWidget;
    widget->setLayout(uvsLayout_);
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widget);

    mainLayout->addLayout(l1);
    mainLayout->addWidget(scrollArea);
    //mainLayout->addStretch(-1);

    // By default display all uvs
    updateCatalog();
}

void MainWindow::createStackedWidget()
{
    // List of all items in the left navigation bar
    QListWidget* lw = new QListWidget(this);
    lw->setFixedWidth(100);
    lw->setSelectionMode(QAbstractItemView::SingleSelection);
    QListWidgetItem* catalogItem = new QListWidgetItem;
    catalogItem->setText("Catalogue Uvs");
    lw->insertItem(0,catalogItem);
    QListWidgetItem *userItem = new QListWidgetItem;
    userItem->setText("Espace perso");
    lw->insertItem(1,userItem);

    // Create the pages
    createCatalog();
    createUser();

    // Link the pages with the vertical navigation bar
    QStackedWidget* sw = new QStackedWidget;
    sw->addWidget(catalog_);
    sw->addWidget(user_);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(lw);
    mainLayout->addWidget(sw);

    QWidget* cw = new QWidget;
    cw->setLayout(mainLayout);
    setCentralWidget(cw);

    QObject::connect(lw,SIGNAL(currentRowChanged(int)),sw,SLOT(setCurrentIndex(int)));
}

void MainWindow::createUser()
{
    user_ = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    user_->setLayout(mainLayout);

    QVBoxLayout* l1 = new QVBoxLayout;

    // Student
    QLabel* studentLabel = new QLabel("Etudiant : ");
    student_ = new QComboBox;

    student_->insertItem(0, "Clement Mercier");
    /*int count = 1;
    for(int i = 0; i < degrees.size(); i++)
    {
        if(!degrees.at(i)->parent())
        {
            degree_->insertItem(count,degrees.at(i)->title());
            count++;
        }
    }*/
    QHBoxLayout* studentLayout_ = new QHBoxLayout;
    studentLayout_->addWidget(studentLabel);
    studentLayout_->addWidget(student_);
    studentLayout_->insertStretch(-1);
    l1->addLayout(studentLayout_);

    //QObject::connect(student_,SIGNAL(activated(QString)),this,SLOT(selectDegree(QString)));


    // Identity
    QLabel* identityLabel = new QLabel("Identité :");
    firstName_ = new QLineEdit("Clement");
    lastName_ = new QLineEdit("Mercier");
    QHBoxLayout* l2 = new QHBoxLayout;
    l2->addWidget(identityLabel);
    l2->addWidget(firstName_);
    l2->addWidget(lastName_);
    l2->insertStretch(-1);
    l1->addLayout(l2);

    // Cursus
    /*QLabel* categoryLabel = new QLabel("Catégorie : ");
    cs_ = new QCheckBox("CS");
    cs_->setChecked(true);
    tm_ = new QCheckBox("TM");
    tm_->setChecked(true);
    tsh_ = new QCheckBox("TSH");
    tsh_->setChecked(true);
    sp_ = new QCheckBox("SP");
    sp_->setChecked(true);
    QHBoxLayout* l3 = new QHBoxLayout;
    l3->addWidget(categoryLabel);
    l3->addWidget(cs_);
    l3->addWidget(tm_);
    l3->addWidget(tsh_);
    l3->addWidget(sp_);
    l3->insertStretch(-1);
    l1->addLayout(l3);*/

    // Uvs

    // Equivalences
    QLabel* equivalenceLabel = new QLabel("Equivalences :");
    equivalenceCs_ = new QLineEdit("6");
    equivalenceTm_ = new QLineEdit("6");
    equivalenceTsh_ = new QLineEdit("6");
    equivalenceSp_ = new QLineEdit("6");
    equivalance_ = new QHBoxLayout;
    equivalance_->addWidget(equivalenceLabel);
    equivalance_->addWidget(equivalenceCs_);
    equivalance_->addWidget(equivalenceTm_);
    equivalance_->addWidget(equivalenceTsh_);
    equivalance_->addWidget(equivalenceSp_);
    equivalance_->insertStretch(-1);

    l1->addLayout(equivalance_);

    mainLayout->addLayout(l1);
}

void MainWindow::selectDegree(const QString &title)
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
    while(degreeLayout_->count() > depth + 2)
    {
        QLayoutItem* item = degreeLayout_->takeAt(degreeLayout_->count() - 1);
        degreeLayout_->removeItem(item);
        delete item->widget();
        delete item;
    }
    degreeLayout_->update();

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

        degreeLayout_->addWidget(subDegree);
        QObject::connect(subDegree,SIGNAL(activated(QString)),this,SLOT(selectDegree(QString)));
    }

    degreeLayout_->insertStretch(-1);
}

void MainWindow::updateCatalog()
{
    QList<const Uv*> uvs;
    selectedDegree_ ? uvs = selectedDegree_->uvs() : uvs = UVManager::instance().uvs();

    int i(0);
    while(i < uvs.size())
    {
        const Uv* uv = uvs.at(i);
        if(
                (
                    (fall_->isChecked() && uv->fall()) ||
                    (spring_->isChecked() && uv->spring())
                ) &&
                (
                    (cs_->isChecked() && uv->category() == CS) ||
                    (tsh_->isChecked() && uv->category() == TSH) ||
                    (tm_->isChecked() && uv->category() == TM) ||
                    (sp_->isChecked() && uv->category() == SP)
                )
           )
            i++;
        else
            uvs.removeAt(i);
    }

    // Clear current uvs layout
    clearLayout(uvsLayout_);

    // Create and populate new uvs layout
    QVBoxLayout* codeCol = new QVBoxLayout;
    uvsLayout_->addLayout(codeCol);

    QVBoxLayout* titleCol = new QVBoxLayout;
    uvsLayout_->addLayout(titleCol);

    QVBoxLayout* creditsCol = new QVBoxLayout;
    uvsLayout_->addLayout(creditsCol);

    for(int i = 0; i < uvs.size(); i++)
    {
        const Uv* uv = uvs.at(i);
        QLineEdit* code = new QLineEdit(uv->code());
        code->setFixedWidth(50);
        codeCol->addWidget(code);
        QLineEdit* title = new QLineEdit(uv->title());
        titleCol->addWidget(title);
        QLineEdit* credits = new QLineEdit(QString::number(uv->credits()));
        credits->setFixedWidth(50);
        creditsCol->addWidget(credits);
    }
}
