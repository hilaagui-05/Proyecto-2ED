#ifndef ARBOLB_H
#define ARBOLB_H

#include "pagina.h"
#include <iostream>

class ArbolB {
private:
    Pagina* Raiz;
    void BuscarNodo(int Clave, Pagina* P, bool& Encontrado, int& K);
    void Empujar(const RegistroB& C1, Pagina* R, bool& EmpujaArriba, RegistroB& Mdna, Pagina*& Xr);
    void MeterHoja(const RegistroB& X, Pagina* Xder, Pagina* P, int K);
    void DividirNodo(const RegistroB& X, Pagina* Xder, Pagina* P, int K, RegistroB& Mda, Pagina*& Mder);
    void Mostrar(Pagina* P, int nivel);

    // Borrado (metodos de la profesora)
    void EliminarRegistro(int C1, Pagina*& R, bool& Encontrado);
    void Quitar(Pagina* P, int K);
    void Sucesor(Pagina* P, int K);
    void Restablecer(Pagina* P, int K);
    void MoverDerecha(Pagina* P, int K);
    void MoverIzquierda(Pagina* P, int K);
    void Combina(Pagina* P, int K);
    bool ArbolVacio(Pagina* P);

public:
    ArbolB();
    void Insertar(const RegistroB& registro);
    RegistroB* Buscar(int clave);
    bool Eliminar(int C1); // false si la clave no existe
    Pagina* obtenerRaiz(); // devuelve la raiz para recorrer el arbol en los reportes
    void Imprimir();
};

#endif
