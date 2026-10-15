#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

// Arbol de diagnosticos.
BinarioAA arbolDiagnosticos;

void insertarDiagnostico(){
    string codigo;
    string nombre;
    string descripcion;
    cout << "Codigo del diagnostico: ";
    cin >> codigo; //pedimos datos
    cin.ignore(); //ignora el enter pendiente
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Descripcion: ";
    getline(cin, descripcion);
    if (arbolDiagnosticos.Buscarvalor(codigo)) { //Revisa que no sea repetido
        cout << "El diagnostico ya existe." << endl;
    }
    else {
        arbolDiagnosticos.Insertar(codigo, nombre, descripcion);
        cout << "Diagnostico insertado correctamente." << endl;
    }
}

void buscarDiagnostico() {
    string codigo;
    cout << "Digite el codigo del diagnostico: ";
    cin >> codigo;
    if (arbolDiagnosticos.Buscarvalor(codigo)) {
        cout << "Diagnostico encontrado: " << endl;
        arbolDiagnosticos.mostrarPorCodigo(codigo);
    }
    else {
        cout << "El diagnostico no existe." << endl;
    }
}

// Muestra todos los diagnosticos.
void mostrarDiagnosticos()
{
    arbolDiagnosticos.mostrarPreorden();
}