#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

// Arbol de especialidades.
BinarioAA arbolEspecialidades;

void insertarEspecialidad()
{
    string codigo;
    string nombre;
    string descripcion;
    cout << "Id de la especialidad: ";
    cin >> codigo; //pedimos datos
    cin.ignore(); //ignora el enter pendiente
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Descripcion: ";
    getline(cin, descripcion);
    if (arbolEspecialidades.Buscarvalor(codigo)) { //Revisa que no sea repetido
        cout << "La especialidad ya existe." << endl;
    }
    else {
        arbolEspecialidades.Insertar(codigo, nombre, descripcion);
        cout << "Especialidad insertada correctamente." << endl;
    }
}

void buscarEspecialidad() {
    string codigo;
    cout << "Digite el id de la especialidad: ";
    cin >> codigo;
    if (arbolEspecialidades.Buscarvalor(codigo)) {
        cout << "Especialidad encontrada: " << endl;
        arbolEspecialidades.mostrarPorCodigo(codigo);
    }
    else {
        cout << "La especialidad no existe." << endl;
    }
}

// Muestra todas las especialidades.
void mostrarEspecialidades()
{
    arbolEspecialidades.mostrarPreorden();
}