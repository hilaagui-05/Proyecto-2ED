
#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

ArbolB arbolMedicos;

void insertarMedico(){
    RegistroB medico;
    string idEspecialidad;
    cout << "Id del medico: ";
    cin >> medico.clave;
    cin.ignore();
    if (arbolMedicos.Buscar(medico.clave) != nullptr)
    {
        cout << "El medico ya existe." << endl;
        return;
    }
    cout << "Nombre: ";
    getline(cin, medico.nombre);
    cout << "Telefono: ";
    getline(cin, medico.telefono);
    cout << "Correo: ";
    getline(cin, medico.correo);
    cout << "Id de la especialidad: ";
    cin >> idEspecialidad;
    if (!arbolEspecialidades.Buscarvalor(idEspecialidad))
    {
        cout << "La especialidad no existe." << endl;
        return;
    }

    medico.idEspecialidad = stoi(idEspecialidad);
    arbolMedicos.Insertar(medico);
    cout << "Medico insertado correctamente." << endl;
}

void buscarMedico(){
    int idMedico;
    string idEspecialidad;
    cout << "Id de la especialidad: ";
    cin >> idEspecialidad;
    if (!arbolEspecialidades.Buscarvalor(idEspecialidad))
    {
        cout << "La especialidad no existe." << endl;
        return;
    }
    cout << "Id del medico: ";
    cin >> idMedico;
    RegistroB* medico = arbolMedicos.Buscar(idMedico);
    if (medico == nullptr ||
        medico->idEspecialidad != stoi(idEspecialidad))
    {
        cout << "No existe el medico en la especialidad." << endl;
        return;
    }
    cout << "\n--- Informacion del medico ---" << endl;
    cout << "Id: " << medico->clave << endl;
    cout << "Nombre: " << medico->nombre << endl;
    cout << "Telefono: " << medico->telefono << endl;
    cout << "Correo: " << medico->correo << endl;
    cout << "Id de la especialidad: " << medico->idEspecialidad << endl;
}

// Muestra todos los medicos almacenados.
void mostrarMedicos()
{
    arbolMedicos.Imprimir();
}
