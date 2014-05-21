#include "uvmanager.h"

UVManager* UVManager::instance_ = 0;

UVManager::UVManager()
{
}

void UVManager::addDegree(QDomElement &element, Degree *parent)
{
    Degree *degree = new Degree;
    degree->setTitle(element.firstChildElement("titre").text());
    degree->setType(element.attribute("type","formation"));
    addUvs(degree,element);

    for(QDomElement childElement = element.firstChildElement("item"); !childElement.isNull(); childElement = childElement.nextSiblingElement("item"))
    {
        addDegree(childElement,degree);
    }

    degree->setParent(parent);
    degrees_.push_back(degree);
}

void UVManager::addUv(Uv *uv)
{
    if(!uv)
        return;

    uvs_.push_back(uv);
}

void UVManager::addDegrees(Student *student, QDomElement &element)
{
    for(QDomElement degreeElement = element.firstChildElement("cursus"); !degreeElement.isNull(); degreeElement = degreeElement.nextSiblingElement("cursus"))
    {
        const Degree *degree = degreeWithTitle(degreeElement.text());
        if(degree)
            student->addDegree(degree);
    }
}

void UVManager::addSemesters(Student *student, QDomElement &element)
{
    for(QDomElement semesterElement = element.firstChildElement("semestre"); !semesterElement.isNull(); semesterElement = semesterElement.nextSiblingElement("semestre"))
    {
        Semester *semester = new Semester();
        semester->setTitle(semesterElement.firstChildElement("titre").text());
        addUvs(semester, semesterElement);
        student->addSemester(semester);
    }
}

void UVManager::addUvs(Degree *degree, QDomElement &element)
{
    for(QDomElement uvElement = element.firstChildElement("uv"); !uvElement.isNull(); uvElement = uvElement.nextSiblingElement("uv"))
    {
        const Uv *uv = uvFromCode(uvElement.text());
        if(uv)
            degree->addUv(uv);
    }
}

void UVManager::addUvs(Semester *semester, QDomElement &element)
{
    for(QDomElement uvElement = element.firstChildElement("uv"); !uvElement.isNull(); uvElement = uvElement.nextSiblingElement("uv"))
    {
        const Uv *uv = uvFromCode(uvElement.text());
        if(uv)
            semester->addUv(uv);
    }
}

void UVManager::addStudent(Student *student)
{
    if(!student)
        return;

    students_.push_back(student);
}

QList<const Degree*> UVManager::degreesWithParent(const QString &parentTitle)
{
    QList<const Degree*> result;
    for(int i = 0; i < degrees_.size(); i++)
    {
        if(degrees_.at(i)->parent() && degrees_.at(i)->parent()->title() == parentTitle)
            result.push_back(degrees_.at(i));
    }
    return result;
}

const Degree* UVManager::degreeWithTitle(const QString &title)
{
    for(int i = 0; i < degrees_.size(); i++)
    {
        if(degrees_.at(i)->title() == title)
            return degrees_.at(i);
    }

    return 0;
}

UVManager& UVManager::instance()
{
    if(!instance_)
        instance_ = new UVManager;

    return *instance_;
}

void UVManager::loadDegrees(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        throw UTProfilerException("Failed to open " + fileName + " in UVManager::loadDegrees.");

    QDomDocument dom;
    dom.setContent(&file);

    QDomElement degrees = dom.documentElement();

    for(QDomElement degreeElement = degrees.firstChildElement("item"); !degreeElement.isNull(); degreeElement = degreeElement.nextSiblingElement("item"))
    {
        addDegree(degreeElement);
    }

    file.close();
}

void UVManager::loadStudents(const QString &fileName)
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
        addDegrees(student, studentElement); // load degrees
        addSemesters(student, studentElement); // load semsters and uvs
        student->setEquivalenceCs(studentElement.firstChildElement("equivalence").firstChildElement("cs").text().toUInt());
        student->setEquivalenceTm(studentElement.firstChildElement("equivalence").firstChildElement("tm").text().toUInt());
        student->setEquivalenceTsh(studentElement.firstChildElement("equivalence").firstChildElement("tsh").text().toUInt());
        student->setEquivalenceSp(studentElement.firstChildElement("equivalence").firstChildElement("sp").text().toUInt());
        addStudent(student);
    }

    file.close();
}

void UVManager::loadUvs(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        throw UTProfilerException("Failed to open " + fileName + " in UVManager::loadUvs.");

    QDomDocument dom;
    dom.setContent(&file);

    QDomElement uvs = dom.documentElement();

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

void UVManager::save(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        //throw UTProfilerException("Failed to open " + fileName + " in UVManager::save.");
        qDebug() << "Failed to open " << fileName << " in save";
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

const Uv* UVManager::uvFromCode(const QString &code) const
{
    for(int i = 0; i < uvs_.size(); i++)
    {
        if(uvs_.at(i)->code() == code)
            return uvs_.at(i);
    }

    return 0;
}

QList<const Uv*> UVManager::uvs() const
{
    QList<const Uv*> result;
    for(int i = 0; i < uvs_.size(); i++)
    {
        result.push_back(uvs_.at(i));
    }
    return result;
}

QList<const Uv*> UVManager::uvsFromCode(const QStringList &codes) const
{
    QList<const Uv*> result;
    for(int i = 0; i < uvs_.size(); i++)
    {
        if(codes.contains(uvs_.at(i)->title()))
            result.push_back(uvs_.at(i));
    }
    return result;
}
