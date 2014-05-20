#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include "catalog.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:

private:
    void clearLayout(QLayout* layout);
    void createCatalog();
    void createStackedWidget();
    void createUser();

    Catalog* catalog_;
    QHBoxLayout* equivalance_;
    QLineEdit* equivalenceCs_;
    QLineEdit* equivalenceTm_;
    QLineEdit* equivalenceTsh_;
    QLineEdit* equivalenceSp_;
    QLineEdit* firstName_;
    QLineEdit* lastName_;
    QComboBox* student_;
    QWidget* user_;
};

#endif // MAINWINDOW_H
