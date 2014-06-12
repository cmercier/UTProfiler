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

void Student::addExp(Expectation *exp)
{
    exp_.push_back(exp);
}

void Student::addSemester(Semester *semester)
{
    if(!semesters_.contains(semester))
        semesters_.push_back(semester);
}

void Student::addUV(const QString codeUV, const QString semester, Grade grade)
{
    // Si le semestre existe déjà
    if (semester.isEmpty())
        return;

    for(int i = 0; i < semesters_.length(); i++)
    {
        if (semesters_[i]->title() == semester)
        {
            semesters_[i]->addUv(codeUV, grade);
            return;
        }
    }
    // Sinon
    Semester *semesterP = new Semester();
    semesterP->setTitle(semester);
    semesterP->addUv(codeUV, grade);
    addSemester(semesterP);
}

void Student::deleteDegree(const QString& title)
{
    for (int i = 0; i < degrees_.size(); i++)
    {
        if (degrees_[i]->title() == title)
        {
            degrees_.removeAt(i);
            return;
        }
    }
}

void Student::deleteUV(const QString& codeUV, const QString& semester)
{
    for (int i = 0; i < semesters_.size(); i++)
    {
        if (semesters_[i]->title() == semester)
        {
            semesters_[i]->deleteUV(codeUV);
            return;
        }
    }
}

Semester::Semester()
{
}

void Semester::addUv(const QString code, const Grade grade)
{
    if(!uvs_.contains(code))
        uvs_[code] = grade;
}

void Semester::deleteUV(const QString& codeUV)
{
    uvs_.remove(codeUV);
}
