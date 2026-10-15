#ifndef COLA_H
#define COLA_H

#include "Nodo.h"
typedef Nodo *pnodo; //Alias  

// Nodo interno de la cola (para la lista enlazada)
class NodoCola 
{
public:
    pnodo valor;
    NodoCola* siguiente;

    NodoCola(Nodo* nodo);
};

class Cola 
{
private:
    NodoCola* frente;
    NodoCola* final;

public:
    Cola();
    ~Cola();

    void encolar(pnodo nodo);
    Nodo* desencolar();
    bool estaVacia();

friend class ABBusqueda;
};

#endif


