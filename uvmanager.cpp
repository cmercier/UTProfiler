#include "uvmanager.h"

UVManager* UVManager::instance_ = 0;
UVManager::Handler UVManager::handler_=Handler();

UVManager::UVManager():
    degreesFilePath_("formations.xml"),
    student_(0),
    studentsFilePath_("etudiants.xml"),
    uvsFilePath_("UV_UTC.xml")
{
}

UVManager::~UVManager()
{
    saveDegrees();
    saveUvs();
    saveStudents();
}

void UVManager::addDegree(QDomElement &element, Degree *parent)
{
    Degree *degree = new Degree;
    degree->setTitle(element.firstChildElement("titre").text());
    degree->setType(element.attribute("type","formation"));
    addUvs(degree,element);
    addQuotas(degree,element);

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

    bool edited(false);
    for(int i = 0; i < uvs_.size(); i++)
    {
        if(uvs_.at(i)->code() == uv->code())
        {
            uvs_.replace(i,uv);
            edited = true;
        }
    }

    if(!edited)
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
        semester->addUv(uvElement.firstChildElement("code").text(), Uv::stringToGrade(uvElement.firstChildElement("note").text()));
    }
}

void UVManager::addQuotas(Degree *degree, QDomElement &element)
{
    for(QDomElement quotaElement = element.firstChildElement("quota"); !quotaElement.isNull(); quotaElement = quotaElement.nextSiblingElement("quota"))
    {
        Category category = Uv::stringToCategory(element.attribute("categorie"));
        int quota = quotaElement.text().toInt();
        degree->setQuota(category,quota);
    }
}

void UVManager::addStudent(const QString &login)
{
    student_ = new Student;
    student_->setLogin(login);
    students_.push_back(student_);
}

void UVManager::addStudent(Student *student)
{
    if(!student)
        return;

    students_.push_back(student);
}

bool UVManager::connect(const QString &login)
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
    {
        instance_ = new UVManager;
        UVManager::handler_.instance_ = instance_;
    }

    return *instance_;
}

