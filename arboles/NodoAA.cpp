#include "NodoAA.h"

NodoAA::NodoAA(string codigo, string nombreDiagnostico, string descripcionDiagnostico)
{
    this->codigo = codigo; //el código que pertenece al nodo
    nombre = nombreDiagnostico;
    descripcion = descripcionDiagnostico;
    nivel = 1;
    izquierda = nullptr;
    derecha = nullptr;
}