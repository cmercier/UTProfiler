#ifndef STUDENT_H
#define STUDENT_H
#include <QList>
#include <QString>
#include "uv.h"
#include "degree.h"

class Student
{
public:
    void addUv(const Uv *uv);
    void addDegree(const Degree *degree);
    const unsigned int & equivalenceCs() const {return equivalenceCs_;}
    const unsigned int & equivalenceTm() const {return equivalenceTm_;}
    const unsigned int & equivalenceTsh() const {return equivalenceTsh_;}
    const unsigned int & equivalenceSp() const {return equivalenceSp_;}
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

    const QList<const Uv*>& uvs() const {return uvs_;}

private:
    Student();
    Student(const Student &student);
    Student& operator=(const Student &student);
    friend class UVManager;

    QList<const Degree*> degrees_;
    unsigned int equivalenceCs_;
    unsigned int equivalenceTm_;
    unsigned int equivalenceTsh_;
    unsigned int equivalenceSp_;
    QString firstName_;
    QString lastName_;
    QString login_;
    QList<const Uv*> uvs_;
};

#endif // STUDENT_H
