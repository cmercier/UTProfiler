#ifndef EXPECTATION_H
#define EXPECTATION_H
#include <QtWidgets>
#include "uv.h"
#include "degree.h"
#include "semester.h"

class Expectation
{
public:
    Expectation();

    void addDegree(const Degree *degree);
    void addRejectedUv(const Uv* uv);
    void addRequiredUv(const Uv* uv);
    void addSemester(Semester *semester);    
    void addUV(const QString codeUV, const QString semester, Grade grade);
    void clearUvs();
    const QList<const Degree*>& degrees() const {return degrees_;}
    void deleteDegree(const QString& title);
    const QString & name() const {return name_;}
    void setName(const QString &name) {name_ = name;}
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
