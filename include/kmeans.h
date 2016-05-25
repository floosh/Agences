#ifndef KMEANS_H
#define KMEANS_H

#include "include/model.h"

class KMeans
{
public:
    KMeans();

    Model* model;
    KMeans(Model*);

    double process();

};

#endif // KMEANS_H
