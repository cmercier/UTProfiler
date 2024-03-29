#ifndef UTPROFILEREXCEPTION_H
#define UTPROFILEREXCEPTION_H
#include <QString>

/**
 * @brief The UTProfilerException class
 * Classe de gestion des exceptions.
 * Elle est utilisée par les fonctions de chargement et de sauvegarde de données dans les fichiers xml.
 */

class UTProfilerException
{
public:
    UTProfilerException(const QString& info, const QString& fileName="unknown", unsigned int line = 0);
    const QString& getInfo() {return info_;}

#ifndef NDEBUG
    // the file from which the exception was raised
    QString getFile() const { return file_; }
    // the line where the exception was raised
    unsigned int getLine() const { return line_; }
#endif

private:
    QString info_;
    QString file_;
    unsigned int line_;
};

#endif // UTPROFILEREXCEPTION_H
