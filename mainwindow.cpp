#include "mainwindow.h"

MainWindow::MainWindow()
{
    UVManager::instance().load();
    createStackedWidget();
}

void MainWindow::createStackedWidget()
{
    // List of all items in the left navigation bar
    QListWidget* lw = new QListWidget(this);
    lw->setFixedWidth(100);
    lw->setSelectionMode(QAbstractItemView::SingleSelection);
    QListWidgetItem* connectionItem = new QListWidgetItem;
    connectionItem->setText("Connexion");
    lw->insertItem(0,connectionItem);
    QListWidgetItem* curriculumItem = new QListWidgetItem;
    curriculumItem->setText("Mon parcours");
    lw->insertItem(1,curriculumItem);
    QListWidgetItem* expectationsItem = new QListWidgetItem;
    expectationsItem->setText("Prévisions");
    lw->insertItem(2,expectationsItem);
    QListWidgetItem* catalogItem = new QListWidgetItem;
    catalogItem->setText("Catalogue Uvs");
    lw->insertItem(3,catalogItem);
    QListWidgetItem* adminItem = new QListWidgetItem;
    adminItem->setText("Gestion Uvs");
    lw->insertItem(4,adminItem);

    // Create the pages
    admin_ = new Admin;
    catalog_ = new Catalog;
    curriculum_ = new Curriculum;
    expectations_ = new Expectations;
    connection_ = new Connection;

    // Link the pages with the vertical navigation bar
    navigationStackedWidget_ = new QStackedWidget;
    navigationStackedWidget_->addWidget(connection_);
    navigationStackedWidget_->addWidget(curriculum_);
    navigationStackedWidget_->addWidget(expectations_);
    navigationStackedWidget_->addWidget(catalog_);
    navigationStackedWidget_->addWidget(admin_);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(lw);
    mainLayout->addWidget(navigationStackedWidget_);

    QWidget* cw = new QWidget;
    cw->setLayout(mainLayout);
    setCentralWidget(cw);

    curriculum_->setEnabled(false);
    expectations_->setEnabled(false);

    QObject::connect(lw,SIGNAL(currentRowChanged(int)),this,SLOT(setTag(int)));
    QObject::connect(connection_,SIGNAL(connected()),expectations_,SLOT(updateExpComboBox()));
    QObject::connect(connection_,SIGNAL(connected()),curriculum_,SLOT(generationView()));
    QObject::connect(connection_,SIGNAL(connected()),this,SLOT(afterConnection()));
}

void MainWindow::setTag(int index)
{
    navigationStackedWidget_->setCurrentIndex(index);
}

void MainWindow::afterConnection()
{
    curriculum_->setEnabled(true);
    expectations_->setEnabled(true);
}
