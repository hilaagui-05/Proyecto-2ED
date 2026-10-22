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

// se valida que el codigo exista y se puede modificar la descripcion.
void modificarDiagnostico(){
    string codigo;
    string descripcion;
    cout << "Digite el codigo del diagnostico: ";
    cin >> codigo;
    cin.ignore(); //ignora el enter pendiente
    if (!arbolDiagnosticos.Buscarvalor(codigo)){ //que el diagnostico exista
        cout << "El diagnostico no existe." << endl;
        return;
    }
    cout << "Datos actuales: " << endl;
    arbolDiagnosticos.mostrarPorCodigo(codigo);
    cout << "Nueva descripcion (Enter para dejarla igual): ";
    getline(cin, descripcion);
    if (descripcion.empty()){
        cout << "No se hicieron cambios." << endl;
        return;
    }
    arbolDiagnosticos.modificarDescripcion(codigo, descripcion);
    cout << "Diagnostico modificado correctamente." << endl;
    cout << "Datos nuevos: " << endl;
    arbolDiagnosticos.mostrarPorCodigo(codigo);
}
