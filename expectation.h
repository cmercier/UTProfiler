#ifndef EXPECTATION_H
#define EXPECTATION_H
#include <QtWidgets>

class Expectation
{
public:
    Expectation();

    const QString & name() const {return name_;}
    void setName(const QString &name) {name_ = name;}

private:
    QString name_;
};

#endif // EXPECTATION_H
