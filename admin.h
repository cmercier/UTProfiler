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
    void showAddUvPanel(bool);
    void showEditUvPanel(bool);
    void showRemoveUvButton(QString);

private:
    void createAddUvPanel();
    void createEditUvPanel();
    void updateUvLists();

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
