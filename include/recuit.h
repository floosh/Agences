#ifndef RECUIT_H
#define RECUIT_H

#include <QDebug>
#include "model.h"


class Recuit
{
public:
    Recuit();

    Model* model;
    Recuit(Model*);

    double process(int iterations);
    bool pass(double temp, double delta);
    QVector<Potato*> generateNeighbor();

};

#endif // RECUIT_H
