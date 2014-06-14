#ifndef ADMIN_H
#define ADMIN_H
#include <QtWidgets>
#include "uvmanager.h"
#include "utilities.h"

/**
 * @brief The Admin class
 * L'onglet de gestion des uvs permet au personnel de l'UTC de rajouter, éditer ou supprimer des uvs ou cursus.
 * Les données sont gérées par l'UVManager, qui sauvegarde le tout à la fermeture de l'application.
 */

class Admin: public QWidget
{
    Q_OBJECT

public:
    Admin();

public slots:
    /**
     * @brief addDegree
     * Ajoute un cursus dans la base. Affiche un message à l'utilisateur.
     */
    void addDegree();

    /**
     * @brief addUv
     *Ajoute une uv dans la base. Affiche un message à l'utilisateur.
     */
    void addUv();

    /**
     * @brief editUv
     * Modifie une uv. Vérifie que les camps soient bien complétés. Affiche un message à l'utilisateur.
     */
    void editUv();

    /**
     * @brief editUv
     * Affiche l'uv que l'on souhaite modifier.
     */
    void editUv(QString);

    /**
     * @brief removeDegree
     * Supprime un cursus de la base. Ne supprime les cursus enfant (qui peuvent être intégrés dans d'autres cursus).
     * Affiche un message à l'utilisateur.
     */
    void removeDegree();

    /**
     * @brief removeUv
     * Supprime une uv de la base. Affiche un message à l'utilisateur.
     */
    void removeUv();

    /**
     * @brief showAddDegreePanel
     * Affiche la panneau d'ajout de cursus.
     */
    void showAddDegreePanel(bool);

    /**
     * @brief showAddUvPanel
     * Affiche le panneau d'ajout d'uvs.
     */
    void showAddUvPanel(bool);

    /**
     * @brief showEditUvPanel
     * Affiche le panneau de modification d'uvs.
     */
    void showEditUvPanel(bool);

    /**
     * @brief showRemoveDegreeButton
     * Affiche le panneau de suppression de cursus.
     */
    void showRemoveDegreeButton(QString);

    /**
     * @brief showRemoveUvButton
     * Affiche le bouton de suppression d'uvs.
     */
    void showRemoveUvButton(QString);

private:
    /**
     * @brief createAddDegreePanel
     * Créé le panneau d'ajout de cursus.
     */
    void createAddDegreePanel();

    /**
     * @brief createAddUvPanel
     * Crée le panneau d'ajout d'uvs.
     */
    void createAddUvPanel();

    /**
     * @brief createEditUvPanel
     * Créé le panneau de modification d'uvs.
     */
    void createEditUvPanel();

    /**
     * @brief updateForms
     * Met à jours les listes déroulantes, en prenant en comptes les ajouts, modifications ou suppression d'uvs et de cursus réalisés.
     */
    void updateForms();

    QList<QSpinBox*> addDegree_criteria_;
    QLineEdit* addDegree_name_;
    QComboBox* addDegree_parent_;
    QComboBox* addDegree_uvs_;
    QVBoxLayout* addDegree_uvs_layout_;
    QList<QCheckBox*> addDegree_uvsBoxes_;
    QWidget* addDegreePanel_;
    QScrollArea* addDegree_scrollArea_;
    QComboBox* addUv_category_;
    QLineEdit* addUv_code_;
    QSpinBox* addUv_credits_;
    QCheckBox* addUv_fall_;
    QWidget* addUvPanel_;
    QCheckBox* addUv_spring_;
    QLineEdit* addUv_title_;
    QComboBox* editUv_category_;
    QLineEdit* editUv_code_;
    QComboBox* editUv_comboBox_;
    QSpinBox* editUv_credits_;
    QCheckBox* editUv_fall_;
    QWidget* editUvPanel_;
    const Uv* editUv_uv_;
    QCheckBox* editUv_spring_;
    QLineEdit* editUv_title_;
    QComboBox* removeDegree_comboBox_;
    QPushButton* removeDegree_remove_;
    QComboBox* removeUv_comboBox_;
    QPushButton* removeUv_remove_;
};

#endif // ADMIN_H
