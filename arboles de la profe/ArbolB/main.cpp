#include <iostream>
#include "ArbolB.h"
using namespace std;

int main() {
    ArbolB arbol;

    // Insertar valores
    arbol.Insertar(2);
    arbol.Insertar(9);  
    arbol.Insertar(3);
    arbol.Insertar(75);
    arbol.Insertar(45);
    /*arbol.Insertar(90);
    arbol.Insertar(100);
    arbol.Insertar(2);
    arbol.Insertar(1);
	arbol.Insertar(99);    */

    arbol.Imprimir();

   /* cout << "\nEliminar 35...\n";
    arbol.Eliminar(35);
    arbol.Imprimir();

    cout << "\nEliminar 30...\n";
    arbol.Eliminar(30);
    arbol.Imprimir();
    arbol.Eliminar(100);
    arbol.Imprimir();*/

    return 0;
}

