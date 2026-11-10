#include "arbolB.h"

using namespace std;

//constructor
ArbolB::ArbolB()
{
    Raiz = nullptr;
}

// Busca una clave dentro de una pagina
void ArbolB::BuscarNodo(int Clave, Pagina* P, bool& Encontrado, int& K)
{
    // Buscar la posicion donde deberia estar la clave
    K = 1;
    // Avanzar mientras K este dentro del rango y la clave sea mayor
    while (K <= P->Cuenta && Clave > P->Claves[K].clave)
    {
        K++;
    }
    // Verificar si encontramos la clave exacta
    if (K <= P->Cuenta && Clave == P->Claves[K].clave)
    {
        Encontrado = true;
        // K ya tiene la posicion correcta donde esta la clave
    }
    else {
        Encontrado = false;
        // K debe ser la posicion de la rama donde seguir buscando
        K--;
    }
}

void ArbolB::Insertar(const RegistroB& C1){ //inserta un registro en el arbol
    bool EmpujaArriba;
    RegistroB X;
    Pagina* Xr;

    Empujar(C1, Raiz, EmpujaArriba, X, Xr);
    if (EmpujaArriba)
    {
        Pagina* P = new Pagina();
        P->Cuenta = 1;
        P->Claves[1] = X;
        P->Ramas[0] = Raiz;
        P->Ramas[1] = Xr;
        Raiz = P;
    }
}

// Inserta recursivamente el registro
void ArbolB::Empujar(const RegistroB& C1, Pagina* R, bool& EmpujaArriba, RegistroB& Mdna, Pagina*& Xr)
{
    int K;
    bool Esta;
    if (R == nullptr)
    {
        EmpujaArriba = true;
        Mdna = C1;
        Xr = nullptr;
    }else{
        BuscarNodo(C1.clave, R, Esta, K);
        if (Esta)
        {
            cout << "Elemento repetido: " << C1.clave << endl;
            EmpujaArriba = false;
            return;
        }
        Empujar(C1, R->Ramas[K], EmpujaArriba, Mdna, Xr);
        if (EmpujaArriba)
        {
            if (R->Cuenta < MAX)
            {
                EmpujaArriba = false;
                MeterHoja(Mdna, Xr, R, K);
            }
            else
            {
                EmpujaArriba = true;
                DividirNodo(Mdna, Xr, R, K, Mdna, Xr);
            }
        }
    }
}

//Inserta un registro dentro de una pagina
void ArbolB::MeterHoja(const RegistroB& X, Pagina* Xder, Pagina* P, int K)
{
    for (int i = P->Cuenta; i > K; i--)
    {
        P->Claves[i + 1] = P->Claves[i];
        P->Ramas[i + 1] = P->Ramas[i];
    }
    P->Claves[K + 1] = X;
    P->Ramas[K + 1] = Xder;
    P->Cuenta++;
}

//Divide una pagina cuando esta llena
void ArbolB::DividirNodo(const RegistroB& X, Pagina* Xder, Pagina* P, int K, RegistroB& Mda, Pagina*& Mder){
    int PosMda, i;
    if (K <= MIN) //3<2x
        PosMda = MIN;
    else
        PosMda = MIN + 1;
    Mder = new Pagina();
    for (i = PosMda + 1; i <= MAX; i++)
    { 
        Mder->Claves[i - PosMda] = P->Claves[i]; //4-3=1
        Mder->Ramas[i - PosMda] = P->Ramas[i];
    }
    Mder->Cuenta = MAX - PosMda;
    P->Cuenta = PosMda;
    if (K <= MIN)
    {
        MeterHoja(X, Xder, P, K);
    }
    else
    {
        MeterHoja(X, Xder, Mder, K - PosMda);
    }
    Mda = P->Claves[P->Cuenta];
    Mder->Ramas[0] = P->Ramas[P->Cuenta];
    P->Cuenta--;
}

// Busca un registro por su id
RegistroB* ArbolB::Buscar(int clave){
    Pagina* P = Raiz;
    bool Encontrado;
    int K;
    while (P != nullptr)
    {
        BuscarNodo(clave, P, Encontrado, K);
        if (Encontrado)
        {
            return &P->Claves[K];
        }
        P = P->Ramas[K];
    }
    return nullptr;
}

// Muestra los registros almacenados en el arbol
void ArbolB::Mostrar(Pagina* P, int nivel){
    if (P != nullptr)
    {
        for (int i = 1; i <= P->Cuenta; i++){
            Mostrar(P->Ramas[i - 1], nivel + 1);
            for (int j = 0; j < nivel; j++)
            {
                cout << "   ";
            }
            cout << "Id: " << P->Claves[i].clave << endl;
            cout << "Nombre: " << P->Claves[i].nombre << endl;
            if (!P->Claves[i].fechaNacimiento.empty())
            {
                cout << "Fecha de nacimiento: " << P->Claves[i].fechaNacimiento << endl;
                cout << "Codigo de pais: " << P->Claves[i].codPais << endl;
                cout << "Codigo de ciudad: " << P->Claves[i].codCiudad << endl;
            }
            cout << "Telefono: " << P->Claves[i].telefono << endl;
            cout << "Correo: " << P->Claves[i].correo << endl;
            if (P->Claves[i].idEspecialidad != 0)
            {
                cout << "Id de especialidad: " << P->Claves[i].idEspecialidad << endl;
            }
        }
        Mostrar(P->Ramas[P->Cuenta], nivel + 1);
    }
}

