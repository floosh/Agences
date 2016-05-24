#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadFile("Ouvrir la liste des villes", cities);
    loadFile("Ouvrir une liste d'agences", agencies);

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

        int value = fields[4].toInt();
        Coords coords = {fields[2].toFloat(), fields[3].toFloat()};

        places.push_back(Place(value, coords));
        qDebug() << "loaded: " << fields << endl;
    }

}
