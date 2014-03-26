#-------------------------------------------------
#
# Project created by QtCreator 2014-02-28T18:54:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sistema_de_Aerolineas
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tinyxml/tinystr.cpp \
    tinyxml/tinyxml.cpp \
    tinyxml/tinyxmlerror.cpp \
    tinyxml/tinyxmlparser.cpp \
    mapwidget.cpp \
    grafoaeropuerto.cpp \
    nodoaeropuerto.cpp \
    arista.cpp

HEADERS  += mainwindow.h \
    tinyxml/tinystr.h \
    tinyxml/tinyxml.h \
    mapwidget.h \
    grafoaeropuerto.h \
    nodoaeropuerto.h \
    arista.h

FORMS    += mainwindow.ui

RESOURCES += \
    Images.qrc
