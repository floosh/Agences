#ifndef PLACE_H
#define PLACE_H

#include <QStringList>
#include "Coords.h"

class Place
{
public:

    Place();
    Place(int, Coords);

    int count;
    Coords coords;

};

#endif // PLACE_H
