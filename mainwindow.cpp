#include "mainwindow.h"

MainWindow::MainWindow()
{
    createStackedWidget();
}

void MainWindow::createStackedWidget()
{
    QWidget *catalog = new QWidget;
    QWidget *user = new QWidget;

    QListWidget *lw = new QListWidget(this);
    lw->setFixedSize(100,400);
    lw->setSelectionMode(QAbstractItemView::SingleSelection);
    QListWidgetItem *catalogItem = new QListWidgetItem;
    catalogItem->setText("Catalogue Uvs");
    lw->insertItem(0,catalogItem);
    QListWidgetItem *userItem = new QListWidgetItem;
    userItem->setText("Espace perso");
    lw->insertItem(1,userItem);

    QStackedWidget *sw = new QStackedWidget;
    sw->addWidget(catalog);
    sw->addWidget(user);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(sw);
    setLayout(layout);
}

