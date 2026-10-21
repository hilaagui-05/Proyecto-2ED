
#ifndef NODORN_H
#define NODORN_H

#include <string>
using namespace std;

class NodoRN
{
public:
    // Categoria: 1 = Tratamiento, 2 = Hospitalizacion
    int categoria;

    // Datos de tratamiento
    int codigo;
    string nombre;
    string descripcion;
    int costo;

    // Datos de hospitalizacion
    int idHospitalizacion;
    int idPaciente;
    int idHabitacion;
    int idMedico;
    string fechaIngreso;
    string fechaSalida;
    string motivo;

    bool color;
    NodoRN* padre;
    NodoRN* Hizq;
    NodoRN* Hder;

    NodoRN(int categoria, int id);
};

#endif
