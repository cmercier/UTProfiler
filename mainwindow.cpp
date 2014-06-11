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
    QListWidgetItem* adminItem = new QListWidgetItem;
    adminItem->setText("Admin");
    lw->insertItem(2,adminItem);
    /*QListWidgetItem *userItem = new QListWidgetItem;
    userItem->setText("Espace perso");
    lw->insertItem(2,userItem);*/

    // Create the pages
    admin_ = new Admin;
    catalog_ = new Catalog;
    curriculum_ = new Curriculum;

    // Link the pages with the vertical navigation bar
    navigationStackedWidget_ = new QStackedWidget;
    navigationStackedWidget_->addWidget(catalog_);
    navigationStackedWidget_->addWidget(curriculum_);
    navigationStackedWidget_->addWidget(admin_);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(lw);
    mainLayout->addWidget(navigationStackedWidget_);

    QWidget* cw = new QWidget;
    cw->setLayout(mainLayout);
    setCentralWidget(cw);

    QObject::connect(lw,SIGNAL(currentRowChanged(int)),this,SLOT(setTag(int)));
}

void MainWindow::setTag(int index)
{
    //if((index == 1 || index == 2) && !SessionManager::instance().currentStudent())
    //        SessionManager::instance().signIn(this);

    navigationStackedWidget_->setCurrentIndex(index);
}
