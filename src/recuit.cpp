#include "include/recuit.h"


Recuit::Recuit(Model* m)
{
    this->model = m;
}


double Recuit::process(int iterations) {

    // Code du recuit
    // on pars de la solution du modèle et on l'ameilore

    double lambda_t = 0.95, base_temp = 1000.0,temp = base_temp, temp_iterations = 100;
    double cur_value = model->solutionCost(), min_value = cur_value;


    for(int i = 0;i<iterations;i++) {


        // Itérations de température
        temp = base_temp;
        for(int j = 0;j<temp_iterations;j++) {

            // Nouvelle solution
            QVector<Potato*> potatoes = generateNeighbor();
            double new_value = model->solutionCost(potatoes);

            if((new_value < cur_value || pass(temp,new_value-cur_value)) && potatoes.size() > 0) {

                // Nouvelle solution acceptée
                cur_value = new_value;

                // Nouvelle solution minimale
                if(new_value < min_value && model->isValidSolution(potatoes)) {
                    qDebug() << "New solution :" << new_value;
                    model->solution = potatoes;
                    min_value = cur_value;
                }
            }

            temp *= lambda_t;

        }

        if(i%(iterations/10) == 0) {
            qDebug() << i << "itérations";
        }

    }

    //renvoie la valeur totale de la solution
    //dans l'attribut model, remplis la liste des solutions avec des patates

    return model->solutionCost();

}

bool Recuit::pass(double temp, double delta)
{
    double r = (qrand()%100)/100.0;
    return (r < qExp(-delta/temp));
}


QVector<Potato*> Recuit::generateNeighbor() {

    double delta = 100.0;
    QVector<Potato*> potatoes;
    for(Potato* p : model->solution) {
        potatoes.push_back(new Potato(*p));
    }

    // Un voisin d'une solution;
    // On change une agence de centre de formation
    // On change de place un centre de formation
    // On ajoute/supprime un centre de formation

    int r = qrand()%50;
    if(r == 0) {
        //qDebug() << "add centre";
        // On ajoute un centre
        Place* c = model->cities.at(qrand()%model->cities.size());


        Potato* p = new Potato(c);

        // Ajout d'agences dans le centre
        for(Place* a : model->agencies) {
            if(a->getDistance(p->center) < delta/2) {
                for(Potato* o : potatoes) {
                    o->agencies.removeOne(a);
                }
                p->agencies.push_back(a);
            }
        }

        potatoes.push_back(p);

    } else if(r == 1) {
        //qDebug() << "delete centre";
        // On supprime un centre
        Potato* deleted_one = potatoes.at(qrand()%potatoes.size());

        for(Place* a : deleted_one->agencies) {
            double min_distance = -1;
            Potato* min_potato = NULL;
            for(Potato* p : potatoes) {
                double distance = p->center->getDistance(a);
                if((min_distance < 0 || distance < min_distance) && p->getPersonCount() + a->count <= model->personsPerCenter ) {
                    min_distance = distance;
                    min_potato = p;
                }
            }

            // Ca marche pô...
            if(min_potato == NULL)
                return QVector<Potato*>();

            min_potato->agencies.push_back(a);
        }


    } else if (r < 10) {
        //qDebug() << "move centre";
        // on déplace un centre de formation
        // choix aléatoire d'une patate
        Potato* p = potatoes.at(qrand()%potatoes.size());

        // Recherche d'une ville proche de ce centre de formation
        QVector<Place*> cities;
        for(Place* c : model->cities) {
            if(c->getDistance(p->center) < delta && c != p-> center) {
                cities.push_back(c);
            }
        }
        // Choix aléatoire dans les villes proches
        Place* city = cities.at(qrand()%cities.size());
        p->center = city;

    } else {
        //qDebug() << "move agence";
        // On change le centre de formation d'une agence

        // choix aléatoire d'une patate ou il reste des places
        QVector<Potato*> possible_potatoes;

        for(Potato* p : potatoes) {
            if(p->getPersonCount() < model->personsPerCenter) {
                possible_potatoes.push_back(p);
            }
        }

        if(possible_potatoes.size() >0) {
            Potato* p = possible_potatoes.at(qrand()%possible_potatoes.size());

            // Recherche d'une agence assez proche de ce centre de formation qui n'en fait pas déja partie
            QVector<Place*> agencies;
            for(Place* a : model->agencies) {
                if(a->getDistance(p->center) < 2*delta && a != p->center && ! p->agencies.contains(a)) {
                    agencies.push_back(a);
                }
            }


            // Choix aléatoire de l'agence
            if(agencies.size()>0) {
                Place* a = agencies.at(qrand()%agencies.size());

                if(a->count + p->getPersonCount() <= model->personsPerCenter) {
                    // Choix aléatoire dans les agences proches
                    for(Potato* o : potatoes) {
                        o->agencies.removeOne(a);
                    }

                    p->agencies.push_back(a);
                }


            }
        }

    }

    return potatoes;

}
