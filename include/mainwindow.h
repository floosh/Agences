#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "include/model.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnAgences_clicked();

    void on_btnVilles_clicked();

private:

    QGraphicsScene* scene;
    Ui::MainWindow *ui;
    Model* model;

    void loadFile(QString, QVector<Place>&);
    void loadFile(QVector<Place>&, QFile&);
    void drawPlace(Place&);
    void updateView();
};

#endif // MAINWINDOW_H
