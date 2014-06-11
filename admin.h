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
    void showAddUvPanel(bool);

private:
    void createAddUvPanel();

    QWidget* addUvPanel_;
};

#endif // ADMIN_H
