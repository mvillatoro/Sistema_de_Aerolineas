#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "qmainwindow.h"
#include "qpainter.h"
#include "qstyleoption.h"
#include "TinyXml/tinyxml.h"
#include "string.h"
#include "iostream"
using namespace std;

class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = 0);


    TiXmlDocument documento;
    TiXmlDocument conexiones;
    QWidget *mapArea;

    int xi, yi, xf, yf;
    void generarMapa(QMainWindow *win);
     void paintEvent(QPaintEvent *);

signals:

public slots:

};

#endif // MAPWIDGET_H
