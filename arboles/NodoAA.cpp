#include "NodoAA.h"

NodoAA::NodoAA(string codigo, string nombreDiagnostico, string descripcionDiagnostico)
{
    codigo = codigo;
    nombre = nombreDiagnostico;
    descripcion = descripcionDiagnostico;
    nivel = 1;
    izquierda = nullptr;
    derecha = nullptr;
}