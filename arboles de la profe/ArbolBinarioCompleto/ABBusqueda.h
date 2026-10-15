#ifndef ABBUSQUEDA_H
#define ABBUSQUEDA_H

#include "Nodo.h"
#include "Cola.h"
#include "Pila.h"

typedef Nodo* pnodo;

class ABBusqueda {
private:
    pnodo raiz;

    // Metodos auxiliares privados
    pnodo InsertaBinario(pnodo raiz, int valor);
    bool Buscarvalor(pnodo raiz, int valor);
    void InordenR(pnodo raiz);
    void PreordenR(pnodo raiz);
    void PostordenR(pnodo raiz);
    void destruirArbol(pnodo raiz);
    pnodo EliminarNodo(pnodo raiz, int valor);
    pnodo encontrarMinimo(pnodo raiz);

    void preordenI(pnodo raiz);
    void inordenI(pnodo raiz);
    void postordenI(pnodo raiz);

public:
    ABBusqueda();
    ~ABBusqueda();

    void InsertaNodo(int valor);
    bool Buscarvalor(int valor);

    void InordenR();
    void PreordenR();
    void PostordenR();

    void recorridoPorNiveles();

    void preordenI();
    void inordenI();
    void postordenI();

    void EliminarNodo(int valor);
};

#endif
