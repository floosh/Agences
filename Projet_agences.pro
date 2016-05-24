#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T10:55:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_agences
TEMPLATE = app


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/place.cpp

HEADERS  += \
    include/mainwindow.h \
    include/place.h \
    include/coords.h

FORMS    += src/mainwindow.ui
