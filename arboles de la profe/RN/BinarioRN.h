#ifndef BINARIORN_H
#define BINARIORN_H

#include "NodoRN.h"

typedef NodoRN* pNodoRN;

class BinarioRN {
private:
    pNodoRN raiz;

    void InsertarRN(pNodoRN nuevo);
    void ArreglaInsercion(pNodoRN nodo);
    void RotIzquierda(pNodoRN x);
    void RotDerecha(pNodoRN x);
    void MostrarInorden(pNodoRN nodo);
    void MostrarPreorden(pNodoRN nodo);
    void LiberarMemoria(pNodoRN nodo);
    void Borrar(int valor);
    void EliminarRN(pNodoRN nodo);
	void Sustitucion(pNodoRN u, pNodoRN v);
	pNodoRN Minimo(pNodoRN nodo);
	void ArreglaEliminacion(pNodoRN nodo);

public:
    BinarioRN();
    ~BinarioRN();

    void Insertar(int x);
    void Mostrar();
    bool EstaVacio();
    void Limpiar();
    void Eliminar(int valor); 
};

#endif

