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
    const QList<const Degree*>& degrees() const {return degrees_;}
    const QString & name() const {return name_;}
    void setName(const QString &name) {name_ = name;}
    QList<const Uv*> rejectedUvs() const;
    QList<const Uv*> requiredUvs() const;
    const QList<Semester*>& semesters() const {return semesters_;}


private:
    QList<const Degree*> degrees_;
    QString name_;
    QList<const Uv*> rejectedUvs_;
    QList<const Uv*> requiredUvs_;
    QList<Semester*> semesters_;

};

#endif // EXPECTATION_H
