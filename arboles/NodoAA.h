#ifndef NODOAA_H
#define NODOAA_H

#include <string>
using namespace std;

class NodoAA
{
public:
    string codDiagnostico;
    string nombre;
    string descripcion;
    int nivel;
    NodoAA* izquierda;
    NodoAA* derecha;
    NodoAA(string codigo, string nombre, string descripcion);
};
#endif