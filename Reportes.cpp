//Reportes en PDF con libHaru 
#include <iostream>
#include <string>
#include "hpdf.h"
#include "CRUD/crud.h"

using namespace std;

// Fecha y hora de emision,se pide al entrar al menu de reportes
string fechaHoraEmision = "";

//Funciones generales para crear reportes PDF
HPDF_Doc pdfActual;// Datos del reporte que se esta generando.
HPDF_Page paginaActual;
HPDF_Font fuenteTitulo;
HPDF_Font fuenteTexto;
string tituloReporte;
string encabezados[8];
int posicionesX[8];
int numColumnas;
int yActual;
int numeroPagina;
int totalRegistros;

HPDF_Doc crearPDF()
{
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    return pdf;
}

HPDF_Page crearPagina(HPDF_Doc pdf)
{
    HPDF_Page pagina = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(pagina, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    return pagina;
}

void guardarPDF(HPDF_Doc pdf, string nombreArchivo)
{
    HPDF_SaveToFile(pdf, nombreArchivo.c_str());
    HPDF_Free(pdf);
}

void escribirTexto(HPDF_Page pagina, HPDF_Font fuente, int tamano, string texto, int x, int posY)
{
    HPDF_Page_BeginText(pagina);
    HPDF_Page_SetFontAndSize(pagina, fuente, tamano);
    HPDF_Page_TextOut(pagina, x, posY, texto.c_str());
    HPDF_Page_EndText(pagina);
}

void nuevaPagina()//con el encabezado: sistema, titulo, fecha y hora
{
    paginaActual = crearPagina(pdfActual);
    numeroPagina++;
    escribirTexto(paginaActual, fuenteTitulo, 14, "SISTEMA DE GESTION HOSPITALARIA", 40, 805);
    escribirTexto(paginaActual, fuenteTitulo, 12, tituloReporte, 40, 785);
    escribirTexto(paginaActual, fuenteTexto, 9, "Fecha y hora de emision: " + fechaHoraEmision, 40, 770);
    for (int i = 0; i < numColumnas; i++)
    {
        escribirTexto(paginaActual, fuenteTitulo, 8, encabezados[i], posicionesX[i], 745);
    }
    escribirTexto(paginaActual, fuenteTexto, 9, "Pagina " + to_string(numeroPagina), 270, 30);
    yActual = 725;
}

void iniciarReporte(string titulo)
{
    pdfActual = crearPDF();
    fuenteTitulo = HPDF_GetFont(pdfActual, "Helvetica-Bold", NULL);
    fuenteTexto = HPDF_GetFont(pdfActual, "Helvetica", NULL);
    tituloReporte = titulo;
    numColumnas = 0;
    numeroPagina = 0;
    totalRegistros = 0;
}

void agregarColumna(string encabezado, int x)// Define una columna de la tabla (titulo y posicion)
{
    encabezados[numColumnas] = encabezado;
    posicionesX[numColumnas] = x;
    numColumnas++;
}

// Escribe una fila de la tabla.si no hay espacio, abre otra pagina
void escribirFila(string c0, string c1 = "", string c2 = "", string c3 = "",
    string c4 = "", string c5 = "", string c6 = "", string c7 = "")
{
    if (numeroPagina == 0 || yActual < 60)
    {
        nuevaPagina();
    }
    string celdas[8] = { c0, c1, c2, c3, c4, c5, c6, c7 };
    for (int i = 0; i < numColumnas; i++)
    {
        escribirTexto(paginaActual, fuenteTexto, 8, celdas[i], posicionesX[i], yActual);
    }
    yActual = yActual - 15;
    totalRegistros++;
}

void terminarReporte(string nombreArchivo)//escribe el total y guarda el archivo
{
    if (numeroPagina == 0 || yActual < 60)
    {
        nuevaPagina();
    }
    if (totalRegistros == 0)
    {
        escribirTexto(paginaActual, fuenteTexto, 9, "No hay registros para mostrar.", 40, yActual);
        yActual = yActual - 15;
    }
    escribirTexto(paginaActual, fuenteTitulo, 9, "Total de registros: " + to_string(totalRegistros), 40, yActual - 5);
    guardarPDF(pdfActual, nombreArchivo);
    cout << "Reporte generado correctamente." << endl;
}

//Recorridos de los arboles (inorden)
void recorrerPaises(pnodo nodo)
{
    if (nodo != nullptr)
    {
        recorrerPaises(nodo->Hizq);
        escribirFila(to_string(nodo->codPais), nodo->nombre);
        recorrerPaises(nodo->Hder);
    }
}

void recorrerCiudades(pnodo nodo, int codPais)//solo las ciudades del pais indicado
{
    if (nodo != nullptr)
    {
        recorrerCiudades(nodo->Hizq, codPais);
        if (nodo->codPais == codPais)
        {
            escribirFila(to_string(nodo->codCiudad), nodo->nombre);
        }
        recorrerCiudades(nodo->Hder, codPais);
    }
}

void recorrerPacientes(Pagina* p, int modo, int codPais, int codCiudad)
{
    if (p == nullptr)
    {
        return;
    }
    for (int i = 1; i <= p->Cuenta; i++)
    {
        recorrerPacientes(p->Ramas[i - 1], modo, codPais, codCiudad);
        RegistroB& paciente = p->Claves[i];
        bool cumple = true;
        if (modo == 1 && paciente.codPais != codPais)//de un pais
        {
            cumple = false;
        }
        else if (modo == 2 && (paciente.codPais != codPais || paciente.codCiudad != codCiudad))
        {//de un pais y una ciudad
            cumple = false;
        }
        if (cumple)
        {
            escribirFila(to_string(paciente.clave), paciente.nombre, paciente.fechaNacimiento,
                paciente.telefono, to_string(paciente.codPais),
                to_string(paciente.codCiudad), paciente.correo);
        }
    }
    recorrerPacientes(p->Ramas[p->Cuenta], modo, codPais, codCiudad);
}

void recorrerMedicos(Pagina* p, int modo, string idEspecialidad)
{
    if (p == nullptr)
    {
        return;
    }
    for (int i = 1; i <= p->Cuenta; i++)
    {
        recorrerMedicos(p->Ramas[i - 1], modo, idEspecialidad);
        RegistroB& medico = p->Claves[i];
        if (modo == 0 || to_string(medico.idEspecialidad) == idEspecialidad)
        {
            escribirFila(to_string(medico.clave), medico.nombre, medico.telefono,
                medico.correo, to_string(medico.idEspecialidad));
        }
    }
    recorrerMedicos(p->Ramas[p->Cuenta], modo, idEspecialidad);
}

void recorrerAA(NodoAA* nodo)//sirve para especialidades y diagnosticos
{
    if (nodo != nullptr)
    {
        recorrerAA(nodo->izquierda);
        escribirFila(nodo->codigo, nodo->nombre, nodo->descripcion);
        recorrerAA(nodo->derecha);
    }
}

//solo las habitaciones con el estado indicado. 0 disponible, 1 ocupada
void recorrerHabitaciones(pNodoAVL nodo, int estado)
{
    if (nodo != nullptr)
    {
        recorrerHabitaciones(nodo->Hizq, estado);
        if (nodo->categoria == 1 && nodo->estado == estado)
        {
            escribirFila(to_string(nodo->idHabitacion), to_string(nodo->numero),
                nodo->piso, to_string(nodo->tipo), to_string(nodo->estado));
        }
        recorrerHabitaciones(nodo->Hder, estado);
    }
}

void recorrerHospitalizaciones(pNodoRN nodo, int modo, int idMedico)
{
    if (nodo != nullptr)
    {
        recorrerHospitalizaciones(nodo->Hizq, modo, idMedico);
        if (nodo->categoria == 2 && (modo == 0 || nodo->idMedico == idMedico))
        {
            escribirFila(to_string(nodo->idHospitalizacion), to_string(nodo->idPaciente),
                to_string(nodo->idHabitacion), to_string(nodo->idMedico),
                nodo->fechaIngreso, nodo->fechaSalida, nodo->motivo);
        }
        recorrerHospitalizaciones(nodo->Hder, modo, idMedico);
    }
}

void recorrerCitas(pNodoAVL nodo, int modo, int numero, string fecha)
{
    if (nodo != nullptr)
    {
        recorrerCitas(nodo->Hizq, modo, numero, fecha);
        if (nodo->categoria == 2)
        {
            bool cumple = false;
            if (modo == 1 && nodo->fecha == fecha) cumple = true;//por fecha
            if (modo == 2 && nodo->idEspecialidad == numero) cumple = true;///por especialidad
            if (modo == 3 && nodo->idMedico == numero) cumple = true;//por medico
            if (modo == 4 && nodo->idPaciente == numero) cumple = true;//por paciente
            if (cumple)
            {
                escribirFila(to_string(nodo->idCita), to_string(nodo->idPaciente),
                    to_string(nodo->idMedico), to_string(nodo->idEspecialidad),
                    nodo->fecha, nodo->hora, to_string(nodo->estado), nodo->motivo);
            }
        }
        recorrerCitas(nodo->Hder, modo, numero, fecha);
    }
}

void recorrerTratamientos(pNodoRN nodo)
{
    if (nodo != nullptr)
    {
        recorrerTratamientos(nodo->Hizq);
        if (nodo->categoria == 1)
        {
            escribirFila(to_string(nodo->codigo), nodo->nombre, nodo->descripcion,
                to_string(nodo->costo));
        }
        recorrerTratamientos(nodo->Hder);
    }
}

//columnas que se repiten en varios reportes

void columnasPacientes()
{
    agregarColumna("Id", 40);
    agregarColumna("Nombre", 70);
    agregarColumna("Nacimiento", 200);
    agregarColumna("Telefono", 258);
    agregarColumna("Pais", 328);
    agregarColumna("Ciudad", 364);
    agregarColumna("Correo", 402);
}

void columnasMedicos()
{
    agregarColumna("Id", 40);
    agregarColumna("Nombre", 80);
    agregarColumna("Telefono", 210);
    agregarColumna("Correo", 290);
    agregarColumna("Especialidad", 450);
}

void columnasHospitalizaciones()
{
    agregarColumna("Id", 40);
    agregarColumna("Paciente", 70);
    agregarColumna("Habitacion", 125);
    agregarColumna("Medico", 190);
    agregarColumna("Ingreso", 235);
    agregarColumna("Salida", 295);
    agregarColumna("Motivo", 350);
}

void columnasHabitaciones()
{
    agregarColumna("Id", 40);
    agregarColumna("Numero", 90);
    agregarColumna("Piso", 150);
    agregarColumna("Tipo", 230);
    agregarColumna("Estado", 280);
}

void columnasCitas()
{
    agregarColumna("Id", 40);
    agregarColumna("Paciente", 70);
    agregarColumna("Medico", 120);
    agregarColumna("Especialidad", 170);
    agregarColumna("Fecha", 235);
    agregarColumna("Hora", 295);
    agregarColumna("Estado", 330);
    agregarColumna("Motivo", 370);
}

//Reportes

void reportePaises()
{
    iniciarReporte("REPORTE DE PAISES");
    agregarColumna("Codigo", 40);
    agregarColumna("Nombre", 120);
    recorrerPaises(arbolPaises.obtenerRaiz());
    terminarReporte("ReportePaises.pdf");
}

void reporteCiudades()
{
    int codPais;
    cout << "Ingrese el codigo del pais: ";
    cin >> codPais;
    if (!arbolPaises.Buscarvalor(codPais))
    {
        cout << "El pais no existe." << endl;
        return;
    }
    iniciarReporte("REPORTE DE CIUDADES DEL PAIS " + to_string(codPais));
    agregarColumna("Codigo", 40);
    agregarColumna("Nombre", 120);
    recorrerCiudades(arbolCiudades.obtenerRaiz(), codPais);
    terminarReporte("ReporteCiudades.pdf");
}

void reportePacientes()
{
    iniciarReporte("REPORTE DE PACIENTES");
    columnasPacientes();
    recorrerPacientes(arbolPacientes.obtenerRaiz(), 0, 0, 0);
    terminarReporte("ReportePacientes.pdf");
}

void reporteEspecialidades()
{
    iniciarReporte("REPORTE DE ESPECIALIDADES");
    agregarColumna("Id", 40);
    agregarColumna("Nombre", 80);
    agregarColumna("Descripcion", 220);
    recorrerAA(arbolEspecialidades.obtenerRaiz());
    terminarReporte("ReporteEspecialidades.pdf");
}

void reporteHabitacionesDisponibles()
{
    iniciarReporte("REPORTE DE HABITACIONES DISPONIBLES");
    columnasHabitaciones();
    recorrerHabitaciones(arbolHabitaciones.obtenerRaiz(), 0);
    terminarReporte("ReporteHabitacionesDisponibles.pdf");
}

void reporteHabitacionesOcupadas()
{
    iniciarReporte("REPORTE DE HABITACIONES OCUPADAS");
    columnasHabitaciones();
    recorrerHabitaciones(arbolHabitaciones.obtenerRaiz(), 1);
    terminarReporte("ReporteHabitacionesOcupadas.pdf");
}

void reporteHospitalizaciones()
{
    iniciarReporte("REPORTE DE HOSPITALIZACIONES");
    columnasHospitalizaciones();
    recorrerHospitalizaciones(arbolHospitalizaciones.obtenerRaiz(), 0, 0);
    terminarReporte("ReporteHospitalizaciones.pdf");
}

void reporteHospitalizacionesPorMedico()
{
    int idMedico;
    cout << "Ingrese el ID del medico: ";
    cin >> idMedico;
    if (arbolMedicos.Buscar(idMedico) == nullptr)
    {
        cout << "El medico no existe." << endl;
        return;
    }
    iniciarReporte("HOSPITALIZACIONES DEL MEDICO " + to_string(idMedico));
    columnasHospitalizaciones();
    recorrerHospitalizaciones(arbolHospitalizaciones.obtenerRaiz(), 1, idMedico);
    terminarReporte("ReporteHospitalizacionesPorMedico.pdf");
}

void reporteMedicos()
{
    iniciarReporte("REPORTE DE MEDICOS");
    columnasMedicos();
    recorrerMedicos(arbolMedicos.obtenerRaiz(), 0, "");
    terminarReporte("ReporteMedicos.pdf");
}

void reporteMedicosPorEspecialidad()
{
    string idEspecialidad;
    cout << "Ingrese el ID de la especialidad: ";
    cin >> idEspecialidad;
    if (!arbolEspecialidades.Buscarvalor(idEspecialidad))
    {
        cout << "La especialidad no existe." << endl;
        return;
    }
    iniciarReporte("MEDICOS DE LA ESPECIALIDAD " + idEspecialidad);
    columnasMedicos();
    recorrerMedicos(arbolMedicos.obtenerRaiz(), 1, idEspecialidad);
    terminarReporte("ReporteMedicosPorEspecialidad.pdf");
}

void reporteCitasPorFecha()
{
    string fecha;
    cout << "Ingrese la fecha (como aparece en el archivo, ejemplo 15/10/2026): ";
    cin >> fecha;
    iniciarReporte("REPORTE DE CITAS DEL " + fecha);
    columnasCitas();
    recorrerCitas(arbolCitas.obtenerRaiz(), 1, 0, fecha);
    terminarReporte("ReporteCitasPorFecha.pdf");
}

void reporteCitasPorEspecialidad()
{
    string idEspecialidad;
    cout << "Ingrese el ID de la especialidad: ";
    cin >> idEspecialidad;
    if (!arbolEspecialidades.Buscarvalor(idEspecialidad))
    {
        cout << "La especialidad no existe." << endl;
        return;
    }
    iniciarReporte("CITAS DE LA ESPECIALIDAD " + idEspecialidad);
    columnasCitas();
    recorrerCitas(arbolCitas.obtenerRaiz(), 2, stoi(idEspecialidad), "");
    terminarReporte("ReporteCitasPorEspecialidad.pdf");
}

void reporteCitasPorMedico()
{
    int idMedico;
    cout << "Ingrese el ID del medico: ";
    cin >> idMedico;
    if (arbolMedicos.Buscar(idMedico) == nullptr)
    {
        cout << "El medico no existe." << endl;
        return;
    }
    iniciarReporte("CITAS DEL MEDICO " + to_string(idMedico));
    columnasCitas();
    recorrerCitas(arbolCitas.obtenerRaiz(), 3, idMedico, "");
    terminarReporte("ReporteCitasPorMedico.pdf");
}

void reportePacientesPorPais()
{
    int codPais;
    cout << "Ingrese el codigo del pais: ";
    cin >> codPais;
    if (!arbolPaises.Buscarvalor(codPais))
    {
        cout << "El pais no existe." << endl;
        return;
    }
    iniciarReporte("PACIENTES DEL PAIS " + to_string(codPais));
    columnasPacientes();
    recorrerPacientes(arbolPacientes.obtenerRaiz(), 1, codPais, 0);
    terminarReporte("ReportePacientesPorPais.pdf");
}

void reportePacientesPorCiudad()
{
    int codPais;
    int codCiudad;
    cout << "Ingrese el codigo del pais: ";
    cin >> codPais;
    cout << "Ingrese el codigo de la ciudad: ";
    cin >> codCiudad;
    if (!arbolPaises.Buscarvalor(codPais))
    {
        cout << "El pais no existe." << endl;
        return;
    }
    if (!arbolCiudades.Buscarvalor(codPais, codCiudad))
    {
        cout << "La ciudad no existe." << endl;
        return;
    }
    iniciarReporte("PACIENTES DE LA CIUDAD " + to_string(codCiudad) + " DEL PAIS " + to_string(codPais));
    columnasPacientes();
    recorrerPacientes(arbolPacientes.obtenerRaiz(), 2, codPais, codCiudad);
    terminarReporte("ReportePacientesPorCiudad.pdf");
}

void reporteCitasPorPaciente()
{
    int idPaciente;
    cout << "Ingrese el ID del paciente: ";
    cin >> idPaciente;
    if (arbolPacientes.Buscar(idPaciente) == nullptr)
    {
        cout << "El paciente no existe." << endl;
        return;
    }
    iniciarReporte("CITAS DEL PACIENTE " + to_string(idPaciente));
    columnasCitas();
    recorrerCitas(arbolCitas.obtenerRaiz(), 4, idPaciente, "");
    terminarReporte("ReporteCitasPorPaciente.pdf");
}

void reporteDiagnosticos()
{
    iniciarReporte("REPORTE DE DIAGNOSTICOS");
    agregarColumna("Codigo", 40);
    agregarColumna("Nombre", 100);
    agregarColumna("Descripcion", 240);
    recorrerAA(arbolDiagnosticos.obtenerRaiz());
    terminarReporte("ReporteDiagnosticos.pdf");
}

void reporteTratamientos()
{
    iniciarReporte("REPORTE DE TRATAMIENTOS");
    agregarColumna("Id", 40);
    agregarColumna("Nombre", 70);
    agregarColumna("Descripcion", 200);
    agregarColumna("Costo", 480);
    recorrerTratamientos(arbolTratamientos.obtenerRaiz());
    terminarReporte("ReporteTratamientos.pdf");
}