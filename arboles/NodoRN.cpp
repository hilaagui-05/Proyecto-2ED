#include "NodoRN.h"

NodoRN::NodoRN(int id, string nombre, string descripcion, int costo) {
    codigo = id;
    this->nombre = nombre;
    this->descripcion = descripcion;
	this->costo = costo; //this indica modificar el atributo de la clase, no la variable local

    color = true; // Todo nodo nuevo inicia en rojo
    padre = nullptr;
    Hizq = nullptr;
    Hder = nullptr;
}