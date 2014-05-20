#ifndef UVMANAGER_H
#define UVMANAGER_H
#include <QtWidgets>
#include <QtXml>
#include <QDebug>
#include "utprofilerexception.h"
#include "degree.h"
#include "student.h"

class UVManager
{
public:
    void addUv(Uv* uv);
    void addStudent(Student *student);
    const QList<Degree*> & degrees() const {return degrees_;}
    const Degree * degreeWithTitle(const QString &title);
    QList<const Degree*> degreesWithParent(const QString &parentTitle);
    static UVManager& instance();
    void loadDegrees(const QString &fileName);
    void loadStudents(const QString &fileName);
    void loadUvs(const QString &fileName);
    void save(const QString &filePath);
    const QList<Student*> students() const {return students_;}
    const Uv* uvFromCode(const QString &code) const;
    QList<const Uv*> uvs() const;
    QList<const Uv*> uvsFromCode(const QStringList &codes) const;

private:
    UVManager();
    UVManager(const UVManager& um);
    UVManager& operator=(const UVManager& um);
    void addDegree(QDomElement &element,Degree *parent = 0);
    void addDegrees(Student *student, QDomElement &element);
    void addUvs(Degree *degree, QDomElement &element);
    void addUvs(Student *student, QDomElement &element);

    static UVManager* instance_;
    QList<Degree*> degrees_;
    QList<Student*> students_;
    QList<Uv*> uvs_;
};

#endif // UVMANAGER_H
