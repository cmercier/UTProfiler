#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include "catalog.h"
#include "curriculum.h"
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
 * - l'onglet 'connexion' permet à l'étudiant de se connecter ou de s'enregistrer dans la base.
 * - l'onglet 'mon parcours' permet à l'étudient de saisir et visualiser son profil.
 * - l'onglet 'prévisions' permet à l'étudiant de réaliser et consulter des prévisions de parcours.
 * - l'onglet 'catalogue' permet à l'étudiant de visualiser l'ensembler des uvs existantes, selon les critères définis.
 * - l'onglet 'gestion uvs' permet au personnel de rajouter et d'éditer les uvs et cursus proposés à l'UTC.
 *
 * La sauvegarde des données est faite automatiquement à la fermeture de l'application.
 */

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    /**
     * @brief setTag
     * @param index
     * Met à jour l'index (l'onglet) de la barre de navigation.
     */
    void setTag(int index);

    /**
     * @brief afterConnection
     * Met à jour les données des formulaires lorsque qu'un nouvel étudiant se connecte.
     */
    void afterConnection();

private:
    /**
     * @brief createStackedWidget
     * Créé la barre de navigation.
     */
    void createStackedWidget();

    Admin* admin_;
    Catalog* catalog_;
    Connection* connection_;
    Curriculum* curriculum_;
    Expectations* expectations_;
    QStackedWidget* navigationStackedWidget_;

};

#endif // MAINWINDOW_H
