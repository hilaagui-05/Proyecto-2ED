#ifndef AVL_H
#define AVL_H

#include "NodoAVL.h"
#include <string>

class AVL {

private:
    pNodoAVL raiz;

public:
    // Constructor
    AVL();

    // Destructor
    ~AVL();

    void Insertar(int id, int numero, string piso, int tipo, int estado);
    bool BuscarValor(int id);
    void mostrarPorCodigo(int id); // muestra los datos si el id existe
    void Mostrar();               // todas las habitaciones en inorden
    bool EstaVacio();
    void Limpiar();


    // Metodos de equilibrado 
    void Equilibrar1(NodoBinario*& n, bool& Hh);
    void Equilibrar2(NodoBinario*& n, bool& Hh);
    void InsertarBalanceado(pNodoBinario& ra, bool& Hh, int x);
    void Borrar(pNodoBinario& nodo, bool& Hh);
    void BorrarBalanceado(pNodoBinario& raiz, bool& Hh, int x);


    // Metodos de rotacion
    void RotacionSimpleIzquierda(NodoBinario*& n, NodoBinario*& n1);
    void RotacionSimpleDerecha(NodoBinario*& n, NodoBinario*& n1);
    void RotacionDobleIzquierda(NodoBinario*& n, NodoBinario*& n1);
    void RotacionDobleDerecha(NodoBinario*& n, NodoBinario*& n1);

    // Metodos auxiliares
    void MostrarInorden(pNodoBinario n);
    void MostrarPreorden(pNodoBinario n);
    void LiberarMemoria(pNodoBinario n);
};

#endif
