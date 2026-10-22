
#ifndef ARBOLRN_H
#define ARBOLRN_H

#include "NodoRN.h"
#include <string>

typedef NodoRN* pNodoRN;

class BinarioRN
{
private:
    pNodoRN raiz;

    bool menor(int categoria1, int id1,
        int categoria2, int id2);

    void InsertarRN(pNodoRN nuevo);
    void ArreglaInsercion(pNodoRN nodo);
    void RotIzquierda(pNodoRN nodo);
    void RotDerecha(pNodoRN nodo);
    void MostrarInorden(pNodoRN nodo);
    void MostrarPreorden(pNodoRN nodo);
    void LiberarMemoria(pNodoRN nodo);

public:
    BinarioRN();
    ~BinarioRN();

    // Tratamientos: categoria 1
    void Insertar(int id, std::string nombre,
        std::string descripcion, int costo);
    void Insertar(int id, int paciente, int habitacion, int medico,
        std::string ingreso, std::string salida, std::string motivo);
    bool Buscarvalor(int id);
    void mostrarPorClave(int id);

    // Modificar (devuelven false si el id no existe)
    // nombre "" , descripcion "" o costo -1 significa dejar ese dato igual
    bool modificarTratamiento(int id, std::string nombre,
        std::string descripcion, int costo);
    bool modificarHospitalizacion(int id, std::string nuevoMotivo);

    // Hospitalizaciones: categoria 2
    void InsertarHospitalizacion(int id, int paciente,
        int habitacion, int medico, std::string ingreso, std::string salida, std::string motivo);
    bool BuscarHospitalizacion(int id);
    void mostrarHospitalizacion(int id);

    void Mostrar();
    bool EstaVacio();
    void Limpiar();
};

#endif