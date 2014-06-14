#ifndef UTILITIES_H
#define UTILITIES_H
#include <QtWidgets>

/**
 * Cet espace de nom contient des fonctions utiles de manipulation des objets Qt.
 * Pour nos besoins, il ne contient qu'une fonction, qui vide un QLayout et assure la destruction des items enlevés.
 */

namespace Utilities
{
    void clearLayout(QLayout *layout);
}

#endif // UTILITIES_H
