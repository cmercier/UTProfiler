#ifndef UVMANAGER_H
#define UVMANAGER_H
#include <QtWidgets>
#include <QDebug>
#include "utprofilerexception.h"
#include "xmldatapersistance.h"

/**
 * @brief The UTManager class
 * Cette classe singleton gère le chargement et la sauvegarde des données.
 * Elle contient donc tous les objets (uv,student,degree) qui portent l'information pendant l'exécution du programme.
 * Les attributs *filePath_ indique le chemin relatif pour le chargement des fichiers xml.
 */

class UTManager
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
    static UTManager& instance();
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
    UTManager();
    ~UTManager();
    UTManager(const UTManager& um);
    UTManager& operator=(const UTManager& um);


    friend struct Handler;
    struct Handler
    {
        UTManager* instance_;
        Handler():instance_(0){}
        ~Handler()
        {
            if(instance_)
                delete instance_;
            instance_ = 0;
        }
    };
    static Handler handler_;

    DataStrategy* data_;
    QList<Degree*> degrees_;
    static UTManager* instance_;
    Student* student_;
    QList<Student*> students_;
    QList<Uv*> uvs_;
};

#endif // UVMANAGER_H
