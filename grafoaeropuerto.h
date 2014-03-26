#ifndef GRAFOAEROPUERTO_H
#define GRAFOAEROPUERTO_H
#include "NodoAeropuerto.h"
#include "arista.h"
#include <QString>
#include <iostream>
//#include <qstring>
//#include <qstring.h>
#include "NodoAeropuerto.h"
using namespace std;

class GrafoAeropuerto
{
public:
    GrafoAeropuerto();
    NodoAeropuerto*p;

    //CREA UN AEROPUERTO
    bool insertar_nodo(QString ciudad,int x,int y);

    //AGREGA ARISTA AL GRAFO
    void insertar_arista(QString i, QString f, double peso);

    void agregar_arista(NodoAeropuerto*Inicio, NodoAeropuerto*Final,Arista*nueva);
    int llenarMatriz(int origen, int destino);
    int recuperar2(QString ciudad);
    void dtra(int origen);
    int cont;
    int graMat [20];
    NodoAeropuerto *recuperar(int x, int y);
};

#endif // GRAFOAEROPUERTO_H
