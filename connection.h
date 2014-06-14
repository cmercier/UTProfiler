#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtWidgets>
#include "uvmanager.h"

/**
 * @brief The Connection class
 * L'onglet connexion permet à l'étudiant de s'identifier ou de s'ajouter à la base.
 * Après l'identification, les autres onglets sont mis à jour et complétés avec les informations propres à l'utilisateur.
 */

class Connection: public QWidget
{
    Q_OBJECT

public:
    Connection();

public slots:
    /**
     * @brief login
     * Appelle la fonction de connexion de l'uvmanager.
     * Vérifie la validité du login (8 caractères).
     * Affiche un message.
     */
    void login();

signals:
    /**
     * @brief connected
     * Signal émis lorsque la connexion réussie.
     */
    void connected();

private:
    QLineEdit* connectionEdit_;
};

#endif // CONNECTION_H
