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

// Quita el '\r' final (archivos con saltos de linea de Windows) y devuelve true
// si la linea no trae datos: vacia o con solo ';' y espacios.
bool lineaVacia(string& linea)
{
    if (!linea.empty() && linea[linea.length() - 1] == '\r')
    {
        linea.erase(linea.length() - 1);
    }
    for (int i = 0; i < (int)linea.length(); i++)
    {
        if (linea[i] != ';' && linea[i] != ' ' && linea[i] != '\t')
        {
            return false;
        }
    }
    return true;
}

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
        if (lineaVacia(linea)) continue; //ignora filas vacias y quita el \r del final
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
        if (lineaVacia(linea)) continue; //ignora filas vacias y quita el \r del final
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
        if (lineaVacia(linea)) continue; //ignora filas vacias y quita el \r del final
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
        if (lineaVacia(linea)) continue; //ignora filas vacias y quita el \r del final
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
        if (lineaVacia(linea)) continue; //ignora filas vacias y quita el \r del final
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
        if (lineaVacia(linea)) continue; //ignora filas vacias y quita el \r del final
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


void cargarPacientes(){
    ifstream archivo("CSV/Pacientes.csv");
    if (!archivo)
    {
        cout << "Error al abrir Pacientes.csv" << endl;
        return;
    }
    string linea;
    string idPaciente, nombre, fechaNacimiento;
    string telefono, codPais, codCiudad, correo;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)){
        if (lineaVacia(linea)) continue; //ignora filas vacias y quita el \r del final
        stringstream datos(linea);
        getline(datos, idPaciente, ';');
        getline(datos, nombre, ';');
        getline(datos, fechaNacimiento, ';');
        getline(datos, telefono, ';');
        getline(datos, codPais, ';');
        getline(datos, codCiudad, ';');
        getline(datos, correo);
        int id = stoi(idPaciente);
        int pais = stoi(codPais);
        int ciudad = stoi(codCiudad);

        // Verificar que el pais y la ciudad existan.
        if (!arbolPaises.Buscarvalor(pais)){
            cout << "No se puede cargar el paciente "
                << id
                << ": el pais no existe." << endl;
            continue;
        }
        if (!arbolCiudades.Buscarvalor(
            pais, ciudad))
        {
            cout << "No se puede cargar el paciente " << id
                << ": la ciudad no existe para ese pais."<< endl;
            continue;
        }
        if (arbolPacientes.Buscar(id) != nullptr){
            cout << "Paciente duplicado: " << id << endl;
            continue;
        }
        RegistroB paciente;
        paciente.clave = id;
        paciente.nombre = nombre;
        paciente.fechaNacimiento = fechaNacimiento;
        paciente.telefono = telefono;
        paciente.codPais = pais;
        paciente.codCiudad = ciudad;
        paciente.correo = correo;
        arbolPacientes.Insertar(paciente);
    }
    archivo.close();
    cout << "Pacientes cargados correctamente." << endl;
}

void cargarMedicos(){
    ifstream archivo("CSV/Medicos.csv");
    if (!archivo)
    {
        cout << "Error al abrir Medicos.csv" << endl;
        return;
    }
    string linea;
    string idMedico, nombre, telefono, correo, idEspecialidad;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)){
        if (lineaVacia(linea)) continue; //ignora filas vacias y quita el \r del final
        stringstream datos(linea);
        getline(datos, idMedico, ';');
        getline(datos, nombre, ';');
        getline(datos, telefono, ';');
        getline(datos, correo, ';');
        getline(datos, idEspecialidad);
        int id = stoi(idMedico);
        // Verificar que la especialidad exista.
        if (!arbolEspecialidades.Buscarvalor(idEspecialidad))
        {
            cout << "No se puede cargar el medico " << id
                << ": la especialidad no existe." << endl;
            continue;
        }

        if (arbolMedicos.Buscar(id) != nullptr)
        {
            cout << "Medico duplicado: " << id << endl;
            continue;
        }
        RegistroB medico;
        medico.clave = id;
        medico.nombre = nombre;
        medico.telefono = telefono;
        medico.correo = correo;
        medico.idEspecialidad = stoi(idEspecialidad);

        arbolMedicos.Insertar(medico);
    }
    archivo.close();
    cout << "Medicos cargados correctamente." << endl;
}

void cargarCitas() {
    ifstream archivo("CSV/Citas.csv");
    if (!archivo)
    {
        cout << "Error al abrir Citas.csv" << endl;
        return;
    }
    string linea;
    string idCita, idPaciente, idMedico, idEspecialidad, fecha, hora, motivo, estado;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)) {
        if (lineaVacia(linea)) continue; //ignora filas vacias y quita el \r del final
        if (linea[linea.length() - 1] == '\r') linea.erase(linea.length() - 1); //quita el salto de linea de Windows
        stringstream datos(linea);
        getline(datos, idCita, ';');
        getline(datos, idPaciente, ';');
        getline(datos, idMedico, ';');
        getline(datos, idEspecialidad, ';');
        getline(datos, fecha, ';');
        getline(datos, hora, ';');
        getline(datos, motivo, ';');
        getline(datos, estado);
        int id = stoi(idCita);
        int paciente = stoi(idPaciente);
        int medico = stoi(idMedico);
        // Las validaciones de paciente y medico se hacen en las inserciones y busquedas del menu.
        if (arbolCitas.BuscarValor(id)) {
            cout << "Cita duplicada: " << id << endl;
            continue;
        }
        arbolCitas.Insertar(id, paciente, medico, stoi(idEspecialidad), fecha, hora, motivo, stoi(estado));
    }
    archivo.close();
    cout << "Citas cargadas correctamente." << endl;
}

