#include "uv.h"

QStringList Uv::categories_ = QStringList();

Uv::Uv()
{
}

QString Uv::gradeToString(Grade grade)
{
    if(grade == A)
        return "A";
    if(grade == B)
        return "B";
    if(grade == C)
        return "C";
    if(grade == D)
        return "D";
    if(grade == E)
        return "E";
    if(grade == F)
        return "F";
    if(grade == FX)
        return "FX";
    if(grade == RES)
        return "RES";
    if(grade == ABS)
        return "ABS";
    if(grade == EC)
        return "EC";
    else
        return "Unknown";
}

Grade Uv::stringToGrade(const QString &gradeString)
{
    if(gradeString == "A")
        return A;
    if(gradeString == "B")
        return B;
    if(gradeString == "C")
        return C;
    if(gradeString == "D")
        return D;
    if(gradeString == "E")
        return E;
    if(gradeString == "F")
        return F;
    if(gradeString == "FX")
        return FX;
    if(gradeString == "RES")
        return RES;
    if(gradeString == "ABS")
        return ABS;
    if(gradeString == "EC")
        return EC;
    else
        return Undefined;
}
