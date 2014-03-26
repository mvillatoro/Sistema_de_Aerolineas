#include "grafoaeropuerto.h"

//CONSTRUCTOR
GrafoAeropuerto::GrafoAeropuerto()
{
 p = NULL;
 cont = 0;
}

//CREA UN AEROPUERTO
bool GrafoAeropuerto::insertar_nodo(QString ciudad,int x,int y)
{
    NodoAeropuerto*t = new NodoAeropuerto();
    NodoAeropuerto *nuevo = new NodoAeropuerto(ciudad,x,y);
        if(p==NULL)
         {
            p = nuevo;
            cont++;
            return true;
         }
        else
         {
            t = p;
            while(t->siguiente!=NULL)
             {
                t = t->siguiente;
              }
            t->siguiente = nuevo;
            cont++;
             return true;
        }
         return false;
}

//CREA CONEXION/ARISTA
void GrafoAeropuerto::agregar_arista(NodoAeropuerto *aux, NodoAeropuerto *aux2, Arista *nuevo){

 Arista *q;
    if(aux->adyacente==NULL)
    {   aux->adyacente=nuevo;
        nuevo->Destino=aux2;
    }
    else
    {   q=aux->adyacente;
        while(q->siguiente!=NULL)
            q=q->siguiente;
        nuevo->Destino=aux2;
        q->siguiente=nuevo;
    }
}

//AGREGA ARISTA AL GRAFO
void GrafoAeropuerto::insertar_arista(QString inicio, QString fin, double peso)
{
    Arista *nuevo=new Arista();
    nuevo->peso = peso;
    NodoAeropuerto *aux, *aux2;
    if(p==NULL)
    {
        return;
    }
    nuevo->siguiente=NULL;

    aux=p;
    aux2=p;
    while(aux2!=NULL)
    {
        if(aux2->nombre==fin)
        {
            break;
        }
        aux2=aux2->siguiente;
    }
     while(aux!=NULL)
    {
        if(aux->nombre==inicio)
        {
            agregar_arista(aux,aux2, nuevo);
            return;
        }
             aux = aux->siguiente;
    }
}

//LLENA LA MATRIZ
int GrafoAeropuerto::llenarMatriz(int origen, int destino)
{
    NodoAeropuerto *ptr;
    Arista *ar;
    int matriz[cont][cont];
    for(int x=0;x<cont;x++)
    {
        for(int y=0;y<cont;y++)
        {
            if(x!=y)
                matriz[x][y]=9999;
            else
                matriz[x][y]=0;
        }
    }
    int x = 0;
    ptr=p;
    if(p==NULL)
        cout<<"ESTA NULO"<<endl;

    while(ptr!=NULL)
    {
        //int y = 0;
        if(ptr->adyacente!=NULL)
        {
            ar=ptr->adyacente;
            while(ar!=NULL)
            {
                int y = recuperar2(ar->Destino->nombre);
                matriz[x][y] = ar->peso;
                //y++;
                ar=ar->siguiente;
            }
        }
        ptr=ptr->siguiente;
        x++;
    }
    for(int fila=0; fila<cont; fila++)
    {
        cout<<" "<<endl;
        for(int columna=0; columna<cont; columna++)
        {
            cout<<matriz[fila][columna]<<" ";
        }
    }
    int Aux[cont], VertInc[cont], Ver1, Ver2, Ind1, Ind2, Menor, Band;
    int DistMin[cont];
    for (Ind1= 0; Ind1 < cont; Ind1++)
    {
        Aux[Ind1]= 0;
        VertInc[Ind1]= 0;
    }
    Aux[origen-1] = 1;
    for (Ind1= 0; Ind1 < cont; Ind1++)
        DistMin[Ind1]= matriz[origen-1][Ind1];
    for (Ind1= 0; Ind1 < cont; Ind1++)
    {
        cout<<"\n"<<DistMin[Ind1]<<endl;
    }
    for (Ind1= 0; Ind1<cont; Ind1++)
    {
        Menor= 9999;
        for (Ind2= 1; Ind2 < cont; Ind2++)
        if (DistMin[Ind2] < Menor && !Aux[Ind2])
        {
            Ver1= Ind2;
            Menor= DistMin[Ind2];
        }
        VertInc[Ind1]= Ver1;
        Aux[Ver1]= 1;
        Ver2= 1;
        while (Ver2 < cont)
        {
            Band=0;
            Ind2= 1;
            while (Ind2 < cont && !Band)
                if (VertInc[Ind2] == Ver2)
                    Band= 1;
                else
                    Ind2++;
                if (!Band)
                    DistMin[Ver2]=  std::min(DistMin[Ver2],DistMin[Ver1] + matriz[Ver1][Ver2]);
                    Ver2++;
        }
    }
    for (Ind1= 0; Ind1 < cont; Ind1++)
    {
        cout<<DistMin[Ind1]<<endl;
    }

    return DistMin[destino];
}

int GrafoAeropuerto::recuperar2(QString ciudad)
{
    NodoAeropuerto *aux;
    aux=p;
    int cont = 0;
    while(aux!=NULL)
    {
        if(aux->nombre==ciudad)
        {
            return cont;
        }
        else
        {
            aux=aux->siguiente;
            cont++;
        }
    }
    return cont;
}

void GrafoAeropuerto::dtra(int Origen)
{


}

NodoAeropuerto * GrafoAeropuerto::recuperar(int x, int y)
{
    NodoAeropuerto *ptr;
    ptr=p;

    if(p==NULL)
    //cout<<"NULO"<<endl;

    while(ptr!=NULL)
    {
        if((((x>= ptr->posx)&& (x<= ptr->posx+20)) || ((x+20 >= ptr->posx)&& (x+20 <= ptr->posx+20))) &&
            (((y >= ptr->posy) && (y <= ptr->posy+20)) || ((y+20 >= ptr->posy) && (y+20 <= ptr->posy+20))))
            return ptr;

         ptr=ptr->siguiente;
    }
    return ptr;
}
