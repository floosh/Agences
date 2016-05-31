#include "include/model.h"

Model::Model()
{

}

double Model::solutionCost()
{
    return solutionCost(this->solution);
}

double Model::solutionCost(QVector<Potato *> potatoes) {
    double cost = 0.0;
    for(Potato* p : potatoes) {
        cost += costPerCenter;
        for(Place* a : p->agencies) {
            cost += p->center->getDistance(a) * costPerKm * a->count;
        }
    }
    return cost;
}

bool Model::isValidSolution()
{
    return isValidSolution(solution);
}


bool Model::isValidSolution(QVector<Potato *> potatoes)
{

    for(Potato* p : potatoes) {
        int count = 0;
        for(Place* a : p->agencies) {
            count += a->count;
        }
        if(count > personsPerCenter) return false;
    }
    return true;
}

void Model::print()
{
    qDebug() << "Solution du modèle actuel: " << this->solutionCost() << endl << "--------------------------------------------";
    for(Potato* p : solution) {
        p->print();
    }
}

