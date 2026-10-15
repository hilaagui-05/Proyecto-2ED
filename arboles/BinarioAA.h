#ifndef BINARIOAA_H
#define BINARIOAA_H

#include "NodoAA.h"
#include <string>

using namespace std;

class BinarioAA
{
private:
    NodoAA* raiz;

    NodoAA* insertarRec(NodoAA* nodo, string codigo, string nombre, string descripcion);
    NodoAA* Giro(NodoAA* nodo);
    NodoAA* Reparto(NodoAA* nodo);
    NodoAA* buscarRec(NodoAA* nodo, string codigo);
    void mostrarPreorden(NodoAA* nodo);
    void liberarMemoria(NodoAA* nodo);
public:
    BinarioAA();
    ~BinarioAA(); //destructor
    void insertar(string codigo, string nombre, string descripcion);
    bool buscar(string codigo);
    void mostrarPorCodigo(string codigo);
    void mostrarPreorden();
    bool estaVacio();
    void limpiar();
};

#endif