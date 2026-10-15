#include "ABBusqueda.h"
#include <iostream>

using namespace std;

int main() 
{
	
    ABBusqueda arbol;

    arbol.InsertaNodo(55);
    arbol.InsertaNodo(23);
    arbol.InsertaNodo(78);
    arbol.InsertaNodo(11);
    arbol.InsertaNodo(64);
    arbol.InsertaNodo(4);
    arbol.InsertaNodo(91);
    arbol.InsertaNodo(37);
    arbol.InsertaNodo(16);
    arbol.InsertaNodo(72);

    cout << "Recorrido en Preorden: ";
    arbol.PreordenR();
    
    cout << "Recorrido en Inorden: ";
    arbol.InordenR();
    
   cout << "Recorrido en Postorden: ";
    arbol.PostordenR();
    
   /* cout << "\nRecorrido Preorden iterativo:\n";
    arbol.preordenI();

    cout << "\n\nRecorrido Inorden iterativo:\n";
    arbol.inordenI();

    cout << "\n\nRecorrido Postorden iterativo:\n";
    arbol.postordenI();*/

    
    

  /*  cout << "Existe el 40 " << (arbol.Buscarvalor(40) ? "Si" : "No") << endl;
    cout << "Existe el 100 " << (arbol.Buscarvalor(100) ? "Si" : "No") << endl;*/
    
    cout << "Recorrido en anchura (por niveles): ";
    arbol.recorridoPorNiveles();

    cout << "Eliminando 200..." << endl;
    arbol.EliminarNodo(200);
    cout << "Recorrido en Preorden: ";
    arbol.PreordenR();

    

    return 0;
}
