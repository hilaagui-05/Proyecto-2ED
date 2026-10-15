#include "NodoAA.h"

NodoAA::NodoAA(string codigo, string nombreDiagnostico, string descripcionDiagnostico)
{
    codDiagnostico = codigo;
    nombre = nombreDiagnostico;
    descripcion = descripcionDiagnostico;
    nivel = 1;
    izquierda = nullptr;
    derecha = nullptr;
}