#ifndef DEGREE_H
#define DEGREE_H
#include <QList>
#include <QString>
#include <QDebug>
#include <QMap>
#include "uv.h"

/**
 * @brief The Degree class
 * Cette classe définit un cursus, une formation proposée à l'UTC.
 * Il contient un ensemble d'uvs, ainsi que des quotas de crédits par catégorie.
 * Elle englobe les branches, filières, mineurs, etc... selon son attribut type (qui prendra les valeurs précédentes).
 * Un cursus peut faire partie d'un autre, considéré comme parent. Par exemple le cursus GI contient comme enfants les différentes filières.
 */

class Degree
{
public:
    Degree(Degree *parent = 0);
    Degree(const Degree &degree);
    Degree& operator=(const Degree &degree);

    /**
     * @brief addUv
     * @param uv
     * Ajout une uv dans le cursus.
     */
    void addUv(const Uv *uv);
    const QList<Degree*> &children() const {return children_;}

    /**
     * @brief depth
     * @return
     * Renvoie la profondeur du cursus.
     * 0 signifie que le cursus n'a pas de parent.
     * 1 signifie que le cursus est intégré dans un autre. Ex : GI -> SRI
     */
    int depth() const;
    const Degree* parent() const {return parent_;}
    void removeChildren();

    /**
     * @brief quota
     * @param category
     * @return
     * Renvoie le quota (nombre de crédits requis) pour la catégorie passée en paramètre.
     */
    int quota(QString category) const;
    const QMap<QString,int> & quotas() const {return quotas_;}
    void setParent(Degree *parent);

    /**
     * @brief setQuota
     * @param category
     * @param quota
     * Définit le quota (nombre de crédits requis) pour la catégorie passée en paramètre.
     */
    void setQuota(QString category,int quota);
    void setTitle(const QString &title) {title_ = title;}
    void setType(const QString &type) {type_ = type;}
    const QString & title() const {return title_;}
    const QString & type() const {return type_;}
    const QList<const Uv*>& uvs() const {return uvs_;}

private:
    /**
     * @brief addChild
     * @param child
     * Définit ce cursus comme parent du cursus passé en paramètre.
     */
    void addChild(Degree *child);

    QList<Degree*> children_;
    Degree* parent_;
    QMap<QString,int> quotas_;
    QString title_;
    QString type_;
    QList<const Uv*> uvs_;
};

#endif // DEGREE_H
