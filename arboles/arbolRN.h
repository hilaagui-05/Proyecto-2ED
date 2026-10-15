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
    pNodoRN BuscarNodo(int idTratamiento);

public:
    BinarioRN();
    ~BinarioRN();

    void Insertar(int idTratamiento, string nombre,string descripcion,int costo);
    void Mostrar();
    bool EstaVacio();
    void Limpiar();
};

#endif

