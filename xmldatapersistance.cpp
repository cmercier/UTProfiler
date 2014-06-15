#include "xmldatapersistance.h"

void XmlDataPersistance::execLoad()
{
    try
    {
        loadCategories(categoriesFilePath_);
        loadUvs(uvsFilePath_);
        loadDegrees(degreesFilePath_);
        loadStudents(studentsFilePath_);
    }
    catch(UTProfilerException e)
    {
        qDebug() << e.getInfo();
    }
}

void XmlDataPersistance::execSave()
{
    saveDegrees();
    saveUvs();
    saveStudents();
}

void XmlDataPersistance::addDegree(QDomElement &element, Degree *parent)
{
    Degree *degree = new Degree;
    degree->setTitle(element.firstChildElement("titre").text());
    degree->setType(element.attribute("type","formation"));
    addUvs(degree,element);
    addQuotas(degree,element);

    for(QDomElement qElem = element.firstChildElement("quota");!qElem.isNull();qElem = qElem.nextSiblingElement("quota"))
    {
        degree->setQuota(qElem.attribute("categorie"),qElem.text().toInt());
    }

    for(QDomElement childElement = element.firstChildElement("item"); !childElement.isNull(); childElement = childElement.nextSiblingElement("item"))
    {
        addDegree(childElement,degree);
    }

    degree->setParent(parent);
    degrees_.push_back(degree);
}

void XmlDataPersistance::addDegrees(Student *student, QDomElement &element)
{
    for(QDomElement degreeElement = element.firstChildElement("cursus"); !degreeElement.isNull(); degreeElement = degreeElement.nextSiblingElement("cursus"))
    {
        const Degree *degree = 0;
        for(int i = 0; i < degrees_.size(); i++)
        {
            if(degrees_.at(i)->title() == degreeElement.text())
            {
                degree = degrees_.at(i);
                break;
            }
        }
        if(degree)
            student->addDegree(degree);
    }
}

void XmlDataPersistance::addSemesters(Student *student, QDomElement &element)
{
    for(QDomElement semesterElement = element.firstChildElement("semestre"); !semesterElement.isNull(); semesterElement = semesterElement.nextSiblingElement("semestre"))
    {
        Semester *semester = new Semester();
        semester->setTitle(semesterElement.firstChildElement("titre").text());
        addUvs(semester, semesterElement);
        student->addSemester(semester);
    }
}

void XmlDataPersistance::addUvs(Degree *degree, QDomElement &element)
{
    for(QDomElement uvElement = element.firstChildElement("uv"); !uvElement.isNull(); uvElement = uvElement.nextSiblingElement("uv"))
    {
        const Uv *uv = uvFromCode(uvElement.text());
        if(uv)
            degree->addUv(uv);
    }
}

void XmlDataPersistance::addUvs(Semester *semester, QDomElement &element)
{
    for(QDomElement uvElement = element.firstChildElement("uv"); !uvElement.isNull(); uvElement = uvElement.nextSiblingElement("uv"))
    {
        semester->addUv(uvElement.firstChildElement("code").text(), Uv::stringToGrade(uvElement.firstChildElement("note").text()));
    }
}

void XmlDataPersistance::addQuotas(Degree *degree, QDomElement &element)
{
    for(QDomElement quotaElement = element.firstChildElement("quota"); !quotaElement.isNull(); quotaElement = quotaElement.nextSiblingElement("quota"))
    {
        QString category = element.attribute("categorie");
        int quota = quotaElement.text().toInt();
        degree->setQuota(category,quota);
    }
}

void XmlDataPersistance::loadCategories(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        throw UTProfilerException("Failed to open " + fileName + " in UVManager::loadDegrees.");

    QDomDocument dom;
    dom.setContent(&file);

    QDomElement categories = dom.documentElement();

    for(QDomElement catElem = categories.firstChildElement("categorie");!catElem.isNull();catElem = catElem.nextSiblingElement("categorie"))
    {
        Uv::categories_.push_back(catElem.text());
    }

    file.close();
}

void XmlDataPersistance::loadDegrees(const QString &fileName)
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

void XmlDataPersistance::loadStudents(const QString &studentsFileName)
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

        for(QDomElement eqElem = studentElement.firstChildElement("equivalence");!eqElem.isNull();eqElem = eqElem.nextSiblingElement("equivalence"))
        {
            student->setEquivalence(eqElem.attribute("categorie"),eqElem.text().toUInt());
        }

        students_.push_back(student);

        // Previsions
        for(QDomElement expElem = studentElement.firstChildElement("prevision"); !expElem.isNull(); expElem = expElem.nextSiblingElement("prevision"))
        {
            Expectation* exp = new Expectation;

            exp->setName(expElem.firstChildElement("nom").text());

            student->addExp(exp);

            for(QDomElement degreeElement = expElem.firstChildElement("cursus"); !degreeElement.isNull(); degreeElement = degreeElement.nextSiblingElement("cursus"))
            {
                for(int i = 0; i < degrees_.size(); i++)
                {
                    if(degrees_.at(i)->title() == degreeElement.text())
                        exp->addDegree(degrees_.at(i));
                }
            }

            for(QDomElement uvElement = expElem.firstChildElement("uvRejete"); !uvElement.isNull(); uvElement = uvElement.nextSiblingElement("uvRejete"))
            {
                const Uv *uv = uvFromCode(uvElement.text());
                if(uv)
                    exp->addRejectedUv(uv);
            }

            for(QDomElement uvElement = expElem.firstChildElement("uvRequise"); !uvElement.isNull(); uvElement = uvElement.nextSiblingElement("uvRequise"))
            {
                const Uv *uv = uvFromCode(uvElement.text());
                if(uv)
                    exp->addRequiredUv(uv);
            }

            for(QDomElement semesterElement = expElem.firstChildElement("semestre"); !semesterElement.isNull(); semesterElement = semesterElement.nextSiblingElement("semestre"))
            {
                Semester *semester = new Semester();
                semester->setTitle(semesterElement.firstChildElement("titre").text());

                for(QDomElement uvElement = semesterElement.firstChildElement("uv"); !uvElement.isNull(); uvElement = uvElement.nextSiblingElement("uv"))
                {
                    semester->addUv(uvElement.text(), Uv::stringToGrade("Undefined"));
                }
                exp->addSemester(semester);
            }
        }
    }

    file.close();
}

