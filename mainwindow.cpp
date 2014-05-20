#include "mainwindow.h"

MainWindow::MainWindow()
{
    try
    {
        UVManager::instance().loadUvs("UV_UTC.xml");
        UVManager::instance().loadDegrees("formations.xml");
        UVManager::instance().loadStudents("etudiants.xml");
    }
    catch(UTProfilerException e)
    {
        qDebug() << e.getInfo();
    }

    createStackedWidget();
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
    QListWidgetItem* curriculumItem = new QListWidgetItem;
    curriculumItem->setText("Mon parcours");
    lw->insertItem(1,curriculumItem);
    QListWidgetItem *userItem = new QListWidgetItem;
    userItem->setText("Espace perso");
    lw->insertItem(2,userItem);

    // Create the pages
    createUser();
    catalog_ = new Catalog;
    curriculum_ = new Curriculum;

    // Link the pages with the vertical navigation bar
    navigationStackedWidget_ = new QStackedWidget;
    navigationStackedWidget_->addWidget(catalog_);
    navigationStackedWidget_->addWidget(curriculum_);
    navigationStackedWidget_->addWidget(user_);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(lw);
    mainLayout->addWidget(navigationStackedWidget_);

    QWidget* cw = new QWidget;
    cw->setLayout(mainLayout);
    setCentralWidget(cw);

    QObject::connect(lw,SIGNAL(currentRowChanged(int)),this,SLOT(setTag(int)));
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

void MainWindow::setTag(int index)
{
    //if((index == 1 || index == 2) && !SessionManager::instance().currentStudent())
    //        SessionManager::instance().signIn(this);

    navigationStackedWidget_->setCurrentIndex(index);
}
