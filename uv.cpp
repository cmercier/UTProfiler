#include "uv.h"

Uv::Uv()
{
}

Uv::Uv(const QString &code, const QString &title, unsigned int credits, Category category, bool spring, bool fall):
    category_(category),
    credits_(credits),
    code_(code),
    fall_(fall),
    spring_(spring),
    title_(title)
{
}

QString Uv::categoryToString(Category category)
{
    if(category == CS)
        return "CS";
    if(category == TM)
        return "TM";
    if(category == TSH)
        return "TSH";
    if(category == SP)
        return "SP";

    return "UndefinedCategory";
}

Category Uv::stringToCategory(const QString &categoryString)
{
    if(categoryString == "CS")
        return CS;
    if(categoryString == "TM")
        return TM;
    if(categoryString == "TSH")
        return TSH;
    if(categoryString == "SP")
        return SP;

    return UndefinedCategory;
}
