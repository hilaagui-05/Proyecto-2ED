#include "Binario.h"
#include <iostream>
using namespace std;

// Constructor
Binario::Binario() 
{
    raiz = nullptr;
}

// Destructor
Binario::~Binario() 
{
    LiberarMemoria(raiz);
}

// Metodo publico para insertar
void Binario::Insertar(int x) 
{
    bool Hh = false;
    InsertarBalanceado(raiz,Hh,x);
}

// Metodo publico para mostrar el arbol se usa Inorden
void Binario::Mostrar() 
{
    if (EstaVacio()) 
	{
        cout << "Arbol esta vacio" << endl;
    } 
	else 
	{
        cout << "Arbol: ";
        MostrarPreorden(raiz);
        cout << endl;
    }
}

// Verificar si esta vacio
bool Binario::EstaVacio() 
{
    return raiz==nullptr;
}

// Limpiar arbol
void Binario::Limpiar() 
{
    LiberarMemoria(raiz);
    raiz = nullptr;
}

// Borrar nodo auxiliar
void Binario::Borrar(pNodoBinario& nodo,bool& Hh) 
{
    pNodoBinario q;
    if (nodo->Hder!=nullptr) 
	{
        Borrar(nodo->Hder,Hh);
        if (Hh)
            Equilibrar2(nodo,Hh);
    } 
	else 
	{
        q=nodo;
        nodo=nodo->Hizq;
        delete q;
        Hh=true;
    }
}

// Metodo publico para eliminar
void Binario::Eliminar(int x) 
{
    bool Hh=false;
    BorrarBalanceado(raiz,Hh,x);
}


// Eliminar balanceado
void Binario::BorrarBalanceado(pNodoBinario& raiz,bool& Hh,int x) 
{
    pNodoBinario q, reemplazo;

    if (raiz!=nullptr) 
    {
        // Buscar por izquierda
        if (x <raiz->valor) 
        {
            BorrarBalanceado(raiz->Hizq,Hh,x);

            if (Hh)
                Equilibrar1(raiz,Hh);
        }

        // Buscar por derecha
        else if (x > raiz->valor) 
        {
            BorrarBalanceado(raiz->Hder,Hh,x);

            if (Hh)
                Equilibrar2(raiz,Hh);
        }

        // Nodo encontrado
        else 
        {
            q = raiz;

            // Caso 1: solo hijo derecho o sin hijos
            if (q->Hizq==nullptr) 
            {
                raiz=q->Hder;
                delete q;
                Hh=true;
            }

            // Caso 2: solo hijo izquierdo
            else if (q->Hder==nullptr) 
            {
                raiz=q->Hizq;
                delete q;
                Hh=true;
            }

            // Caso 3: dos hijos
            else 
            {
                // Buscar el mayor de la izquierda
                reemplazo=q->Hizq;

                while (reemplazo->Hder!=nullptr)
                {
                    reemplazo=reemplazo->Hder;
                }

                // Copiar valor del reemplazo
                q->valor=reemplazo->valor;

                // Borrar el nodo reemplazo
                BorrarBalanceado(q->Hizq,Hh,reemplazo->valor);

                // Reequilibrar
                if (Hh)
                    Equilibrar1(raiz,Hh);
            }
        }
    }
}

//  Equilibrar1
void Binario::Equilibrar1(NodoBinario*& n,bool& Hh) 
{
    NodoBinario *n1;
    switch (n->FB) 
	{
        case -1: 
            n->FB = 0;
            break;
        case 0: 
            n->FB = 1;
            Hh = false;
            break;
        case 1: 
            n1 = n->Hder;
            if (n1->FB >= 0) 
			{
                if (n1->FB == 0) 
				{  
                    Hh = false;
                    RotacionSimpleDerecha(n, n1);
                } 
				else 
				{
                    RotacionDobleDerecha(n, n1);
                }
            }
            break;
    }
}

// Equilibrar2
void Binario::Equilibrar2(NodoBinario*& n, bool& Hh)
{
    NodoBinario *n1;
    switch (n->FB)
	{
        case 1: 
            n->FB = 0;
            break;
        case 0: 
            n->FB = -1;  
            Hh = false;
            break;
        case -1: 
            n1 = n->Hizq;
            if (n1->FB <= 0) 
			{
                if (n1->FB == 0) 
				{  
                    Hh = false;
                    RotacionSimpleIzquierda(n, n1);
                } 
				else 
				{
                    RotacionDobleIzquierda(n, n1);
                }
            }
            break;
    }
}

