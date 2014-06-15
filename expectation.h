#ifndef EXPECTATION_H
#define EXPECTATION_H
#include <QtWidgets>
#include "uv.h"
#include "degree.h"
#include "semester.h"

/**
 * @brief The Expectation class
 * Cette classe porte toutes les informations d'une prévision (uvs voulues et non voulues, semestres restant, formation souhaitée).
 */

class Expectation
{
public:
    Expectation();

    /**
     * @brief addDegree
     * @param degree
     * Ajoute un cursus que l'étudiant souhaite suivre.
     */
    void addDegree(const Degree *degree);

    /**
     * @brief addRejectedUv
     * @param uv
     * Ajoute une uv que l'étudiant ne souhaite pas suivre.
     */
    void addRejectedUv(const Uv* uv);

    /**
     * @brief addRequiredUv
     * @param uv
     * Ajoute une uv que l'étudiant souhaite suivre.
     */
    void addRequiredUv(const Uv* uv);

    /**
     * @brief addSemester
     * @param semester
     * Ajoute un semestre dans la liste des semestres restant à l'étudiant.
     */
    void addSemester(Semester *semester);    
    void addUV(const QString codeUV, const QString semester, Grade grade);
    void clearUvs();
    const QList<const Degree*>& degrees() const {return degrees_;}
    void deleteDegree(const QString& title);
    void deleteSemester(const QString& title);
    const QString & name() const {return name_;}
    void setName(const QString &name) {name_ = name;}
    void setSemesters(QList<Semester*> semesters);
    const QList<const Uv*>& rejectedUvs() const {return rejectedUvs_;}
    const QList<const Uv*>& requiredUvs() const {return requiredUvs_;}
    const QList<Semester*>& semesters() const {return semesters_;}


private:
    QList<const Degree*> degrees_;
    QString name_;
    QList<const Uv*> rejectedUvs_;
    QList<const Uv*> requiredUvs_;
    QList<Semester*> semesters_;

};

#endif // EXPECTATION_H
