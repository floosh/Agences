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
