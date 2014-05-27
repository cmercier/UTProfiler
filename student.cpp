#include "student.h"
#include "uv.h"

Student::Student()
{
}

void Student::addDegree(const Degree *degree)
{
    if(!degrees_.contains(degree))
        degrees_.push_back(degree);
}

void Student::addSemester(const Semester *semester)
{
    if(!semesters_.contains(semester))
        semesters_.push_back(semester);
}

Semester::Semester()
{
}

void Semester::addUv(QString code, Grade grade)
{
    if(!uvs_.contains(code))
        uvs_[code] = grade;
}
