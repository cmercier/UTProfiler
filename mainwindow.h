#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    void createStackedWidget();
};

#endif // MAINWINDOW_H
