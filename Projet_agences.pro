#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T10:55:58
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = $$PWD

TARGET = Projet_agences
TEMPLATE = app



SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/place.cpp \
    src/algogenetic.cpp \
    src/model.cpp \
    src/kmeans.cpp \
    src/recuit.cpp \
    src/potato.cpp

HEADERS  += \
    include/mainwindow.h \
    include/place.h \
    include/coords.h \
    include/algogenetic.h \
    include/model.h \
    include/kmeans.h \
    include/potato.h \
    include/recuit.h

FORMS    += src/mainwindow.ui
