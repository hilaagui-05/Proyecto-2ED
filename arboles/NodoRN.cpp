
#include "NodoRN.h"

NodoRN::NodoRN(int categoria, int id){
    this->categoria = categoria;

    codigo = 0;
    nombre = "";
    descripcion = "";
    costo = 0;

    idHospitalizacion = 0;
    idPaciente = 0;
    idHabitacion = 0;
    idMedico = 0;
    fechaIngreso = "";
    fechaSalida = "";
    motivo = "";

    if (categoria == 1)
        codigo = id;
    else
        idHospitalizacion = id;

    color = true;
    padre = nullptr;
    Hizq = nullptr;
    Hder = nullptr;
}
