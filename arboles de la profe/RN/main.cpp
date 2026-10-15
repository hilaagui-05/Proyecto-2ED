#include <iostream>
#include "BinarioRN.h"
using namespace std;

int main() {
    BinarioRN arbol;

    // Insertar valores
    arbol.Insertar(10);
   // arbol.Mostrar();
    arbol.Insertar(20);
    //arbol.Mostrar();
    arbol.Insertar(30);
    //arbol.Mostrar();
    arbol.Insertar(40);
  //  arbol.Mostrar();
   arbol.Insertar(35);
    arbol.Mostrar();
    /*arbol.Insertar(90);
    //arbol.Mostrar();
    arbol.Insertar(100);
    //arbol.Mostrar();
    arbol.Insertar(2);
    //arbol.Mostrar();
    arbol.Insertar(1);
    arbol.Mostrar();
   // arbol.Insertar(37);
   // arbol.Mostrar();
*/
  //  cout << "Arbol despues de inserciones:" << endl;
   // arbol.Mostrar();

  /*  // Eliminar un nodo hoja
    cout << "\nEliminando 100 (nodo hoja):" << endl;
    arbol.Eliminar(100); //20 2  1 10 35 30 90 40
    arbol.Mostrar();*/

 /*   // Eliminar nodo con un hijo
   cout << "\nEliminando 40 (nodo con un hijo):" << endl;
    arbol.Eliminar(40);
    arbol.Mostrar(); //20 2 1 10 35 30 90 37 100*/

    // Eliminar nodo con dos hijos
  //  cout << "\nEliminando 20 (nodo con dos hijos):" << endl;
   // arbol.Eliminar(20);
    //arbol.Mostrar();

   /* // Limpiar árbol
    cout << "\nLimpiando árbol completo..." << endl;
    arbol.Limpiar();
    arbol.Mostrar();*/

    return 0;
}

