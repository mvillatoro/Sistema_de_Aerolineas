#include "nodoaeropuerto.h"
#include <QString>
NodoAeropuerto::NodoAeropuerto(QString ciudad,int posx, int posy)
{
   this->posx = posx;
   this->posy = posy;
   this->nombre = ciudad;
   this->siguiente = NULL;
   this->adyacente = NULL;
}
NodoAeropuerto::NodoAeropuerto()
{
    this->siguiente = NULL;
    this->adyacente = NULL;
}
