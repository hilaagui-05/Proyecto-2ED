#include "NodoRN.h"

NodoRN::NodoRN(int val) {
    valor = val;
    color = true; // nuevo nodo es rojo
    padre = nullptr;
    Hizq = nullptr;
    Hder = nullptr;
}
