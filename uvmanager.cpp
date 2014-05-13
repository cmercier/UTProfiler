#include "uvmanager.h"

UVManager* UVManager::instance_ = 0;

UVManager::UVManager()
{
}

UVManager& UVManager::instance()
{
    if(!instance_)
        instance_ = new UVManager;

    return *instance_;
}

void UVManager::loadFromFile(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
        throw UTProfilerException("Failed to open " + filePath + " in loadFromFile.");

    QDomDocument domDocument;
    domDocument.setContent(&file);

    QDomElement uvs = domDocument.documentElement();

    //for(QDomElement uv = uvs.firstChildElement("uv"); !uv.isNull(); uv = u)
}

