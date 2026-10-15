#ifndef ABBUSQUEDA_H
#define ABBUSQUEDA_H

#include "NodoABB.h"
#include <string>

using namespace std;

typedef NodoABB* pnodo;

// Para indicar si es el arbol de paises o de ciudades.
enum class TipoClave
{
    Pais,
    Ciudad
};

// Cola para el recorrido por niveles.
class Cola
{
private:
    class NodoCola
    {
    public:
        pnodo dato;
        NodoCola* siguiente;

        NodoCola(pnodo nodo);
    };

    NodoCola* frente;
    NodoCola* final;

public:
    Cola();
    ~Cola();

    void encolar(pnodo nodo);
    pnodo desencolar();
    bool estaVacia() const;
};

// Pila para los recorridos iterativos.
class Pila
{
private:
    class NodoPila
    {
    public:
        pnodo dato;
        NodoPila* siguiente;

        NodoPila(pnodo nodo, NodoPila* siguiente);
    };
    NodoPila* tope;

public:
    Pila();
    ~Pila();
    void push(pnodo nodo);
    pnodo pop();
    bool vacia() const;
};

class ABBusqueda
{
private:
    pnodo raiz;
    TipoClave tipoClave;

    // Metodos privados.
    int compararClaves(pnodo raiz, int codPais, int codCiudad);
    pnodo buscarNodo(pnodo raiz, int codPais, int codCiudad);
    void mostrarDato(pnodo raiz);
    pnodo InsertaBinario(pnodo raiz, int codPais, int codCiudad, string nombre);
    bool Buscarvalor(pnodo raiz, int codPais, int codCiudad);

    void InordenR(pnodo raiz);
    void PreordenR(pnodo raiz);
    void PostordenR(pnodo raiz);

    void destruirArbol(pnodo raiz);

public:
    ABBusqueda(TipoClave tipoClave);
    ~ABBusqueda();

    void InsertaNodo(int codPais, int codCiudad, string nombre);
    bool Buscarvalor(int codigo);
    bool Buscarvalor(int codPais, int codCiudad);
    void mostrarPorClave(int codigo);
    void mostrarPorClave(int codPais, int codCiudad);

    void InordenR();
    void PreordenR();
    void PostordenR();

    void recorridoPorNiveles();

    void preordenI();
    void inordenI();
    void postordenI();
};

#endif