#ifndef NODOAVL_H
#define NODOAVL_H

#include <string>
using namespace std;

// Nodo del arbol AVL de habitaciones.
class NodoAVL
{
public:
    int idHabitacion;
    int numero;
    string piso;
    int tipo;
    int estado;
    int FB; // factor de balance: -1 (pesa la izquierda), 0, 1 (pesa la derecha)
    NodoAVL* Hizq;
    NodoAVL* Hder;

    NodoAVL(int idHabitacion, int numero, string piso, int tipo, int estado);
};

typedef NodoAVL* pNodoAVL;

#endif