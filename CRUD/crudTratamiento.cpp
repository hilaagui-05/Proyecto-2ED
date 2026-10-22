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
    arbolTratamientos.Insertar(codTratamiento, nombre, descripcion, costo);
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

// Revisa que el texto tenga solo digitos (maximo 9 para que quepa en un int).
bool soloDigitos(string texto)
{
    if (texto.empty() || texto.length() > 9) // || es o en cpp
    {
        return false;
    }
    for (int i = 0; i < (int)texto.length(); i++)
    {
        if (texto[i] < '0' || texto[i] > '9')
        {
            return false;
        }
    }
    return true;
}

// se valida que el id exista y se puede modificar el nombre, la descripcion y/o el costo.
void modificarTratamiento()
{
    int codTratamiento;
    string nombre;
    string descripcion;
    string textoCosto;
    int costo = -1; //-1 significa dejar el costo igual

    cout << "Digite el codigo del tratamiento: ";
    cin >> codTratamiento;
    cin.ignore(); //ignora el enter pendiente
    if (!arbolTratamientos.Buscarvalor(codTratamiento)) { //que el tratamiento exista
        cout << "El tratamiento no existe." << endl;
        return;
    }
    cout << "Datos actuales:";
    arbolTratamientos.mostrarPorClave(codTratamiento);
    cout << "Nuevo nombre (Enter para dejarlo igual): ";
    getline(cin, nombre);
    cout << "Nueva descripcion (Enter para dejarla igual): ";
    getline(cin, descripcion);
    bool costoValido = false;
    while (!costoValido) {
        cout << "Nuevo costo (Enter para dejarlo igual): ";
        getline(cin, textoCosto);
        if (textoCosto.empty()) {
            costoValido = true;
        }
        else if (soloDigitos(textoCosto)) {
            costo = stoi(textoCosto);
            costoValido = true;
        }
        else {
            cout << "Costo no valido, digite solo numeros." << endl;
        }
    }
    if (nombre.empty() && descripcion.empty() && costo == -1) {
        cout << "No se hicieron cambios." << endl;
        return;
    }
    arbolTratamientos.modificarTratamiento(codTratamiento, nombre, descripcion, costo);
    cout << "Tratamiento modificado correctamente." << endl;
    cout << "Datos nuevos:";
    arbolTratamientos.mostrarPorClave(codTratamiento);
}