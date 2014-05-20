#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include "catalog.h"
#include "curriculum.h"
#include "sessionmanager.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void setTag(int index);

private:
    void createStackedWidget();
    void createUser();

    Catalog* catalog_;
    Curriculum* curriculum_;
    QHBoxLayout* equivalance_;
    QLineEdit* equivalenceCs_;
    QLineEdit* equivalenceTm_;
    QLineEdit* equivalenceTsh_;
    QLineEdit* equivalenceSp_;
    QLineEdit* firstName_;
    QLineEdit* lastName_;
    QStackedWidget* navigationStackedWidget_;
    QComboBox* student_;
    QWidget* user_;
};

#endif // MAINWINDOW_H
