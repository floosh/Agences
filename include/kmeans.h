#ifndef KMEANS_H
#define KMEANS_H

#include "include/model.h"

class KMeans
{
public:

    QVector<Place> places;


    KMeans();
    KMeans(QVector<Place>);

    double process();

    Coords computeCentre(QVector<Place>);
    Coords computeCartesianCenter(QVector<Place>);

};

#endif // KMEANS_H
