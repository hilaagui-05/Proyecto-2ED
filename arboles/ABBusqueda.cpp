#include "ABBusqueda.h"
#include <iostream>
#include <fstream>

using namespace std;

//-----Cola---------
Cola::NodoCola::NodoCola(NodoABB* nodo){
    dato = nodo;
    siguiente = nullptr;
}

Cola::Cola(){
    frente = nullptr;
    final = nullptr;
}

Cola::~Cola(){
    while (!estaVacia()){
        desencolar();
    }
}

bool Cola::estaVacia() const{
    return frente == nullptr;
}

void Cola::encolar(NodoABB* nodo){
    NodoCola* nuevo = new NodoCola(nodo);
    if (estaVacia()){
        frente = nuevo;
        final = nuevo;
    }
    else{
        final->siguiente = nuevo;
        final = nuevo;
    }
}

NodoABB* Cola::desencolar(){
    if (estaVacia())
    {
        return nullptr;
    }
    NodoCola* temporal = frente;
    NodoABB* dato = temporal->dato;
    frente = frente->siguiente;
    if (frente == nullptr)
    {
        final = nullptr;
    }
    delete temporal;
    return dato;
}

//-----------Pila----------
Pila::NodoPila::NodoPila(NodoABB* nodo, NodoPila* siguiente){
    dato = nodo;
    this->siguiente = siguiente;
}

Pila::Pila(){
    tope = nullptr;
}

Pila::~Pila(){
    while (!vacia())
    {
        pop();
    }
}

void Pila::push(NodoABB* nodo){
    NodoPila* nuevo = new NodoPila(nodo, tope);
    tope = nuevo;
}

NodoABB* Pila::pop(){
    if (vacia())
    {
        return nullptr;
    }

    NodoPila* temporal = tope;
    NodoABB* dato = temporal->dato;

    tope = tope->siguiente;

    delete temporal;
    return dato;
}

bool Pila::vacia() const{
    return tope == nullptr;
}

//----------ARBOL BB---------------
// Constructor
ABBusqueda::ABBusqueda(TipoClave tipoClave)
{
    raiz = nullptr;
    this->tipoClave = tipoClave;
}

// Destructor
ABBusqueda::~ABBusqueda()
{
    destruirArbol(raiz);
}

// -----MÉTODOS PÚBLICOS-----
// Inserta un nodo en el arbol ya sea un pais o una ciudad.
void ABBusqueda::InsertaNodo(int codPais, int codCiudad, string nombre)
{
    if (raiz == nullptr){
        raiz = new NodoABB(codPais, codCiudad, nombre);
    }
    else {
        raiz = InsertaBinario(raiz, codPais, codCiudad, nombre);
    }
}

// Busca un pais por su codigo.
// Para ciudades se debe utilizar la busqueda con dos codigos.
bool ABBusqueda::Buscarvalor(int codigo){
    if (tipoClave == TipoClave::Pais)
    {
        return Buscarvalor(raiz, codigo, 0);
    }
    return false;
}

// Busca un pais o una ciudad segun el tipo de arbol.
bool ABBusqueda::Buscarvalor(int codPais, int codCiudad)
{
    return Buscarvalor(raiz, codPais, codCiudad);
}

// Recorrido inorden recursivo.
void ABBusqueda::InordenR()
{
    InordenR(raiz);
    cout << endl;
}

// Recorrido preorden recursivo.
void ABBusqueda::PreordenR()
{
    PreordenR(raiz);
    cout << endl;
}

// Recorrido postorden recursivo.
void ABBusqueda::PostordenR()
{
    PostordenR(raiz);
    cout << endl;
}

// Recorrido por niveles utilizando una cola.
void ABBusqueda::recorridoPorNiveles()
{
    if (raiz == nullptr)
    {
        cout << "El arbol esta vacio." << endl;
        return;
    }

    Cola cola;
    cola.encolar(raiz);

    while (!cola.estaVacia()){
        pnodo actual = cola.desencolar();
        mostrarDato(actual);
        cout << " | ";
        if (actual->Hizq != nullptr){
            cola.encolar(actual->Hizq);
        }
        if (actual->Hder != nullptr){
            cola.encolar(actual->Hder);
        }
    }
    cout << endl;
}

// Recorrido preorden iterativo.
void ABBusqueda::preordenI()
{
    pnodo act = raiz;
    Pila pila;

    while (!pila.vacia() || act != nullptr){
        if (act != nullptr){
            mostrarDato(act);
            pila.push(act);
            act = act->Hizq;
        }
        else{
            act = pila.pop();
            act = act->Hder;
        }
    }
}

// Recorrido inorden iterativo.
void ABBusqueda::inordenI()
{
    pnodo act = raiz;
    Pila pila;
    while (true){
        while (act != nullptr){
            pila.push(act);
            act = act->Hizq;
        }
        if (!pila.vacia()){
            act = pila.pop();
            mostrarDato(act);
            act = act->Hder;
        }
        if (pila.vacia() && act == nullptr){
            break;
        }
    }
}

// Recorrido postorden iterativo.
void ABBusqueda::postordenI(){
    pnodo act = raiz;
    Pila pila1, pila2;

    while (!pila1.vacia() || act != nullptr){
        if (act != nullptr)
        {
            pila2.push(act);
            pila1.push(act);
            act = act->Hder;
        }else{
            act = pila1.pop();
            act = act->Hizq;
        }
    }
    while (!pila2.vacia()){
        pnodo temp = pila2.pop();
        mostrarDato(temp);
    }
}

