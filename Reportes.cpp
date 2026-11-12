//Reportes en PDF con libHaru 
#include <iostream>
#include <string>
#include <sstream>
#include "hpdf.h"
#include "CRUD/crud.h"

using namespace std;

// Fecha y hora de emision, la ventana de reportes la escribe antes de generar cada reporte
string fechaHoraEmision = "";

// Nombre del ultimo PDF generado, la ventana lo usa para abrirlo
string ultimoReporte = "";

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

bool guardarPDF(HPDF_Doc pdf, string nombreArchivo)
{
    HPDF_STATUS estado = HPDF_SaveToFile(pdf, nombreArchivo.c_str());
    HPDF_Free(pdf);
    return estado == HPDF_OK; //false si no se pudo escribir (por ejemplo, el PDF esta abierto)
}

// Los textos del programa estan en UTF-8, pero el PDF usa la codificacion WinAnsi (Latin-1).
// Esta funcion convierte las letras con tilde (a, e, i, o, u, n con tilde) para que se vean bien.
string aLatin1(string texto)
{
    string resultado = "";
    int largo = (int)texto.length();
    for (int i = 0; i < largo; i++)
    {
        unsigned char c = (unsigned char)texto[i];
        if (c < 128)
        {
            resultado += (char)c;
        }
        else if (c == 0xC3 && i + 1 < largo)
        {
            resultado += (char)((unsigned char)texto[i + 1] + 0x40); //letras con tilde
            i++;
        }
        else if (c == 0xC2 && i + 1 < largo)
        {
            resultado += texto[i + 1];
            i++;
        }
        else
        {
            resultado += '?'; //simbolo que el PDF no maneja
            while (i + 1 < largo && ((unsigned char)texto[i + 1] & 0xC0) == 0x80)
            {
                i++; //salta el resto de los bytes del simbolo
            }
        }
    }
    return resultado;
}

// Ancho en puntos que ocupa el texto (en UTF-8) al escribirlo en el PDF
int anchoTexto(HPDF_Font fuente, int tamano, string texto)
{
    string latin = aLatin1(texto);
    return (int)(HPDF_Font_TextWidth(fuente, (HPDF_BYTE*)latin.c_str(), (HPDF_UINT)latin.length()).width * tamano / 1000);
}

// Corta el texto (en UTF-8) para que no se salga de su columna (ancho en puntos)
string recortarTexto(HPDF_Font fuente, int tamano, string texto, int ancho)
{
    while (texto.length() > 0 && anchoTexto(fuente, tamano, texto) > ancho)
    {
        while (texto.length() > 0 && ((unsigned char)texto[texto.length() - 1] & 0xC0) == 0x80)
        {
            texto.erase(texto.length() - 1); //quita los bytes finales de una letra con tilde
        }
        if (texto.length() > 0)
        {
            texto.erase(texto.length() - 1); //quita la letra completa
        }
    }
    return texto;
}

void escribirTexto(HPDF_Page pagina, HPDF_Font fuente, int tamano, string texto, int x, int posY)
{
    HPDF_Page_BeginText(pagina);
    HPDF_Page_SetFontAndSize(pagina, fuente, tamano);
    HPDF_Page_TextOut(pagina, (float)x, (float)posY, aLatin1(texto).c_str());
    HPDF_Page_EndText(pagina);
}

void nuevaPagina()//con el encabezado: sistema, titulo, fecha y hora
{
    paginaActual = crearPagina(pdfActual);
    numeroPagina++;
    escribirTexto(paginaActual, fuenteTitulo, 14, "SISTEMA DE GESTIÓN HOSPITALARIA", 40, 805);
    escribirTexto(paginaActual, fuenteTitulo, 12, tituloReporte, 40, 785);
    escribirTexto(paginaActual, fuenteTexto, 9, "Fecha y hora de emisión: " + fechaHoraEmision, 40, 770);
    for (int i = 0; i < numColumnas; i++)
    {
        escribirTexto(paginaActual, fuenteTitulo, 8, encabezados[i], posicionesX[i], 745);
    }
    escribirTexto(paginaActual, fuenteTexto, 9, "Página " + to_string(numeroPagina), 270, 30);
    yActual = 725;
}

void iniciarReporte(string titulo)
{
    pdfActual = crearPDF();
    fuenteTitulo = HPDF_GetFont(pdfActual, "Helvetica-Bold", "WinAnsiEncoding");
    fuenteTexto = HPDF_GetFont(pdfActual, "Helvetica", "WinAnsiEncoding");
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
        int limite = 555; //margen derecho de la pagina
        if (i + 1 < numColumnas)
        {
            limite = posicionesX[i + 1] - 3; //hasta donde empieza la siguiente columna
        }
        string texto = recortarTexto(fuenteTexto, 8, celdas[i], limite - posicionesX[i]);
        escribirTexto(paginaActual, fuenteTexto, 8, texto, posicionesX[i], yActual);
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
    if (guardarPDF(pdfActual, nombreArchivo))
    {
        ultimoReporte = nombreArchivo;
        cout << "Reporte generado correctamente: " << nombreArchivo << endl;
    }
    else
    {
        cout << "No se pudo guardar el PDF. Si lo tiene abierto, cierrelo e intente de nuevo." << endl;
    }
}

