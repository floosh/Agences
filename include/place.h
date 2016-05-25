#ifndef PLACE_H
#define PLACE_H

#include <QStringList>
#include <QtMath>
#include "include/coords.h"

class Place
{
public:

    Place();
    Place(QString, int, Coords);

    QString name;
    int count;
    Coords coords;

    double getDistance(Place&);

};

#endif // PLACE_H
