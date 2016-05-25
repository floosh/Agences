#include "include/place.h"

Place::Place(QString n,int v, Coords c)
{
    this->name = n;
    this->count = v;
    this->coords = c;
}

Place::Place()
{

}

double Place::getDistance(Place& p2) {
    double R = 6371000.0; // metres

    double lat1 = qDegreesToRadians(this->coords.latitude);
    double lat2 = qDegreesToRadians(p2.coords.latitude);
    double dlat = qDegreesToRadians(p2.coords.latitude-this->coords.latitude);
    double dlong = qDegreesToRadians(p2.coords.longitude-this->coords.longitude);

    double a = qSin(dlat/2) * qSin(dlat/2) +
            qCos(lat1) * qCos(lat2) *
            qSin(dlong/2) * qSin(dlong/2);
    double c = 2 * qAtan2(qSqrt(a), qSqrt(1-a));

    return R * c;
}
