#ifndef EXPECTATIONS_H
#define EXPECTATIONS_H
#include <QtWidgets>
#include "uvmanager.h"
#include "utilities.h"
#include "student.h"
#include "algo.h"

/**
 * @brief The Expectations class
 * Onglet des prévisions. L'étudiant peut consulter des prévisions effectuées auparavant ou en générer de nouvelles.
 * Pour faire une prévisions, il spécifie les uvs qu'il souhaite suivre ou pas, le cursus, ainsi que les semestres restants.
 */

class Expectations: public QWidget
{
    Q_OBJECT

public:
    Expectations();

    /**
     * @brief setStrategy
     * @param strategy
     * Définit l'algorithme utilisé.
     */
    void setStrategy(AlgoStrategy* strategy) { autocompletion_ = strategy; }

public slots:
    /**
     * @brief addWantedDegree
     * Ajouter une formation que l'étudiant souhaite suivre.
     */
    void addWantedDegree();

    /**
     * @brief addSemester
     * Ajoute une semestre dans la liste des semestres restant à l'étudiant.
     */
    void addSemester();

    /**
     * @brief createExpPanel
     * Créé l'interface avec les différents widgets.
     */
    void createExpPanel();
    void deleteDegree();
    void deleteExp();
    void deleteSemester();

    /**
     * @brief generateExp
     * Génère la prévision en fonction de la stratégie définie.
     */
    void generateExp();

    /**
     * @brief saveDatas
     * Sauvegarde le résultat de la prévision dans l'attribut associé.
     */
    void saveDatas();

    /**
     * @brief selectDegree
     * Sélectionne une formation, affiche les sous formations existantes.
     */
    void selectDegree(const QString &);
    void updateExp();
    void updateExpComboBox();
    void updateExpPanel();
    void updateUnwantedUvs();
    void updateWantedUvs();

    /**
     * @brief validateExp
     * Appelée lors l'utilisateur clique sur valider. Lance la génération de la prévision.
     */
    void validateExp();

private:
    void getParentDegree(QHBoxLayout* degreeLayout, const Degree* degree);
    void loadSemesters() const;


    Expectation* exp_;
    QHBoxLayout* degreeLayout_;
    QComboBox* degreesBox_;
    QComboBox* deleteDegree_;
    QVBoxLayout* expLayout_;
    QComboBox* expSelect_;
    QScrollArea* expScrollArea_;
    QLineEdit* name_;
    QComboBox* seasonBox_;
    const Degree* selectedDegree_;
    QComboBox* semestersBox_;
    QVBoxLayout* semestersLayout_;
    QScrollArea* semestersScrollArea_;
    AlgoStrategy* autocompletion_;
    QVBoxLayout* unwantedUvsLayout_;
    QVBoxLayout* wantedUvsLayout_;
    QSpinBox* yearBox_;
};

#endif // EXPECTATIONS_H
