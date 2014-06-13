#ifndef DEGREE_H
#define DEGREE_H
#include <QList>
#include <QString>
#include <QMap>
#include "uv.h"

class Degree
{
public:
    Degree(Degree *parent = 0);
    Degree(const Degree &degree);
    Degree& operator=(const Degree &degree);

    void addUv(const Uv *uv);
    const QList<Degree*> &children() const {return children_;}
    int depth() const;
    const Degree* parent() const {return parent_;}
    void removeChildren();
    int quota(QString category) const;
    const QMap<QString,int> & quotas() const {return quotas_;}
    void setParent(Degree *parent);
    void setQuota(QString category,int quota);
    void setTitle(const QString &title) {title_ = title;}
    void setType(const QString &type) {type_ = type;}
    const QString & title() const {return title_;}
    const QString & type() const {return type_;}
    const QList<const Uv*>& uvs() const {return uvs_;}

private:
    void addChild(Degree *child);

    QList<Degree*> children_;
    Degree* parent_;
    QMap<QString,int> quotas_;
    QString title_;
    QString type_;
    QList<const Uv*> uvs_;
};

#endif // DEGREE_H
