#ifndef XMLDATAPERSISTANCE_H
#define XMLDATAPERSISTANCE_H
#include "datastrategy.h"
#include <QtXml>
#include "utprofilerexception.h"

/**
 * @brief The XmlDataPersistance class
 * Implémente les fonctions de chargement et de sauvegarde des données pour le format xml.
 */

class XmlDataPersistance: public DataStrategy
{
public:
    XmlDataPersistance(QList<Uv*>& uvs,QList<Degree*>& degrees,QList<Student*>& students):
        DataStrategy(uvs,degrees,students),
        categoriesFilePath_("categories.xml"),
        degreesFilePath_("formations.xml"),
        studentsFilePath_("etudiants.xml"),
        uvsFilePath_("UV_UTC.xml")
    {}

protected:
    void execLoad();
    void execSave();

private:
    /**
     * @brief addDegree
     * @param element
     * @param parent
     * Appelée pendant le cahrgement. Rajoute un cursus.
     */
    void addDegree(QDomElement &element,Degree *parent = 0);

    /**
     * @brief addDegrees
     * @param student
     * @param element
     * Appelée pendant le chargement. Rajoute l'ensemble des cursus.
     * addDegree() est une fonctions séparée afin de permettre la récursivité (puisque qu'un cursus peut contenir d'autres cursus).
     */
    void addDegrees(Student *student, QDomElement &element);

    /**
     * @brief addSemesters
     * @param student
     * @param element
     * Appelée pendant le chargement. Rajoute un semestre dans le profil d'un étudiant.
     */
    void addSemesters(Student *student, QDomElement &element);

    /**
     * @brief addUvs
     * @param degree
     * @param element
     * Appelée pendant le chargement. Rajoute un ensemble d'uvs.
     */
    void addUvs(Degree *degree, QDomElement &element);

    /**
     * @brief addUvs
     * @param semester
     * @param element
     * Appelée pendant le chargement. Rajoute un semestre.
     */
    void addUvs(Semester *semester, QDomElement &element);

    /**
     * @brief addQuotas
     * @param degree
     * @param element
     * Appelée pendant le chargement. Rajoute un quota dans un cursus.
     */
    void addQuotas(Degree *degree, QDomElement &element);

    /**
     * @brief loadCategories
     * @param fileName
     * Charge le fichier xml de catégories des uvs.
     */
    void loadCategories(const QString &fileName);

    /**
     * @brief loadDegrees
     * @param fileName
     * Charge le fichier xml des cursus.
     */
    void loadDegrees(const QString &fileName);

    /**
     * @brief loadStudents
     * @param studentsFileName
     * Charge le fichier xml des profils étudiants.
     */
    void loadStudents(const QString &studentsFileName);

    /**
     * @brief loadUvs
     * @param fileName
     * Charge le fichier xml de l'ensemble des uvs.
     */
    void loadUvs(const QString &fileName);

    /**
     * @brief saveDegree
     * @param degree
     * @param element
     * @param dom
     * Appelée pendant la sauvegarde. Sauvegarde un cursus.
     */
    void saveDegree(Degree *degree, QDomElement &element, QDomDocument &dom);

    /**
     * @brief saveDegrees
     * Fonction de sauvegarde des cursus.
     */
    void saveDegrees();

    /**
     * @brief saveStudents
     * Fonction de sauvegarde des étudiants.
     */
    void saveStudents();

    /**
     * @brief saveUvs
     * Fonction de sauvegarde des uvs.
     */
    void saveUvs();

    /**
     * @brief uvFromCode
     * @param code
     * @return
     * Renvoie l'uv avec le code demandé.
     */
    const Uv* uvFromCode(const QString &code) const;

    QString categoriesFilePath_;
    QString degreesFilePath_;
    QString studentsFilePath_;
    QString uvsFilePath_;
};

#endif // XMLDATAPERSISTANCE_H
