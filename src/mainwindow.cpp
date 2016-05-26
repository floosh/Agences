#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  model = new Model();
  loadFile("Ouvrir la liste des villes", model->cities);
  loadFile("Ouvrir une liste d'agences", model->agencies);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loadFile(QString title, QVector<Place> &places) {
  QString url =
      QFileDialog::getOpenFileName(this, title, "", "Text file (*.txt)");
  QFile fichier(url);
  fichier.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream stream(&fichier);

  //to ignore first line (title of the column)
  bool firstLine = true;

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

    places.push_back(Place(name, value, coords));
    qDebug() << "loaded: " << fields << endl;
  }
}

/**
 * Barycentre par moyenne latitude et longitude
 * @brief MainWindow::testBarycentre1
 * @param places
 */
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
}

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
