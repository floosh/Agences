#ifndef POTATO_H
#define POTATO_H

#include <QVector>
#include "place.h"

struct Potato {
    Place center;
    QVector<Place> agencies;
};


#endif // POTATO_H
