#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

// Arbol de paises.
ABBusqueda arbolPaises(TipoClave::Pais);

void insertarPais()
{
    int codigo;
    string nombre;
    cout << "Codigo del pais: ";
    cin >> codigo; //pedimos datos
    cin.ignore(); //ignora el enter pendiente
    cout << "Nombre: ";
    getline(cin, nombre); //
    if (arbolPaises.Buscarvalor(codigo)){ //Revisa que no sea repetido
        cout << "El pais ya existe." << endl;
    }
    else{
        arbolPaises.InsertaNodo(codigo, 0, nombre);
        cout << "Pais insertado correctamente." << endl;
    }
}

void buscarPais(){
    int codPais;
    cout << "Digite el codigo del pais: ";
    cin >> codPais;
    if (arbolPaises.Buscarvalor(codPais)){
        cout << "Pais encontrado: ";
        arbolPaises.mostrarPorClave(codPais);
    }
    else{
        cout << "El pais no existe." << endl;
    }
}


