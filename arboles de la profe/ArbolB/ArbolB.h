#ifndef ARBOLB_H
#define ARBOLB_H

#include "Pagina.h"
#include <iostream>

class ArbolB {
private:
    Pagina* Raiz;

    void BuscarNodo(int Clave, Pagina* P, bool& Encontrado, int& K);
    void Empujar(int C1, Pagina* R, bool& EmpujaArriba, int& Mdna, Pagina*& Xr);
    void MeterHoja(int X, Pagina* Xder, Pagina* P, int K);
    void DividirNodo(int X, Pagina* Xder, Pagina* P, int K, int& Mda, Pagina*& Mder);

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
    void Insertar(int C1);
    void Eliminar(int C1);
    void Mostrar(Pagina* P, int nivel);
    void Imprimir(); 
};

#endif

