#ifndef CRUD_H
#define CRUD_H

#include "arboles/ABBusqueda.h"
#include "arboles/arbolRN.h"
#include "arboles/BinarioAA.h"

// Arboles
extern ABBusqueda arbolPaises; //extern para qye se pueda usar en otros archivos
extern ABBusqueda arbolCiudades;
extern BinarioRN arbolTratamientos;
extern BinarioAA arbolDiagnosticos;

// Paises
void insertarPais();
void buscarPais();

// Ciudades
void insertarCiudad();
void buscarCiudad();

// Tratamientos
void insertarTratamiento();
void buscarTratamiento();

// Diagnosticos
void insertarDiagnostico();
void buscarDiagnostico();
void mostrarDiagnosticos();

#endif