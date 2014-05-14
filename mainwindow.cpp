#include "mainwindow.h"

MainWindow::MainWindow()
{
    createStackedWidget();

    UVManager::instance().loadFromFile("UV_UTC.xml");
    UVManager::instance().save("UV_UTC.xml");
}

void MainWindow::createStackedWidget()
{
    // List of all items in the left navigation bar
    QListWidget *lw = new QListWidget(this);
    lw->setFixedWidth(100);
    lw->setSelectionMode(QAbstractItemView::SingleSelection);
    QListWidgetItem *catalogItem = new QListWidgetItem;
    catalogItem->setText("Catalogue Uvs");
    lw->insertItem(0,catalogItem);
    QListWidgetItem *userItem = new QListWidgetItem;
    userItem->setText("Espace perso");
    lw->insertItem(1,userItem);

    // Corresponding pages
    QWidget *catalog = new QWidget;
    catalog->setStyleSheet("background-color:black;");
    QWidget *user = new QWidget;
    user->setStyleSheet("background-color:green;");

    QStackedWidget *sw = new QStackedWidget;
    sw->addWidget(catalog);
    sw->addWidget(user);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(lw);
    mainLayout->addWidget(sw);

    QWidget* cw = new QWidget;
    cw->setLayout(mainLayout);
    setCentralWidget(cw);

    QObject::connect(lw,SIGNAL(currentRowChanged(int)),sw,SLOT(setCurrentIndex(int)));
}

