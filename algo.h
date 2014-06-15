#ifndef ALGO_H
#define ALGO_H
#include "strategy.h"

/**
 * @brief The Algo class
 * Une première implémentation simplifiée de l'algorithme de prévisions.
 */
class Algo: public AlgoStrategy
{
public:
    Algo(Student* student,Expectation* exp):AlgoStrategy(student,exp){}

private:
    QList<Semester*> exec();
};

#endif // ALGO_H