//InsertarBalanceado
void Binario::InsertarBalanceado(pNodoBinario& raiz, bool& Hh, int x) 
{
    pNodoBinario n1;
    
    if (raiz == nullptr) 
	{  
        raiz = new NodoBinario(x);
        cout << "Insertado: " << raiz->valor << endl;  
        Hh = true;
    } 
	else 
	{
        if (x < raiz->valor) 
		{
            InsertarBalanceado(raiz->Hizq, Hh, x);
            if (Hh) 
			{
                switch (raiz->FB) 
				{ 
                    case 1: 
                        raiz->FB = 0;
                        Hh = false;
                        break;
                    case 0: 
                        raiz->FB = -1;
                        break;
                    case -1: 
                        n1 = raiz->Hizq;
                        if (n1->FB == -1) 
						{ 
                            RotacionSimpleIzquierda(raiz, n1);
                        } 
						else 
						{
                            RotacionDobleIzquierda(raiz, n1);
                        }
                        Hh = false;
                        break;
                }
            }
        } else 
		   if (x > raiz->valor) 
		   { 
            InsertarBalanceado(raiz->Hder, Hh, x);
            if (Hh) 
			{
                switch (raiz->FB) 
				{
                    case -1: 
                        raiz->FB = 0;
                        Hh = false;
                        break;
                    case 0: 
                        raiz->FB = 1;
                        break;
                    case 1:
                        n1 = raiz->Hder;
                        if (n1->FB == 1) 
						{  
                            RotacionSimpleDerecha(raiz, n1);
                        } 
						else 
						{
                            RotacionDobleDerecha(raiz, n1);
                        }
                        Hh = false;
                        break;
                }
            }
        }
        
    }
}

//  RotacionDobleIzquierda
void Binario::RotacionDobleIzquierda(NodoBinario*& n, NodoBinario*& n1) 
{
    NodoBinario *n2;
    n2 = n1->Hder;
    n->Hizq = n2->Hder;
    n2->Hder = n;
    n1->Hder = n2->Hizq;
    n2->Hizq = n1;
    
    if (n2->FB == 1) 
	{
        n1->FB = -1;
    } 
	else 
	{
        n1->FB = 0;
    }
    
    if (n2->FB == -1) 
	{
        n->FB = 1;
    } 
	else 
	{
        n->FB = 0;
    }
    
    n2->FB = 0;
    n = n2;
}

// RotacionDobleDerecha
void Binario::RotacionDobleDerecha(NodoBinario*& n, NodoBinario*& n1) 
{
    NodoBinario *n2;
    n2 = n1->Hizq;
    n->Hder = n2->Hizq;
    n2->Hizq = n;
    n1->Hizq = n2->Hder;
    n2->Hder = n1;
    
    if (n2->FB == 1) 
	{
        n->FB = -1;
    } 
	else 
	{
        n->FB = 0;
    }
    
    if (n2->FB == -1) 
	{
        n1->FB = 1;
    } 
	else 
	{
        n1->FB = 0;
    }
    
    n2->FB = 0;
    n = n2;
}

//  RotacionSimpleDerecha
void Binario::RotacionSimpleDerecha(NodoBinario*& n, NodoBinario*& n1) 
{
    n->Hder = n1->Hizq;
    n1->Hizq = n;
    
    if (n1->FB == 1) 
	{
        n->FB = 0;
        n1->FB = 0;
    } 
	else 
	{
        n->FB = 1;
        n1->FB = -1;
    }
    n = n1;
}

//  RotacionSimpleIzquierda
void Binario::RotacionSimpleIzquierda(NodoBinario*& n, NodoBinario*& n1) 
{
    n->Hizq = n1->Hder;
    n1->Hder = n;
    
    if (n1->FB == -1) 
	{
        n->FB = 0;
        n1->FB = 0;
    } 
	else 
	{
        n->FB = -1;
        n1->FB = 1;  
    }
    n = n1;
}

// Mostrar Arbol
void Binario::MostrarInorden(pNodoBinario n) 
{
    if (n != nullptr) 
	{
        MostrarInorden(n->Hizq);
        cout << n->valor << " ";
        MostrarInorden(n->Hder);
    }
}

// Mostrar Arbol
void Binario::MostrarPreorden(pNodoBinario n) 
{
    if (n != nullptr) 
	{
        cout << n->valor << " ";
		MostrarPreorden(n->Hizq);
        MostrarPreorden(n->Hder);
    }
}

//Liberar memoria
void Binario::LiberarMemoria(pNodoBinario n) 
{
    if (n != nullptr) 
	{
        LiberarMemoria(n->Hizq);
        LiberarMemoria(n->Hder);
        delete n;
    }
}
