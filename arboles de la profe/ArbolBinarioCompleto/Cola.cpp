#include "Cola.h"
#include <iostream>

using namespace std;

NodoCola::NodoCola(pnodo nodo) {
    valor= nodo;
    siguiente = nullptr;
}

Cola::Cola() {
    frente = nullptr;
    final = nullptr;
}

Cola::~Cola() {
    while (!estaVacia()) {
        desencolar();
    }
}

bool Cola::estaVacia() {
    return frente == nullptr;
}

void Cola::encolar(pnodo nodo) {
    NodoCola* nuevo = new NodoCola(nodo);
    if (estaVacia()) {
        frente = final = nuevo;
    } else {
        final->siguiente = nuevo;
        final = nuevo;
    }
}

pnodo Cola::desencolar() 
{
    if (estaVacia()) 
	{
        cout << "Cola vacia" << endl;
        return nullptr;
    }

    NodoCola* temp = frente;
    pnodo dato = temp->valor;

    frente = frente->siguiente;
    if (frente == nullptr) 
	{
        final = nullptr;
    }

    delete temp;
    return dato;
}

