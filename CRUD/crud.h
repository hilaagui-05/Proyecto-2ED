#ifndef CRUD_H
#define CRUD_H

#include "../arboles/ABBusqueda.h"
#include "../arboles/arbolRN.h"
#include "../arboles/BinarioAA.h"
#include "../arboles/AVL.h"
#include "../arboles/arbolB.h"


// Arboles
extern ABBusqueda arbolPaises; //extern para que se pueda usar en otros archivos
extern ABBusqueda arbolCiudades;
extern BinarioRN arbolTratamientos; //variable compartida
extern BinarioAA arbolDiagnosticos;
extern BinarioAA arbolEspecialidades;
extern AVL arbolHabitaciones;
extern ArbolB arbolPacientes;
extern ArbolB arbolMedicos;

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

// Especialidades
void insertarEspecialidad();
void buscarEspecialidad();
void mostrarEspecialidades();

// Habitaciones
void insertarHabitacion();
void buscarHabitacion();
void mostrarHabitaciones();

// Pacientes
void insertarPaciente();
void buscarPaciente();
void mostrarPacientes();

// Medicos
void insertarMedico();
void buscarMedico();
void mostrarMedicos();


#endif