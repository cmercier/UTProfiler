#ifndef ALGO_H
#define ALGO_H
#include "strategy.h"

class Algo: public Strategy
{
public:
    Algo(Student* student,Expectation* exp):Strategy(student,exp){}

private:
    QList<Semester*> exec();
};

#endif // ALGO_H
