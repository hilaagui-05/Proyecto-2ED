#ifndef ARBOLRN_H
#define ARBOLRN_H

#include "NodoRN.h"

using namespace std;

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

public:
    BinarioRN();
    ~BinarioRN();

    void Insertar(int idTratamiento, string nombre,string descripcion, int costo);
    bool Buscarvalor(int idTratamiento);
    void mostrarPorClave(int idTratamiento);

    void Mostrar();
    bool EstaVacio();
    void Limpiar();
};

#endif

