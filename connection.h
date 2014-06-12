#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtWidgets>
#include "uvmanager.h"

class Connection: public QWidget
{
    Q_OBJECT

public:
    Connection();

public slots:
    void login();

signals:
    void connected();

private:
    QLineEdit* connectionEdit_;
};

#endif // CONNECTION_H
