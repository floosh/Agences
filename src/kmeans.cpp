#include "include/kmeans.h"

KMeans::KMeans(Model* m)
{
    this->model = m;
}


double KMeans::process(int nb_clusters) {

    // Code du K-Means

    //renvoie la valeur totale de la solution
    //dans l'attribut model, remplis la liste des solutions avec des patates

    // Création de nb clusters
    model->solution.clear();
    do {
        Place* center = model->cities.at(qrand()%model->cities.size());
        Potato* p = new Potato(center);

        if(!model->solution.contains(p)) {
            model->solution.push_back(p);
            nb_clusters --;
        }
    } while(nb_clusters > 0);

    // On itère jusqu'a que l'on ne puisse plus ameilorer la solution
    double last_value, value = 0.0;
    do {
        last_value = value;
        iterate();
        double value = model->solutionCost();
        qDebug() << "k-mean value: " << value << endl;
    } while (value != last_value);

}

void KMeans::iterate()
{
    // Clustering
    // Reset de nos patates
    for(Potato* p : model->solution) {
        p->agencies.clear();
    }

    // On rattache chaque agence à son centre le plus proche
    for(Place* a : model->agencies) {
        // Recherche du centre le + proche
        double min_dist = -1.0;
        Potato* min_potato;
        for(Potato* p : model->solution) {
            double dist = p->center->getDistance(a);
            if(dist < min_dist || min_dist < 0) {
                min_dist = dist;
                min_potato = p;
            }
        }
        min_potato->agencies.push_back(a);
    }

    // Barycentre
    // Pour chaque patate, on cherche un centre mieux adapté

    for(Potato* p : model->solution) {
        Coords c = computeCentre(p->agencies);
        double min_dist = -1.0;
        Place* min_centre;
        for(Place* c : model->cities) {
            double dist = p->center->getDistance(c);
            if(dist < min_dist || min_dist < 0) {
                min_dist = dist;
                min_centre = c;
            }
        }
        p->center = min_centre;

    }

}

/**
 * @brief KMeans::computeCentre
 * @return the centroid of the given places
 */
Coords KMeans::computeCentre(QVector<Place*> places) {
    double sumLongitude = 0;
    double sumLatitude = 0;
    int coeff = 0;
    for (Place* p : places) {
        sumLongitude += p->count * p->coords.longitude;
        sumLatitude += p->count * p->coords.latitude;
        coeff += p->count;
    }

    double latitude = sumLatitude / coeff;
    double longitude = sumLongitude / coeff;

    return Coords {longitude, latitude};
}