// Quita los ceros a la izquierda de un numero escrito como texto (05 queda 5)
string quitarCeros(string numero)
{
    while (numero.length() > 1 && numero[0] == '0')
    {
        numero.erase(0, 1);
    }
    return numero;
}

// Deja la fecha como dia/mes/anio sin ceros, para comparar 15/09/2026 con 15/9/2026
string normalizarFecha(string fecha)
{
    stringstream datos(fecha);
    string dia, mes, anio;
    getline(datos, dia, '/');
    getline(datos, mes, '/');
    getline(datos, anio);
    return quitarCeros(dia) + "/" + quitarCeros(mes) + "/" + quitarCeros(anio);
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
            if (modo == 1 && normalizarFecha(nodo->fecha) == normalizarFecha(fecha)) cumple = true;//por fecha
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
    agregarColumna("Teléfono", 258);
    agregarColumna("País", 328);
    agregarColumna("Ciudad", 364);
    agregarColumna("Correo", 402);
}

void columnasMedicos()
{
    agregarColumna("Id", 40);
    agregarColumna("Nombre", 80);
    agregarColumna("Teléfono", 210);
    agregarColumna("Correo", 290);
    agregarColumna("Especialidad", 450);
}

void columnasHospitalizaciones()
{
    agregarColumna("Id", 40);
    agregarColumna("Paciente", 70);
    agregarColumna("Habitación", 125);
    agregarColumna("Médico", 190);
    agregarColumna("Ingreso", 235);
    agregarColumna("Salida", 295);
    agregarColumna("Motivo", 350);
}

void columnasHabitaciones()
{
    agregarColumna("Id", 40);
    agregarColumna("Número", 90);
    agregarColumna("Piso", 150);
    agregarColumna("Tipo", 230);
    agregarColumna("Estado", 280);
}

void columnasCitas()
{
    agregarColumna("Id", 40);
    agregarColumna("Paciente", 70);
    agregarColumna("Médico", 120);
    agregarColumna("Especialidad", 170);
    agregarColumna("Fecha", 235);
    agregarColumna("Hora", 295);
    agregarColumna("Estado", 330);
    agregarColumna("Motivo", 370);
}

//Reportes

void reportePaises()
{
    iniciarReporte("REPORTE DE PAÍSES");
    agregarColumna("Código", 40);
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
    iniciarReporte("REPORTE DE CIUDADES DEL PAÍS " + to_string(codPais));
    agregarColumna("Código", 40);
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
    agregarColumna("Descripción", 220);
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
    iniciarReporte("HOSPITALIZACIONES DEL MÉDICO " + to_string(idMedico));
    columnasHospitalizaciones();
    recorrerHospitalizaciones(arbolHospitalizaciones.obtenerRaiz(), 1, idMedico);
    terminarReporte("ReporteHospitalizacionesPorMedico.pdf");
}

void reporteMedicos()
{
    iniciarReporte("REPORTE DE MÉDICOS");
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
    iniciarReporte("MÉDICOS DE LA ESPECIALIDAD " + idEspecialidad);
    columnasMedicos();
    recorrerMedicos(arbolMedicos.obtenerRaiz(), 1, idEspecialidad);
    terminarReporte("ReporteMedicosPorEspecialidad.pdf");
}

void reporteCitasPorFecha()
{
    string fecha;
    cout << "Ingrese la fecha (dia/mes/anio, ejemplo 15/10/2026): ";
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
    iniciarReporte("CITAS DEL MÉDICO " + to_string(idMedico));
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
    iniciarReporte("PACIENTES DEL PAÍS " + to_string(codPais));
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
    iniciarReporte("PACIENTES DE LA CIUDAD " + to_string(codCiudad) + " DEL PAÍS " + to_string(codPais));
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
    iniciarReporte("REPORTE DE DIAGNÓSTICOS");
    agregarColumna("Código", 40);
    agregarColumna("Nombre", 100);
    agregarColumna("Descripción", 240);
    recorrerAA(arbolDiagnosticos.obtenerRaiz());
    terminarReporte("ReporteDiagnosticos.pdf");
}

void reporteTratamientos()
{
    iniciarReporte("REPORTE DE TRATAMIENTOS");
    agregarColumna("Id", 40);
    agregarColumna("Nombre", 70);
    agregarColumna("Descripción", 200);
    agregarColumna("Costo", 480);
    recorrerTratamientos(arbolTratamientos.obtenerRaiz());
    terminarReporte("ReporteTratamientos.pdf");
}