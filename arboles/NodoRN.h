#ifndef NODORN_H
#define NODORN_H

#include <string>
using namespace std;

class NodoRN {
public:
    int idTratamiento;
    string nombre;
    string descripcion;
    int costo;

    bool color; // true = rojo, false = negro
    NodoRN* padre;
    NodoRN* Hizq;
    NodoRN* Hder;

    NodoRN(int id, string nom, string desc, int cos);
};

#endif