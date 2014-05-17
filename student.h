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
    const QString & firstName() const {return firstName_;}
    const QString & lastName() const {return lastName_;}
    void setFirstName(const QString &firstName) {firstName_ = firstName;}
    void setLastName(const QString &lastName) {lastName_ = lastName;}

    const QList<const Uv*>& uvs() const {return uvs_;}

private:
    Student(const Student &student);
    Student& operator=(const Student &student);
    //friend class UVManager; ?

    QList<Degree*> degrees_;
    QString firstName_;
    QString lastName_;
    QList<const Uv*> uvs_;
};

#endif // STUDENT_H
