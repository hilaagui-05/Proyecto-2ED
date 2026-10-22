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

// Inserta un nodo en el arbol (si el codigo ya existe no hace nada).
void BinarioAA::Insertar(string codigo, string nombre, string descripcion)
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
    if (codigo < nodo->codigo)
    {
        nodo->izquierda = insertarRec(nodo->izquierda, codigo, nombre, descripcion);
    }
    else if (codigo > nodo->codigo)
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

// Busca un nodo.
bool BinarioAA::Buscarvalor(string codigo)
{
    return buscarRec(raiz, codigo) != nullptr;
}

// Muestra los datos del nodo con ese codigo (no imprime nada si no existe;
// el mensaje de "no existe" lo da el crud, igual que en paises y ciudades).
void BinarioAA::mostrarPorCodigo(string codigo)
{
    NodoAA* nodo = buscarRec(raiz, codigo);
    if (nodo != nullptr)
    {
        cout << "Codigo: " << nodo->codigo << endl;
        cout << "Nombre: " << nodo->nombre << endl;
        cout << "Descripcion: " << nodo->descripcion << endl;
    }
}

// Cambia la descripcion del nodo con ese codigo. Devuelve false si no existe.
bool BinarioAA::modificarDescripcion(string codigo, string nuevaDescripcion)
{
    NodoAA* nodo = buscarRec(raiz, codigo);
    if (nodo == nullptr)
    {
        return false;
    }
    nodo->descripcion = nuevaDescripcion;
    return true;
}

// Busqueda recursiva.
NodoAA* BinarioAA::buscarRec(NodoAA* nodo, string codigo)
{
    if (nodo == nullptr)
    {
        return nullptr;
    }
    if (codigo == nodo->codigo)
    {
        return nodo;
    }
    else if (codigo < nodo->codigo)
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
        cout << "Codigo: " << nodo->codigo
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