#ifndef EXPECTATIONS_H
#define EXPECTATIONS_H
#include <QtWidgets>
#include "uvmanager.h"
#include "utilities.h"
#include "student.h"
#include "algo.h"

class Expectations: public QWidget
{
    Q_OBJECT

public:
    Expectations();
    void setStrategy(Strategy* strategy) { autocompletion_ = strategy; }

public slots:
    void addWantedDegree();
    void addSemester();
    void createExpPanel();
    void deleteDegree();
    void deleteExp();
    void deleteSemester();
    void generateExp();
    void saveDatas();
    void selectDegree(const QString &);
    void updateExp();
    void updateExpComboBox();
    void updateExpPanel();
    void updateUnwantedUvs();
    void updateWantedUvs();
    void validateExp();

private:
    void getParentDegree(QHBoxLayout* degreeLayout, const Degree* degree);
    void loadSemesters() const;


    Expectation* exp_;
    QHBoxLayout* degreeLayout_;
    QComboBox* degreesBox_;
    QComboBox* deleteDegree_;
    QVBoxLayout* expLayout_;
    QComboBox* expSelect_;
    QScrollArea* expScrollArea_;
    QLineEdit* name_;
    QComboBox* seasonBox_;
    const Degree* selectedDegree_;
    QComboBox* semestersBox_;
    QVBoxLayout* semestersLayout_;
    QScrollArea* semestersScrollArea_;
    Strategy* autocompletion_;
    QVBoxLayout* unwantedUvsLayout_;
    QVBoxLayout* wantedUvsLayout_;
    QSpinBox* yearBox_;
};

#endif // EXPECTATIONS_H
