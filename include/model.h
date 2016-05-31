#ifndef MODEL_H
#define MODEL_H

#include "potato.h"

class Model
{
public:


    Model();
    QVector<Place*> agencies;
    QVector<Place*> cities;

    QVector<Potato*> solution;

    const double costPerCenter = 3000.0;
    const double costPerKm = 0.8;
    const int personsPerCenter = 60;

    double solutionCost();
    double solutionCost(QVector<Potato*>);

    bool isValidSolution();
    bool isValidSolution(QVector<Potato*>);

    void print();

};

#endif // MODEL_H
