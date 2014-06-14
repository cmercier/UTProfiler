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
    void addUv();
    void editUv();
    void editUv(QString);
    void removeDegree();
    void removeUv();
    void showAddDegreePanel(bool);
    void showAddUvPanel(bool);
    void showEditUvPanel(bool);
    void showRemoveDegreeButton(QString);
    void showRemoveUvButton(QString);

private:
    void createAddDegreePanel();
    void createAddUvPanel();
    void createEditUvPanel();
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
