#include "student.h"
#include "uv.h"

Student::Student():
    firstName_(""),
    lastName_("")
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
    if (semester.isEmpty())
        return;

    // Si le semestre existe déjà
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

void Student::deleteExp(Expectation* exp)
{
    exp_.removeOne(exp);
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
