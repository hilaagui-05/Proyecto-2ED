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

    // Metodos publicos principales
    void Insertar(int x);
    //void EliminarValor(int x);
    void Mostrar();
    bool EstaVacio();
    void Limpiar();
    void Eliminar(int x);


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
