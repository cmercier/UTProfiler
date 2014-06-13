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
    void deleteDegree();
    void deleteUV();
    void editStudent(bool edit);
    void generationView();
    void saveQLineEdit();
    void selectDegree(const QString &title);
    void updateStudent();
    void updateUvs();

private:
    void getParentDegree(QHBoxLayout* degreeLayout, const Degree* degree);
    void loadSemesters(const Student *student) const;

    QComboBox* code_;
    QComboBox* degree_;
    QVBoxLayout* degreesLayout_;
    QComboBox* deleteDegree_;
    QComboBox* deleteUVCodeUV_;
    QComboBox* deleteUVSemester_;
    QHBoxLayout* deleteUvLayout_;
    bool editStudent_;
    QHBoxLayout* equivalence_;
    QList<QLineEdit*> equivalences_;
    QLineEdit* firstName_;
    QComboBox* grade_;
    QHBoxLayout* identityLayout_;
    QLineEdit* lastName_;
    QLabel* login_;
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
