#ifndef BINARIOAA_H
#define BINARIOAA_H

#include "NodoAA.h"
#include <string>

using namespace std;

// Arbol AA. Se usa una instancia para Diagnosticos y otra para Especialidades.
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
    ~BinarioAA();

    void Insertar(string codigo, string nombre, string descripcion);
    bool Buscarvalor(string codigo);
    void mostrarPorCodigo(string codigo); // muestra los datos si el codigo existe
    void mostrarPreorden();
    bool estaVacio();
    void limpiar();
};

#endif