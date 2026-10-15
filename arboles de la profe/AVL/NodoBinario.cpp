#include "NodoBinario.h"

// Constructor
NodoBinario::NodoBinario(int x) {
    valor = x;
    FB = 0; //Factor Balance
    Hizq = nullptr;
    Hder = nullptr;
}

// Destructor
NodoBinario::~NodoBinario() {
    
}
