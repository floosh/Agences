#ifndef PLACE_H
#define PLACE_H

#include <QStringList>
#include <QtMath>
#include <QDebug>
#include "include/coords.h"

class Place
{
public:

    Place();
    Place(QString, int, Coords);

    QString name;
    int count;
    Coords coords;

    double getDistance(Place*);
    inline bool operator ==(const Place& l) {return l.coords.latitude == coords.latitude && l.coords.longitude == coords.longitude;}
    void print();
};

#endif // PLACE_H
