#ifndef EXPECTATIONS_H
#define EXPECTATIONS_H
#include <QtWidgets>
#include "uvmanager.h"
#include "utilities.h"
#include "student.h"

class Expectations: public QWidget
{
    Q_OBJECT

public:
    Expectations();

public slots:
    void addWantedDegree();
    void createExpPanel();
    void deleteDegree();
    void deleteExp();
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

    Expectation* exp_;
    QHBoxLayout* degreeLayout_;
    QComboBox* degreesBox_;
    QComboBox* deleteDegree_;
    QVBoxLayout* expLayout_;
    QComboBox* expSelect_;
    QScrollArea* expScrollArea_;
    QLineEdit* name_;
    const Degree* selectedDegree_;
    QVBoxLayout* unwantedUvsLayout_;
    QVBoxLayout* wantedUvsLayout_;
};

#endif // EXPECTATIONS_H
