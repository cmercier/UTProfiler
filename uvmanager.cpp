#include "uvmanager.h"

UVManager* UVManager::instance_ = 0;

UVManager::UVManager()
{
}

void UVManager::addUv(Uv *uv)
{
    if(!uv)
        return;

    uvs_.push_back(uv);
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
        throw UTProfilerException("Failed to open " + filePath + " in UVManager::loadFromFile.");

    QDomDocument domDocument;

    domDocument.setContent(&file);

    QDomElement uvs = domDocument.documentElement();

    for(QDomElement uvElement = uvs.firstChildElement("uv"); !uvElement.isNull(); uvElement = uvElement.nextSiblingElement("uv"))
    {
        Uv* uv = new Uv;
        uv->setCategory(Uv::stringToCategory(uvElement.firstChildElement("categorie").text()));
        uv->setCode(uvElement.firstChildElement("code").text());
        uv->setCredits(uvElement.firstChildElement("credits").text().toFloat());
        uv->setFall(uvElement.attribute("automne") == "true" ? true : false);
        uv->setSpring(uvElement.attribute("printemps") == "true" ? true : false);
        uv->setTitle(uvElement.firstChildElement("titre").text());
        addUv(uv);
    }

    file.close();
}

void UVManager::save(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        //throw UTProfilerException("Failed to open " + filePath + " in UVManager::save.");
        qDebug() << "Failed to open " << filePath << " in save";
        return;
    }

    QDomDocument dom;
    dom.setContent(&file);

    QDomElement uvs = dom.createElement("uvs");
    dom.appendChild(uvs);

    for(int i = 0; i < uvs_.size(); i++)
    {
        Uv* uv = uvs_.at(i);

        QDomElement uvElement = dom.createElement("uv");

        QDomElement category = dom.createElement("categorie");
        category.appendChild(dom.createTextNode(Uv::categoryToString(uv->category())));
        uvElement.appendChild(category);

        QDomElement code = dom.createElement("code");
        code.appendChild(dom.createTextNode(uv->code()));
        uvElement.appendChild(code);

        QDomElement credits = dom.createElement("credits");
        credits.appendChild(dom.createTextNode(QString::number(uv->credits())));
        uvElement.appendChild(credits);

        QString fall;
        uv->fall() ? fall = "true" : fall = "false";
        uvElement.setAttribute("automne",fall);

        QString spring;
        uv->spring() ? spring = "true" : spring = "false";
        uvElement.setAttribute("printemps",spring);

        QDomElement title = dom.createElement("titre");
        title.appendChild(dom.createTextNode(uv->title()));
        uvElement.appendChild(title);

        uvs.appendChild(uvElement);
    }

    file.write(dom.toByteArray());
    file.close();
}