void UVManager::load()
{
    try
    {
        loadUvs(uvsFilePath_);
        loadDegrees(degreesFilePath_);
        loadStudents(studentsFilePath_);
    }
    catch(UTProfilerException e)
    {
        qDebug() << e.getInfo();
    }
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

void UVManager::loadStudents(const QString &studentsFileName)
{
    QFile file(studentsFileName);
    if(!file.open(QIODevice::ReadOnly))
        throw UTProfilerException("Failed to open " + studentsFileName + " in UVManager::loadStudents.");

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

        for(QDomElement expElem = studentElement.firstChildElement("prevision");!expElem.isNull();expElem = expElem.nextSiblingElement("prevision"))
        {
            Expectation* exp = new Expectation;

            exp->setName(expElem.firstChildElement("nom").text());

            student->addExp(exp);
        }
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

void UVManager::removeUv(const QString &code)
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

void UVManager::saveDegree(Degree *degree, QDomElement &element, QDomDocument &dom)
{
    QDomElement degreeElement = dom.createElement("item");
    degreeElement.setAttribute("type",degree->type());
    element.appendChild(degreeElement);

    QDomElement titleElement = dom.createElement("titre");
    titleElement.appendChild(dom.createTextNode(degree->title()));
    degreeElement.appendChild(titleElement);

    const QList<const Uv*> &uvs = degree->uvs();
    for(int i = 0; i < uvs.size(); i++)
    {
        QDomElement uvElement = dom.createElement("uv");
        uvElement.appendChild(dom.createTextNode(uvs.at(i)->code()));
        degreeElement.appendChild(uvElement);
    }

    const QMap<Category,int> &quotas = degree->quotas();
    QMapIterator<Category,int> it(quotas);
    while(it.hasNext())
    {
        it.next();
        QDomElement quotaElement = dom.createElement("quota");
        quotaElement.setAttribute("categorie",Uv::categoryToString(it.key()));
        quotaElement.appendChild(dom.createTextNode(QString::number(it.value())));
        degreeElement.appendChild(quotaElement);
    }

    const QList<Degree*> &children = degree->children();
    for(int i = 0; i < children.size(); i++)
        saveDegree(children.at(i),degreeElement,dom);
}

void UVManager::saveDegrees()
{
    QFile file(degreesFilePath_);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        //throw UTProfilerException("Failed to open " + fileName + " in UVManager::save.");
        qDebug() << "Failed to open " << degreesFilePath_ << " in save";
        return;
    }

    QDomDocument dom;
    dom.setContent(&file);

    QDomElement degrees = dom.createElement("formations");
    dom.appendChild(degrees);

    for(int i = 0; i < degrees_.size(); i++)
        if(degrees_.at(i)->depth() == 0)
            saveDegree(degrees_.at(i),degrees,dom);

    file.write(dom.toByteArray());
    file.close();
}

void UVManager::saveStudents()
{
    QFile file(studentsFilePath_);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        //throw UTProfilerException("Failed to open " + fileName + " in UVManager::save.");
        qDebug() << "Failed to open " << uvsFilePath_ << " in save";
        return;
    }

    QDomDocument dom;
    dom.setContent(&file);

    QDomElement students = dom.createElement("etudiants");
    dom.appendChild(students);

    // Students
    for(int i = 0; i < students_.size(); i++)
    {
        Student* student = students_.at(i);

        QDomElement studentElement = dom.createElement("etudiant");

        QDomElement login = dom.createElement("login");
        login.appendChild(dom.createTextNode(student->login()));
        studentElement.appendChild(login);

        QDomElement prenom = dom.createElement("prenom");
        prenom.appendChild(dom.createTextNode(student->firstName()));
        studentElement.appendChild(prenom);

        QDomElement nom = dom.createElement("nom");
        nom.appendChild(dom.createTextNode(student->lastName()));
        studentElement.appendChild(nom);

        // Degrees
        for (int i = 0; i < student->degrees().size(); i++)
        {
            QDomElement degree = dom.createElement("cursus");
            degree.appendChild(dom.createTextNode(student->degrees()[i]->title()));
            studentElement.appendChild(degree);
        }

        // Semesters
        for (int i = 0; i < student->semesters().size(); i++)
        {
            QDomElement semester = dom.createElement("semestre");

            QDomElement title = dom.createElement("titre");
            title.appendChild(dom.createTextNode(student->semesters()[i]->title()));
            semester.appendChild(title);

            // Uvs
            QMapIterator<QString, Grade> it(student->semesters()[i]->uvs());
            while (it.hasNext()) {
                it.next();

                QDomElement uv = dom.createElement("uv");

                QDomElement code = dom.createElement("code");
                code.appendChild(dom.createTextNode(it.key()));
                uv.appendChild(code);

                QDomElement grade = dom.createElement("note");
                grade.appendChild(dom.createTextNode(Uv::gradeToString(it.value())));
                uv.appendChild(grade);

                semester.appendChild(uv);
            }

            studentElement.appendChild(semester);
        }

        // Equivalences
        QDomElement equivalences = dom.createElement("equivalence");

        QDomElement equivalenceCs = dom.createElement("cs");
        equivalenceCs.appendChild(dom.createTextNode(QString::number(student->equivalenceCs())));
        equivalences.appendChild(equivalenceCs);

        QDomElement equivalenceTm = dom.createElement("tm");
        equivalenceTm.appendChild(dom.createTextNode(QString::number(student->equivalenceTm())));
        equivalences.appendChild(equivalenceTm);

        QDomElement equivalenceTsh = dom.createElement("tsh");
        equivalenceTsh.appendChild(dom.createTextNode(QString::number(student->equivalenceTsh())));
        equivalences.appendChild(equivalenceTsh);

        QDomElement equivalenceSp = dom.createElement("sp");
        equivalenceSp.appendChild(dom.createTextNode(QString::number(student->equivalenceSp())));
        equivalences.appendChild(equivalenceSp);

        studentElement.appendChild(equivalences);


        students.appendChild(studentElement);
    }

    file.write(dom.toByteArray());
    file.close();
}

void UVManager::saveUvs()
{
    QFile file(uvsFilePath_);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        //throw UTProfilerException("Failed to open " + fileName + " in UVManager::save.");
        qDebug() << "Failed to open " << uvsFilePath_ << " in save";
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
