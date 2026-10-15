#ifndef BINARIOAA_H
#define BINARIOAA_H

#include "NodoAA.h"
typedef NodoAA* pNodoAA;

class BinarioAA {
private:
    pNodoAA raiz;

    // Metodos internos
    pNodoAA insertarRec(pNodoAA nodo, int valor);
    pNodoAA Giro(pNodoAA nodo);// en la teoria se le llama tambien skew
    pNodoAA Reparto(pNodoAA nodo);// en la teoria se le llama split
    void mostrarPreorden(pNodoAA nodo);
    void liberarMemoria(pNodoAA nodo);
    pNodoAA eliminarRec(pNodoAA nodo, int valor);

public:
    BinarioAA();
    ~BinarioAA();

    void insertar(int valor);
    void mostrarPreorden();
    bool estaVacio();
    void limpiar();
    void eliminar(int valor);
  	
};

#endif

