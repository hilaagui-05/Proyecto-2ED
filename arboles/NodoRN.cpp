#include "NodoRN.h"

NodoRN::NodoRN(int id, string nombre, string descripcion, int costo) {
    idTratamiento = id;
    nombre = nombre;
    descripcion = descripcion;
    costo = costo;

    color = true; // Todo nodo nuevo inicia en rojo
    padre = nullptr;
    Hizq = nullptr;
    Hder = nullptr;
}