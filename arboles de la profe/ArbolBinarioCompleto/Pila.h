// Pila.h
#ifndef PILA_H
#define PILA_H

#include "Nodo.h"
typedef Nodo *pnodo; //Alias  

class Pila {
private:
    class NodoPila 
	{
    	
    public:
        pnodo valor;
        NodoPila* sig;

        NodoPila(pnodo d, NodoPila* s);
    };

    NodoPila* tope;

public:
    Pila();
    ~Pila();

    void push(pnodo val);
    pnodo pop();
    bool vacia();
};

#endif

