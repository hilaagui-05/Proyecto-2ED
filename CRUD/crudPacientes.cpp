#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

ArbolB arbolPacientes;

void insertarPaciente(){
    RegistroB paciente;
    int codPais, codCiudad;
    cout << "Id del paciente: ";
    cin >> paciente.clave;
    cin.ignore();
    if (arbolPacientes.Buscar(paciente.clave) != nullptr){ //que el paciente no exista
        cout << "El paciente ya existe." << endl;
        return;
    }
    cout << "Nombre: ";
    getline(cin, paciente.nombre);
    cout << "Fecha de nacimiento: ";
    getline(cin, paciente.fechaNacimiento);
    cout << "Telefono: ";
    getline(cin, paciente.telefono);
    cout << "Codigo del pais: ";
    cin >> codPais;
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    cin.ignore();
    if (!arbolCiudades.Buscarvalor(codPais, codCiudad)){
        cout << "La ciudad no existe para ese pais." << endl;
        return;
    }
    cout << "Correo: ";
    getline(cin, paciente.correo);
    paciente.codPais = codPais;
    paciente.codCiudad = codCiudad;
    arbolPacientes.Insertar(paciente);
    cout << "Paciente insertado correctamente." << endl;
}

// Buscar paciente
void buscarPaciente(){
    int idPaciente, codPais, codCiudad;
    cout << "Codigo del pais: ";
    cin >> codPais;
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    if (!arbolCiudades.Buscarvalor(codPais, codCiudad)){
        cout << "La ciudad no existe para ese pais." << endl;
        return;
    }

    cout << "Id del paciente: ";
    cin >> idPaciente;
    RegistroB* paciente = arbolPacientes.Buscar(idPaciente);
    if (paciente == nullptr ||
        paciente->codPais != codPais ||
        paciente->codCiudad != codCiudad)
    {
        cout << "No existe ese paciente en la ciudad indicada." << endl;
        return;
    }
    cout << "Id: " << paciente->clave << endl;
    cout << "Nombre: " << paciente->nombre << endl;
    cout << "Fecha de nacimiento: " << paciente->fechaNacimiento << endl;
    cout << "Telefono: " << paciente->telefono << endl;
    cout << "Codigo del pais: " << paciente->codPais << endl;
    cout << "Codigo de la ciudad: " << paciente->codCiudad << endl;
    cout << "Correo: " << paciente->correo << endl;
}

// Muestra todos los pacientes almacenados.
void mostrarPacientes()
{
    arbolPacientes.Imprimir();
}
