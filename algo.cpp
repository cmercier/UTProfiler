#include "algo.h"
#include "uvmanager.h"

QList<Semester*> Algo::exec()
{
    QList<Semester*> result = exp_->semesters();
    QList<const Uv*> uvs = UTManager::instance().uvs();
    unsigned int count = 0;

    for (int i = 0; i < result.size(); i++)
    {
        while (result.at(i)->uvs().size() < 6)
        {
            result.at(i)->addUv(uvs.at(count)->code(), Uv::stringToGrade("Undefined"));
            count ++;
        }
    }

    return result;
}
