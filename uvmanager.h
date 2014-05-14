#ifndef UVMANAGER_H
#define UVMANAGER_H
#include <QtWidgets>
#include <QtXml>
#include <QDebug>
#include "utprofilerexception.h"
#include "uv.h"

class UVManager
{
public:
    void addUv(Uv* uv);
    static UVManager& instance();
    void loadFromFile(const QString &filePath);
    void save(const QString &filePath);

private:
    UVManager();
    UVManager(const UVManager& um);
    UVManager& operator=(const UVManager& um);

    static UVManager* instance_;
    QList<Uv*> uvs_;
};

#endif // UVMANAGER_H
