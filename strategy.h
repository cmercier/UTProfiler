    #ifndef STRATEGY_H
#define STRATEGY_H
#include "student.h"
#include "expectation.h"
#include "semester.h"

/**
 * @brief The Strategy class
 * Cette classe implémente le patron de conception stategie.
 * Elle est utilisée par l'onglet expectations. Ce dernier contient un pointeur sur strategy.
 * Lors de l'update, il appelle la fonction run() de la stratégie, qui exécute l'algorithme associé.
 * Pour changer l'algo, il suffit de créer une classe dérivée de strategy et réimplémenter la fonction exec.
 */

class Strategy
{
public:
    Strategy(Student* student,Expectation* exp):student_(student),exp_(exp){}

    /**
     * @brief run
     * @return
     * Exécute l'algorithme associé.
     */
    QList<Semester*> run();

protected:
    /**
     * @brief exec
     * @return
     * Algorithme à implémenter dans les classes filles.
     */
    virtual QList<Semester*> exec() = 0;

    Student* student_;
    Expectation* exp_;
};

#endif // STRATEGY_H
