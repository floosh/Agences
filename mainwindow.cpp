#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString filename = QFileDialog::getOpenFileName(NULL,"Ouvrir une liste d'agences", "C:/", "Text file (*.txt)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(QString url) {
    QFile fichier(url);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&fichier);

    while(!stream.atEnd()) {
        // read file /o/
        QString line = stream.readLine();
        QStringList fields = line.split(";");

        int value = fields[4].toInt();
        Coords coords = {fields[2].toFloat(), fields[3].toFloat()};

        agences.push_back(Place(value, coords));

        qDebug() << fields << endl;
    }

}
