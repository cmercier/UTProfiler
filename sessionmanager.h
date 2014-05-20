#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H
#include <QtWidgets>
#include <QtXml>
#include "student.h"
#include "utprofilerexception.h"

class SessionManager
{
public:
    void addStudent(Student *student);
    const Student* currentStudent() const {return currentStudent_;}
    static SessionManager& instance();
    void load(const QString &fileName);
    const QList<Student*> students() const {return students_;}

private:
    SessionManager();
    SessionManager(const SessionManager& session);
    SessionManager& operator=(const SessionManager& session);
    const Student* studentWithLogin(const QString &login) const;

    Student* currentStudent_;
    static SessionManager* instance_;
    QList<Student*> students_;
};

#endif // SESSIONMANAGER_H
