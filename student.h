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
    void deleteUV(const QString& codeUV, const QString& semester);
    unsigned int equivalenceCs() const {return equivalenceCs_;}
    unsigned int equivalenceTm() const {return equivalenceTm_;}
    unsigned int equivalenceTsh() const {return equivalenceTsh_;}
    unsigned int equivalenceSp() const {return equivalenceSp_;}
    const QList<Expectation*> &exp() const {return exp_;}
    const QString & firstName() const {return firstName_;}
    const QString & lastName() const {return lastName_;}
    const QString & login() const {return login_;}
    void setEquivalenceCs(const unsigned int &equivalenceCs) {equivalenceCs_ = equivalenceCs;}
    void setEquivalenceTm(const unsigned int &equivalenceTm) {equivalenceTm_ = equivalenceTm;}
    void setEquivalenceTsh(const unsigned int &equivalenceTsh) {equivalenceTsh_ = equivalenceTsh;}
    void setEquivalenceSp(const unsigned int &equivalenceSp) {equivalenceSp_ = equivalenceSp;}
    void setFirstName(const QString &firstName) {firstName_ = firstName;}
    void setLastName(const QString &lastName) {lastName_ = lastName;}
    void setLogin(const QString &login) {login_ = login;}
    const QList<Semester*>& semesters() const {return semesters_;}

private:   
    Student(const Student &student);
    Student& operator=(const Student &student);
    friend class UVManager;
    friend class SessionManager;

    QList<const Degree*> degrees_;
    QList<Expectation*> exp_;
    unsigned int equivalenceCs_;
    unsigned int equivalenceTm_;
    unsigned int equivalenceTsh_;
    unsigned int equivalenceSp_;
    QString firstName_;
    QString lastName_;
    QString login_;
    QList<Semester*> semesters_;

};

#endif // STUDENT_H
