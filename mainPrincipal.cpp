//Elaborado por : Hilary Aguilar y Arina Tarasova
//Proyecto Programado #2 - Estructuras de Datos

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "CRUD/crud.h"

using namespace std;


bool fechaValida(string fecha)
{
    if (fecha.length() != 10)
    {
        return false;
    }
    if (fecha[4] != '-' || fecha[7] != '-')
    {
        return false;
    }
    for (int i = 0; i < 10; i++)
    {
        if (i != 4 && i != 7 && (fecha[i] < '0' || fecha[i] > '9'))
        {
            return false;
        }
    }
    return true;
}

bool horaValida(string hora)
{
    if (hora.length() != 5)
    {
        return false;
    }
    if (hora[2] != ':')
    {
        return false;
    }
    for (int i = 0; i < 5; i++)
    {
        if (i != 2 && (hora[i] < '0' || hora[i] > '9'))
        {
            return false;
        }
    }
    int horas = stoi(hora.substr(0, 2));
    int minutos = stoi(hora.substr(3, 2));
    if (horas < 0 || horas > 23 || minutos < 0 || minutos > 59)
    {
        return false;
    }
    return true;
}

//------ARCHIVOS---------
void cargarPaises(){
    ifstream archivo("CSV/Paises.csv");
    if (!archivo){
        cout << "Error al abrir Paises.csv" << endl;
        return;
    }
    string linea;
    string codigo, nombre;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)){
        stringstream datos(linea);
        getline(datos, codigo, ';');
        getline(datos, nombre);
        int codPais = stoi(codigo);
        if (!arbolPaises.Buscarvalor(codPais)){
            arbolPaises.InsertaNodo(codPais, 0, nombre);
        }
    }
    archivo.close();
    cout << "Paises cargados correctamente." << endl;
}

void cargarCiudades(){
    ifstream archivo("CSV/Ciudades.csv");
    if (!archivo)
    {
        cout << "Error al abrir Ciudades.csv" << endl;
        return;
    }
    string linea;
    string textoCodPais, textoCodCiudad, nombre;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea))
    {
        stringstream datos(linea);
        getline(datos, textoCodPais, ';');
        getline(datos, textoCodCiudad, ';');
        getline(datos, nombre);
        int codPais = stoi(textoCodPais);
        int codCiudad = stoi(textoCodCiudad);
        // Verificar que el pais exista.
        if (!arbolPaises.Buscarvalor(codPais))
        {
            cout << "No se puede cargar la ciudad " << codCiudad
                << ": el pais " << codPais << " no existe." << endl;
            continue;
        }
        // Evitar ciudades duplicadas dentro del mismo pais.
        if (arbolCiudades.Buscarvalor(codPais, codCiudad))
        {
            cout << "Ciudad duplicada: pais " << codPais
                << ", ciudad " << codCiudad << endl;
            continue;
        }
        arbolCiudades.InsertaNodo(codPais, codCiudad, nombre);
    }
    archivo.close();
    cout << "Ciudades cargadas correctamente." << endl;
}

void cargarTratamientos(){
    ifstream archivo("CSV/Tratamiento.csv");
    if (!archivo) {
        cout << "Error al abrir Tratamiento.csv" << endl;
        return;
    }

    string linea;
    string idTratamiento, nombre, descripcion, Costo;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)) {
        stringstream datos(linea);
        getline(datos, idTratamiento, ';');
        getline(datos, nombre, ';');
        getline(datos, descripcion, ';');
        getline(datos, Costo);

        int id = stoi(idTratamiento);
        int costo = stoi(Costo);
        if (!arbolTratamientos.Buscarvalor(id)) {
            arbolTratamientos.Insertar(id, nombre, descripcion, costo);
        }
    }
    archivo.close();
    cout << "Tratamientos cargados correctamente." << endl;
}

void cargarDiagnosticos(){
    ifstream archivo("CSV/Diagnostico.csv");
    if (!archivo)
    {
        cout << "Error al abrir Diagnostico.csv" << endl;
        return;
    }
    string linea;
    string codigo;
    string nombre;
    string descripcion;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)){
        stringstream datos(linea);
        getline(datos, codigo, ';');
        getline(datos, nombre, ';');
        getline(datos, descripcion);
        if (!arbolDiagnosticos.Buscarvalor(codigo))
        {
            arbolDiagnosticos.Insertar(codigo, nombre, descripcion);
        }
    }
    archivo.close();
    cout << "Diagnosticos cargados correctamente." << endl;
}

void cargarEspecialidades(){
    ifstream archivo("CSV/Especialidades.csv");
    if (!archivo)
    {
        cout << "Error al abrir Especialidades.csv" << endl;
        return;
    }
    string linea;
    string codigo;
    string nombre;
    string descripcion;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)){
        stringstream datos(linea);
        getline(datos, codigo, ';');
        getline(datos, nombre, ';');
        getline(datos, descripcion);
        if (!arbolEspecialidades.Buscarvalor(codigo)) //evita especialidades repetidas
        {
            arbolEspecialidades.Insertar(codigo, nombre, descripcion);
        }
    }
    archivo.close();
    cout << "Especialidades cargadas correctamente." << endl;
}

