#include "Pagina.h"

Pagina::Pagina() {
    Cuenta = 0;
    for (int i = 0; i <= MAX; i++) {
        Claves[i] = 0;
        Ramas[i] = nullptr;
    }
}

