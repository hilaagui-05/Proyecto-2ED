#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

BinarioAA arbolDiagnosticos;

void insertarDiagnostico()
{
    string codigo;
    string nombre;
    string descripcion;
    cout << "Codigo del diagnostico: ";
    cin >> codigo;
    if (arbolDiagnosticos.buscar(codigo))
    {
        cout << "El diagnostico ya existe." << endl;
        return;
    }
    cin.ignore();
    cout << "Nombre del diagnostico: ";
    getline(cin, nombre);
    cout << "Descripcion del diagnostico: ";
    getline(cin, descripcion);
    if (nombre.empty() || descripcion.empty())
    {
        cout << "El nombre y la descripcion no pueden estar vacios." << endl;
        return;
    }
    arbolDiagnosticos.insertar(codigo, nombre, descripcion);
    cout << "Diagnostico insertado correctamente." << endl;
}

// Busca un diagnostico por su codigo.
void buscarDiagnostico()
{
    string codigo;
    cout << "Digite el codigo del diagnostico: ";
    cin >> codigo;
    arbolDiagnosticos.mostrarPorCodigo(codigo);
}
// Muestra todos los diagnosticos.
void mostrarDiagnosticos()
{
    arbolDiagnosticos.mostrarPreorden();
}