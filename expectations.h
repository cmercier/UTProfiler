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
    void updateExpComboBox();
    void updateExpPanel();

private:
    void createExpPanel();

    QVBoxLayout* expLayout_;
    QComboBox* expSelect_;
    QScrollArea* expScrollArea_;
    QLineEdit* name_;
};

#endif // EXPECTATIONS_H
