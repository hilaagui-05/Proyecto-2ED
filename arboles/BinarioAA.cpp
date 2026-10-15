#include <iostream>
#include "BinarioAA.h"

using namespace std;

// Constructor del arbol.
BinarioAA::BinarioAA()
{
    raiz = nullptr;
}

// Destructor del arbol.
BinarioAA::~BinarioAA()
{
    liberarMemoria(raiz);
}

// Inserta un diagnostico en el arbol.
void BinarioAA::insertar(string codigo, string nombre, string descripcion)
{
    raiz = insertarRec(raiz, codigo, nombre, descripcion);
}

// Insercion recursiva.
NodoAA* BinarioAA::insertarRec(NodoAA* nodo, string codigo, string nombre, string descripcion)
{
    if (nodo == nullptr)
    {
        return new NodoAA(codigo, nombre, descripcion);
    }
    if (codigo < nodo->codDiagnostico)
    {
        nodo->izquierda = insertarRec(nodo->izquierda, codigo, nombre, descripcion);
    }
    else if (codigo > nodo->codDiagnostico)
    {
        nodo->derecha = insertarRec(nodo->derecha, codigo, nombre, descripcion);
    }
    else
    {
        return nodo;
    }
    nodo = Giro(nodo);
    nodo = Reparto(nodo);
    return nodo;
}

// Giro hacia la derecha.
NodoAA* BinarioAA::Giro(NodoAA* nodo)
{
    if (nodo->izquierda != nullptr &&
        nodo->izquierda->nivel == nodo->nivel)
    {
        NodoAA* auxiliar = nodo->izquierda;
        nodo->izquierda = auxiliar->derecha;
        auxiliar->derecha = nodo;
        return auxiliar;
    }
    return nodo;
}

// Giro hacia la izquierda y aumento de nivel.
NodoAA* BinarioAA::Reparto(NodoAA* nodo)
{
    if (nodo->derecha != nullptr &&
        nodo->derecha->derecha != nullptr &&
        nodo->nivel == nodo->derecha->derecha->nivel)
    {
        NodoAA* auxiliar = nodo->derecha;
        nodo->derecha = auxiliar->izquierda;
        auxiliar->izquierda = nodo;
        auxiliar->nivel++;
        return auxiliar;
    }
    return nodo;
}

// Busca un diagnostico.
bool BinarioAA::buscar(string codigo)
{
    return buscarRec(raiz, codigo) != nullptr;
}

// Muestra los datos de un diagnostico.
void BinarioAA::mostrarPorCodigo(string codigo)
{
    NodoAA* nodo = buscarRec(raiz, codigo);
    if (nodo != nullptr)
    {
        cout << "Codigo: " << nodo->codDiagnostico << endl;
        cout << "Nombre: " << nodo->nombre << endl;
        cout << "Descripcion: " << nodo->descripcion << endl;
    }
    else
    {
        cout << "El diagnostico no existe." << endl;
    }
}

// Busqueda recursiva.
NodoAA* BinarioAA::buscarRec(NodoAA* nodo, string codigo)
{
    if (nodo == nullptr)
    {
        return nullptr;
    }
    if (codigo == nodo->codDiagnostico)
    {
        return nodo;
    }
    else if (codigo < nodo->codDiagnostico)
    {
        return buscarRec(nodo->izquierda, codigo);
    }
    else
    {
        return buscarRec(nodo->derecha, codigo);
    }
}

// Muestra el arbol en preorden.
void BinarioAA::mostrarPreorden()
{
    if (raiz == nullptr)
    {
        cout << "El arbol esta vacio." << endl;
    }
    else
    {
        mostrarPreorden(raiz);
    }
}

// Recorrido recursivo en preorden.
void BinarioAA::mostrarPreorden(NodoAA* nodo)
{
    if (nodo != nullptr)
    {
        cout << "Codigo: " << nodo->codDiagnostico
            << " | Nombre: " << nodo->nombre
            << " | Descripcion: " << nodo->descripcion << endl;
        mostrarPreorden(nodo->izquierda);
        mostrarPreorden(nodo->derecha);
    }
}
// Indica si el arbol esta vacio.
bool BinarioAA::estaVacio()
{
    return raiz == nullptr;
}
// Elimina todos los nodos del arbol.
void BinarioAA::limpiar()
{
    liberarMemoria(raiz);
    raiz = nullptr;
}
// Libera la memoria de los nodos.
void BinarioAA::liberarMemoria(NodoAA* nodo)
{
    if (nodo != nullptr)
    {
        liberarMemoria(nodo->izquierda);
        liberarMemoria(nodo->derecha);
        delete nodo;
    }
}