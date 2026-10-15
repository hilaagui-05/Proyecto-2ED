#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //permite separar los campos de cada linea
#include "hpdf.h"

using namespace std;

class NodoEspecialidad //lista doble circular
{
public:
    int idEspecialidad;
    string nombre;
    string descripcion;
    NodoEspecialidad* anterior;
    NodoEspecialidad* siguiente;

    NodoEspecialidad(int id, string nombreEspecialidad, string desc)
    {
        idEspecialidad = id;
        nombre = nombreEspecialidad;
        descripcion = desc;
        anterior = NULL;
        siguiente = NULL;
    }
};

void insertarEspecialidad()
{
    int id;
    string nombre;
    string descripcion;
    cout << "Id de especialidad: ";
    cin >> id;
    cin.ignore();
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Descripcion: ";
    getline(cin, descripcion);
    if (listaEspecialidades.existe(id))
    {
        cout << "La especialidad ya existe" << endl;
    }
    else
    {
        listaEspecialidades.insertar(id, nombre, descripcion);
        cout << "Especialidad insertada correctamente" << endl;
    }
}

void buscarEspecialidad() {
    int idEspecialidad;

    cout << "Id de la Especialidad: ";
    cin >> idEspecialidad;
    if (listaEspecialidades.existe(idEspecialidad)) {
        NodoEspecialidad* especialidadEncontrada = listaEspecialidades.buscar(idEspecialidad);
        listaEspecialidades.mostrar(especialidadEncontrada);
    }
    else {
        cout << "La especialidad no existe." << endl;
    }
}

void modificarEspecialidad()
{
    int idEspecialidad;
    string descripcion;
    cout << "Id de especialidad: ";
    cin >> idEspecialidad;
    cin.ignore();
    NodoEspecialidad* especialidad = listaEspecialidades.buscar(idEspecialidad);
    if (especialidad == NULL)
    {
        cout << "La especialidad no existe." << endl;
        return;
    }
    cout << "Nueva descripcion: ";
    getline(cin, descripcion);
    especialidad->descripcion = descripcion; //actualiza descripcion
    cout << "Especialidad modificada correctamente." << endl;
}