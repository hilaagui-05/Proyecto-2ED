#include <iostream>
#include "ABBusqueda.h"

using namespace std;

// Constructor
ABBusqueda::ABBusqueda() 
{
    raiz = nullptr;
}

// Destructor
ABBusqueda::~ABBusqueda() 
{
    destruirArbol(raiz);
}

// Metodos publicos

void ABBusqueda::InsertaNodo(int valor) 
{
    if(raiz==NULL){
        raiz = new Nodo(valor);
    }else{
        raiz = InsertaBinario(raiz, valor);
    }
}

bool ABBusqueda::Buscarvalor(int valor) 
{
    return Buscarvalor(raiz, valor);
}

void ABBusqueda::InordenR() 
{
    InordenR(raiz);
    cout << endl;
}

void ABBusqueda::PreordenR() 
{
    PreordenR(raiz);
    cout << endl;
}

void ABBusqueda::PostordenR() 
{
    PostordenR(raiz);
    cout << endl;
}

void ABBusqueda::EliminarNodo(int valor) 
{
    raiz = EliminarNodo(raiz, valor);
}

void ABBusqueda::recorridoPorNiveles() 
{
    if (raiz == nullptr) 
	{
        cout << "Arbol vacio" << endl;
        return;
    }

    Cola cola;
    cola.encolar(raiz);

    while (!cola.estaVacia()) 
	{
        pnodo actual = cola.desencolar();
        cout << actual->valor << " ";

        if (actual->Hizq != nullptr)
            cola.encolar(actual->Hizq);
        if (actual->Hder != nullptr)
            cola.encolar(actual->Hder);
    }

    cout << endl;
}

void ABBusqueda::preordenI() 
{
    Nodo* act = raiz;
    Pila pila;

    while (!pila.vacia() || act != nullptr) 
	{
        if (act != nullptr) {
            cout << act->valor << " - ";
            pila.push(act);
            act = act->Hizq;
        } 
		else 
		{
            act = pila.pop();
            act = act->Hder;
        }
    }
}

void ABBusqueda::inordenI() 
{
    Nodo* act = raiz;
    Pila pila;

    while (true) 
	{
        while (act != nullptr) 
		{
            pila.push(act);
            act = act->Hizq;
        }

        if (!pila.vacia()) 
		{
            act = pila.pop();
            cout << act->valor << " - ";
            act = act->Hder;
        }

        if (pila.vacia() && act == nullptr)
            break;
    }
}

void ABBusqueda::postordenI() 
{
    Nodo* act = raiz;
    Pila pila1, pila2;

    while (!pila1.vacia() || act != nullptr) 
	{
        if (act != nullptr) 
		{
            pila2.push(act);
            pila1.push(act);
            act = act->Hder;
        } 
		else 
		{
            act = pila1.pop();
            act = act->Hizq;
        }
    }

    while (!pila2.vacia()) 
	{
        Nodo* temp = pila2.pop();
        cout << temp->valor << " - ";
    }
}

// Metodos privados

pnodo ABBusqueda::InsertaBinario(pnodo raiz, int valor) 
{
    if (raiz == nullptr) 
	{
        return new Nodo(valor);
    }

    if (valor < raiz->valor) 
	{
        raiz->Hizq = InsertaBinario(raiz->Hizq, valor);
    } 
	else 
	   if (valor > raiz->valor) 
	   {
        raiz->Hder = InsertaBinario(raiz->Hder, valor);
       }

    return raiz;
}

bool ABBusqueda::Buscarvalor(pnodo raiz, int valor) 
{
    if (raiz == nullptr) return false;
    if (valor == raiz->valor) return true;
    if (valor < raiz->valor)
        return Buscarvalor(raiz->Hizq, valor);
    else
        return Buscarvalor(raiz->Hder, valor);
}

void ABBusqueda::InordenR(pnodo raiz) 
{
    if (raiz == nullptr) return;
    InordenR(raiz->Hizq);
    cout << raiz->valor << " - ";
    InordenR(raiz->Hder);
}

void ABBusqueda::PreordenR(pnodo raiz) 
{
    if (raiz == nullptr) return;
    cout << raiz->valor << " - ";
    PreordenR(raiz->Hizq);
    PreordenR(raiz->Hder);
}

void ABBusqueda::PostordenR(pnodo raiz) 
{
    if (raiz == nullptr) return;
    PostordenR(raiz->Hizq);
    PostordenR(raiz->Hder);
    cout << raiz->valor << " - ";
}

void ABBusqueda::destruirArbol(pnodo raiz) 
{
    if (raiz == nullptr) return;
    destruirArbol(raiz->Hizq);
    destruirArbol(raiz->Hder);
    delete raiz;
}

pnodo ABBusqueda::encontrarMinimo(pnodo raiz) 
{
    while (raiz->Hizq != nullptr) 
	{
        raiz = raiz->Hizq;
    }
    return raiz;
}

pnodo ABBusqueda::EliminarNodo(pnodo raiz, int valor) 
{
    if (raiz == nullptr) {
        cout << "Valor no encontrado: " << valor << endl;
        return nullptr;
    }

    if (valor < raiz->valor) 
	{
        raiz->Hizq = EliminarNodo(raiz->Hizq, valor);
    } 
	else 
	   if (valor > raiz->valor) 
	   {
        raiz->Hder = EliminarNodo(raiz->Hder, valor);
       } 
	   else 
	   {
        // Nodo encontrado
        if (raiz->Hizq == nullptr && raiz->Hder == nullptr) 
		{
            delete raiz;
            return nullptr;
        } 
		else 
		   if (raiz->Hizq == nullptr) 
		   {
             pnodo temp = raiz->Hder;
             delete raiz;
             return temp;
           } 
		   else 
		      if (raiz->Hder == nullptr) 
			  {
                pnodo temp = raiz->Hizq;
                delete raiz;
                return temp;
              } 
			  else 
			  {
                pnodo sucesor = encontrarMinimo(raiz->Hder);
                raiz->valor = sucesor->valor;
                raiz->Hder = EliminarNodo(raiz->Hder, sucesor->valor);
              }
        }

    return raiz;
}

