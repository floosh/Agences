#ifndef POTATO_H
#define POTATO_H

#include <QVector>
#include "place.h"

class Potato {

public:

    Place* center;
    QVector<Place*> agencies;

    bool operator==(const Potato& p) const
    {
        return (p.center == center);
    }

    Potato(Place*);
    Potato(const Potato&);
    Potato & operator=(Potato&);
    int getPersonCount();
    void print();

};


#endif // POTATO_H
