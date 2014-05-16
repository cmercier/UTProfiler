#ifndef DEGREE_H
#define DEGREE_H
#include <QList>
#include <QString>
#include "uv.h"

class Degree
{
public:
    void addUv(const Uv *uv);
    int depth() const;
    const Degree* parent() const {return parent_;}
    void setParent(Degree *parent);
    void setTitle(const QString &title) {title_ = title;}
    void setType(const QString &type) {type_ = type;}
    const QString & title() const {return title_;}
    const QString & type() const {return type_;}
    const QList<const Uv*>& uvs() const {return uvs_;}

private:
    Degree(Degree *parent = 0);
    Degree(const Degree &degree);
    Degree& operator=(const Degree &degree);
    friend class UVManager;
    void addChild(Degree *child);

    QString type_;
    QList<Degree*> children_;
    Degree* parent_;
    QString title_;
    QList<const Uv*> uvs_;
};

#endif // DEGREE_H
