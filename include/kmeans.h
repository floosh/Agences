#ifndef KMEANS_H
#define KMEANS_H

#include <QDebug>
#include "include/model.h"

class KMeans
{
public:

    Model* model;


    KMeans();
    KMeans(Model*);

    double process(int nb_clusters);
    void iterate();

    Coords computeCentre(QVector<Place*>);

};

#endif // KMEANS_H
