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

public:
    ArbolB();
    void Insertar(const RegistroB& registro);
    RegistroB* Buscar(int clave);
    void Imprimir();
};

#endif
