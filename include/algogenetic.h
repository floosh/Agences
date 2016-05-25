#ifndef ALGOGENETIC_H
#define ALGOGENETIC_H

#include "include/model.h"

class AlgoGenetic
{
public:

   Model* model;
   AlgoGenetic(Model*);

   double process();
   double evaluate();

};

#endif // ALGOGENETIC_H

