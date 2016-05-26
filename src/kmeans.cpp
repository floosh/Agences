#include "include/kmeans.h"

KMeans::KMeans(QVector<Place> places)
{
    this->places = places;
}


double KMeans::process() {

    // Code du K-Means

    //renvoie la valeur totale de la solution
    //dans l'attribut model, remplis la liste des solutions avec des patates
}

/**
 * @brief KMeans::computeCentre
 * @return the centroid of the given places
 */
Coords KMeans::computeCentre(QVector<Place>) {
    double sumLongitude = 0;
    double sumLatitude = 0;
    int coeff = 0;
    for (Place p : places) {
      sumLongitude += p.count * p.coords.longitude;
      sumLatitude += p.count * p.coords.latitude;
      coeff += p.count;
    }

    double latitude = sumLatitude / coeff;
    double longitutde = sumLongitude / coeff;

    return Coord {longitude, latitude};
}

/**
 * @brief KMeans::computeCartesianCenter
 * @return the centroid of the given places, calcultated using Cartesian coordinates
 */
Coords KMeans::computeCartesianCenter(QVector<Place>) {
    double sumX = 0;
    double sumY = 0;
    double sumZ = 0;
    int coeff = 0;
    for (Place p : places) {
      double latRad = 2 * M_PI * (p.coords.latitude / 360);
      double longRad = 2 * M_PI * (p.coords.longitude / 360);
      double x = 6371 * cos(latRad) * cos(longRad);
      double y = 6371 * cos(latRad) * sin(longRad);
      double z = 6371 * sin(latRad);

      sumX += x * p.count;
      sumY += y * p.count;
      sumZ += z * p.count;
      coeff += p.count;
    }

    double xFinal = sumX / coeff;
    double yFinal = sumY / coeff;
    double zFinal = sumZ / coeff;

    double latFinal = (asin(zFinal / 6371) / (2 * M_PI)) * 360;
    double longFinal = (atan2(yFinal, xFinal) / (2 * M_PI)) * 360;

    return Coords {longFinal, latFinal};
}
