#include "sessionmanager.h"

SessionManager* SessionManager::instance_ = 0;

SessionManager::SessionManager():
    currentStudent_(0)
{
}

void SessionManager::addStudent(Student *student)
{
    if(!student)
        return;

    students_.push_back(student);
}

SessionManager& SessionManager::instance()
{
    if(!instance_)
        instance_ = new SessionManager();

    return *instance_;
}

void SessionManager::load(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        throw UTProfilerException("Failed to open " + fileName + " in UVManager::loadStudents.");

    QDomDocument dom;
    dom.setContent(&file);

    QDomElement students = dom.documentElement();

    for(QDomElement studentElement = students.firstChildElement("etudiant"); !studentElement.isNull(); studentElement = studentElement.nextSiblingElement("etudiant"))
    {
        Student* student = new Student;
        student->setLogin(studentElement.firstChildElement("login").text());
        student->setFirstName(studentElement.firstChildElement("prenom").text());
        student->setLastName(studentElement.firstChildElement("nom").text());
        //addDegrees(student, studentElement); // load degrees
        //addUvs(student, studentElement); // load uvs

        for(QDomElement eqElem = studentElement.firstChildElement("equivalence");!eqElem.isNull();eqElem = eqElem.nextSiblingElement("equivalence"))
        {
            student->setEquivalence(eqElem.attribute("categorie"),eqElem.text().toUInt());
        }
        addStudent(student);
    }

    file.close();
}


const Student* SessionManager::studentWithLogin(const QString &login) const
{
    for(int i = 0; i < students_.size(); i++)
    {
        if(students_.at(i)->login() == login)
            return students_.at(i);
    }

    return 0;
}
