
#ifndef PAGINA_H
#define PAGINA_H

#include <string>

const int MAX = 4;
const int MIN = 2;

// Registro para pacientes y medicos
struct RegistroB{ //struct agrupa los datos, para almacenarlos como registros en las claves del árbolB
    int clave;
    std::string nombre;
    std::string fechaNacimiento;
    std::string telefono;
    int codPais;
    int codCiudad;
    std::string correo;
    int idEspecialidad;

    RegistroB(){
        clave = 0;
        codPais = 0;
        codCiudad = 0;
        idEspecialidad = 0;
    }
};

class Pagina{
public:
    int Cuenta;
    RegistroB Claves[MAX + 1];
    Pagina* Ramas[MAX + 1];
    Pagina();
    friend class ArbolB;
};

#endif
