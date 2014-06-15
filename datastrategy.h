#ifndef DATASTRATEGY_H
#define DATASTRATEGY_H
#include "uv.h"
#include "degree.h"
#include "student.h"

/**
 * @brief The DataStrategy class
 * Cette classe implémente le patron de conception stratégie.
 * Elle est utilisée par UTManager pour la gestion du chargement et de la sauvegarde des données.
 * Si l'on souhaitait changer de mode de persistance des données, par exemple passer à SqLite il suffirait de créer une
 * une classe SqlStrategy héritant de DataStrategy et d'implémenter les méthodes execLoad et execSave.
 */

class DataStrategy
{
public:
    DataStrategy(QList<Uv*>& uvs,QList<Degree*>& degrees,QList<Student*>& students):
        degrees_(degrees),
        students_(students),
        uvs_(uvs)
    {}

    /**
     * @brief load
     * Chargement de l'ensemble des données dans les attributs degrees_, students_ et uvs_.
     */
    void load();

    /**
     * @brief save
     * Sauvegarde des données à partir des attributs degrees_, students_ et uvs_.
     */
    void save();

protected:
    virtual void execLoad() = 0;
    virtual void execSave() = 0;

    QList<Degree*>& degrees_;
    QList<Student*>& students_;
    QList<Uv*>& uvs_;
};

#endif // DATASTRATEGY_H
