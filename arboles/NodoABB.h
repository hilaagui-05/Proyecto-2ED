
#ifndef NODOABB_H
#define NODOABB_H

#include <string>
using namespace std;

class NodoABB
{
public:
    int codPais;
    int codCiudad;
    string nombre;

    NodoABB* Hizq;
    NodoABB* Hder;

    NodoABB(int codPais, int codCiudad, string nombre);
};

#endif
