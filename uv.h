#ifndef UV_H
#define UV_H
#include <QString>
#include <QStringList>

enum Grade
{
    A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC, Undefined
};

/**
 * @brief The Uv class
 * Cette class contient toutes les informations propres à une uv.
 */

class Uv
{
public:
    Uv();
    Uv(const Uv& uv);

    QString category() const {return category_;}
    const QString & code() const {return code_;}
    unsigned int credits() const {return credits_;}
    bool fall() const {return fall_;}

    /**
     * @brief gradeToString
     * @param grade
     * @return
     * Permet de manipuler l'enum grade sous forme de QString.
     */
    static QString gradeToString(Grade grade);
    bool spring() const {return spring_;}
    void setCategory(const QString & category) {category_ = category;}
    void setCredits(unsigned int credits) {credits_ = credits;}
    void setCode(const QString &code) {code_ = code;}
    void setFall(bool fall) {fall_ = fall;}
    void setSpring(bool spring) {spring_ = spring;}
    void setTitle(const QString &title) {title_ = title;}

    /**
     * @brief stringToGrade
     * @param gradeString
     * @return
     * Traduit un QString en grade. Retourne undefined si le paramètre est invalide.
     */
    static Grade stringToGrade(const QString &gradeString);
    const QString & title() const {return title_;}

    static QStringList categories_;

private:
    QString category_;
    unsigned int credits_;
    QString code_;
    bool fall_;
    bool spring_;
    QString title_;
};



#endif // UV_H
