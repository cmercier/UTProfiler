#include "utilities.h"

void Utilities::clearLayout(QLayout *layout)
{
    if(layout)
    {
        QLayoutItem* item;
        while( (item = layout->takeAt(0)) )
        {
            if(item->widget())
                item->widget()->deleteLater();
            if(item->layout())
            {
                clearLayout(item->layout());
                item->layout()->deleteLater();
            }
            delete item;
        }
    }
}
