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
void eliminarPais();

// Ciudades
void insertarCiudad();
void buscarCiudad();
void modificarCiudad();
void eliminarCiudad();

// Tratamientos
void insertarTratamiento();
void buscarTratamiento();
void modificarTratamiento();
void eliminarTratamiento();

// Diagnosticos
void insertarDiagnostico();
void buscarDiagnostico();
void modificarDiagnostico();
void eliminarDiagnostico();
void mostrarDiagnosticos();

// Especialidades
void insertarEspecialidad();
void buscarEspecialidad();
void modificarEspecialidad();
void eliminarEspecialidad();
void mostrarEspecialidades();

// Habitaciones
void insertarHabitacion();
void buscarHabitacion();
void modificarHabitacion();
void eliminarHabitacion();
void mostrarHabitaciones();

// Pacientes
void insertarPaciente();
void buscarPaciente();
void modificarPaciente();
void eliminarPaciente();
void mostrarPacientes();

// Medicos
void insertarMedico();
void buscarMedico();
void modificarMedico();
void eliminarMedico();
void mostrarMedicos();

// Citas
void insertarCita();
void buscarCita();
void modificarCita();
void eliminarCita();
void mostrarCitas();

// Hospitalizaciones
void insertarHospitalizacion();
void buscarHospitalizacion();
void modificarHospitalizacion();
void eliminarHospitalizacion();
void mostrarHospitalizaciones();

// Borrados en cascada: buscan el primer registro relacionado, lo borran y repiten hasta que no quede ninguno
void eliminarCitasDePaciente(int idPaciente);
void eliminarCitasDeMedico(int idMedico);
void eliminarHospitalizacionesDePaciente(int idPaciente);
void eliminarHospitalizacionesDeHabitacion(int idHabitacion);
void eliminarPacienteConRelacionados(int idPaciente); // borra al paciente, sus citas y sus hospitalizaciones
void eliminarPacientesDeCiudad(int codPais, int codCiudad);
void eliminarPacientesDePais(int codPais);
void eliminarMedicoConRelacionados(int idMedico); // borra al medico y sus citas
void eliminarMedicosDeEspecialidad(int idEspecialidad);
void eliminarCiudadesDePais(int codPais); // borra cada ciudad con sus pacientes

// Reportes 
extern string fechaHoraEmision; // fecha y hora que se escribe en todos los reportes

void reportePaises();
void reporteCiudades();
void reportePacientes();
void reporteEspecialidades();
void reporteHabitacionesDisponibles();
void reporteHabitacionesOcupadas();
void reporteHospitalizaciones();
void reporteHospitalizacionesPorMedico();
void reporteMedicos();
void reporteMedicosPorEspecialidad();
void reporteCitasPorFecha();
void reporteCitasPorEspecialidad();
void reporteCitasPorMedico();
void reportePacientesPorPais();
void reportePacientesPorCiudad();
void reporteCitasPorPaciente();
void reporteDiagnosticos();
void reporteTratamientos();

#endif