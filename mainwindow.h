#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <QDebug>
#include "uvmanager.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void selectDegree(const QString &title);
    void updateCatalog();

private:
    void clearLayout(QLayout* layout);
    void createCatalog();
    void createStackedWidget();
    void createUser(); // pour toi clément

    QWidget* catalog_;
    QCheckBox* cs_;
    QComboBox* degree_;
    QHBoxLayout* degreeLayout_;
    QHBoxLayout* equivalance_;
    QLineEdit* equivalenceCs_;
    QLineEdit* equivalenceTm_;
    QLineEdit* equivalenceTsh_;
    QLineEdit* equivalenceSp_;
    QCheckBox* fall_;
    QLineEdit* firstName_;
    QLineEdit* lastName_;
    const Degree* selectedDegree_;
    QCheckBox* sp_;
    QCheckBox* spring_;
    QComboBox* student_;
    QCheckBox* tm_;
    QCheckBox* tsh_;
    QWidget* user_;
    QHBoxLayout* uvsLayout_;
};

#endif // MAINWINDOW_H