void cargarHabitaciones(){
    ifstream archivo("CSV/Habitaciones.csv");
    if (!archivo)
    {
        cout << "Error al abrir Habitaciones.csv" << endl;
        return;
    }
    string linea;
    string campo;
    string piso;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)){
        stringstream datos(linea);
        getline(datos, campo, ';');
        int id = stoi(campo);
        getline(datos, campo, ';');
        int numero = stoi(campo);
        getline(datos, piso, ';');
        getline(datos, campo, ';');
        int tipo = stoi(campo);
        getline(datos, campo);
        int estado = stoi(campo);
        if (!arbolHabitaciones.BuscarValor(id)) //evita habitaciones repetidas
        {
            arbolHabitaciones.Insertar(id, numero, piso, tipo, estado);
        }
    }
    archivo.close();
    cout << "Habitaciones cargadas correctamente." << endl;
}


void cargarArchivos()
{
    cargarPaises();
    cargarCiudades();
    cargarEspecialidades();
    cargarHabitaciones();
	cargarTratamientos();
    cargarDiagnosticos();
}


//---------MENÚ-------

void menuInserciones() {
    int opcion;
    do {
        cout << "\n===== INSERCIONES =====" << endl;
        cout << "1. Pais" << endl;
        cout << "2. Ciudad" << endl;
        cout << "3. Especialidad" << endl;
        cout << "4. Habitacion" << endl;
        cout << "5. Diagnostico" << endl;
        cout << "6. Tratamiento" << endl;
        cout << "0. Regresar" << endl;
        cout << "Digite una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            insertarPais();
            break;
        case 2:
            insertarCiudad();
            break;
        case 3:
            insertarEspecialidad();
            break;
        case 4:
            insertarHabitacion();
            break;
        case 5:
            insertarDiagnostico();
            break;
        case 6:
            insertarTratamiento();
            break;
        case 0:
            cout << "Regresando..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

void menuBusquedas() {
    int opcion;
    do {
        cout << "\n===== BUSQUEDAS =====" << endl;
        cout << "1. Pais" << endl;
        cout << "2. Ciudad" << endl;
        cout << "3. Especialidad" << endl;
        cout << "4. Habitacion" << endl;
        cout << "5. Diagnostico" << endl;
        cout << "6. Tratamiento" << endl;
        cout << "0. Regresar" << endl;
        cout << "Digite una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            buscarPais();
            break;
        case 2:
            buscarCiudad();
            break;
        case 3:
            buscarEspecialidad();
            break;
        case 4:
            buscarHabitacion();
            break;
        case 5:
            buscarDiagnostico();
            break;
        case 6:
            buscarTratamiento();
            break;
        case 0:
            cout << "Regresando..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

/*void menuModificaciones()
{
    int opcion;
    do {
        cout << "\n===== MODIFICACIONES =====" << endl;
        cout << "1. Pais" << endl;
        cout << "2. Ciudad" << endl;
        cout << "3. Paciente" << endl;
        cout << "4. Medico" << endl;
        cout << "5. Especialidad" << endl;
        cout << "6. Cita" << endl;
        cout << "7. Habitacion" << endl;
        cout << "8. Hospitalizacion" << endl;
        cout << "0. Regresar" << endl;
        cout << "Digite una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            modificarPais();
            break;
        case 2:
            modificarCiudad();
            break;
        case 3:
            modificarPaciente();
            break;
        case 4:
            modificarMedico();
            break;
        case 5:
            modificarEspecialidad();
            break;
        case 6:
            modificarCita();
            break;
        case 7:
            modificarHabitacion();
            break;
        case 8:
            modificarHospitalizacion();
            break;
        case 0:
            cout << "Regresando..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}*/

void menuMantenimiento() {
    int opcion;
    do {
        cout << "\n===== MANTENIMIENTO DE LA BASE DE DATOS =====" << endl;
        cout << "1. Inserciones" << endl;
        cout << "2. Busquedas" << endl;
        cout << "0. Regresar" << endl;
        cout << "Digite una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuInserciones();
            break;
        case 2:
            menuBusquedas();
            break;
        case 0:
            cout << "Regresando..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

int main() {
    int opcion;
    do {
        cout << "\n===== SISTEMA DE GESTION HOSPITALARIA =====" << endl;
        cout << "1. Leer archivos y construir los arboles" << endl;
        cout << "2. Mantenimiento de la base de datos" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cargarArchivos();
            break;
        case 2:
            menuMantenimiento();
            break;
        case 0:
            cout << "Programa finalizado." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
    return 0;
}