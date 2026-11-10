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

// Devuelve la llave del nodo: codigo en el arbol de tratamientos e idHospitalizacion en el de hospitalizaciones.
int BinarioRN::claveDe(pNodoRN nodo)
{
    return (nodo->categoria == 1) ? nodo->codigo : nodo->idHospitalizacion;
}

// Metodo publico para eliminar. Devuelve false si el id no existe.
bool BinarioRN::Eliminar(int id)
{
    pNodoRN nodo = raiz;
    while (nodo != nullptr && claveDe(nodo) != id)
    {
        if (id < claveDe(nodo))
            nodo = nodo->Hizq;
        else
            nodo = nodo->Hder;
    }
    if (nodo == nullptr)
        return false;

    EliminarRN(nodo);
    return true;
}

void BinarioRN::EliminarRN(pNodoRN z)
{
    pNodoRN y = z;
    pNodoRN x;
    pNodoRN xPadre = nullptr;
    bool yOriginalColor = y->color;

    if (z->Hizq == nullptr)
    {
        x = z->Hder;
        xPadre = z->padre;
        Sustitucion(z, z->Hder);
    }
    else
        if (z->Hder == nullptr)
        {
            x = z->Hizq;
            xPadre = z->padre;
            Sustitucion(z, z->Hizq);
        }
        else
        {
            y = Minimo(z->Hder);
            yOriginalColor = y->color;
            x = y->Hder;
            xPadre = y->padre;

            if (y->padre == z)
            {
                xPadre = y;
                if (x != nullptr)
                    x->padre = y;
            }
            else
            {
                Sustitucion(y, y->Hder);
                y->Hder = z->Hder;
                if (y->Hder != nullptr)
                    y->Hder->padre = y;
            }

            Sustitucion(z, y);
            y->Hizq = z->Hizq;
            if (y->Hizq != nullptr)
                y->Hizq->padre = y;
            y->color = z->color;
        }

    delete z;

    if (!yOriginalColor)
    {
        // Si x es nullptr, crear un nodo centinela temporal
        if (x == nullptr)
        {
            pNodoRN centinela = new NodoRN(1, 0);
            centinela->color = false;
            centinela->padre = xPadre;
            centinela->Hizq = nullptr;
            centinela->Hder = nullptr;

            // Conectar el centinela al padre
            if (xPadre != nullptr)
            {
                if (xPadre->Hizq == nullptr)
                    xPadre->Hizq = centinela;
                else
                    xPadre->Hder = centinela;
            }

            ArreglaEliminacion(centinela);

            // Desconectar y eliminar el centinela
            if (xPadre != nullptr)
            {
                if (xPadre->Hizq == centinela)
                    xPadre->Hizq = nullptr;
                if (xPadre->Hder == centinela)
                    xPadre->Hder = nullptr;
            }

            delete centinela;
        }
        else
        {
            ArreglaEliminacion(x);
        }
    }
}

void BinarioRN::Sustitucion(pNodoRN u, pNodoRN v)
{
    if (u->padre == nullptr)
    {
        raiz = v;
    }
    else
        if (u == u->padre->Hizq)
        {
            u->padre->Hizq = v;
        }
        else
        {
            u->padre->Hder = v;
        }

    if (v != nullptr)
    {
        v->padre = u->padre;
    }
}

pNodoRN BinarioRN::Minimo(pNodoRN nodo)
{
    while (nodo->Hizq != nullptr)
    {
        nodo = nodo->Hizq;
    }
    return nodo;
}

void BinarioRN::ArreglaEliminacion(pNodoRN x)
{
    while (x != raiz && x->color == false)
    {
        if (x->padre == nullptr)
            break;

        if (x == x->padre->Hizq)
        {
            pNodoRN w = x->padre->Hder;

            // Caso 1: hermano es rojo
            if (w != nullptr && w->color == true)
            {
                w->color = false;
                x->padre->color = true;
                RotIzquierda(x->padre);
                w = x->padre->Hder;
            }

            if (w == nullptr)
            {
                x = x->padre;
                continue;
            }

            // Caso 2: hermano es negro y ambos hijos del hermano son negros
            if ((w->Hizq == nullptr || w->Hizq->color == false) && (w->Hder == nullptr || w->Hder->color == false))
            {
                w->color = true;
                x = x->padre;
            }
            else
            {
                // Caso 3: hermano es negro, hijo derecho del hermano es negro, hijo izquierdo es rojo
                if (w->Hder == nullptr || w->Hder->color == false)
                {
                    if (w->Hizq != nullptr)
                        w->Hizq->color = false;
                    w->color = true;
                    RotDerecha(w);
                    w = x->padre->Hder;
                }

                // Caso 4: hermano es negro, hijo derecho del hermano es rojo
                if (w != nullptr)
                {
                    w->color = x->padre->color;
                    x->padre->color = false;
                    if (w->Hder != nullptr)
                        w->Hder->color = false;
                    RotIzquierda(x->padre);
                }
                x = raiz;
            }
        }
        else
        {
            // Casos simetricos (x es hijo derecho)
            pNodoRN w = x->padre->Hizq;

            // Caso 1 simetrico
            if (w != nullptr && w->color == true)
            {
                w->color = false;
                x->padre->color = true;
                RotDerecha(x->padre);
                w = x->padre->Hizq;
            }

            if (w == nullptr)
            {
                x = x->padre;
                continue;
            }

            // Caso 2 simetrico
            if ((w->Hder == nullptr || w->Hder->color == false) && (w->Hizq == nullptr || w->Hizq->color == false))
            {
                w->color = true;
                x = x->padre;
            }
            else {
                // Caso 3 simetrico
                if (w->Hizq == nullptr || w->Hizq->color == false)
                {
                    if (w->Hder != nullptr)
                        w->Hder->color = false;
                    w->color = true;
                    RotIzquierda(w);
                    w = x->padre->Hizq;
                }

                // Caso 4 simetrico
                if (w != nullptr)
                {
                    w->color = x->padre->color;
                    x->padre->color = false;
                    if (w->Hizq != nullptr)
                        w->Hizq->color = false;
                    RotDerecha(x->padre);
                }
                x = raiz;
            }
        }
    }

    if (x != nullptr)
        x->color = false;
}

pNodoRN BinarioRN::obtenerRaiz()
{
    return raiz;
}