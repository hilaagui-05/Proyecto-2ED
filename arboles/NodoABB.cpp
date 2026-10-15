
#include "NodoABB.h"

NodoABB::NodoABB(int codPais, int codCiudad, string nombre)
{
    this->codPais = codPais;
    this->codCiudad = codCiudad;
    this->nombre = nombre;

    Hizq = nullptr;
    Hder = nullptr;
}
