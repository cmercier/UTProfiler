#ifndef UV_H
#define UV_H
#include <QString>

enum Category
{
    /* Connaissances Scientifiques */ CS,  /* Techniques et Méthodes */ TM,
    /* Technologies et Sciences de l'Homme */ TSH, /* Stage et Projet */ SP,
    UndefinedCategory
};

enum Grade
{
    A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC
};

class Uv
{
public:
    Category category() const {return category_;}
    static QString categoryToString(Category category);
    const QString & code() const {return code_;}
    unsigned int credits() const {return credits_;}
    bool fall() const {return fall_;}
    bool spring() const {return spring_;}
    void setCategory(Category category) {category_ = category;}
    void setCredits(unsigned int credits) {credits_ = credits;}
    void setCode(const QString &code) {code_ = code;}
    void setFall(bool fall) {fall_ = fall;}
    void setSpring(bool spring) {spring_ = spring;}
    void setTitle(const QString &title) {title_ = title;}
    static Category stringToCategory(const QString &categoryString);
    const QString & title() const {return title_;}

private:
    Uv();
    Uv(const Uv& uv);
    Uv(const QString &code, const QString &title, unsigned int credits, Category category, bool spring, bool fall);
    Uv& operator=(const Uv& uv);
    friend class UVManager;

    Category category_;
    unsigned int credits_;
    QString code_;
    bool fall_;
    bool spring_;
    QString title_;
};

#endif // UV_H
