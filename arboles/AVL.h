
#ifndef AVL_H
#define AVL_H

#include "NodoAVL.h"
#include <string>

class AVL
{
private:
    pNodoAVL raiz;

    bool menor(int categoria1, int id1, int categoria2, int id2);
    pNodoAVL buscarNodo(pNodoAVL n, int id);

    void InsertarBalanceado(pNodoAVL& raiz, bool& Hh,
        int categoria, int id, int numero, std::string piso,
        int tipo, int estado, int paciente, int medico,
        int especialidad, std::string fecha, std::string hora,
        std::string motivo);

    void RotacionSimpleIzquierda(pNodoAVL& n, pNodoAVL& n1);
    void RotacionSimpleDerecha(pNodoAVL& n, pNodoAVL& n1);
    void RotacionDobleIzquierda(pNodoAVL& n, pNodoAVL& n1);
    void RotacionDobleDerecha(pNodoAVL& n, pNodoAVL& n1);
    void MostrarInorden(pNodoAVL n);
    void LiberarMemoria(pNodoAVL n);

public:
    AVL();
    ~AVL();

    // Habitaciones: categoria 1
    void Insertar(int id, int numero, std::string piso,
        int tipo, int estado);
    void Insertar(int id, int paciente, int medico, int especialidad,
        std::string fecha, std::string hora, std::string motivo, int estado);
    bool BuscarValor(int id);
    void mostrarPorCodigo(int id);

    // Modificar (devuelven false si el id no existe)
    bool modificarEstadoHabitacion(int id, int nuevoEstado);
    // motivo "" o estado -1 significa dejar ese dato igual
    bool modificarCita(int id, std::string nuevoMotivo, int nuevoEstado);

    // Citas: categoria 2
    void InsertarCita(int id, int paciente, int medico,
        int especialidad, std::string fecha,
        std::string hora, std::string motivo,int estado);
    bool BuscarCita(int id);
    void mostrarCita(int id);

    void Mostrar();
    bool EstaVacio();
    void Limpiar();
};

#endif
