#ifndef CURRICULUM_H
#define CURRICULUM_H
#include <QtWidgets>
#include <QString>
#include "uvmanager.h"
#include "utilities.h"

/**
 * @brief The Curriculum class
 * L'onglet mon parcours permet à l'étudiant de visualiser et compléter son profil UTC.
 * Il renseigne ses informations personnelles (nom, prénom).
 * Il renseigne les uvs effectués, en précisant la note et le semestre.
 */

class Curriculum: public QWidget
{
    Q_OBJECT

public:
    Curriculum();

public slots:
    /**
     * @brief addUV
     * Vérifie la validité des champs, puis ajoute l'uv via le manager et met à jour l'onglet.
     */
    void addUV();

    /**
     * @brief addDegree
     * Vérifie la validité des champs, puis ajoute le cursus via le manager et met à jour l'onglet.
     */
    void addDegree();

    /**
     * @brief deleteDegree
     * Supprime un cursus via le manager et met à jour les champs.
     */
    void deleteDegree();

    /**
     * @brief deleteUV
     * Supprime une uv via le manager et met à jour les champs.
     */
    void deleteUV();

    /**
     * @brief editStudent
     * @param edit
     * Active ou désactive le mode 'modification'.
     */
    void editStudent(bool edit);

    /**
     * @brief generationView
     * Regénère l'onglet avec les nouvelles informations.
     */
    void generationView();

    /**
     * @brief saveQLineEdit
     * Sauvegarde les données de l'étudiants dans l'objet student.
     */
    void saveQLineEdit();

    /**
     * @brief selectDegree
     * @param title
     * Appelée lorsque l'utilisateur choisit une option de la comboBox.
     * Affiche les cursus enfant.
     */
    void selectDegree(const QString &title);

    /**
     * @brief updateStudent
     * Sauvegarde les données de l'étudiant et regénère l'onglet avec les nouvelles informations.
     */
    void updateStudent();

    /**
     * @brief updateUvs
     * Met à jour la liste des uvs réalisées par l'étudiant.
     */
    void updateUvs();

private:
    /**
     * @brief getParentDegree
     * @param degreeLayout
     * @param degree
     * Renvoie le cursus parent de celui passé en paramètre.
     */
    void getParentDegree(QHBoxLayout* degreeLayout, const Degree* degree);

    /**
     * @brief loadSemesters
     * @param student
     * Met à jour (recharge) les widgets d'affichage des semestres.
     */
    void loadSemesters(const Student *student) const;

    QComboBox* code_;
    QComboBox* degree_;
    QVBoxLayout* degreesLayout_;
    QComboBox* deleteDegree_;
    QComboBox* deleteUVCodeUV_;
    QComboBox* deleteUVSemester_;
    QHBoxLayout* deleteUvLayout_;
    bool editStudent_;
    QHBoxLayout* equivalence_;
    QList<QLineEdit*> equivalences_;
    QLineEdit* firstName_;
    QComboBox* grade_;
    QHBoxLayout* identityLayout_;
    QLineEdit* lastName_;
    QLabel* login_;
    QHBoxLayout* newDegreeLayout_;
    const Degree* selectedDegree_;
    QLineEdit* semester_;
    QVBoxLayout* semestersLayout_;
    QScrollArea* semestersScrollArea_;
    Student* student_;
    QHBoxLayout* studentLayout_;
    QHBoxLayout* uvLayout_;
};

#endif // CURRICULUM_H
