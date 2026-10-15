#include <iostream>
#include "Binario.h"

using namespace std;

int main() {
    Binario arbol;

    // Insertar elementos
    arbol.Insertar(30);
    arbol.Insertar(20);
    arbol.Insertar(40);
    arbol.Insertar(10);
    arbol.Insertar(25);
    arbol.Insertar(35);
    arbol.Insertar(50);

    cout << "Arbol despues de insertar elementos:" << endl;
    arbol.Mostrar();  // Inorden

    // Eliminar un elemento
    cout << "\nEliminando el nodo con valor 20..." << endl;
    arbol.Eliminar(20);

    cout << "Arbol despues de eliminar 20:" << endl;
    arbol.Mostrar();

    // Eliminar otro
  /*  cout << "\nEliminando el nodo con valor 30..." << endl;
    arbol.Eliminar(30);

    cout << "Arbol despues de eliminar 30:" << endl;
    arbol.Mostrar();*/

    return 0;
}

