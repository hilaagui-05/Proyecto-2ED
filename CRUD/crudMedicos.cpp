
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

// se valida que la especialidad exista y que el medico exista en ella
// se puede modificar el telefono y/o el correo
void modificarMedico(){
    int idMedico;
    string idEspecialidad;
    string telefono, correo;
    cout << "Id de la especialidad: ";
    cin >> idEspecialidad;
    if (!arbolEspecialidades.Buscarvalor(idEspecialidad)) //que la especialidad exista
    {
        cout << "La especialidad no existe." << endl;
        return;
    }
    cout << "Id del medico: ";
    cin >> idMedico;
    cin.ignore(); //ignora el enter pendiente
    RegistroB* medico = arbolMedicos.Buscar(idMedico);
    if (medico == nullptr ||
        medico->idEspecialidad != stoi(idEspecialidad))
    {
        cout << "No existe el medico en la especialidad." << endl;
        return;
    }
    cout << "Nombre: " << medico->nombre << endl;
    cout << "Telefono actual: " << medico->telefono << endl;
    cout << "Nuevo telefono (Enter para dejarlo igual): ";
    getline(cin, telefono);
    cout << "Correo actual: " << medico->correo << endl;
    cout << "Nuevo correo (Enter para dejarlo igual): ";
    getline(cin, correo);
    if (telefono.empty() && correo.empty()){
        cout << "No se hicieron cambios." << endl;
        return;
    }
    if (!telefono.empty()){
        medico->telefono = telefono; //se modifica directamente en el arbol B
    }
    if (!correo.empty()){
        medico->correo = correo;
    }
    cout << "Medico modificado correctamente." << endl;
    cout << "Telefono: " << medico->telefono << endl;
    cout << "Correo: " << medico->correo << endl;
}