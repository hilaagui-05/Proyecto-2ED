#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

// Arbol de habitaciones (AVL).
AVL arbolHabitaciones;

void insertarHabitacion(){
    int id;
    int numero;
    string piso;
    int tipo;
    int estado;
    cout << "Id de la habitacion: ";
    cin >> id; //pedimos datos
    cout << "Numero: ";
    cin >> numero;
    cin.ignore(); //ignora el enter pendiente
    cout << "Piso: ";
    getline(cin, piso);
    cout << "Tipo (1 individual, 2 compartida, 3 UCI): ";
    cin >> tipo;
    cout << "Estado (0 disponible, 1 ocupada): ";
    cin >> estado;
    if (arbolHabitaciones.Buscarvalor(id)) { //Revisa que no sea repetido
        cout << "La habitacion ya existe." << endl;
    }
    else {
        arbolHabitaciones.Insertar(id, numero, piso, tipo, estado);
        cout << "Habitacion insertada correctamente." << endl;
    }
}

void buscarHabitacion() {
    int id;
    cout << "Digite el id de la habitacion: ";
    cin >> id;
    if (arbolHabitaciones.Buscarvalor(id)) {
        cout << "Habitacion encontrada: ";
        arbolHabitaciones.mostrarPorCodigo(id);
    }
    else {
        cout << "La habitacion no existe." << endl;
    }
}

// Muestra todas las habitaciones.
void mostrarHabitaciones()
{
    arbolHabitaciones.Mostrar();
}