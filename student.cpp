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

void Student::addUV(const QString& codeUV, const QString& semester, Grade grade)
{
    /*for(int i = 0; i < semesters_.size(); i++)
    {
        if (semesters_[i]->title() = semester)
            semesters_[i]->addUv(codeUV, grade);
        else
        {
            Semester *semesterP = new Semester();
            semesterP->setTitle(semester);
            semesterP->addUv(codeUV, grade);
            addSemester(semesterP);
        }
    }*/
}

Semester::Semester()
{
}

void Semester::addUv(QString code, Grade grade)
{
    if(!uvs_.contains(code))
        uvs_[code] = grade;
}
