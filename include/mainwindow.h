#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTime>

#include "include/model.h"
#include "include/kmeans.h"
#include "include/recuit.h"


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

    void on_pushButton_4_clicked();

private:

    QGraphicsScene* scene;
    Ui::MainWindow *ui;
    Model* model;

    void loadFile(QString, QVector<Place*>&);
    void loadFile(QVector<Place*>&, QFile&);
    void drawPlace(Place*, const QColor &color = Qt::red, int size = -1);
    void updateView();
};

#endif // MAINWINDOW_H
