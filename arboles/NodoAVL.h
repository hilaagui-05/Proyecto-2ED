
#ifndef NODOAVL_H
#define NODOAVL_H

#include <string>
using namespace std;

class NodoAVL
{
public:
    // Categoria: 1 = Habitacion, 2 = Cita
    int categoria;

    // Datos de habitacion
    int idHabitacion;
    int numero;
    string piso;
    int tipo;
    int estado;

    // Datos de cita
    int idCita;
    int idPaciente;
    int idMedico;
    int idEspecialidad;
    string fecha;
    string hora;
    string motivo;

    int FB;
    NodoAVL* Hizq;
    NodoAVL* Hder;

    NodoAVL(int categoria, int id);
};

typedef NodoAVL* pNodoAVL;

#endif
