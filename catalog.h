#ifndef CATALOG_H
#define CATALOG_H
#include <QtWidgets>
#include "uvmanager.h"
#include "utilities.h"

/**
 * @brief The Catalog class
 * L'onglet catalogue affiche l'ensemble des uvs, comme proposé sur l'ENT, rubrique 'consultation des enseignement'.
 * Il permet de trier selon les catégories d'uvs (CS,TSH...)  et leur ouverture (printemps, automne).
 * Il est possible de visualiser les uvs propres à un cursus.
 */

class Catalog: public QWidget
{
    Q_OBJECT

public:
    Catalog();

public slots:
    /**
     * @brief criteriaChanged
     * Slot appelé lorsque l'utilisateur change de critère de tri.
     * Active le bouton 'rechercher'.
     */
    void criteriaChanged();

    /**
     * @brief selectDegree
     * @param title
     * Sélection d'un cursus particulier. Affiche la liste des sous-cursus associés.
     */
    void selectDegree(const QString &title);

    /**
     * @brief updateCatalog
     * Rafraîchit la page selon les nouveaux critères.
     */
    void updateCatalog();

private:
    QList<QCheckBox*> categories_;
    QComboBox* degree_;
    QHBoxLayout* degreeLayout_;
    bool editCatalog_;
    QCheckBox* fall_;
    bool isCriteriaChange_;
    const Degree* selectedDegree_;
    QCheckBox* spring_;
    QPushButton* submit_;
    QHBoxLayout* uvsLayout_;
    QScrollArea* uvsScrollArea_;
};

#endif // CATALOG_H
