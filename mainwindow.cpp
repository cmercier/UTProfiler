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
    QListWidgetItem* catalogItem = new QListWidgetItem;
    catalogItem->setText("Catalogue Uvs");
    lw->insertItem(0,catalogItem);
    QListWidgetItem* curriculumItem = new QListWidgetItem;
    curriculumItem->setText("Mon parcours");
    lw->insertItem(1,curriculumItem);
    QListWidgetItem* adminItem = new QListWidgetItem;
    adminItem->setText("Admin");
    lw->insertItem(2,adminItem);

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
    navigationStackedWidget_->setCurrentIndex(index);
}
