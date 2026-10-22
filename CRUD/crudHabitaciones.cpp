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
    if (arbolHabitaciones.BuscarValor(id)) { //Revisa que no sea repetido
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
    if (arbolHabitaciones.BuscarValor(id)) {
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

// se valida que el id exista y se puede modificar el estado.
void modificarHabitacion(){
    int id;
    string textoEstado;
    cout << "Digite el id de la habitacion: ";
    cin >> id;
    cin.ignore(); //ignora el enter pendiente
    if (!arbolHabitaciones.BuscarValor(id)){ //que la habitacion exista
        cout << "La habitacion no existe." << endl;
        return;
    }
    cout << "Datos actuales: ";
    arbolHabitaciones.mostrarPorCodigo(id);
    bool estadoValido = false;
    while (!estadoValido){
        cout << "Nuevo estado (0 disponible, 1 ocupada, Enter para dejarlo igual): ";
        getline(cin, textoEstado);
        if (textoEstado.empty()){
            cout << "No se hicieron cambios." << endl;
            return;
        }
        if (textoEstado == "0" || textoEstado == "1"){
            estadoValido = true;
        }
        else{
            cout << "Estado no valido, digite 0 o 1." << endl;
        }
    }
    arbolHabitaciones.modificarEstadoHabitacion(id, stoi(textoEstado));
    cout << "Habitacion modificada correctamente." << endl;
    cout << "Datos nuevos: ";
    arbolHabitaciones.mostrarPorCodigo(id);
}
