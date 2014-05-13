#include <QApplication>
#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc,argv);

    MainWindow mainWindow;
    mainWindow.setFixedSize(850,420);
    mainWindow.show();

    return app.exec();
}