void ArbolB::Imprimir() {
    cout << "Recorrido en preorden:\n";
    Mostrar(Raiz, 0);
}

// Elimina el registro con esa clave. Devuelve false si no existe.
bool ArbolB::Eliminar(int C1)
{
    bool Encontrado;
    Pagina* P;

    EliminarRegistro(C1, Raiz, Encontrado);

    if (!Encontrado)
    {
        return false;
    }

    // Si la raiz quedo sin claves, el arbol baja un nivel
    if (Raiz != nullptr && Raiz->Cuenta == 0)
    {
        P = Raiz;
        Raiz = Raiz->Ramas[0];
        delete P;
    }
    return true;
}

void ArbolB::EliminarRegistro(int C1, Pagina*& R, bool& Encontrado)
{
    int K = 0;

    if (ArbolVacio(R))
    {
        Encontrado = false;
    }
    else
    {
        BuscarNodo(C1, R, Encontrado, K);
        if (Encontrado) {
            if (R->Ramas[K] == nullptr)
            {
                Quitar(R, K);
            }
            else
            {
                Sucesor(R, K);
                EliminarRegistro(R->Claves[K].clave, R->Ramas[K], Encontrado);
                if (!Encontrado)
                {
                    cout << "Error en el proceso\n";
                }
                // Si la rama quedo con menos claves del minimo, se restablece
                if (R->Ramas[K] != nullptr && R->Ramas[K]->Cuenta < MIN)
                {
                    Restablecer(R, K);
                }
            }
        }
        else
        {
            EliminarRegistro(C1, R->Ramas[K], Encontrado);
            if (R->Ramas[K] != nullptr && R->Ramas[K]->Cuenta < MIN)
            {
                Restablecer(R, K);
            }
        }
    }
}

void ArbolB::Quitar(Pagina* P, int K)
{
    for (int j = K + 1; j <= P->Cuenta; j++)
    {
        P->Claves[j - 1] = P->Claves[j];
        P->Ramas[j - 1] = P->Ramas[j];
    }
    P->Cuenta--;
}

// Copia en la posicion K el registro sucesor (el menor de la rama derecha)
void ArbolB::Sucesor(Pagina* P, int K)
{
    Pagina* Q = P->Ramas[K];
    while (Q->Ramas[0] != nullptr)
    {
        Q = Q->Ramas[0];
    }
    P->Claves[K] = Q->Claves[1];
}

void ArbolB::Restablecer(Pagina* P, int K)
{
    if (K > 0)
    {
        if (P->Ramas[K - 1]->Cuenta > MIN)
        {
            MoverDerecha(P, K);
        }
        else
        {
            Combina(P, K);
        }
    }
    else
    {
        if (P->Ramas[1]->Cuenta > MIN)
        {
            MoverIzquierda(P, 1);
        }
        else
        {
            Combina(P, 1);
        }
    }
}

void ArbolB::MoverDerecha(Pagina* P, int K)
{
    Pagina* H = P->Ramas[K];
    Pagina* HIzq = P->Ramas[K - 1];

    for (int j = H->Cuenta; j >= 1; j--)
    {
        H->Claves[j + 1] = H->Claves[j];
        H->Ramas[j + 1] = H->Ramas[j];
    }

    H->Ramas[1] = H->Ramas[0];
    H->Cuenta++;
    H->Claves[1] = P->Claves[K];
    H->Ramas[0] = HIzq->Ramas[HIzq->Cuenta];
    P->Claves[K] = HIzq->Claves[HIzq->Cuenta];
    HIzq->Cuenta--;
}

void ArbolB::MoverIzquierda(Pagina* P, int K)
{
    Pagina* HIzq = P->Ramas[K - 1];
    Pagina* H = P->Ramas[K];

    HIzq->Cuenta++;
    HIzq->Claves[HIzq->Cuenta] = P->Claves[K];
    HIzq->Ramas[HIzq->Cuenta] = H->Ramas[0];

    P->Claves[K] = H->Claves[1];
    H->Ramas[0] = H->Ramas[1];

    for (int j = 1; j < H->Cuenta; j++)
    {
        H->Claves[j] = H->Claves[j + 1];
        H->Ramas[j] = H->Ramas[j + 1];
    }

    H->Cuenta--;
}

void ArbolB::Combina(Pagina* P, int K)
{
    Pagina* Q = P->Ramas[K];
    Pagina* HIzq = P->Ramas[K - 1];

    HIzq->Cuenta++;
    HIzq->Claves[HIzq->Cuenta] = P->Claves[K];
    HIzq->Ramas[HIzq->Cuenta] = Q->Ramas[0];

    for (int j = 1; j <= Q->Cuenta; j++)
    {
        HIzq->Cuenta++;
        HIzq->Claves[HIzq->Cuenta] = Q->Claves[j];
        HIzq->Ramas[HIzq->Cuenta] = Q->Ramas[j];
    }

    for (int j = K; j < P->Cuenta; j++)
    {
        P->Claves[j] = P->Claves[j + 1];
        P->Ramas[j] = P->Ramas[j + 1];
    }

    P->Cuenta--;

    delete Q;
}

bool ArbolB::ArbolVacio(Pagina* P)
{
    return P == nullptr;
}

Pagina* ArbolB::obtenerRaiz()
{
    return Raiz;
}
