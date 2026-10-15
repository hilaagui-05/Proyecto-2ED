#include "AVL.h"
#include <iostream>
using namespace std;

// Constructor
AVL::AVL()
{
    raiz = nullptr;
}

// Destructor
AVL::~AVL()
{
    LiberarMemoria(raiz);
}

// Metodo publico para insertar (si el id ya existe no hace nada)
void AVL::Insertar(int id, int numero, string piso, int tipo, int estado)
{
    bool Hh = false;
    InsertarBalanceado(raiz, Hh, id, numero, piso, tipo, estado);
}

// Busca un id de habitacion
bool AVL::BuscarValor(int id)
{
    return buscarNodo(raiz, id) != nullptr;
}

// Muestra los datos de una habitacion (no imprime nada si no existe);.
void AVL::mostrarPorCodigo(int id){
    pNodoAVL nodo = buscarNodo(raiz, id);
    if (nodo != nullptr){
        string tipo;
        string estado;
        switch (nodo->tipo){
        case 1:
            tipo = "UCI";
            break;
        case 2:
            tipo = "Individual";
            break;
        default:
            tipo = "Desconocido";
            break;
        }

        switch (nodo->estado){
        case 1:
            estado = "Disponible";
            break;
        case 2:
            estado = "Ocupada";
            break;
        default:
            estado = "Desconocido";
            break;
        }
        cout << "Id: " << nodo->idHabitacion
            << " ,Numero: " << nodo->numero
            << " ,Piso: " << nodo->piso
            << " ,Tipo: " << tipo
            << " ,Estado: " << estado << endl;
    }
}

// Metodo publico para mostrar el arbol en Inorden
void AVL::Mostrar()
{
    if (EstaVacio())
    {
        cout << "El arbol esta vacio." << endl;
    }
    else
    {
        MostrarInorden(raiz);
    }
}

// Verificar si esta vacio
bool AVL::EstaVacio()
{
    return raiz == nullptr;
}

// Limpiar arbol
void AVL::Limpiar()
{
    LiberarMemoria(raiz);
    raiz = nullptr;
}

pNodoAVL AVL::buscarNodo(pNodoAVL n, int id){
    if (n == nullptr)
    {
        return nullptr;
    }

    if (id == n->idHabitacion){
        return n;
    }
    else if (id < n->idHabitacion)
    {
        return buscarNodo(n->Hizq, id);
    }else{
        return buscarNodo(n->Hder, id);
    }
}

// InsertarBalanceado
void AVL::InsertarBalanceado(pNodoAVL& raiz, bool& Hh, int id, int numero, string piso, int tipo, int estado){
    pNodoAVL n1;
    if (raiz == nullptr)
    {
        raiz = new NodoAVL(id, numero, piso, tipo, estado);
        Hh = true;
    }else{
        if (id < raiz->idHabitacion){
            InsertarBalanceado(raiz->Hizq, Hh, id, numero, piso, tipo, estado);
            if (Hh){
                switch (raiz->FB)
                {
                case 1:
                    raiz->FB = 0;
                    Hh = false;
                    break;
                case 0:
                    raiz->FB = -1;
                    break;
                case -1:
                    n1 = raiz->Hizq;
                    if (n1->FB == -1)
                    {
                        RotacionSimpleIzquierda(raiz, n1);
                    }
                    else{
                        RotacionDobleIzquierda(raiz, n1);
                    }
                    Hh = false;
                    break;
                }
            }
        }
        else if (id > raiz->idHabitacion)
        {
            InsertarBalanceado(raiz->Hder, Hh, id, numero, piso, tipo, estado);
            if (Hh){
                switch (raiz->FB)
                {
                case -1:
                    raiz->FB = 0;
                    Hh = false;
                    break;
                case 0:
                    raiz->FB = 1;
                    break;
                case 1:
                    n1 = raiz->Hder;
                    if (n1->FB == 1)
                    {
                        RotacionSimpleDerecha(raiz, n1);
                    }else{
                        RotacionDobleDerecha(raiz, n1);
                    }
                    Hh = false;
                    break;
                }
            }
        }
    }
}

// RotacionDobleIzquierda
void AVL::RotacionDobleIzquierda(pNodoAVL& n, pNodoAVL& n1){
    pNodoAVL n2;
    n2 = n1->Hder;
    n->Hizq = n2->Hder;
    n2->Hder = n;
    n1->Hder = n2->Hizq;
    n2->Hizq = n1;

    if (n2->FB == 1)
    {
        n1->FB = -1;
    }else{
        n1->FB = 0;
    }

    if (n2->FB == -1)
    {
        n->FB = 1;
    }else{
        n->FB = 0;
    }

    n2->FB = 0;
    n = n2;
}

// RotacionDobleDerecha
void AVL::RotacionDobleDerecha(pNodoAVL& n, pNodoAVL& n1)
{
    pNodoAVL n2;
    n2 = n1->Hizq;
    n->Hder = n2->Hizq;
    n2->Hizq = n;
    n1->Hizq = n2->Hder;
    n2->Hder = n1;

    if (n2->FB == 1)
    {
        n->FB = -1;
    }else{
        n->FB = 0;
    }

    if (n2->FB == -1)
    {
        n1->FB = 1;
    }else{
        n1->FB = 0;
    }

    n2->FB = 0;
    n = n2;
}

// RotacionSimpleDerecha
void AVL::RotacionSimpleDerecha(pNodoAVL& n, pNodoAVL& n1)
{
    n->Hder = n1->Hizq;
    n1->Hizq = n;

    if (n1->FB == 1)
    {
        n->FB = 0;
        n1->FB = 0;
    }else{
        n->FB = 1;
        n1->FB = -1;
    }
    n = n1;
}

// RotacionSimpleIzquierda
void AVL::RotacionSimpleIzquierda(pNodoAVL& n, pNodoAVL& n1)
{
    n->Hizq = n1->Hder;
    n1->Hder = n;

    if (n1->FB == -1)
    {
        n->FB = 0;
        n1->FB = 0;
    }else{
        n->FB = -1;
        n1->FB = 1;
    }
    n = n1;
}

// Mostrar Arbol en Inorden
void AVL::MostrarInorden(pNodoAVL n)
{
    if (n != nullptr)
    {
        MostrarInorden(n->Hizq);
        cout << "Id: " << n->idHabitacion
            << " ,Numero: " << n->numero
            << " ,Piso: " << n->piso
            << " ,Tipo: " << n->tipo
            << " ,Estado: " << n->estado << endl;
        MostrarInorden(n->Hder);
    }
}

// Liberar memoria
void AVL::LiberarMemoria(pNodoAVL n){
    if (n != nullptr){
        LiberarMemoria(n->Hizq);
        LiberarMemoria(n->Hder);
        delete n;
    }
}