void XmlDataPersistance::loadUvs(const QString &fileName)
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
        uv->setCategory(uvElement.firstChildElement("categorie").text());
        uv->setCode(uvElement.firstChildElement("code").text());
        uv->setCredits(uvElement.firstChildElement("credits").text().toFloat());
        uv->setFall(uvElement.attribute("automne") == "true" ? true : false);
        uv->setSpring(uvElement.attribute("printemps") == "true" ? true : false);
        uv->setTitle(uvElement.firstChildElement("titre").text());
        uvs_.push_back(uv);
    }

    file.close();
}

void XmlDataPersistance::saveDegree(Degree *degree, QDomElement &element, QDomDocument &dom)
{
    QDomElement degreeElement = dom.createElement("item");
    degreeElement.setAttribute("type",degree->type());
    element.appendChild(degreeElement);

    QDomElement titleElement = dom.createElement("titre");
    titleElement.appendChild(dom.createTextNode(degree->title()));
    degreeElement.appendChild(titleElement);

    QDomElement typeElement = dom.createElement("type");
    typeElement.appendChild(dom.createTextNode(degree->type()));
    degreeElement.appendChild(typeElement);

    const QList<const Uv*> &uvs = degree->uvs();
    for(int i = 0; i < uvs.size(); i++)
    {
        QDomElement uvElement = dom.createElement("uv");
        uvElement.appendChild(dom.createTextNode(uvs.at(i)->code()));
        degreeElement.appendChild(uvElement);
    }

    const QMap<QString,int> &quotas = degree->quotas();
    QMapIterator<QString,int> it(quotas);
    while(it.hasNext())
    {
        it.next();
        QDomElement quotaElement = dom.createElement("quota");
        QDomAttr cat = dom.createAttribute("categorie");
        cat.setNodeValue(it.key());
        quotaElement.setAttributeNode(cat);
        quotaElement.appendChild(dom.createTextNode(QString::number(it.value())));
        degreeElement.appendChild(quotaElement);
    }

    const QList<Degree*> &children = degree->children();
    for(int i = 0; i < children.size(); i++)
        saveDegree(children.at(i),degreeElement,dom);
}

void XmlDataPersistance::saveDegrees()
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

void XmlDataPersistance::saveStudents()
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
        QMapIterator<QString,unsigned int> it(student->equivalences());
        while(it.hasNext())
        {
            it.next();
            QDomElement eqElem = dom.createElement("equivalence");
            eqElem.setAttribute("categorie",it.key());
            eqElem.appendChild(dom.createTextNode(QString::number(it.value())));
            studentElement.appendChild(eqElem);
        }

        // Previsions
        for (int i = 0; i < student->exp().size(); i++)
        {
            QDomElement exp = dom.createElement("prevision");

            QDomElement name = dom.createElement("nom");
            name.appendChild(dom.createTextNode(student->exp().at(i)->name()));
            exp.appendChild(name);

            for (int j = 0; j < student->exp().at(i)->degrees().size(); j++)
            {
                QDomElement degree = dom.createElement("cursus");
                degree.appendChild(dom.createTextNode(student->exp().at(i)->degrees().at(j)->title()));
                exp.appendChild(degree);
            }
            for (int j = 0; j < student->exp().at(i)->rejectedUvs().size(); j++)
            {
                QDomElement rejectedUv = dom.createElement("uvRejete");
                rejectedUv.appendChild(dom.createTextNode(student->exp().at(i)->rejectedUvs().at(j)->code()));
                exp.appendChild(rejectedUv);
            }

            for (int j = 0; j < student->exp().at(i)->requiredUvs().size(); j++)
            {
                QDomElement requiredUv = dom.createElement("uvRequise");
                requiredUv.appendChild(dom.createTextNode(student->exp().at(i)->requiredUvs().at(j)->code()));
                exp.appendChild(requiredUv);
            }

            for (int j = 0; j < student->exp().at(i)->semesters().size(); j++)
            {
                QDomElement semester = dom.createElement("semestre");

                QDomElement title = dom.createElement("titre");
                title.appendChild(dom.createTextNode(student->exp().at(i)->semesters().at(j)->title()));
                semester.appendChild(title);

                // Uvs
                QMapIterator<QString, Grade> it(student->exp().at(i)->semesters().at(j)->uvs());
                while (it.hasNext()) {
                    it.next();

                    QDomElement uv = dom.createElement("uv");
                    uv.appendChild(dom.createTextNode(it.key()));

                    semester.appendChild(uv);
                }

                exp.appendChild(semester);
            }

            studentElement.appendChild(exp);
        }

        students.appendChild(studentElement);
    }

    file.write(dom.toByteArray());
    file.close();
}

void XmlDataPersistance::saveUvs()
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
        category.appendChild(dom.createTextNode(uv->category()));
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

const Uv* XmlDataPersistance::uvFromCode(const QString &code) const
{
    for(int i = 0; i < uvs_.size(); i++)
    {
        if(uvs_.at(i)->code() == code)
            return uvs_.at(i);
    }

    return 0;
}
