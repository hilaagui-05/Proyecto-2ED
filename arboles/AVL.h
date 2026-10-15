
#ifndef AVL_H
#define AVL_H

#include "NodoAVL.h"
#include <string>

class AVL {
private:
    pNodoAVL raiz;

    pNodoAVL buscarNodo(pNodoAVL n, int id);

    void InsertarBalanceado(
        pNodoAVL& raiz,
        bool& Hh,
        int id,
        int numero,
        std::string piso,
        int tipo,
        int estado
    );

    void RotacionSimpleIzquierda(pNodoAVL& n, pNodoAVL& n1);
    void RotacionSimpleDerecha(pNodoAVL& n, pNodoAVL& n1);
    void RotacionDobleIzquierda(pNodoAVL& n, pNodoAVL& n1);
    void RotacionDobleDerecha(pNodoAVL& n, pNodoAVL& n1);

    void MostrarInorden(pNodoAVL n);
    void LiberarMemoria(pNodoAVL n);

public:
    AVL();
    ~AVL();

    void Insertar(
        int id,
        int numero,
        std::string piso,
        int tipo,
        int estado
    );

    bool BuscarValor(int id);
    void mostrarPorCodigo(int id);
    void Mostrar();
    bool EstaVacio();
    void Limpiar();
};

#endif
