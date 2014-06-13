#include "semester.h"

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
