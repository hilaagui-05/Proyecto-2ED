#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

// Arbol de hospitalizaciones (Rojo-Negro).
BinarioRN arbolHospitalizaciones;

void insertarHospitalizacion() {
    int idHospitalizacion;
    int idPaciente;
    int idHabitacion;
    int idMedico;
    string fechaIngreso;
    string fechaSalida;
    string motivo;
    cout << "Id de la hospitalizacion: ";
    cin >> idHospitalizacion; //pedimos datos
    if (arbolHospitalizaciones.Buscarvalor(idHospitalizacion)) { //Revisa que no sea repetido
        cout << "La hospitalizacion ya existe." << endl;
        return;
    }
    cout << "Id del paciente: ";
    cin >> idPaciente;
    if (arbolPacientes.Buscar(idPaciente) == nullptr) { //que el paciente exista
        cout << "El paciente no existe." << endl;
        return;
    }
    cout << "Id de la habitacion: ";
    cin >> idHabitacion;
    if (!arbolHabitaciones.BuscarValor(idHabitacion)) { //que la habitacion exista
        cout << "La habitacion no existe." << endl;
        return;
    }
    cout << "Id del medico: ";
    cin >> idMedico;
    cin.ignore(); //ignora el enter pendiente
    cout << "Fecha de ingreso: ";
    getline(cin, fechaIngreso);
    cout << "Fecha de salida (0 si sigue hospitalizado): ";
    getline(cin, fechaSalida);
    cout << "Motivo: ";
    getline(cin, motivo);
    arbolHospitalizaciones.Insertar(idHospitalizacion, idPaciente, idHabitacion, idMedico,
        fechaIngreso, fechaSalida, motivo);
    cout << "Hospitalizacion insertada correctamente." << endl;
}

void buscarHospitalizacion() {
    int idHospitalizacion;
    int idPaciente;
    int idHabitacion;
    cout << "Id del paciente: ";
    cin >> idPaciente;
    if (arbolPacientes.Buscar(idPaciente) == nullptr) {
        cout << "El paciente no existe." << endl;
        return;
    }
    cout << "Id de la habitacion: ";
    cin >> idHabitacion;
    if (!arbolHabitaciones.BuscarValor(idHabitacion)) {
        cout << "La habitacion no existe." << endl;
        return;
    }
    cout << "Id de la hospitalizacion: ";
    cin >> idHospitalizacion;
    if (arbolHospitalizaciones.Buscarvalor(idHospitalizacion)) {
        cout << "Hospitalizacion encontrada:" << endl;
        arbolHospitalizaciones.mostrarPorClave(idHospitalizacion);
    }
    else {
        cout << "La hospitalizacion no existe." << endl;
    }
}

// Muestra todas las hospitalizaciones.
void mostrarHospitalizaciones()
{
    arbolHospitalizaciones.Mostrar();
}

// se valida que el paciente, la habitacion y la hospitalizacion existan
// se puede modificar el motivo
void modificarHospitalizacion() {
    int idHospitalizacion;
    int idPaciente;
    int idHabitacion;
    string motivo;
    cout << "Id del paciente: ";
    cin >> idPaciente;
    if (arbolPacientes.Buscar(idPaciente) == nullptr) { //que el paciente exista
        cout << "El paciente no existe." << endl;
        return;
    }
    cout << "Id de la habitacion: ";
    cin >> idHabitacion;
    if (!arbolHabitaciones.BuscarValor(idHabitacion)) { //que la habitacion exista
        cout << "La habitacion no existe." << endl;
        return;
    }
    cout << "Id de la hospitalizacion: ";
    cin >> idHospitalizacion;
    cin.ignore(); //ignora el enter pendiente
    if (!arbolHospitalizaciones.Buscarvalor(idHospitalizacion)) { //que la hospitalizacion exista
        cout << "La hospitalizacion no existe." << endl;
        return;
    }
    cout << "Datos actuales:" << endl;
    arbolHospitalizaciones.mostrarPorClave(idHospitalizacion);
    cout << "Nuevo motivo (Enter para dejarlo igual): ";
    getline(cin, motivo);
    if (motivo.empty()) {
        cout << "No se hicieron cambios." << endl;
        return;
    }
    arbolHospitalizaciones.modificarHospitalizacion(idHospitalizacion, motivo);
    cout << "Hospitalizacion modificada correctamente." << endl;
    cout << "Datos nuevos:" << endl;
    arbolHospitalizaciones.mostrarPorClave(idHospitalizacion);
}

// Busca la primera hospitalizacion del paciente (modo 1) o de la habitacion (modo 2). Devuelve -1 si no hay.
int primeraHospitalizacion(pNodoRN nodo, int modo, int id)
{
    if (nodo == nullptr)
    {
        return -1;
    }
    int encontrada = primeraHospitalizacion(nodo->Hizq, modo, id);
    if (encontrada != -1)
    {
        return encontrada;
    }
    if (nodo->categoria == 2)
    {
        if ((modo == 1 && nodo->idPaciente == id) || (modo == 2 && nodo->idHabitacion == id))
        {
            return nodo->idHospitalizacion;
        }
    }
    return primeraHospitalizacion(nodo->Hder, modo, id);
}

// Borrado en cascada: elimina todas las hospitalizaciones de un paciente
void eliminarHospitalizacionesDePaciente(int idPaciente)
{
    int idHosp = primeraHospitalizacion(arbolHospitalizaciones.obtenerRaiz(), 1, idPaciente);
    while (idHosp != -1)
    {
        arbolHospitalizaciones.Eliminar(idHosp);
        idHosp = primeraHospitalizacion(arbolHospitalizaciones.obtenerRaiz(), 1, idPaciente);
    }
}

// Borrado en cascada: elimina todas las hospitalizaciones de una habitacion
void eliminarHospitalizacionesDeHabitacion(int idHabitacion)
{
    int idHosp = primeraHospitalizacion(arbolHospitalizaciones.obtenerRaiz(), 2, idHabitacion);
    while (idHosp != -1)
    {
        arbolHospitalizaciones.Eliminar(idHosp);
        idHosp = primeraHospitalizacion(arbolHospitalizaciones.obtenerRaiz(), 2, idHabitacion);
    }
}

// Se valida que el paciente y la habitacion existan y que la hospitalizacion exista, luego se elimina.
void eliminarHospitalizacion() {
    int idHospitalizacion;
    int idPaciente;
    int idHabitacion;
    cout << "Id del paciente: ";
    cin >> idPaciente;
    if (arbolPacientes.Buscar(idPaciente) == nullptr) {
        cout << "El paciente no existe." << endl;
        return;
    }
    cout << "Id de la habitacion: ";
    cin >> idHabitacion;
    if (!arbolHabitaciones.BuscarValor(idHabitacion)) {
        cout << "La habitacion no existe." << endl;
        return;
    }
    cout << "Id de la hospitalizacion: ";
    cin >> idHospitalizacion;
    if (!arbolHospitalizaciones.Buscarvalor(idHospitalizacion)) { //que la hospitalizacion exista
        cout << "La hospitalizacion no existe." << endl;
        return;
    }
    arbolHospitalizaciones.Eliminar(idHospitalizacion);
    cout << "Hospitalizacion eliminada correctamente." << endl;
}
