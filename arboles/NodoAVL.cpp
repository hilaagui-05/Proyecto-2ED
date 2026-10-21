
#include "NodoAVL.h"

NodoAVL::NodoAVL(int categoria, int id)
{
    this->categoria = categoria;

    idHabitacion = 0;
    numero = 0;
    piso = "";
    tipo = 0;
    estado = 0;

    idCita = 0;
    idPaciente = 0;
    idMedico = 0;
    idEspecialidad = 0;
    fecha = "";
    hora = "";
    motivo = "";

    if (categoria == 1)
        idHabitacion = id;
    else
        idCita = id;

    FB = 0;
    Hizq = nullptr;
    Hder = nullptr;
}
