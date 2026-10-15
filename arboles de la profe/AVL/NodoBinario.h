#ifndef NODO_BINARIO_H
#define NODO_BINARIO_H

class NodoBinario {
public:
    int valor;
    int FB;  // Factor de Balance
    NodoBinario* Hizq;  // Hijo izquierdo
    NodoBinario* Hder;  // Hijo derecho
    
    // Constructor
    NodoBinario(int x);
    
    // Destructor
    ~NodoBinario();
};

typedef NodoBinario* pNodoBinario;

#endif
