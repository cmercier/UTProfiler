#include "expectation.h"

Expectation::Expectation()
{
}

void Expectation::addDegree(const Degree *degree)
{
    if(!degrees_.contains(degree))
        degrees_.push_back(degree);
}

void Expectation::addRejectedUv(Uv *uv)
{
    if(!rejectedUvs_.contains(uv))
        rejectedUvs_.push_back(uv);
}

void Expectation::addRequiredUv(Uv *uv)
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
