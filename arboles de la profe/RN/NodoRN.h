#ifndef NODORN_H
#define NODORN_H

class NodoRN {
public:
    int valor;
    bool color; // true = rojo, false = negro
    NodoRN* padre;
    NodoRN* Hizq;
    NodoRN* Hder;

    NodoRN(int val);
};

#endif


