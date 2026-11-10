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

// Elimina el nodo con ese codigo. Devuelve false si no existe.
bool BinarioAA::Eliminar(string codigo)
{
    if (buscarRec(raiz, codigo) == nullptr)
    {
        return false;
    }
    raiz = eliminarRec(raiz, codigo);
    return true;
}

// Eliminacion recursiva (metodo de la profesora).
NodoAA* BinarioAA::eliminarRec(NodoAA* nodo, string codigo)
{
    if (nodo == nullptr)
        return nullptr;

    if (codigo < nodo->codigo)
    {
        nodo->izquierda = eliminarRec(nodo->izquierda, codigo);
    }
    else if (codigo > nodo->codigo)
    {
        nodo->derecha = eliminarRec(nodo->derecha, codigo);
    }
    else
    {
        // Caso 1: Hoja
        if (nodo->izquierda == nullptr && nodo->derecha == nullptr)
        {
            delete nodo;
            return nullptr;
        }

        // Caso 2: Un hijo
        if (nodo->izquierda == nullptr)
        {
            NodoAA* temp = nodo->derecha;
            delete nodo;
            return temp;
        }
        else if (nodo->derecha == nullptr)
        {
            NodoAA* temp = nodo->izquierda;
            delete nodo;
            return temp;
        }

        // Caso 3: Dos hijos => tomar el sucesor
        NodoAA* sucesor = nodo->derecha;
        while (sucesor->izquierda != nullptr)
            sucesor = sucesor->izquierda;

        nodo->codigo = sucesor->codigo;
        nodo->nombre = sucesor->nombre;
        nodo->descripcion = sucesor->descripcion;
        nodo->derecha = eliminarRec(nodo->derecha, sucesor->codigo);
    }

    // Ajuste de niveles (propio AA)
    // El nivel de un nodo no puede ser mayor que (nivel del menor hijo + 1); un hijo nulo vale 0
    int nivelIzq = 0;
    if (nodo->izquierda != nullptr)
        nivelIzq = nodo->izquierda->nivel;

    int nivelDer = 0;
    if (nodo->derecha != nullptr)
        nivelDer = nodo->derecha->nivel;

    int nivelEsperado = nivelIzq + 1;
    if (nivelDer + 1 < nivelEsperado)
        nivelEsperado = nivelDer + 1;

    if (nivelEsperado < nodo->nivel)
    {
        nodo->nivel = nivelEsperado;

        if (nodo->derecha != nullptr && nodo->derecha->nivel > nivelEsperado)
            nodo->derecha->nivel = nivelEsperado;
    }

    // Rebalancear AA: tres giros y dos repartos
    nodo = Giro(nodo);

    if (nodo->derecha != nullptr)
        nodo->derecha = Giro(nodo->derecha);

    if (nodo->derecha != nullptr && nodo->derecha->derecha != nullptr)
        nodo->derecha->derecha = Giro(nodo->derecha->derecha);

    nodo = Reparto(nodo);

    if (nodo->derecha != nullptr)
        nodo->derecha = Reparto(nodo->derecha);

    return nodo;
}

NodoAA* BinarioAA::obtenerRaiz()
{
    return raiz;
}
