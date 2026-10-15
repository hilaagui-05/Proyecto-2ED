#ifndef BINARIO_H
#define BINARIO_H

#include "NodoBinario.h"

class Binario {
private:
    pNodoBinario raiz;

public:
    // Constructor
    Binario();
    
    // Destructor
    ~Binario();
    
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
