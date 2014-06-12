#ifndef ADMIN_H
#define ADMIN_H
#include <QtWidgets>
#include "uvmanager.h"
#include "utilities.h"

class Admin: public QWidget
{
    Q_OBJECT

public:
    Admin();

public slots:
    void addUv();
    void editUv();
    void editUv(QString);
    void removeUv();
    void showAddDegreePanel(bool);
    void showAddUvPanel(bool);
    void showEditUvPanel(bool);
    void showRemoveUvButton(QString);

private:
    void createAddDegreePanel();
    void createAddUvPanel();
    void createEditUvPanel();
    void updateUvLists();

    QSpinBox* addDegree_criteria_cs_;
    QSpinBox* addDegree_criteria_tm_;
    QSpinBox* addDegree_criteria_tsh_;
    QSpinBox* addDegree_criteria_sp_;
    QVBoxLayout* addDegree_degrees_layout_;
    QLineEdit* addDegree_name_;
    QComboBox* addDegree_uvs_;
    QVBoxLayout* addDegree_uvs_layout_;
    QWidget* addDegreePanel_;
    QScrollArea* addDegree_parentScrollArea_;
    QScrollArea* addDegree_scrollArea_;
    QComboBox* addUv_category_;
    QLineEdit* addUv_code_;
    QSpinBox* addUv_credits_;
    QCheckBox* addUv_fall_;
    QWidget* addUvPanel_;
    QCheckBox* addUv_spring_;
    QLineEdit* addUv_title_;
    QComboBox* editUv_category_;
    QLineEdit* editUv_code_;
    QComboBox* editUv_comboBox_;
    QSpinBox* editUv_credits_;
    QCheckBox* editUv_fall_;
    QWidget* editUvPanel_;
    const Uv* editUv_uv_;
    QCheckBox* editUv_spring_;
    QLineEdit* editUv_title_;
    QComboBox* removeUv_comboBox_;
    QPushButton* removeUv_remove_;
};

#endif // ADMIN_H
