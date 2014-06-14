#ifndef UVMANAGER_H
#define UVMANAGER_H
#include <QtWidgets>
#include <QtXml>
#include <QDebug>
#include "utprofilerexception.h"
#include "degree.h"
#include "student.h"

/**
 * @brief The UVManager class
 * Cette classe singleton gère le chargement et la sauvegarde des données.
 * Elle contient donc tous les objets (uv,student,degree) qui portent l'information pendant l'exécution du programme.
 * Les attributs *filePath_ indique le chemin relatif pour le chargement des fichiers xml.
 */

class UVManager
{
public:
    void addDegree(Degree *degree);
    void addUv(Uv* uv);
    void addStudent(const QString &login);
    void addStudent(Student *student);

    /**
     * @brief connect
     * @param login
     * @return connection status
     * Réalise une tentative de connexion de l'étudiant à partir du login passé en paramètre.
     * Renvoie vrai si la connexion est réussie, faux sinon.
     */
    bool connect(const QString &login);
    const QList<Degree*> & degrees() const {return degrees_;}
    const QString & degreesFilePath() const {return degreesFilePath_;}

    /**
     * @brief degreeWithTitle
     * @param title
     * @return
     * Renvoie le premier cursus trouvé avec le titre passé en paramètre.
     */
    Degree * degreeWithTitle(const QString &title);

    /**
     * @brief degreesWithParent
     * @param parentTitle
     * @return
     * Renvoie la liste des cursus ayant pour parent celui portant le titre passé en paramètre.
     */
    QList<const Degree*> degreesWithParent(const QString &parentTitle);
    static UVManager& instance();

    /**
     * @brief load
     * Appelle les différentes fonctions de chargements des fichiers xml.
     */
    void load();
    void removeDegree(const QString &title);
    void removeUv(const QString &code);
    Student* student() {return student_;}
    const QList<Student*> students() const {return students_;}

    /**
     * @brief uvFromCode
     * @param code
     * @return
     * Renvoie l'uv avec le code demandé.
     */
    const Uv* uvFromCode(const QString &code) const;
    QList<const Uv*> uvs() const;

    /**
     * @brief uvsFromCode
     * @param codes
     * @return
     * Renvoie l'ensemble des uvs demandées selon leur code.
     */
    QList<const Uv*> uvsFromCode(const QStringList &codes) const;

private:
    UVManager();
    ~UVManager();
    UVManager(const UVManager& um);
    UVManager& operator=(const UVManager& um);
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

    friend struct Handler;
    struct Handler
    {
        UVManager* instance_;
        Handler():instance_(0){}
        ~Handler()
        {
            if(instance_)
                delete instance_;
            instance_ = 0;
        }
    };
    static Handler handler_;

    QString categoriesFilePath_;
    static UVManager* instance_;
    QList<Degree*> degrees_;
    QString degreesFilePath_;
    Student* student_;
    QList<Student*> students_;
    QString studentsFilePath_;
    QList<Uv*> uvs_;
    QString uvsFilePath_;
};

#endif // UVMANAGER_H
