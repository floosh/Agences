#ifndef MODEL_H
#define MODEL_H

#include "include/place.h"
#include <QVector>

class Model
{
public:
    Model();
    QVector<Place> agencies;
    QVector<Place> cities;
    QVector<Place> centers;

    const double costPerCenter = 3000.0;
    const double costPerKm = 0.4;

};

#endif // MODEL_H
