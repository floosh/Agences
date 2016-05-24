#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QFileDialog>
#include <QString>
#include <QVector>
#include <QDebug>
#include "include/place.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    QVector<Place> agencies;
    QVector<Place> cities;

    void loadFile(QString url, QVector<Place>);

};

#endif // MAINWINDOW_H
