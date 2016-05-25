#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new Model();
    loadFile("Ouvrir la liste des villes", model->cities);
    loadFile("Ouvrir une liste d'agences", model->agencies);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(QString title, QVector<Place> places) {
    QString url = QFileDialog::getOpenFileName(this,title, "", "Text file (*.txt)");
    QFile fichier(url);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&fichier);

    while(!stream.atEnd()) {

        // read file /o/
        QString line = stream.readLine();
        QStringList fields = line.split(";");

        QString name = fields[0];
        int value = fields[4].toInt();
        Coords coords = {fields[2].toFloat(), fields[3].toFloat()};

        places.push_back(Place(name,value, coords));
        qDebug() << "loaded: " << fields << endl;
    }

}


