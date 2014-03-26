#ifndef ARISTA_H
#define ARISTA_H
#include "nodoaeropuerto.h"
class NodoAeropuerto;
class Arista
{
public:
    double peso;
    Arista*siguiente;
    NodoAeropuerto*Destino;
    Arista();
};

#endif // ARISTA_H
