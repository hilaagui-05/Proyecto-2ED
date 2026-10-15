#include <iostream>
#include "BinarioAA.h"

int main() {
    BinarioAA arbol;

    arbol.insertar(10);
    arbol.insertar(20);
    arbol.insertar(30);
    arbol.insertar(15);
    arbol.insertar(25);
    arbol.insertar(5);
    arbol.insertar(1);

    arbol.mostrarPreorden();
    arbol.eliminar(30);
    arbol.mostrarPreorden();
    arbol.eliminar(10);
    arbol.mostrarPreorden();
    	
    

    return 0;
}

