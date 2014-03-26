#ifndef NODOAEROPUERTO_H
#define NODOAEROPUERTO_H
#include <Qstring>
#include "arista.h"

class Arista;
class NodoAeropuerto
{
public:
    NodoAeropuerto();
    NodoAeropuerto(QString ciudad,int posx, int posy);
    NodoAeropuerto*siguiente;
    Arista*adyacente;
    int posx, posy;
    QString nombre;

//
};

#endif // NODOAEROPUERTO_H
