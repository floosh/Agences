#include "include/model.h"

Model::Model()
{

}

double Model::solutionCost() {
    double cost = 0.0;
    for(Potato p : solution) {
        cost += costPerCenter;
        for(Place a : p.agencies) {
            cost += p.center.getDistance(a) * costPerKm;
        }
    }
    return cost;
}
