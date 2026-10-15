#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

// Arbol de ciudades (clave compuesta: codPais + codCiudad).
ABBusqueda arbolCiudades(TipoClave::Ciudad);

void insertarCiudad()
{
    int codPais;
    int codCiudad;
    string nombre;
    cout << "Codigo del pais: ";
    cin >> codPais;
    if (!arbolPaises.Buscarvalor(codPais))
    {
        cout << "El pais no existe." << endl;
        return;
    }
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    if (arbolCiudades.Buscarvalor(codPais, codCiudad))
    {
        cout << "La ciudad ya existe en ese pais." << endl;
        return;
    }
    cin.ignore();
    cout << "Nombre de la ciudad: ";
    getline(cin, nombre);
    if (nombre.empty())
    {
        cout << "El nombre no puede estar vacio." << endl;
        return;
    }
    arbolCiudades.InsertaNodo(codPais, codCiudad, nombre);
    cout << "Ciudad insertada correctamente." << endl;
}

void buscarCiudad()
{
    int codPais;
    int codCiudad;
    cout << "Digite el codigo del pais: ";
    cin >> codPais;
    if (!arbolPaises.Buscarvalor(codPais))
    {
        cout << "El pais no existe." << endl;
        return;
    }
    cout << "Digite el codigo de la ciudad: ";
    cin >> codCiudad;
    if (arbolCiudades.Buscarvalor(codPais, codCiudad))
    {
        cout << "Ciudad encontrada: ";
        arbolCiudades.mostrarPorClave(codPais, codCiudad);
    }
    else
    {
        cout << "La ciudad no existe en ese pais." << endl;
    }
}