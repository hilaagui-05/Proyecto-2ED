#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

// Arbol de citas (AVL).
AVL arbolCitas;

void insertarCita() {
    int idCita;
    int idPaciente;
    int idMedico;
    int idEspecialidad;
    string fecha;
    string hora;
    string motivo;
    int estado;
    cout << "Id de la cita: ";
    cin >> idCita; //pedimos datos
    if (arbolCitas.BuscarValor(idCita)) { //Revisa que no sea repetido
        cout << "La cita ya existe." << endl;
        return;
    }
    cout << "Id del paciente: ";
    cin >> idPaciente;
    if (arbolPacientes.Buscar(idPaciente) == nullptr) { //que el paciente exista
        cout << "El paciente no existe." << endl;
        return;
    }
    cout << "Id del medico: ";
    cin >> idMedico;
    if (arbolMedicos.Buscar(idMedico) == nullptr) { //que el medico exista
        cout << "El medico no existe." << endl;
        return;
    }
    cout << "Id de la especialidad: ";
    cin >> idEspecialidad;
    cin.ignore(); //ignora el enter pendiente
    cout << "Fecha: ";
    getline(cin, fecha);
    cout << "Hora: ";
    getline(cin, hora);
    cout << "Motivo: ";
    getline(cin, motivo);
    cout << "Estado: ";
    cin >> estado;
    arbolCitas.Insertar(idCita, idPaciente, idMedico, idEspecialidad, fecha, hora, motivo, estado);
    cout << "Cita insertada correctamente." << endl;
}

void buscarCita() {
    int idPaciente;
    int idMedico;
    int idCita;
    cout << "Id del paciente: ";
    cin >> idPaciente;
    if (arbolPacientes.Buscar(idPaciente) == nullptr) {
        cout << "El paciente no existe." << endl;
        return;
    }
    cout << "Id del medico: ";
    cin >> idMedico;
    if (arbolMedicos.Buscar(idMedico) == nullptr) {
        cout << "El medico no existe." << endl;
        return;
    }
    cout << "Id de la cita: ";
    cin >> idCita;
    if (arbolCitas.BuscarValor(idCita)) {
        cout << "Cita encontrada: " << endl;
        arbolCitas.mostrarPorCodigo(idCita);
    }
    else {
        cout << "La cita no existe." << endl;
    }
}

// Muestra todas las citas.
void mostrarCitas()
{
    arbolCitas.Mostrar();
}
