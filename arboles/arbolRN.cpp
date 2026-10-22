#include "arbolRN.h"
#include <iostream>
using namespace std;


//Constructor
BinarioRN::BinarioRN()
{
    raiz = nullptr;
}

void BinarioRN::Insertar(int id, int paciente, int habitacion, int medico,
    string ingreso, string salida, string motivo)
{
    pNodoRN nuevo = new NodoRN(2, id);
    nuevo->idPaciente = paciente;
    nuevo->idHabitacion = habitacion;
    nuevo->idMedico = medico;
    nuevo->fechaIngreso = ingreso;
    nuevo->fechaSalida = salida;
    nuevo->motivo = motivo;
    InsertarRN(nuevo);
    ArreglaInsercion(nuevo);
}

//Destructor
BinarioRN::~BinarioRN()
{
    LiberarMemoria(raiz);
}

bool BinarioRN::menor(int categoria1, int id1,
    int categoria2, int id2)
{
    if (categoria1 != categoria2)
        return categoria1 < categoria2;

    return id1 < id2;
}

void BinarioRN::Insertar(int idTratamiento, string nombre, string descripcion, int costo)
{
    pNodoRN nuevo = new NodoRN(1, idTratamiento);
    nuevo->nombre = nombre;
    nuevo->descripcion = descripcion;
    nuevo->costo = costo;
    InsertarRN(nuevo);
    ArreglaInsercion(nuevo);
}

//Insercion 
void BinarioRN::InsertarRN(pNodoRN nodo)
{
    pNodoRN actual = raiz;
    pNodoRN padre = nullptr;

    // La llave es codigo en el arbol de tratamientos e idHospitalizacion en el de hospitalizaciones
    int idNuevo;
    if (nodo->categoria == 1)
        idNuevo = nodo->codigo;
    else
        idNuevo = nodo->idHospitalizacion;

	// Encuentra la posición correcta para el nuevo nodo
    while (actual != nullptr){
        padre = actual;
        int idActual;
        if (actual->categoria == 1)
            idActual = actual->codigo;
        else
            idActual = actual->idHospitalizacion;
        // Avanza hacia el hijo correspondiente (antes no avanzaba y el ciclo era infinito)
        if (idNuevo < idActual)
            actual = actual->Hizq;
        else
            actual = actual->Hder;
    }

    int idPadre = 0;
    if (padre != nullptr) {
        if (padre->categoria == 1)
            idPadre = padre->codigo;
        else
            idPadre = padre->idHospitalizacion;
    }

    nodo->padre = padre; 
    if (padre == nullptr) {
        raiz = nodo;
    }
    else if (idNuevo < idPadre) {
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
            padre->color = false;
            tio->color = false;
            abuelo->color = true;
            nodo = abuelo;
        }
        else{
            if (padreEsIzquierdo)
            {
                if (nodo == padre->Hder){
                    nodo = padre;
                    RotIzquierda(nodo);
                    padre = nodo->padre;
                    if (padre){
                        abuelo = padre->padre;
                    }else{
                        abuelo = nullptr;
                    }
                }
                padre->color = false;
                if (abuelo) { 
                    abuelo->color = true; 
                }
                RotDerecha(abuelo);
            }
            else{
                if (nodo == padre->Hizq)
                {
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
        // La llave es codigo (tratamientos) o idHospitalizacion (hospitalizaciones)
        int idActual = (actual->categoria == 1) ? actual->codigo : actual->idHospitalizacion;
        if (idTratamiento == idActual)
            return true;
        if (idTratamiento < idActual)
            actual = actual->Hizq;
        else
            actual = actual->Hder;
    }
    return false;
}

// Cambia nombre, descripcion y/o costo de un tratamiento. Devuelve false si no existe.
// Si nombre o descripcion son "" o el costo es -1, ese dato se deja igual.
bool BinarioRN::modificarTratamiento(int id, string nombre, string descripcion, int costo)
{
    pNodoRN actual = raiz;
    while (actual != nullptr){
        if (id == actual->codigo){
            if (!nombre.empty())
                actual->nombre = nombre;
            if (!descripcion.empty())
                actual->descripcion = descripcion;
            if (costo >= 0)
                actual->costo = costo;
            return true;
        }
        if (id < actual->codigo)
            actual = actual->Hizq;
        else
            actual = actual->Hder;
    }
    return false;
}

// Cambia el motivo de una hospitalizacion. Devuelve false si no existe.
bool BinarioRN::modificarHospitalizacion(int id, string nuevoMotivo)
{
    pNodoRN actual = raiz;
    while (actual != nullptr){
        if (id == actual->idHospitalizacion){
            actual->motivo = nuevoMotivo;
            return true;
        }
        if (id < actual->idHospitalizacion)
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
        // La llave es codigo (tratamientos) o idHospitalizacion (hospitalizaciones)
        int idActual = (actual->categoria == 1) ? actual->codigo : actual->idHospitalizacion;
        if (idTratamiento == idActual) {
            if (actual->categoria == 2) { //si es una hospitalizacion se muestra como tal
                cout << "\nId: " << actual->idHospitalizacion << endl;
                cout << "Paciente: " << actual->idPaciente << endl;
                cout << "Habitacion: " << actual->idHabitacion << endl;
                cout << "Medico: " << actual->idMedico << endl;
                cout << "Fecha de ingreso: " << actual->fechaIngreso << endl;
                cout << "Fecha de salida (0 si sigue hospitalizado): " << actual->fechaSalida << endl;
                cout << "Motivo: " << actual->motivo << endl;
                return;
            }
            cout << "\nCodigo: " << actual-> codigo << endl;
            cout << "Nombre: " << actual->nombre << endl;
            cout << "Descripcion: " << actual->descripcion << endl;
            cout << "Costo: " << actual->costo << endl;
            return;
        }

        if (idTratamiento < idActual)
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
        cout << ((nodo->categoria == 1) ? nodo->codigo : nodo->idHospitalizacion) << (nodo->color ? "(R) " : "(N) ");
        MostrarPreorden(nodo->Hizq);
        MostrarPreorden(nodo->Hder);
    }
}

// Recorrido inorden
void BinarioRN::MostrarInorden(pNodoRN nodo){
    if (nodo != nullptr){
        MostrarInorden(nodo->Hizq);
        cout << ((nodo->categoria == 1) ? nodo->codigo : nodo->idHospitalizacion) << (nodo->color ? "(R) " : "(N) ");
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