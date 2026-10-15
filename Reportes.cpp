//------------REPORTES----------------
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //permite separar los campos de cada linea
#include "hpdf.h"

using namespace std;

// funciones generales para crear reportes PDF
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

void escribirTitulo(HPDF_Page pagina, HPDF_Font fuenteTitulo, string titulo)
{
    HPDF_Page_BeginText(pagina);
    HPDF_Page_SetFontAndSize(pagina, fuenteTitulo, 16);
    HPDF_Page_TextOut(pagina, 50, 800, titulo.c_str());
    HPDF_Page_EndText(pagina);
}

void escribirLinea(HPDF_Page pagina, HPDF_Font fuenteTexto, string texto, int y)
{
    HPDF_Page_BeginText(pagina);
    HPDF_Page_SetFontAndSize(pagina, fuenteTexto, 12);
    HPDF_Page_TextOut(pagina, 50, y, texto.c_str());
    HPDF_Page_EndText(pagina);
}

void guardarPDF(HPDF_Doc pdf, string nombreArchivo)
{
    HPDF_SaveToFile(pdf, nombreArchivo.c_str());
    HPDF_Free(pdf);
}

void reportePaises()
{
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE PAISES");
    int y = 760;
    NodoPais* actual = listaPaises.obtenerPrimero();
    while (actual != NULL)
    {
        string linea = "Codigo: " + to_string(actual->codPais) + " Nombre: " + actual->nombre;
        escribirLinea(pagina, fuenteTexto, linea, y);
        y = y - 20;
        actual = actual->siguiente;
    }
    guardarPDF(pdf, "ReportePaises.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteCiudades()
{
    int codPais;
    cout << "Ingrese el codigo del pais: ";
    cin >> codPais;

    NodoPais* pais = listaPaises.obtenerPrimero();
    bool paisEncontrado = false;

    while (pais != NULL)
    {
        if (pais->codPais == codPais)
        {
            paisEncontrado = true;
            break;
        }
        pais = pais->siguiente;
    }
    if (!paisEncontrado)
    {
        cout << "El pais no existe." << endl;
        return;
    }
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE CIUDADES");
    int y = 760;
    NodoCiudad* actual = listaCiudades.primero;
    bool hayCiudades = false;
    if (actual != NULL)
    {
        do
        {
            if (actual->codPais == codPais)
            {
                string linea = "Codigo: " + to_string(actual->codCiudad) +
                    " Nombre: " + actual->nombre;
                escribirLinea(pagina, fuenteTexto, linea, y);
                y = y - 20;
                hayCiudades = true;
            }
            actual = actual->siguiente;
        } while (actual != listaCiudades.primero);
    }
    if (!hayCiudades)
    {
        escribirLinea(pagina, fuenteTexto, "No hay ciudades registradas.", y);
    }
    guardarPDF(pdf, "ReporteCiudades.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteEspecialidades()
{
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE ESPECIALIDADES");
    int y = 760;
    NodoEspecialidad* actual = listaEspecialidades.obtenerPrimero();
    if (actual != NULL)
    {
        do
        {
            string linea = "ID: " + to_string(actual->idEspecialidad) +
                " Nombre: " + actual->nombre +
                " Descripcion: " + actual->descripcion;
            escribirLinea(pagina, fuenteTexto, linea, y);
            y = y - 20;
            actual = actual->siguiente;
        } while (actual != listaEspecialidades.obtenerPrimero());
    }
    guardarPDF(pdf, "ReporteEspecialidades.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteHabitacionesDisponibles()
{
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE HABITACIONES DISPONIBLES");
    int y = 760;
    NodoHabitacion* actual = listaHabitaciones.obtenerPrimero();
    bool hayHabitaciones = false;
    if (actual != NULL)
    {
        do
        {
            if (actual->estado == 0)
            {
                string linea = "ID: " + to_string(actual->idHabitacion) +
                    " Numero: " + to_string(actual->numero) +
                    " Piso: " + to_string(actual->piso) +
                    " Tipo: " + to_string(actual->tipo);
                escribirLinea(pagina, fuenteTexto, linea, y);
                y = y - 20;
                hayHabitaciones = true;
            }
            actual = actual->siguiente;
        } while (actual != listaHabitaciones.obtenerPrimero());
    }
    if (!hayHabitaciones)
    {
        escribirLinea(pagina, fuenteTexto, "No hay habitaciones disponibles.", y);
    }
    guardarPDF(pdf, "ReporteHabitacionesDisponibles.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteHabitacionesOcupadas()
{
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE HABITACIONES OCUPADAS");
    int y = 760;
    NodoHabitacion* actual = listaHabitaciones.obtenerPrimero();
    bool hayHabitaciones = false;
    if (actual != NULL)
    {
        do
        {
            if (actual->estado == 1)
            {
                string linea = "ID: " + to_string(actual->idHabitacion) +
                    " Numero: " + to_string(actual->numero) +
                    " Piso: " + to_string(actual->piso) +
                    " Tipo: " + to_string(actual->tipo);
                escribirLinea(pagina, fuenteTexto, linea, y);
                y = y - 20;
                hayHabitaciones = true;
            }
            actual = actual->siguiente;
        } while (actual != listaHabitaciones.obtenerPrimero());
    }
    if (!hayHabitaciones)
    {
        escribirLinea(pagina, fuenteTexto, "No hay habitaciones ocupadas.", y);
    }
    guardarPDF(pdf, "ReporteHabitacionesOcupadas.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteHospitalizaciones()
{
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);

    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE HOSPITALIZACIONES");

    int y = 760;
    NodoHospitalizacion* actual = listaHospitalizaciones.primero;

    while (actual != NULL)
    {
        string linea = "ID: " + to_string(actual->idHospitalizacion) +
            " Paciente: " + to_string(actual->idPaciente) +
            " Habitacion: " + to_string(actual->idHabitacion) +
            " Medico: " + to_string(actual->idMedico) +
            " Ingreso: " + actual->fechaIngreso +
            " Salida: " + actual->fechaSalida;

        escribirLinea(pagina, fuenteTexto, linea, y);
        y = y - 20;

        actual = actual->siguiente;
    }

    guardarPDF(pdf, "ReporteHospitalizaciones.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteHospitalizacionesPorMedico()
{
    int idMedico;
    cout << "Ingrese el ID del medico: ";
    cin >> idMedico;
    NodoMedico* medico = tablaMedicos.buscar(idMedico);
    if (medico == NULL)
    {
        cout << "El medico no existe." << endl;
        return;
    }
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "HOSPITALIZACIONES DE UN MEDICO");
    int y = 760;
    NodoHospitalizacion* actual = listaHospitalizaciones.primero;
    bool hayHospitalizaciones = false;
    while (actual != NULL)
    {
        if (actual->idMedico == idMedico)
        {
            string linea = "ID: " + to_string(actual->idHospitalizacion) +
                " Paciente: " + to_string(actual->idPaciente) +
                " Habitacion: " + to_string(actual->idHabitacion) +
                " Ingreso: " + actual->fechaIngreso +
                " Salida: " + actual->fechaSalida;
            escribirLinea(pagina, fuenteTexto, linea, y);
            y = y - 20;
            hayHospitalizaciones = true;
        }
        actual = actual->siguiente;
    }
    if (!hayHospitalizaciones)
    {
        escribirLinea(pagina, fuenteTexto, "No hay hospitalizaciones para este medico.", y);
    }
    guardarPDF(pdf, "ReporteHospitalizacionesPorMedico.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteMedicos()
{
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE MEDICOS");
    int y = 760;
    for (int i = 0; i < TAM_HASH; i++)
    {
        NodoMedico* actual = tablaMedicos.tabla[i];
        while (actual != NULL)
        {
            string linea = "ID: " + to_string(actual->idMedico) +
                " Nombre: " + actual->nombre +
                " Telefono: " + actual->telefono +
                " Correo: " + actual->correo +
                " Especialidad: " + to_string(actual->idEspecialidad);
            escribirLinea(pagina, fuenteTexto, linea, y);
            y = y - 20;
            actual = actual->siguiente;
        }
    }
    guardarPDF(pdf, "ReporteMedicos.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteMedicosPorEspecialidad()
{
    int idEspecialidad;
    cout << "Ingrese el ID de la especialidad: ";
    cin >> idEspecialidad;
    NodoEspecialidad* especialidad = listaEspecialidades.obtenerPrimero();
    bool especialidadEncontrada = false;
    if (especialidad != NULL)
    {
        do
        {
            if (especialidad->idEspecialidad == idEspecialidad)
            {
                especialidadEncontrada = true;
                break;
            }
            especialidad = especialidad->siguiente;
        } while (especialidad != listaEspecialidades.obtenerPrimero());
    }
    if (!especialidadEncontrada)
    {
        cout << "La especialidad no existe." << endl;
        return;
    }
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE MEDICOS POR ESPECIALIDAD");
    int y = 760;
    bool hayMedicos = false;
    for (int i = 0; i < TAM_HASH; i++)
    {
        NodoMedico* actual = tablaMedicos.tabla[i];
        while (actual != NULL)
        {
            if (actual->idEspecialidad == idEspecialidad)
            {
                string linea = "ID: " + to_string(actual->idMedico) +
                    " Nombre: " + actual->nombre +
                    " Telefono: " + actual->telefono +
                    " Correo: " + actual->correo;
                escribirLinea(pagina, fuenteTexto, linea, y);
                y = y - 20;
                hayMedicos = true;
            }
            actual = actual->siguiente;
        }
    }
    if (!hayMedicos)
    {
        escribirLinea(pagina, fuenteTexto, "No hay medicos para esta especialidad.", y);
    }
    guardarPDF(pdf, "ReporteMedicosPorEspecialidad.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteCitasPorFecha()
{
    string fecha;
    cout << "Ingrese la fecha (AAAA-MM-DD): ";
    cin >> fecha;
    if (!fechaValida(fecha))
    {
        cout << "La fecha no es valida." << endl;
        return;
    }
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE CITAS POR FECHA");
    int y = 760;
    NodoCita* actual = listaCitas.primero;
    bool hayCitas = false;
    while (actual != NULL)
    {
        if (actual->fecha == fecha)
        {
            string linea = "ID: " + to_string(actual->idCita) +
                " Paciente: " + to_string(actual->idPaciente) +
                " Medico: " + to_string(actual->idMedico) +
                " Especialidad: " + to_string(actual->idEspecialidad) +
                " Hora: " + actual->hora +
                " Motivo: " + actual->motivo;
            escribirLinea(pagina, fuenteTexto, linea, y);
            y = y - 20;
            hayCitas = true;
        }
        actual = actual->siguiente;
    }
    if (!hayCitas)
    {
        escribirLinea(pagina, fuenteTexto, "No hay citas para esta fecha.", y);
    }
    guardarPDF(pdf, "ReporteCitasPorFecha.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteCitasPorEspecialidad()
{
    int idEspecialidad;
    cout << "Ingrese el ID de la especialidad: ";
    cin >> idEspecialidad;
    NodoEspecialidad* especialidad = listaEspecialidades.obtenerPrimero();
    bool especialidadEncontrada = false;
    if (especialidad != NULL)
    {
        do
        {
            if (especialidad->idEspecialidad == idEspecialidad)
            {
                especialidadEncontrada = true;
                break;
            }
            especialidad = especialidad->siguiente;
        } while (especialidad != listaEspecialidades.obtenerPrimero());
    }
    if (!especialidadEncontrada)
    {
        cout << "La especialidad no existe." << endl;
        return;
    }
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE CITAS POR ESPECIALIDAD");
    int y = 760;
    NodoCita* actual = listaCitas.primero;
    bool hayCitas = false;
    while (actual != NULL)
    {
        if (actual->idEspecialidad == idEspecialidad)
        {
            string linea = "ID: " + to_string(actual->idCita) +
                " Paciente: " + to_string(actual->idPaciente) +
                " Medico: " + to_string(actual->idMedico) +
                " Fecha: " + actual->fecha +
                " Hora: " + actual->hora +
                " Motivo: " + actual->motivo;
            escribirLinea(pagina, fuenteTexto, linea, y);
            y = y - 20;
            hayCitas = true;
        }
        actual = actual->siguiente;
    }
    if (!hayCitas)
    {
        escribirLinea(pagina, fuenteTexto, "No hay citas para esta especialidad.", y);
    }
    guardarPDF(pdf, "ReporteCitasPorEspecialidad.pdf");
    cout << "Reporte generado correctamente." << endl;
}

void reporteCitasPorMedico()
{
    int idMedico;
    cout << "Ingrese el ID del medico: ";
    cin >> idMedico;
    NodoMedico* medico = tablaMedicos.buscar(idMedico);
    if (medico == NULL)
    {
        cout << "El medico no existe." << endl;
        return;
    }
    HPDF_Doc pdf = crearPDF();
    HPDF_Page pagina = crearPagina(pdf);
    HPDF_Font fuenteTitulo = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font fuenteTexto = HPDF_GetFont(pdf, "Helvetica", NULL);
    escribirTitulo(pagina, fuenteTitulo, "REPORTE DE CITAS DE UN MEDICO");
    int y = 760;
    NodoCita* actual = listaCitas.primero;
    bool hayCitas = false;
    while (actual != NULL)
    {
        if (actual->idMedico == idMedico)
        {
            string linea = "ID: " + to_string(actual->idCita) +
                " Paciente: " + to_string(actual->idPaciente) +
                " Especialidad: " + to_string(actual->idEspecialidad) +
                " Fecha: " + actual->fecha +
                " Hora: " + actual->hora +
                " Motivo: " + actual->motivo;
            escribirLinea(pagina, fuenteTexto, linea, y);
            y = y - 20;
            hayCitas = true;
        }
        actual = actual->siguiente;
    }
    if (!hayCitas)
    {
        escribirLinea(pagina, fuenteTexto, "No hay citas para este medico.", y);
    }
    guardarPDF(pdf, "ReporteCitasPorMedico.pdf");
    cout << "Reporte generado correctamente." << endl;
}
