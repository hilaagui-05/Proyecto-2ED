#include "NodoAVL.h"

NodoAVL::NodoAVL(int idHabitacion, int numero, string piso, int tipo, int estado)
{
    this->idHabitacion = idHabitacion;
    this->numero = numero;
    this->piso = piso;
    this->tipo = tipo;
    this->estado = estado;
    FB = 0;
    Hizq = nullptr;
    Hder = nullptr;
}