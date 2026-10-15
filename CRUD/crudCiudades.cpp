#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

// Arbol de ciudades.
ABBusqueda arbolCiudades(TipoClave::Ciudad);

void insertarCiudad()
{
    int codPais;
    int codCiudad;
    string nombre;
    cout << "Codigo del pais: ";
    cin >> codPais; //pedimos datos
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    cin.ignore(); //ignora el enter pendiente
    cout << "Nombre: ";
    getline(cin, nombre);
    if (!arbolPaises.Buscarvalor(codPais)) { //Revisa que el pais exista
        cout << "El pais no existe." << endl;
    }
    else if (arbolCiudades.Buscarvalor(codPais, codCiudad)) { //Revisa que no sea repetida
        cout << "La ciudad ya existe." << endl;
    }
    else {
        arbolCiudades.InsertaNodo(codPais, codCiudad, nombre);
        cout << "Ciudad insertada correctamente." << endl;
    }
}

void buscarCiudad() {
    int codPais;
    int codCiudad;
    cout << "Digite el codigo del pais: ";
    cin >> codPais;
    cout << "Digite el codigo de la ciudad: ";
    cin >> codCiudad;
    if (!arbolPaises.Buscarvalor(codPais)) {
        cout << "El pais no existe." << endl;
    }
    else if (arbolCiudades.Buscarvalor(codPais, codCiudad)) {
        cout << "Ciudad encontrada: ";
        arbolCiudades.mostrarPorClave(codPais, codCiudad);
    }
    else {
        cout << "La ciudad no existe." << endl;
    }
}