#include "student.h"

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

void Semester::addUv(const Uv *uv)
{
    if(!uvs_.contains(uv))
        uvs_.push_back(uv);
}
