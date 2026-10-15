#ifndef PAGINA_H
#define PAGINA_H

const int MAX = 4; // Maximo de claves por nodo               x x x
const int MIN = 2; // Minimo de claves por nodo

class Pagina {
public:
    int Cuenta;               // Numero de claves en la pagina
    int Claves[MAX + 1];      // Arreglo de claves (indexado desde 1)
    Pagina* Ramas[MAX + 1];   // Ramas hijas (indexadas desde 0)

    Pagina();

    friend class ArbolB;
};

#endif

