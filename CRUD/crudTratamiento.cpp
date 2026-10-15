#include <iostream>
#include <string>
#include "crud.h"

using namespace std;
BinarioRN arbolTratamientos;

void insertarTratamiento(){
    int codTratamiento;
    string nombre;
    string descripcion;
    int costo;

    cout << "Codigo del tratamiento: ";
    cin >> codTratamiento;
    cin.ignore();
    if (arbolTratamientos.Buscarvalor(codTratamiento)) {
        cout << "El tratamiento ya existe." << endl;
        return;
    }

    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Descripcion: ";
    getline(cin, descripcion);
    cout << "Costo: ";
    cin >> costo;
    arbolTratamientos.InsertaNodo(codTratamiento, 0, nombre, descripcion, costo);
    cout << "Tratamiento insertado correctamente." << endl;
}

void buscarTratamiento()
{
    int codTratamiento;

    cout << "Digite el codigo del tratamiento: ";
    cin >> codTratamiento;

    if (arbolTratamientos.Buscarvalor(codTratamiento)) {
        cout << "Tratamiento encontrado:" << endl;
        arbolTratamientos.mostrarPorClave(codTratamiento);
    }
    else {
        cout << "El tratamiento no existe." << endl;
    }
}