#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include "catalog.h"
#include "curriculum.h"
#include "sessionmanager.h"
#include "admin.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void setTag(int index);

private:
    void createStackedWidget();

    Admin* admin_;
    Catalog* catalog_;
    Curriculum* curriculum_;
    QStackedWidget* navigationStackedWidget_;

};

#endif // MAINWINDOW_H