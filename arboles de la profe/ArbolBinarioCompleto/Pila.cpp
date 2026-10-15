#include "Pila.h"
#include <iostream>
using namespace std;

// Constructor del nodo interno de la pila
Pila::NodoPila::NodoPila(pnodo d, NodoPila* s) {
    valor = d;
    sig = s;
}

// Constructor de la pila
Pila::Pila() {
    tope = nullptr;
}

// Destructor de la pila
Pila::~Pila() {
    while (!vacia()) {
        pop();
    }
}

// Metodo push (agrega al tope)
void Pila::push(pnodo valor) 
{
    NodoPila* nuevo = new NodoPila(valor, tope);
    tope = nuevo;
}

// Metodo pop (saca del tope)
pnodo Pila::pop() 
{
    if (vacia()) return nullptr;
    NodoPila* temp = tope;
    pnodo dato = temp->valor;
    tope = temp->sig;
    delete temp;
    return dato;
}

// Verificar si esta vacia
bool Pila::vacia() 
{
    return tope == nullptr;
}

