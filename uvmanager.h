#ifndef UVMANAGER_H
#define UVMANAGER_H
#include <QtWidgets>
#include <QtXml>
#include "utprofilerexception.h"

class UVManager
{
public:
    static UVManager& instance();
    void loadFromFile(const QString& filePath);

private:
    UVManager();
    UVManager(const UVManager& um);
    UVManager& operator=(const UVManager& um);

    static UVManager* instance_;
};

#endif // UVMANAGER_H
