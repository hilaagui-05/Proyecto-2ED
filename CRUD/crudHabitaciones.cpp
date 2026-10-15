#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //permite separar los campos de cada linea
#include "hpdf.h"

using namespace std;

class NodoHabitacion 
{
public:
    int idHabitacion;
    int numero;
    int piso;
    int tipo;
    int estado;
    NodoHabitacion* anterior;
    NodoHabitacion* siguiente;

    NodoHabitacion(int id, int numeroHabitacion, int pisoHabitacion, int tipoHabitacion, int estadoHabitacion)
    {
        idHabitacion = id;
        numero = numeroHabitacion;
        piso = pisoHabitacion;
        tipo = tipoHabitacion;
        estado = estadoHabitacion;
        anterior = NULL;
        siguiente = NULL;
    }
};

void insertarHabitacion() {
    int idHabitacion;
    int numero;
    int piso;
    int tipo;
    int estado;

    cout << "Digite el Id de la habitacion: ";
    cin >> idHabitacion;

    if (listaHabitaciones.existe(idHabitacion)) { // valida que idhabitacion no este repetido
        cout << "La habitacion ya existe." << endl;
        return;
    }
    cout << "Digite el numero de la habitacion: ";
    cin >> numero;
    cout << "Digite el piso: ";
    cin >> piso;
    cin.ignore();
    cout << "Digite el tipo de habitacion: ";
    cin >> tipo;
    cout << "Digite el estado de la habitacion: ";
    cin >> estado;

    listaHabitaciones.insertar(idHabitacion, numero, piso, tipo, estado);
    cout << "HabitaciÃ³n insertada correctamente" << endl;
}

void buscarHabitacion() {
    int idHabitacion;

    cout << "Id de la Habitacion: ";
    cin >> idHabitacion;
    if (listaHabitaciones.existe(idHabitacion)) {
        NodoHabitacion* habitacionEncontrada = listaHabitaciones.buscar(idHabitacion);
        listaHabitaciones.mostrar(habitacionEncontrada);
    }
    else {
        cout << "La habitacion no existe." << endl;
    }
}

void modificarHabitacion()
{
    int idHabitacion;
    int estado;
    cout << "Id de la habitacion: ";
    cin >> idHabitacion;
    NodoHabitacion* habitacion = listaHabitaciones.buscar(idHabitacion);
    if (habitacion == NULL)
    {
        cout << "La habitacion no existe." << endl;
        return;
    }
    cout << "Nuevo estado: ";
    cin >> estado;
    habitacion->estado = estado; //actualiza estado
    cout << "Habitacion modificada correctamente." << endl;
}