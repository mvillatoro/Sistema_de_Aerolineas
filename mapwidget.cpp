#include "mapwidget.h"

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent)
{

    mapArea = new QWidget(parent);
    documento = TiXmlDocument("documento.xml");
    conexiones = TiXmlDocument("conexiones.xml");
}

void MapWidget::generarMapa(QMainWindow *win)
{
    mapArea->setGeometry(10,50,1400,750);
    mapArea->setStyleSheet("border-image: url(:/Images/mapa4.png)");
    mapArea->raise();
    mapArea->show();
}

void MapWidget::paintEvent(QPaintEvent *)
{
    QStyleOption o;
    o.initFrom(this->mapArea);
    QPainter p1(this->mapArea);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p1, this->mapArea);
    QPainter painter(this->mapArea);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setWidth(10);
    pen.setBrush(Qt::black);
    painter.setPen(pen);
    //painter.drawLine(QLine(xi,yi ,xf,yf));
    painter.drawLine(0,0 ,900,10);
}
