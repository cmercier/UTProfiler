#ifndef ADMIN_H
#define ADMIN_H
#include <QtWidgets>
#include "uvmanager.h"
#include "utilities.h"

class UvInputView: public QWidget
{
public:
    UvInputView(Uv& uv);

private:
    Uv& uv_;
};

class Admin: public QWidget
{
    Q_OBJECT

public:
    Admin();

public slots:
    void showAddUvPanel(bool show);

private:
    UvInputView* addUvPanel_;
};

#endif // ADMIN_H
