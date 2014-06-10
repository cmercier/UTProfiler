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

public slots:
    void addUV();
    void addDegree();
    void editStudent(bool edit);
    void selectDegree(const QString &title);


private:
    void getParentDegree(QHBoxLayout* degreeLayout, const Degree* degree);
    void loadSemesters(const Student *student) const;
    void updateStudent();

    QComboBox* code_;
    QComboBox* degree_;
    QVBoxLayout* degreesLayout_;
    bool editStudent_;
    QHBoxLayout* equivalence_;
    QLineEdit* equivalenceCs_;
    QLineEdit* equivalenceTm_;
    QLineEdit* equivalenceTsh_;
    QLineEdit* equivalenceSp_;
    QLineEdit* firstName_;
    QComboBox* grade_;
    QHBoxLayout* identityLayout_;
    QLineEdit* lastName_;
    QLineEdit* login_;
    QHBoxLayout* newDegreeLayout_;
    const Degree* selectedDegree_;
    QLineEdit* semester_;
    QVBoxLayout* semestersLayout_;
    QScrollArea* semestersScrollArea_;
    Student* student_;
    QHBoxLayout* studentLayout_;
    QHBoxLayout* uvLayout_;
};

#endif // CURRICULUM_H
