#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

ArbolB arbolPacientes;

void insertarPaciente() {
    RegistroB paciente;
    int codPais, codCiudad;
    cout << "Id del paciente: ";
    cin >> paciente.clave;
    cin.ignore();
    if (arbolPacientes.Buscar(paciente.clave) != nullptr) { //que el paciente no exista
        cout << "El paciente ya existe." << endl;
        return;
    }
    cout << "Nombre: ";
    getline(cin, paciente.nombre);
    cout << "Fecha de nacimiento: ";
    getline(cin, paciente.fechaNacimiento);
    cout << "Telefono: ";
    getline(cin, paciente.telefono);
    cout << "Codigo del pais: ";
    cin >> codPais;
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    cin.ignore();
    if (!arbolCiudades.Buscarvalor(codPais, codCiudad)) {
        cout << "La ciudad no existe para ese pais." << endl;
        return;
    }
    cout << "Correo: ";
    getline(cin, paciente.correo);
    paciente.codPais = codPais;
    paciente.codCiudad = codCiudad;
    arbolPacientes.Insertar(paciente);
    cout << "Paciente insertado correctamente." << endl;
}

// Buscar paciente
void buscarPaciente() {
    int idPaciente, codPais, codCiudad;
    cout << "Codigo del pais: ";
    cin >> codPais;
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    if (!arbolCiudades.Buscarvalor(codPais, codCiudad)) {
        cout << "La ciudad no existe para ese pais." << endl;
        return;
    }

    cout << "Id del paciente: ";
    cin >> idPaciente;
    RegistroB* paciente = arbolPacientes.Buscar(idPaciente);
    if (paciente == nullptr ||
        paciente->codPais != codPais ||
        paciente->codCiudad != codCiudad)
    {
        cout << "No existe ese paciente en la ciudad indicada." << endl;
        return;
    }
    cout << "Id: " << paciente->clave << endl;
    cout << "Nombre: " << paciente->nombre << endl;
    cout << "Fecha de nacimiento: " << paciente->fechaNacimiento << endl;
    cout << "Telefono: " << paciente->telefono << endl;
    cout << "Codigo del pais: " << paciente->codPais << endl;
    cout << "Codigo de la ciudad: " << paciente->codCiudad << endl;
    cout << "Correo: " << paciente->correo << endl;
}

// Muestra todos los pacientes almacenados.
void mostrarPacientes()
{
    arbolPacientes.Imprimir();
}

// se valida que la ciudad exista y que el paciente exista en esa ciudad
// se puede modificar el telefono y/o el correo
void modificarPaciente() {
    int idPaciente, codPais, codCiudad;
    string telefono, correo;
    cout << "Codigo del pais: ";
    cin >> codPais;
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    if (!arbolCiudades.Buscarvalor(codPais, codCiudad)) { //que la ciudad exista
        cout << "La ciudad no existe para ese pais." << endl;
        return;
    }
    cout << "Id del paciente: ";
    cin >> idPaciente;
    cin.ignore(); //ignora el enter pendiente
    RegistroB* paciente = arbolPacientes.Buscar(idPaciente);
    if (paciente == nullptr ||
        paciente->codPais != codPais ||
        paciente->codCiudad != codCiudad)
    {
        cout << "No existe ese paciente en la ciudad indicada." << endl;
        return;
    }
    cout << "Nombre: " << paciente->nombre << endl;
    cout << "Telefono actual: " << paciente->telefono << endl;
    cout << "Nuevo telefono (Enter para dejarlo igual): ";
    getline(cin, telefono);
    cout << "Correo actual: " << paciente->correo << endl;
    cout << "Nuevo correo (Enter para dejarlo igual): ";
    getline(cin, correo);
    if (telefono.empty() && correo.empty()) {
        cout << "No se hicieron cambios." << endl;
        return;
    }
    if (!telefono.empty()) {
        paciente->telefono = telefono; //se modifica directamente en el arbol B
    }
    if (!correo.empty()) {
        paciente->correo = correo;
    }
    cout << "Paciente modificado correctamente." << endl;
    cout << "Telefono: " << paciente->telefono << endl;
    cout << "Correo: " << paciente->correo << endl;
}

// Busca el primer paciente de un pais (modo 1) o de una ciudad (modo 2). Devuelve -1 si no hay.
int primerPaciente(Pagina* p, int modo, int codPais, int codCiudad)
{
    if (p == nullptr)
    {
        return -1;
    }
    for (int i = 1; i <= p->Cuenta; i++)
    {
        int encontrado = primerPaciente(p->Ramas[i - 1], modo, codPais, codCiudad);
        if (encontrado != -1)
        {
            return encontrado;
        }
        RegistroB& paciente = p->Claves[i];
        if (modo == 1 && paciente.codPais == codPais)
        {
            return paciente.clave;
        }
        if (modo == 2 && paciente.codPais == codPais && paciente.codCiudad == codCiudad)
        {
            return paciente.clave;
        }
    }
    return primerPaciente(p->Ramas[p->Cuenta], modo, codPais, codCiudad);
}

// Borrado en cascada: elimina al paciente junto con sus citas y sus hospitalizaciones
void eliminarPacienteConRelacionados(int idPaciente)
{
    eliminarCitasDePaciente(idPaciente);
    eliminarHospitalizacionesDePaciente(idPaciente);
    arbolPacientes.Eliminar(idPaciente);
}

// Borrado en cascada: elimina los pacientes de una ciudad
void eliminarPacientesDeCiudad(int codPais, int codCiudad)
{
    int idPaciente = primerPaciente(arbolPacientes.obtenerRaiz(), 2, codPais, codCiudad);
    while (idPaciente != -1)
    {
        eliminarPacienteConRelacionados(idPaciente);
        idPaciente = primerPaciente(arbolPacientes.obtenerRaiz(), 2, codPais, codCiudad);
    }
}

// Borrado en cascada: elimina los pacientes de un pais
void eliminarPacientesDePais(int codPais)
{
    int idPaciente = primerPaciente(arbolPacientes.obtenerRaiz(), 1, codPais, 0);
    while (idPaciente != -1)
    {
        eliminarPacienteConRelacionados(idPaciente);
        idPaciente = primerPaciente(arbolPacientes.obtenerRaiz(), 1, codPais, 0);
    }
}

// Se valida que la ciudad exista y que el paciente exista en esa ciudad, luego se elimina.
void eliminarPaciente() {
    int idPaciente, codPais, codCiudad;
    cout << "Codigo del pais: ";
    cin >> codPais;
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    if (!arbolCiudades.Buscarvalor(codPais, codCiudad)) { //que la ciudad exista
        cout << "La ciudad no existe para ese pais." << endl;
        return;
    }
    cout << "Id del paciente: ";
    cin >> idPaciente;
    RegistroB* paciente = arbolPacientes.Buscar(idPaciente);
    if (paciente == nullptr ||
        paciente->codPais != codPais ||
        paciente->codCiudad != codCiudad)
    {
        cout << "No existe ese paciente en la ciudad indicada." << endl;
        return;
    }
    eliminarPacienteConRelacionados(idPaciente); //tambien se eliminan sus citas y hospitalizaciones
    cout << "Paciente eliminado correctamente." << endl;
}
