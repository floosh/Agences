#include "include/potato.h"


Potato::Potato(Place *c)
{
    this->center = c;
}

Potato::Potato(const Potato &p)
{
    this->center = p.center;
    this->agencies = QVector<Place*>(p.agencies);
}

Potato &Potato::operator=(Potato & p)
{
    this->center = p.center;
    this->agencies = QVector<Place*>(p.agencies);
}

int Potato::getPersonCount()
{
    int count = 0;
    for(Place* a : agencies) {
        count += a->count;
    }
    return count;
}

void Potato::print()
{
    qDebug() << "Centre de formation: " << center->name << " (" << getPersonCount() << "personnes)";
    for(Place* a : agencies) {
        a->print();
    }
}
