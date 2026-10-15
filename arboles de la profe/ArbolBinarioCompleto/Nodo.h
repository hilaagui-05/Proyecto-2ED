#ifndef NODO_H
#define NODO_H

class Nodo 
{
public:
    int valor;
    Nodo* Hizq;
    Nodo* Hder;

    Nodo(int val);
    
friend class ABBusqueda;
};

#endif
