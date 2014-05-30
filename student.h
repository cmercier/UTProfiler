#ifndef STUDENT_H
#define STUDENT_H
#include <QList>
#include <QMap>
#include <QString>
#include "uv.h"
#include "degree.h"

class Semester
{
public:
    void addUv(QString, Grade);
    const QString & title() const {return title_;}
    void setTitle(const QString &title) {title_ = title;}
    const QMap<QString, Grade> uvs() const {return uvs_;}

private:
    Semester();
    Semester(const Semester &semester);
    Semester& operator=(const Semester &semester);
    friend class UVManager;
    friend class SessionManager;
    friend class Student;

    QString title_;
    QMap<QString, Grade> uvs_; // doute sur la référence constante
};

class Student
{
public:
    void addDegree(const Degree *degree);
    void addSemester(const Semester *semester);
    void addUV(const QString &codeUV, const QString &semester, Grade grade);
    const QList<const Degree*>& degrees() const {return degrees_;}
    unsigned int equivalenceCs() const {return equivalenceCs_;}
    unsigned int equivalenceTm() const {return equivalenceTm_;}
    unsigned int equivalenceTsh() const {return equivalenceTsh_;}
    unsigned int equivalenceSp() const {return equivalenceSp_;}
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
    const QList<const Semester*>& semesters() const {return semesters_;}

private:
    Student();
    Student(const Student &student);
    Student& operator=(const Student &student);
    friend class UVManager;
    friend class SessionManager;

    QList<const Degree*> degrees_;
    unsigned int equivalenceCs_;
    unsigned int equivalenceTm_;
    unsigned int equivalenceTsh_;
    unsigned int equivalenceSp_;
    QString firstName_;
    QString lastName_;
    QString login_;
    QList<const Semester*> semesters_;

};

#endif // STUDENT_H
