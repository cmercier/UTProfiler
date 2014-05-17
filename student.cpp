#include "student.h"

void Student::addUv(const Uv *uv)
{
    if(!uvs_.contains(uv))
        uvs_.push_back(uv);
}
