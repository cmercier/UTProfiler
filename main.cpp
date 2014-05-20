#include <QApplication>
#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc,argv);

    MainWindow mainWindow;
    mainWindow.setFixedSize(1280,720);
    mainWindow.show();

    return app.exec();
}
