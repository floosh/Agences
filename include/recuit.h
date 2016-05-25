#ifndef RECUIT_H
#define RECUIT_H

#include "model.h"

class Recuit
{
public:
    Recuit();

    Model* model;
    Recuit(Model*);

    double process();
};

#endif // RECUIT_H
