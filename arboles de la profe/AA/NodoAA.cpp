#include "NodoAA.h"

NodoAA::NodoAA(int val) {
    valor = val;
    nivel = 1; // nodo nuevo tiene nivel 1
    padre = nullptr;
    izquierda = nullptr;
    derecha = nullptr;
}

