#include "BinarioAA.h"
#include <iostream>
using namespace std;

BinarioAA::BinarioAA() {
    raiz = nullptr;
}

BinarioAA::~BinarioAA() {
    liberarMemoria(raiz);
}

void BinarioAA::liberarMemoria(pNodoAA nodo) {
    if (nodo != nullptr) {
        liberarMemoria(nodo->izquierda);
        liberarMemoria(nodo->derecha);
        delete nodo;
    }
}

bool BinarioAA::estaVacio() 
{
    return raiz == nullptr;
}

void BinarioAA::limpiar() 
{
    liberarMemoria(raiz);
    raiz = nullptr;
}

void BinarioAA::insertar(int valor) 
{
    raiz = insertarRec(raiz, valor);
    if (raiz != nullptr)
        raiz->padre = nullptr;
}

pNodoAA BinarioAA::insertarRec(pNodoAA nodo, int valor) 
{
    if (nodo == nullptr) 
	{
        pNodoAA nuevo = new NodoAA(valor);
        return nuevo;
    }

    if (valor < nodo->valor) 
	{
        nodo->izquierda = insertarRec(nodo->izquierda, valor);
        if (nodo->izquierda != nullptr)
            nodo->izquierda->padre = nodo;
    } 
	else 
	     if (valor > nodo->valor) 
		 {
           nodo->derecha = insertarRec(nodo->derecha, valor);
         if (nodo->derecha != nullptr)
            nodo->derecha->padre = nodo;
         }    
	     else 
		 {
           // Valor ya existe, no insertar duplicados
           return nodo;
         }

    // Balanceos
    nodo = Giro(nodo);
    nodo = Reparto(nodo);

    return nodo;
}

// Giro: rotacion derecha si el hijo izquierdo esta en mismo nivel
pNodoAA BinarioAA::Giro(pNodoAA nodo) 
{
    if (nodo == nullptr) return nodo;

    if (nodo->izquierda != nullptr && nodo->izquierda->nivel == nodo->nivel) 
	{
        pNodoAA izq = nodo->izquierda;
        nodo->izquierda = izq->derecha;
        if (izq->derecha != nullptr)
            izq->derecha->padre = nodo;

        izq->derecha = nodo;
        izq->padre = nodo->padre;
        nodo->padre = izq;

        return izq;
    }
    return nodo;
}

// Reparto: rotacion izquierda + aumento de nivel si hay dos hijos derechos consecutivos
pNodoAA BinarioAA::Reparto(pNodoAA nodo) 
{
    if (nodo == nullptr) return nodo;

    if (nodo->derecha != nullptr && nodo->derecha->derecha != nullptr && nodo->nivel == nodo->derecha->derecha->nivel) 
	{

          pNodoAA der = nodo->derecha;
          nodo->derecha = der->izquierda;
          if (der->izquierda != nullptr)
              der->izquierda->padre = nodo;

          der->izquierda = nodo;
          der->padre = nodo->padre;
          nodo->padre = der;

          der->nivel += 1;
          return der;
    }
    return nodo;
}

void BinarioAA::mostrarPreorden() 
{
    if (estaVacio()) 
	{
        cout << "Arbol vacio" << endl;
    } 
	else 
	{
        cout << "Arbol AA en preorden: ";
        mostrarPreorden(raiz);
        cout << endl;
    }
}

void BinarioAA::mostrarPreorden(pNodoAA nodo) 
{
    if (nodo != nullptr) 
	{
        cout << nodo->valor << "(" << nodo->nivel << ") ";
        mostrarPreorden(nodo->izquierda);
        mostrarPreorden(nodo->derecha);
    }
}

void BinarioAA::eliminar(int valor)
{
    raiz = eliminarRec(raiz, valor);
    if (raiz != nullptr)
        raiz->padre = nullptr;
}

pNodoAA BinarioAA::eliminarRec(pNodoAA nodo, int valor)
{
    if (nodo == nullptr)
        return nullptr;

    if (valor < nodo->valor)
    {
        nodo->izquierda = eliminarRec(nodo->izquierda, valor);
        if (nodo->izquierda != nullptr)
            nodo->izquierda->padre = nodo;
    }
    else if (valor > nodo->valor)
    {
        nodo->derecha = eliminarRec(nodo->derecha, valor);
        if (nodo->derecha != nullptr)
            nodo->derecha->padre = nodo;
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
            pNodoAA temp = nodo->derecha;
            temp->padre = nodo->padre;
            delete nodo;
            return temp;
        }
        else if (nodo->derecha == nullptr)
        {
            pNodoAA temp = nodo->izquierda;
            temp->padre = nodo->padre;
            delete nodo;
            return temp;
        }

        // Caso 3: Dos hijos=> tomar sucesor
        pNodoAA sucesor = nodo->derecha;
        while (sucesor->izquierda != nullptr)
            sucesor = sucesor->izquierda;

        nodo->valor = sucesor->valor;
        nodo->derecha = eliminarRec(nodo->derecha, sucesor->valor);
        if (nodo->derecha != nullptr)
            nodo->derecha->padre = nodo;
    }

    //  Ajuste de niveles (propio AA)
    int nivelEsperado = 1;
    if (nodo->izquierda != nullptr)
        nivelEsperado = nodo->izquierda->nivel + 1;

    if (nodo->derecha != nullptr && nodo->derecha->nivel + 1 < nivelEsperado)
        nivelEsperado = nodo->derecha->nivel + 1;

    if (nivelEsperado < nodo->nivel)
    {
        nodo->nivel = nivelEsperado;

        if (nodo->derecha != nullptr && nodo->derecha->nivel > nivelEsperado)
            nodo->derecha->nivel = nivelEsperado;
    }

    // Rebalancear AA
    nodo = Giro(nodo);
    nodo = Reparto(nodo);

    if (nodo->derecha != nullptr)
        nodo->derecha = Reparto(nodo->derecha);

    if (nodo->derecha != nullptr && nodo->derecha->derecha != nullptr)
        nodo->derecha->derecha = Reparto(nodo->derecha->derecha);

    return nodo;
}
