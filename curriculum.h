#ifndef CURRICULUM_H
#define CURRICULUM_H
#include <QtWidgets>
#include <QString>
#include "uvmanager.h"
#include "utilities.h"

class Curriculum: public QWidget
{
    Q_OBJECT

public:
    Curriculum();
private:
    void getParentDegree(QHBoxLayout* degreeLayout, const Degree* degree);
    void loadSemesters(const Student *student) const;

    QVBoxLayout* degreesLayout_;
    QHBoxLayout* equivalence_;
    QLineEdit* equivalenceCs_;
    QLineEdit* equivalenceTm_;
    QLineEdit* equivalenceTsh_;
    QLineEdit* equivalenceSp_;
    QLineEdit* firstName_;
    QLineEdit* lastName_;
    QLineEdit* login_;
    QVBoxLayout* semestersLayout_;
    QScrollArea* semestersScrollArea_;
};

#endif // CURRICULUM_H
