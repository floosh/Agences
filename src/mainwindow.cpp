#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    model = new Model();
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    QFile places("sample_files/LieuxPossibles.txt");
    loadFile(model->cities, places);
    QFile agencies("sample_files/ListeAgences_100.txt");
    loadFile(model->agencies,agencies);

    updateView();


}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loadFile(QString title, QVector<Place*> &places) {
    QString url =
            QFileDialog::getOpenFileName(this, title, "", "Text file (*.txt)");
    QFile fichier(url);
    loadFile(places, fichier);
}

void MainWindow::loadFile(QVector<Place*> &places, QFile &fichier) {

    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&fichier);

    //to ignore first line (title of the column)
    bool firstLine = true;
    places.clear();

    while (!stream.atEnd()) {

        // read file /o/
        QString line = stream.readLine();

        if(firstLine) {
            firstLine = false;
            continue;
        }

        line = line.replace("\"", "");
        QStringList fields = line.split(";");

        QString name = fields[0];
        int value = 0;
        if(fields.length() == 6) //there is also a column for count (agences file)
            value = fields[5].toInt();
        Coords coords = {fields[3].toFloat(), fields[4].toFloat()};

        Place* p = new Place();
        p->name = name;
        p->count = value;
        p->coords = coords;

        places.push_back(p);
        qDebug() << "loaded: " << fields << endl;
    }
}

void MainWindow::drawPlace(Place* p, const QColor &color, int size) {

    if(size < 0) size = p->count + 2;

    int width = 15000, height = 12800;
    double x = fmod((width*(180+p->coords.longitude)/360), (width +(width/2)));

    // height and width are map height and width
    double PI = 3.14159265359;
    double latRad = p->coords.latitude*PI/180;

    // get y value
    double mercN = log(tan((PI/4)+(latRad/2)));
    double y = (height/2)-(width*mercN/(2*PI));

    scene->addEllipse(QRect(x-7280,y-3910,size, size), QPen(), QBrush(color) );
}

void MainWindow::updateView() {

    QImage image("res/france.png");

    if(!image.isNull())
    {
        scene->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(image)));
    }

    if(model->solution.size() == 0) {
        for(Place* p : model->agencies) {
            drawPlace(p, Qt::red);
        }
    } else {
        for(Potato* p : model->solution) {
            QColor c(qrand()%255,qrand()%255,qrand()%255);
            drawPlace(p->center, c, 20);
            for(Place* place : p->agencies) {
                drawPlace(place, c);
            }
        }
    }

    ui->lblAgences->setText(QStringLiteral("%1 Agence(s)").arg(model->agencies.size()));
    ui->lblVilles->setText(QStringLiteral("%1 Ville(s)").arg(model->cities.size()));
}



/**
 * Barycentre par moyenne latitude et longitude
 * @brief MainWindow::testBarycentre1
 * @param places
 */
/*
void MainWindow::testBarycentre1(QVector<Place> places) {
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

    qDebug() << "Méthode moyenne des coordonnées" << endl;
    qDebug() << "latitude : " << latitude << endl;
    qDebug() << "longitutde : " << longitutde << endl;
}*/

/*void MainWindow::testBarycentre2(QVector<Place> places) {
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

  qDebug() << "Méthode conversion des coordonnées" << endl;
  qDebug() << "latitude : " << latFinal << endl;
  qDebug() << "longitutde : " << longFinal << endl;
}*/

void MainWindow::on_btnAgences_clicked()
{
    loadFile("Ouvrir une liste d'agences", model->agencies);
    updateView();
}

void MainWindow::on_btnVilles_clicked()
{
    loadFile("Ouvrir une liste de villes", model->cities);
    updateView();
}

void MainWindow::on_pushButton_4_clicked()
{
    //KMeans k(model);
    //k.process(200);

    // Création de nb clusters
    int nb_clusters = 13;
    model->solution.clear();
    do {
        Place* center = model->cities.at(qrand()%model->cities.size());
        Potato* p = new Potato(center);

        if(!model->solution.contains(p)) {
            model->solution.push_back(p);
            nb_clusters --;
        }
    } while(nb_clusters > 0);

    // Affectation des agences 'au plus proche'
    for(Place* a : model->agencies) {
        for(Potato* p : model->solution) {
            if( p->getPersonCount() + a->count < model->personsPerCenter) {
                p->agencies.push_back(a);
                break;
            }
        }

    }


    Recuit r(model);
    r.process(1000);

    model->print();

    updateView();
}
