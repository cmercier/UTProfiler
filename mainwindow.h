#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include "uvmanager.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    void createStackedWidget();
};

#endif // MAINWINDOW_H
