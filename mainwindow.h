#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include "catalog.h"
#include "curriculum.h"
#include "sessionmanager.h"
#include "expectations.h"
#include "admin.h"
#include "connection.h"

/**
 * @brief The MainWindow class
 * La fenêtre principale comporte deux parties:
 * - à gauche la barre de navigation permet de naviguer entre les différents onglets.
 * - la partie centrale affiche l'onglet ouvert.
 *
 * L'application comporte 5 onglets:
 * -
 */

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void setTag(int index);
    void afterConnection();

private:
    void createStackedWidget();

    Admin* admin_;
    Catalog* catalog_;
    Connection* connection_;
    Curriculum* curriculum_;
    Expectations* expectations_;
    QStackedWidget* navigationStackedWidget_;

};

#endif // MAINWINDOW_H