//--------METODOS PRIVADOS ------------

// Compara las claves segun el tipo de arbol.
// Devuelve -1 si es menor, 0 si es igual y 1 si es mayor.
int ABBusqueda::compararClaves(pnodo raiz,int codPais,int codCiudad){
    if (tipoClave == TipoClave::Pais){
        if (codPais < raiz->codPais){
            return -1;
        }
        else if (codPais > raiz->codPais)
        {
            return 1;
        }else{
            return 0;
        }
    }else{
        // Para ciudades se compara primero el pais.
        if (codPais < raiz->codPais){
            return -1;
        }
        else if (codPais > raiz->codPais)
        {
            return 1;
        }
        else
        {
            // Si el pais es igual, se compara la ciudad.
            if (codCiudad < raiz->codCiudad){
                return -1;
            }
            else if (codCiudad > raiz->codCiudad)
            {
                return 1;
            }else{
                return 0;
            }
        }
    }
}

// Busca y devuelve el nodo que coincide con las claves.
pnodo ABBusqueda::buscarNodo(pnodo raiz, int codPais, int codCiudad){
    if (raiz == nullptr){
        return nullptr;
    }
    int comparacion = compararClaves(raiz, codPais, codCiudad);
    if (comparacion == 0){
        return raiz;
    }
    else if (comparacion < 0)
    {
        return buscarNodo(raiz->Hizq, codPais, codCiudad);
    }else{
        return buscarNodo(raiz->Hder, codPais, codCiudad);
    }
}

// Cambia el nombre de un pais (codCiudad = 0) o de una ciudad. Devuelve false si no existe.
bool ABBusqueda::modificarNombre(int codPais, int codCiudad, string nuevoNombre){
    pnodo encontrado = buscarNodo(raiz, codPais, codCiudad);
    if (encontrado == nullptr){
        return false;
    }
    encontrado->nombre = nuevoNombre;
    return true;
}

// Busca y muestra un pais por su codigo.
void ABBusqueda::mostrarPorClave(int codigo){
    if (tipoClave != TipoClave::Pais){
        return;
    }
    pnodo encontrado = buscarNodo(raiz, codigo, 0);
    if (encontrado != nullptr){
        mostrarDato(encontrado);
        cout << endl;
    }
}

// Busca y muestra una ciudad por el codigo del pais y de la ciudad.
void ABBusqueda::mostrarPorClave(int codPais, int codCiudad){
    if (tipoClave != TipoClave::Ciudad){
        return;
    }
    pnodo encontrado = buscarNodo(raiz, codPais, codCiudad);
    if (encontrado != nullptr){
        mostrarDato(encontrado);
        cout << endl;
    }
}

pnodo ABBusqueda::InsertaBinario(pnodo raiz,int codPais,int codCiudad,string nombre){
    if (raiz == nullptr){
        return new NodoABB(codPais, codCiudad, nombre);
    }

    int comparacion = compararClaves(raiz,codPais,codCiudad);
    if (comparacion < 0){
        raiz->Hizq = InsertaBinario(raiz->Hizq,codPais,codCiudad,nombre);
    }
    else if (comparacion > 0)
    {
        raiz->Hder = InsertaBinario(raiz->Hder,codPais,codCiudad,nombre);
    }
    return raiz;
}

bool ABBusqueda::Buscarvalor(pnodo raiz,int codPais,int codCiudad){
    if (raiz == nullptr){
        return false;
    }
    int comparacion = compararClaves(raiz,codPais,codCiudad);
    if (comparacion == 0){
        return true;
    }
    else if (comparacion < 0)
    {
        return Buscarvalor(raiz->Hizq,codPais,codCiudad);
    }else{
        return Buscarvalor(raiz->Hder,codPais,codCiudad);
    }
}

void ABBusqueda::InordenR(pnodo raiz){
    if (raiz != nullptr){
        InordenR(raiz->Hizq);
        mostrarDato(raiz);
        cout << " | ";
        InordenR(raiz->Hder);
    }
}

void ABBusqueda::PreordenR(pnodo raiz){
    if (raiz != nullptr){
        mostrarDato(raiz);
        cout << " | ";
        PreordenR(raiz->Hizq);
        PreordenR(raiz->Hder);
    }
}

void ABBusqueda::PostordenR(pnodo raiz){
    if (raiz != nullptr){
        PostordenR(raiz->Hizq);
        PostordenR(raiz->Hder);
        mostrarDato(raiz);
        cout << " | ";
    }
}

// Muestra los datos del nodo segun el tipo de arbol pais o ciudad.
void ABBusqueda::mostrarDato(pnodo raiz){
    if (raiz == nullptr)
    {
        return;
    }
    if (tipoClave == TipoClave::Pais){
        cout << raiz->codPais << " - " << raiz->nombre;
    }else{
        cout << raiz->codPais << " - "<< raiz->codCiudad << " - " << raiz->nombre;
    }
}

// Destruye el arbol recursivamente.
void ABBusqueda::destruirArbol(pnodo raiz){
    if (raiz == nullptr) return;
    destruirArbol(raiz->Hizq);
    destruirArbol(raiz->Hder);
    delete raiz;
}
