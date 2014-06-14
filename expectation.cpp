#include "expectation.h"

Expectation::Expectation():
    name_("")
{
}

void Expectation::addDegree(const Degree *degree)
{
    if(!degrees_.contains(degree))
        degrees_.push_back(degree);
}

void Expectation::addRejectedUv(const Uv *uv)
{
    if(!rejectedUvs_.contains(uv))
        rejectedUvs_.push_back(uv);
}

void Expectation::addRequiredUv(const Uv *uv)
{
    if(!requiredUvs_.contains(uv))
        requiredUvs_.push_back(uv);
}

void Expectation::addSemester(Semester *semester)
{
    if(!semesters_.contains(semester))
        semesters_.push_back(semester);
}

void Expectation::addUV(const QString codeUV, const QString semester, Grade grade)
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

void Expectation::clearUvs()
{
    rejectedUvs_.clear();
    requiredUvs_.clear();
}

void Expectation::deleteDegree(const QString& title)
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

void Expectation::deleteSemester(const QString& title)
{
    for (int i = 0; i < semesters_.size(); i++)
    {
        if (semesters_[i]->title() == title)
        {
            semesters_.removeAt(i);
            return;
        }
    }
}
