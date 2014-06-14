#ifndef SEMESTER_H
#define SEMESTER_H
#include <QList>
#include <QMap>
#include <QString>
#include "uv.h"
#include "degree.h"

/**
 * @brief The Semester class
 * Cette classe contient toutes les informations propres à un semestre.
 * Elle comporte l'ensemble des uvs réalisées ou à réaliser.
 */

class Semester
{
public:
    Semester();
    void addUv(const QString, const Grade);
    void deleteUV(const QString& codeUV);
    const QString & title() const {return title_;}
    void setTitle(const QString &title) {title_ = title;}
    const QMap<QString, Grade> uvs() const {return uvs_;}

private:
    Semester(const Semester &semester);
    Semester& operator=(const Semester &semester);
    friend class UVManager;
    friend class Student;

    QString title_;
    QMap<QString, Grade> uvs_; // doute sur la référence constante
};

#endif // SEMESTER_H
