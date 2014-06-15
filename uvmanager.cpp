#include "uvmanager.h"
#include <QDebug>

UTManager* UTManager::instance_ = 0;
UTManager::Handler UTManager::handler_=Handler();

UTManager::UTManager():
    student_(0)
{
    data_ = new XmlDataPersistance(uvs_,degrees_,students_);
    data_->load();
}

UTManager::~UTManager()
{
    data_->save();
}

void UTManager::addDegree(Degree *degree)
{
    if(!degree)
        return;

    for(int i = 0; i < degrees_.size(); i++)
    {
        if(degrees_.at(i)->title() == degree->title())
        {
            degrees_.replace(i,degree);
            return;
        }
    }

    degrees_.push_back(degree);
}

void UTManager::addUv(Uv *uv)
{
    if(!uv)
        return;

    for(int i = 0; i < uvs_.size(); i++)
    {
        if(uvs_.at(i)->code() == uv->code())
        {
            uvs_.replace(i,uv);
            return;
        }
    }

    uvs_.push_back(uv);
}

void UTManager::addStudent(const QString &login)
{
    student_ = new Student;
    student_->setLogin(login);
    students_.push_back(student_);
}

void UTManager::addStudent(Student *student)
{
    if(!student)
        return;

    students_.push_back(student);
}

bool UTManager::connect(const QString &login)
{
    for(int i = 0; i < students_.size(); i++)
    {
        if(students_.at(i)->login() == login)
        {
            student_ = students_.at(i);
            return true;
        }
    }
    return false;
}

QList<const Degree*> UTManager::degreesWithParent(const QString &parentTitle)
{
    QList<const Degree*> result;
    for(int i = 0; i < degrees_.size(); i++)
    {
        if(degrees_.at(i)->parent() && degrees_.at(i)->parent()->title() == parentTitle)
            result.push_back(degrees_.at(i));
    }
    return result;
}

Degree* UTManager::degreeWithTitle(const QString &title)
{
    for(int i = 0; i < degrees_.size(); i++)
    {
        if(degrees_.at(i)->title() == title)
            return degrees_.at(i);
    }

    return 0;
}

UTManager& UTManager::instance()
{
    if(!instance_)
    {
        instance_ = new UTManager;
        UTManager::handler_.instance_ = instance_;
    }

    return *instance_;
}

void UTManager::removeDegree(const QString &title)
{
    for(int i = 0; i < degrees_.size(); i++)
    {
        if(degrees_.at(i)->title() == title)
        {
            if(degrees_.at(i)->parent())
                degrees_[i]->parent()->removeChild(title);
            degrees_.at(i)->removeChildren();
            degrees_.removeAt(i);

            return;
        }
    }
}

void UTManager::removeUv(const QString &code)
{
    for(int i = 0; i < uvs_.size(); i++)
    {
        if(uvs_.at(i)->code() == code)
        {
            uvs_.removeAt(i);
            return;
        }
    }
}

const Uv* UTManager::uvFromCode(const QString &code) const
{
    for(int i = 0; i < uvs_.size(); i++)
    {
        if(uvs_.at(i)->code() == code)
            return uvs_.at(i);
    }

    return 0;
}

QList<const Uv*> UTManager::uvs() const
{
    QList<const Uv*> result;
    for(int i = 0; i < uvs_.size(); i++)
    {
        result.push_back(uvs_.at(i));
    }
    return result;
}

QList<const Uv*> UTManager::uvsFromCode(const QStringList &codes) const
{
    QList<const Uv*> result;
    for(int i = 0; i < uvs_.size(); i++)
    {
        if(codes.contains(uvs_.at(i)->title()))
            result.push_back(uvs_.at(i));
    }
    return result;
}
