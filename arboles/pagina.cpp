#include "pagina.h"

Pagina::Pagina() {
    Cuenta = 0;
    for (int i = 0; i <= MAX; i++) {
        Claves[i] = RegistroB();
        Ramas[i] = nullptr;
    }
}

