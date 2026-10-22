#include "AVL.h"
#include <iostream>
using namespace std;

// Constructor
AVL::AVL()
{
    raiz = nullptr;
}

void AVL::Insertar(int id, int paciente, int medico, int especialidad,
    string fecha, string hora, string motivo, int estado)
{
    InsertarCita(id, paciente, medico, especialidad, fecha, hora, motivo, estado);
}

// Destructor
AVL::~AVL()
{
    LiberarMemoria(raiz);
}

//ordena primero las habitaciones y luego las citas
bool AVL::menor(int categoria1, int id1,
    int categoria2, int id2)
{
    if (categoria1 != categoria2)
        return categoria1 < categoria2;

    return id1 < id2;
}

// Metodo publico para insertar 
void AVL::Insertar(int id, int numero, string piso, int tipo, int estado)
{
    bool Hh = false;
    InsertarBalanceado(raiz, Hh, 1, id, numero, piso, tipo, estado, 0, 0, 0, "", "", "");
}

void AVL::InsertarCita(int id, int paciente, int medico,
    int especialidad, string fecha,
    string hora, string motivo, int estado)
{
    bool Hh = false;
    InsertarBalanceado(raiz, Hh, 2, id, 0, "", 0, estado,
        paciente, medico, especialidad, fecha, hora, motivo);
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
        if (nodo->categoria == 2){ //si es una cita se muestra como cita
            mostrarCita(id);
            return;
        }
        string tipo;
        string estado;
        switch (nodo->tipo){
        case 1:
            tipo = "Individual";
            break;
        case 2:
            tipo = "Compartida";
            break;
        case 3:
            tipo = "UCI";
            break;
        default:
            tipo = "Desconocido";
            break;
        }

        switch (nodo->estado){
        case 0:
            estado = "Disponible";
            break;
        case 1:
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

// Muestra los datos de una cita (no imprime nada si no existe).
void AVL::mostrarCita(int id){
    pNodoAVL nodo = buscarNodo(raiz, id);
    if (nodo != nullptr && nodo->categoria == 2){
        string estado;
        if (nodo->estado == 0){
            estado = "Pendiente";
        }
        else if (nodo->estado == 1){
            estado = "Confirmada";
        }
        else{
            estado = "Desconocido";
        }
        cout << "Id: " << nodo->idCita
            << " ,Paciente: " << nodo->idPaciente
            << " ,Medico: " << nodo->idMedico
            << " ,Especialidad: " << nodo->idEspecialidad
            << " ,Fecha: " << nodo->fecha
            << " ,Hora: " << nodo->hora
            << " ,Motivo: " << nodo->motivo
            << " ,Estado: " << estado << endl;
    }
}

// Cambia el estado de una habitacion. Devuelve false si no existe.
bool AVL::modificarEstadoHabitacion(int id, int nuevoEstado){
    pNodoAVL nodo = buscarNodo(raiz, id);
    if (nodo == nullptr || nodo->categoria != 1){
        return false;
    }
    nodo->estado = nuevoEstado;
    return true;
}

// Modifica el motivo y/o el estado de una cita. Devuelve false si no existe.
// Si nuevoMotivo es "" o nuevoEstado es -1, ese dato se deja igual.
bool AVL::modificarCita(int id, string nuevoMotivo, int nuevoEstado){
    pNodoAVL nodo = buscarNodo(raiz, id);
    if (nodo == nullptr || nodo->categoria != 2){
        return false;
    }
    if (!nuevoMotivo.empty()){
        nodo->motivo = nuevoMotivo;
    }
    if (nuevoEstado == 0 || nuevoEstado == 1){
        nodo->estado = nuevoEstado;
    }
    return true;
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

    // La llave es idHabitacion en el arbol de habitaciones e idCita en el de citas.
    int idNodo = (n->categoria == 1) ? n->idHabitacion : n->idCita;
    if (id == idNodo){
        return n;
    }
    else if (id < idNodo)
    {
        return buscarNodo(n->Hizq, id);
    }else{
        return buscarNodo(n->Hder, id);
    }
}

// InsertarBalanceado
void AVL::InsertarBalanceado(
    pNodoAVL& raiz, bool& Hh,int categoria, int id, int numero, string piso,
    int tipo, int estado, int paciente, int medico, int especialidad, string fecha, string hora, string motivo){
    pNodoAVL n1;
    if (raiz == nullptr)
    {
        raiz = new NodoAVL(categoria, id);
        raiz->numero = numero;
        raiz->piso = piso;
        raiz->tipo = tipo;
        raiz->estado = estado;
        raiz->idPaciente = paciente;
        raiz->idMedico = medico;
        raiz->idEspecialidad = especialidad;
        raiz->fecha = fecha;
        raiz->hora = hora;
        raiz->motivo = motivo;
        Hh = true;
    }else{
        // La llave es idHabitacion en el arbol de habitaciones e idCita en el de citas.
        int idRaiz = (raiz->categoria == 1) ? raiz->idHabitacion : raiz->idCita;
        if (id < idRaiz){
            InsertarBalanceado(raiz->Hizq, Hh, categoria, id, numero, piso,
                tipo, estado, paciente, medico, especialidad, fecha, hora, motivo);
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
        else if (id > idRaiz)
        {
            InsertarBalanceado(raiz->Hder, Hh, categoria, id, numero, piso,
                tipo, estado, paciente, medico, especialidad, fecha, hora, motivo);
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
        if (n->categoria == 2){
            cout << "Id: " << n->idCita
                << " ,Paciente: " << n->idPaciente
                << " ,Medico: " << n->idMedico
                << " ,Especialidad: " << n->idEspecialidad
                << " ,Fecha: " << n->fecha
                << " ,Hora: " << n->hora
                << " ,Motivo: " << n->motivo
                << " ,Estado: " << n->estado << endl;
        }
        else{
            cout << "Id: " << n->idHabitacion
                << " ,Numero: " << n->numero
                << " ,Piso: " << n->piso
                << " ,Tipo: " << n->tipo
                << " ,Estado: " << n->estado << endl;
        }
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