#ifndef NODOAA_H
#define NODOAA_H

class NodoAA {
public:
    int valor;
    int nivel; // nivel del nodo, equivalente a color en ARN
    NodoAA* padre;
    NodoAA* izquierda;
    NodoAA* derecha;

    NodoAA(int val);
};

#endif

