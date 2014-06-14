#ifndef STUDENT_H
#define STUDENT_H
#include <QList>
#include <QMap>
#include <QString>
#include "uv.h"
#include "degree.h"
#include "expectation.h"
#include "semester.h"

class Student
{
public:
    Student();
    void addDegree(const Degree *degree);
    void addExp(Expectation* exp);
    void addSemester(Semester *semester);
    void addUV(const QString codeUV, const QString semester, Grade grade);
    const QList<const Degree*>& degrees() const {return degrees_;}
    void deleteDegree(const QString& title);
    void deleteExp(Expectation* exp);
    void deleteUV(const QString& codeUV, const QString& semester);
    unsigned int equivalence(const QString &cat) {return equivalences_.contains(cat) ? equivalences_[cat] : 0;}
    const QMap<QString,unsigned int> & equivalences() const {return equivalences_;}
    const QList<Expectation*> &exp() const {return exp_;}
    const QString & firstName() const {return firstName_;}
    const QString & lastName() const {return lastName_;}
    const QString & login() const {return login_;}
    void setEquivalence(const QString &cat,unsigned int eq) {equivalences_[cat] = eq;}
    void setFirstName(const QString &firstName) {firstName_ = firstName;}
    void setLastName(const QString &lastName) {lastName_ = lastName;}
    void setLogin(const QString &login) {login_ = login;}
    const QList<Semester*>& semesters() const {return semesters_;}

private:   
    Student(const Student &student);
    Student& operator=(const Student &student);
    friend class UVManager;

    QList<const Degree*> degrees_;
    QList<Expectation*> exp_;
    QMap<QString,unsigned int> equivalences_;
    QString firstName_;
    QString lastName_;
    QString login_;
    QList<Semester*> semesters_;

};

#endif // STUDENT_H