void cargarHospitalizaciones() {
    ifstream archivo("CSV/Hospitalizaciones.csv");
    if (!archivo)
    {
        cout << "Error al abrir Hospitalizaciones.csv" << endl;
        return;
    }
    string linea;
    string idHosp, idPaciente, idHabitacion, idMedico, fechaIngreso, fechaSalida, motivo;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)) {
        if (lineaVacia(linea)) continue; //ignora filas vacias y quita el \r del final
        if (linea[linea.length() - 1] == '\r') linea.erase(linea.length() - 1); //quita el salto de linea de Windows
        stringstream datos(linea);
        getline(datos, idHosp, ';');
        getline(datos, idPaciente, ';');
        getline(datos, idHabitacion, ';');
        getline(datos, idMedico, ';');
        getline(datos, fechaIngreso, ';');
        getline(datos, fechaSalida, ';');
        getline(datos, motivo);
        int id = stoi(idHosp);
        int paciente = stoi(idPaciente);
        int habitacion = stoi(idHabitacion);
        // Las validaciones de paciente y habitacion se hacen en las inserciones y busquedas del menu.
        if (arbolHospitalizaciones.Buscarvalor(id)) {
            cout << "Hospitalizacion duplicada: " << id << endl;
            continue;
        }
        arbolHospitalizaciones.Insertar(id, paciente, habitacion, stoi(idMedico), fechaIngreso, fechaSalida, motivo);
    }
    archivo.close();
    cout << "Hospitalizaciones cargadas correctamente." << endl;
}

void cargarArchivos()
{
    cargarPaises();
    cargarCiudades();
    cargarEspecialidades();
    cargarPacientes();
    cargarMedicos();
    cargarHabitaciones();
    cargarTratamientos();
    cargarDiagnosticos();
    cargarCitas();
    cargarHospitalizaciones();
}


//---------MENÚ-------

void menuInserciones() {
    int opcion;
    do {
        cout << "\n===== INSERCIONES =====" << endl;
        cout << "1. Pais" << endl;
        cout << "2. Ciudad" << endl;
        cout << "3. Paciente" << endl;
        cout << "4. Medico" << endl;
        cout << "5. Especialidad" << endl;
        cout << "6. Habitacion" << endl;
        cout << "7. Cita" << endl;
        cout << "8. Hospitalizacion" << endl;
        cout << "9. Diagnostico" << endl;
        cout << "10. Tratamiento" << endl;
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
            insertarPaciente();
            break;
        case 4:
            insertarMedico();
            break;
        case 5:
            insertarEspecialidad();
            break;
        case 6:
            insertarHabitacion();
            break;
        case 7:
            insertarCita();
            break;
        case 8:
            insertarHospitalizacion();
            break;
        case 9:
            insertarDiagnostico();
            break;
        case 10:
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
        cout << "3. Paciente" << endl;
        cout << "4. Medico" << endl;
        cout << "5. Especialidad" << endl;
        cout << "6. Habitacion" << endl;
        cout << "7. Cita" << endl;
        cout << "8. Hospitalizacion" << endl;
        cout << "9. Diagnostico" << endl;
        cout << "10. Tratamiento" << endl;
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
            buscarPaciente();
            break;
        case 4:
            buscarMedico();
            break;
        case 5:
            buscarEspecialidad();
            break;
        case 6:
            buscarHabitacion();
            break;
        case 7:
            buscarCita();
            break;
        case 8:
            buscarHospitalizacion();
            break;
        case 9:
            buscarDiagnostico();
            break;
        case 10:
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

void menuModificaciones() {
    int opcion;
    do {
        cout << "\n===== MODIFICACIONES =====" << endl;
        cout << "1. Pais" << endl;
        cout << "2. Ciudad" << endl;
        cout << "3. Paciente" << endl;
        cout << "4. Medico" << endl;
        cout << "5. Especialidad" << endl;
        cout << "6. Habitacion" << endl;
        cout << "7. Cita" << endl;
        cout << "8. Hospitalizacion" << endl;
        cout << "9. Diagnostico" << endl;
        cout << "10. Tratamiento" << endl;
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
            modificarHabitacion();
            break;
        case 7:
            modificarCita();
            break;
        case 8:
            modificarHospitalizacion();
            break;
        case 9:
            modificarDiagnostico();
            break;
        case 10:
            modificarTratamiento();
            break;
        case 0:
            cout << "Regresando..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

void menuMantenimiento() {
    int opcion;
    do {
        cout << "\n===== MANTENIMIENTO DE LA BASE DE DATOS =====" << endl;
        cout << "1. Inserciones" << endl;
        cout << "2. Busquedas" << endl;
        cout << "3. Modificaciones" << endl;
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
        case 3:
            menuModificaciones();
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