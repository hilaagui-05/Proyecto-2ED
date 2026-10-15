#include "arbolRN.h"
#include <iostream>
using namespace std;


//Constructor
BinarioRN::BinarioRN()
{
    raiz = nullptr;
}

//Destructor
BinarioRN::~BinarioRN()
{
    LiberarMemoria(raiz);
}

//insertar tratamiento
void BinarioRN::Insertar(int idTratamiento, string nombre, string descripcion, int costo)
{
    pNodoRN nuevo = new NodoRN(idTratamiento, nombre, descripcion, costo);
    InsertarRN(nuevo);
    ArreglaInsercion(nuevo);
}

//Insercion 
void BinarioRN::InsertarRN(pNodoRN nodo)
{
    pNodoRN actual = raiz;
    pNodoRN padre = nullptr;

	// Encuentra la posición correcta para el nuevo nodo
    while (actual != nullptr){
        padre = actual;
        if (nodo-> idTratamiento < actual->idTratamiento)
            actual = actual->Hizq;
        else
            actual = actual->Hder;
    }

    nodo->padre = padre; 
    if (padre == nullptr) {
        raiz = nodo;
    }
    else if (nodo->idTratamiento < padre->idTratamiento) {
        padre->Hizq = nodo;
    }
    else { 
        padre->Hder = nodo; 
    }
}

//arregla propiedades del arbolRN
void BinarioRN::ArreglaInsercion(pNodoRN nodo){
    while (nodo != raiz && nodo->padre != nullptr && nodo->padre->color == true)
    {
        pNodoRN padre = nodo->padre;
        pNodoRN abuelo = padre->padre;

        if (abuelo == nullptr)
            break;

        pNodoRN tio;
        bool padreEsIzquierdo;

        if (abuelo->Hizq == padre)
        {
            padreEsIzquierdo = true;
            tio = abuelo->Hder;
        }
        else
        {
            padreEsIzquierdo = false;
            tio = abuelo->Hizq;
        }

        if (tio != nullptr && tio->color == true){
            cout << "Caso 1: tio rojo, recoloreando" << endl;
            cout << endl;
            padre->color = false;
            tio->color = false;
            abuelo->color = true;
            nodo = abuelo;
        }
        else{
            if (padreEsIzquierdo)
            {
                if (nodo == padre->Hder){
                    cout << "Caso 2: nodo es hijo derecho, rotar izquierda en padre" << endl;
                    cout << endl;
                    nodo = padre;
                    RotIzquierda(nodo);
                    padre = nodo->padre;
                    if (padre){
                        abuelo = padre->padre;
                    }else{
                        abuelo = nullptr;
                    }
                }
                cout << "Caso 3: rotar derecha en abuelo" << endl;
                cout << endl;
                padre->color = false;
                if (abuelo) { 
                    abuelo->color = true; 
                }
                RotDerecha(abuelo);
            }
            else{
                if (nodo == padre->Hizq)
                {
                    cout << "Caso 2 espejo: nodo es hijo izquierdo, rotar derecha en padre" << endl;;
                    nodo = padre;
                    RotDerecha(nodo);
                    padre = nodo->padre;
                    if (padre != nullptr)
                    {
                        abuelo = padre->padre;
                    }
                    else{
                        abuelo = nullptr;
                    }
                }
                cout << "Caso 3 espejo: rotar izquierda en abuelo" << endl;
                padre->color = false;
                if (abuelo) {
                    abuelo->color = true;
                }
                RotIzquierda(abuelo);
            }
            break;
        }
    }
    raiz->color = false;
}

void BinarioRN::RotIzquierda(pNodoRN nodo)
{
    pNodoRN hijoDerecho = nodo->Hder;
    nodo->Hder = hijoDerecho->Hizq;

    if (hijoDerecho->Hizq != nullptr)
        hijoDerecho->Hizq->padre = nodo;

    hijoDerecho->padre = nodo->padre;

    if (nodo->padre == nullptr)
        raiz = hijoDerecho;
    else
        if (nodo == nodo->padre->Hizq)
            nodo->padre->Hizq = hijoDerecho;
        else
            nodo->padre->Hder = hijoDerecho;

    hijoDerecho->Hizq = nodo;
    nodo->padre = hijoDerecho;
}

void BinarioRN::RotDerecha(pNodoRN nodo)
{
    pNodoRN hijoIzquierdo = nodo->Hizq;
    nodo->Hizq = hijoIzquierdo->Hder;

    if (hijoIzquierdo->Hder != nullptr)
        hijoIzquierdo->Hder->padre = nodo;

    hijoIzquierdo->padre = nodo->padre;

    if (nodo->padre == nullptr)
        raiz = hijoIzquierdo;
    else
        if (nodo == nodo->padre->Hder)
            nodo->padre->Hder = hijoIzquierdo;
        else
            nodo->padre->Hizq = hijoIzquierdo;

    hijoIzquierdo->Hder = nodo;
    nodo->padre = hijoIzquierdo;
}

// Buscar tratamiento 
bool BinarioRN::Buscarvalor(int idTratamiento){
    pNodoRN actual = raiz;
    while (actual != nullptr){
        if (idTratamiento == actual->idTratamiento)
            return true;
        if (idTratamiento < actual->idTratamiento)
            actual = actual->Hizq;
        else
            actual = actual->Hder;
    }
    return false;
}

// Mostrar datos del tratamiento encontrado
void BinarioRN::mostrarPorClave(int idTratamiento)
{
    pNodoRN actual = raiz;
    while (actual != nullptr) {
        if (idTratamiento == actual->idTratamiento) {
            cout << "\nCodigo: " << actual->idTratamiento << endl;
            cout << "Nombre: " << actual->nombre << endl;
            cout << "Descripcion: " << actual->descripcion << endl;
            cout << "Costo: " << actual->costo << endl;
            return;
        }

        if (idTratamiento < actual->idTratamiento)
            actual = actual->Hizq;
        else
            actual = actual->Hder;
    }
    cout << "Tratamiento no encontrado." << endl;
}

// Mostrar arbol en preorden
void BinarioRN::Mostrar()
{
    if (EstaVacio())
    {
        cout << "Arbol vacio" << endl;
    }else{
        cout << "Arbol en preorden: ";
        MostrarPreorden(raiz);
        cout << endl;
    }
}

// Recorrido preorden
void BinarioRN::MostrarPreorden(pNodoRN nodo){
    if (nodo != nullptr){
        cout << nodo->valor << (nodo->color ? "(R) " : "(N) ");
        MostrarPreorden(nodo->Hizq);
        MostrarPreorden(nodo->Hder);
    }
}

// Recorrido inorden
void BinarioRN::MostrarInorden(pNodoRN nodo){
    if (nodo != nullptr){
        MostrarInorden(nodo->Hizq);
        cout << nodo->valor << (nodo->color ? "(R) " : "(N) ");
        MostrarInorden(nodo->Hder);
    }
}

bool BinarioRN::EstaVacio()
{
    return raiz == nullptr;
}

// Limpiar memoria
void BinarioRN::Limpiar()
{
    LiberarMemoria(raiz);
    raiz = nullptr;
}

// Liberar memoria de los nodos
void BinarioRN::LiberarMemoria(pNodoRN nodo)
{
    if (nodo != nullptr)
    {
        LiberarMemoria(nodo->Hizq);
        LiberarMemoria(nodo->Hder);
        delete nodo;
    }
}