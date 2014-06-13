#ifndef CATALOG_H
#define CATALOG_H
#include <QtWidgets>
#include "uvmanager.h"
#include "utilities.h"

class Catalog: public QWidget
{
    Q_OBJECT

public:
    Catalog();

public slots:
    void criteriaChanged();
    void editCatalog(bool edit);
    void selectDegree(const QString &title);
    void updateCatalog();

private:
    QList<QCheckBox*> categories_;
    QComboBox* degree_;
    QHBoxLayout* degreeLayout_;
    bool editCatalog_;
    QCheckBox* fall_;
    bool isCriteriaChange_;
    const Degree* selectedDegree_;
    QCheckBox* spring_;
    QPushButton* submit_;
    QHBoxLayout* uvsLayout_;
    QScrollArea* uvsScrollArea_;
};

#endif // CATALOG_H
