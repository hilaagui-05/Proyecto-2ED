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
extern BinarioRN arbolHospitalizaciones;
extern BinarioAA arbolDiagnosticos;
extern BinarioAA arbolEspecialidades;
extern AVL arbolHabitaciones;
extern AVL arbolCitas;
extern ArbolB arbolPacientes;
extern ArbolB arbolMedicos;

// Paises
void insertarPais();
void buscarPais();
void modificarPais();

// Ciudades
void insertarCiudad();
void buscarCiudad();
void modificarCiudad();

// Tratamientos
void insertarTratamiento();
void buscarTratamiento();
void modificarTratamiento();

// Diagnosticos
void insertarDiagnostico();
void buscarDiagnostico();
void modificarDiagnostico();
void mostrarDiagnosticos();

// Especialidades
void insertarEspecialidad();
void buscarEspecialidad();
void modificarEspecialidad();
void mostrarEspecialidades();

// Habitaciones
void insertarHabitacion();
void buscarHabitacion();
void modificarHabitacion();
void mostrarHabitaciones();

// Pacientes
void insertarPaciente();
void buscarPaciente();
void modificarPaciente();
void mostrarPacientes();

// Medicos
void insertarMedico();
void buscarMedico();
void modificarMedico();
void mostrarMedicos();

// Citas
void insertarCita();
void buscarCita();
void modificarCita();
void mostrarCitas();

// Hospitalizaciones
void insertarHospitalizacion();
void buscarHospitalizacion();
void modificarHospitalizacion();
void mostrarHospitalizaciones();


#endif