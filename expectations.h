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
    void selectDegree(const QString &);
    void updateExpComboBox();
    void updateExpPanel();
    void updateUnwantedUvs();
    void updateWantedUvs();

private:
    void createExpPanel();
    void getParentDegree(QHBoxLayout* degreeLayout, const Degree* degree);

    Expectation* exp_;
    QHBoxLayout* degreeLayout_;
    QComboBox* degreesBox_;
    QVBoxLayout* expLayout_;
    QComboBox* expSelect_;
    QScrollArea* expScrollArea_;
    QLineEdit* name_;
    const Degree* selectedDegree_;
    QVBoxLayout* unwantedUvsLayout_;
    QVBoxLayout* wantedUvsLayout_;
};

#endif // EXPECTATIONS_H
