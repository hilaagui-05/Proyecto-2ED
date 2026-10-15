#include "BinarioRN.h"
#include <iostream>
using namespace std;

BinarioRN::BinarioRN() 
{
    raiz = nullptr;
}

BinarioRN::~BinarioRN() 
{
    LiberarMemoria(raiz);
}

void BinarioRN::Insertar(int valor) 
{
    pNodoRN nuevo = new NodoRN(valor);
    InsertarRN(nuevo);  
    ArreglaInsercion(nuevo);
}

void BinarioRN::InsertarRN(pNodoRN nodo) 
{
    pNodoRN actual = raiz;
    pNodoRN padre = nullptr;

    while (actual != nullptr) 
	{
        padre = actual;
        if (nodo->valor < actual->valor)
            actual = actual->Hizq;
        else
            actual = actual->Hder;
    }

    nodo->padre = padre;

    if (padre == nullptr)
        raiz = nodo;
    else 
	    if (nodo->valor < padre->valor)
           padre->Hizq = nodo;
        else
           padre->Hder = nodo;
}

void BinarioRN::ArreglaInsercion(pNodoRN nodo) 
{
    while (nodo != raiz && nodo->padre != nullptr && nodo->padre->color == true) 
	{
        pNodoRN padre = nodo->padre;
        pNodoRN abuelo = padre->padre;

        if (abuelo == nullptr)
            break;

        pNodoRN tio;
        bool padreEsIzquierdo;

        if (abuelo->Hizq == padre) 
		{
            padreEsIzquierdo = true;
            tio = abuelo->Hder;
        } 
		else 
		{
            padreEsIzquierdo = false;
            tio = abuelo->Hizq;
        }

        if (tio != nullptr && tio->color == true) 
		{
            cout << "Caso 1: tio rojo, recoloreando" << endl;
            cout<<endl;
            cout<<endl;
            padre->color = false;
            tio->color = false;
            abuelo->color = true;
            nodo = abuelo;
        } 
		else
		 {
            if (padreEsIzquierdo) 
			{
                if (nodo == padre->Hder) 
				{
                    cout << "Caso 2: nodo es hijo derecho, rotar izquierda en padre" << endl;
                    cout<<endl;
                    cout<<endl;
                    nodo = padre;
                    RotIzquierda(nodo);
                    padre = nodo->padre;
                    if (padre) 
					{
    					abuelo = padre->padre;
					} 
					else
					{
    					abuelo = nullptr;
					}
                }
                cout << "Caso 3: rotar derecha en abuelo" << endl;
                cout<<endl;
                cout<<endl;
                padre->color = false;
                if(abuelo) abuelo->color = true;
                RotDerecha(abuelo);
            } 
			else 
			{
                if (nodo == padre->Hizq) 
				{
                    cout << "Caso 2 espejo: nodo es hijo izquierdo, rotar derecha en padre" << endl;
                    cout<<endl;
                    cout<<endl;
                    nodo = padre;
                    RotDerecha(nodo);
                    padre = nodo->padre;
                    if (padre != nullptr) 
					{
   						abuelo = padre->padre;
					} 	
					else
					{
    					abuelo = nullptr;
					}
                }
                cout << "Caso 3 espejo: rotar izquierda en abuelo" << endl;
                cout<<endl;
                cout<<endl;
                padre->color = false;
                if(abuelo) abuelo->color = true;
                RotIzquierda(abuelo);
            }
            break;
        }
    }

    raiz->color = false;
}

void BinarioRN::RotIzquierda(pNodoRN nodo) 
{
    pNodoRN hijoDerecho = nodo->Hder;
    nodo->Hder = hijoDerecho->Hizq;

    if (hijoDerecho->Hizq != nullptr)
        hijoDerecho->Hizq->padre = nodo;

    hijoDerecho->padre = nodo->padre;

    if (nodo->padre == nullptr)
        raiz = hijoDerecho;
    else 
	    if (nodo == nodo->padre->Hizq)
           nodo->padre->Hizq = hijoDerecho;
        else
           nodo->padre->Hder = hijoDerecho;

    hijoDerecho->Hizq = nodo;
    nodo->padre = hijoDerecho;
}

void BinarioRN::RotDerecha(pNodoRN nodo) 
{
    pNodoRN hijoIzquierdo = nodo->Hizq;
    nodo->Hizq = hijoIzquierdo->Hder;

    if (hijoIzquierdo->Hder != nullptr)
        hijoIzquierdo->Hder->padre = nodo;

    hijoIzquierdo->padre = nodo->padre;

    if (nodo->padre == nullptr)
        raiz = hijoIzquierdo;
    else 
	    if (nodo == nodo->padre->Hder)
            nodo->padre->Hder = hijoIzquierdo;
        else
            nodo->padre->Hizq = hijoIzquierdo;

    hijoIzquierdo->Hder = nodo;
    nodo->padre = hijoIzquierdo;
}

void BinarioRN::Mostrar() 
{
    if (EstaVacio()) 
	{
        cout << "Arbol vacio" << endl;
    } 
	else 
	{
        cout << "Arbol en preorden: ";
        MostrarPreorden(raiz);
        cout << endl;
    }
}

void BinarioRN::MostrarPreorden(pNodoRN nodo) 
{
    if (nodo != nullptr) 
	{
        cout << nodo->valor << (nodo->color ? "(R) " : "(N) ");
        MostrarPreorden(nodo->Hizq);
        MostrarPreorden(nodo->Hder);
    }
}

void BinarioRN::MostrarInorden(pNodoRN nodo) 
{
    if (nodo != nullptr) 
	{
        MostrarInorden(nodo->Hizq);
        cout << nodo->valor << (nodo->color ? "(R) " : "(N) ");
        MostrarInorden(nodo->Hder);
    }
}

bool BinarioRN::EstaVacio() 
{
    return raiz == nullptr;
}

void BinarioRN::Limpiar() 
{
    LiberarMemoria(raiz);
    raiz = nullptr;
}

void BinarioRN::LiberarMemoria(pNodoRN nodo) 
{
    if (nodo != nullptr) 
	{
        LiberarMemoria(nodo->Hizq);
        LiberarMemoria(nodo->Hder);
        delete nodo;
    }
}

void BinarioRN::Eliminar(int valor) 
{
    pNodoRN nodo = raiz;
    while (nodo != nullptr && nodo->valor != valor) 
	{
        if (valor < nodo->valor)
            nodo = nodo->Hizq;
        else
            nodo = nodo->Hder;
    }
    if (nodo == nullptr)
        return;

    EliminarRN(nodo);
}

void BinarioRN::EliminarRN(pNodoRN z) 
{
    pNodoRN y = z;
    pNodoRN x;
    pNodoRN xPadre = nullptr;
    bool yOriginalColor = y->color;

    if (z->Hizq == nullptr) 
	{
        x = z->Hder;
        xPadre = z->padre;
        Sustitucion(z, z->Hder);
    } 
	else 
	    if (z->Hder == nullptr) 
		{
           x = z->Hizq;
           xPadre = z->padre;
           Sustitucion(z, z->Hizq);
        } 
		else
		{
           y = Minimo(z->Hder);
           yOriginalColor = y->color;
           x = y->Hder;
           xPadre = y->padre;
        
        if (y->padre == z) 
		{
            xPadre = y;
            if (x != nullptr) 
                x->padre = y;
        } 
		else 
		{
            Sustitucion(y, y->Hder);
            y->Hder = z->Hder;
            if (y->Hder != nullptr) 
                y->Hder->padre = y;
        }
        
        Sustitucion(z, y);
        y->Hizq = z->Hizq;
        if (y->Hizq != nullptr) 
            y->Hizq->padre = y;
        y->color = z->color;
    }

    delete z;

    if (!yOriginalColor) 
	{
        // Si x es nullptr, crear un nodo centinela temporal
        if (x == nullptr) 
		{
            pNodoRN centinela = new NodoRN(0);
            centinela->color = false;
            centinela->padre = xPadre;
            centinela->Hizq = nullptr;
            centinela->Hder = nullptr;
            
            // Conectar el centinela al padre
            if (xPadre != nullptr) 
			{
                if (xPadre->Hizq == nullptr)
                    xPadre->Hizq = centinela;
                else
                    xPadre->Hder = centinela;
            }
            
            ArreglaEliminacion(centinela);
            
            // Desconectar y eliminar el centinela
            if (xPadre != nullptr) 
			{
                if (xPadre->Hizq == centinela)
                    xPadre->Hizq = nullptr;
                if (xPadre->Hder == centinela)
                    xPadre->Hder = nullptr;
            }
            
            delete centinela;
        } 
		else 
		{
            ArreglaEliminacion(x);
        }
    }
}

void BinarioRN::Sustitucion(pNodoRN u, pNodoRN v) 
{
    if (u->padre == nullptr) 
	{
        raiz = v;
    } 
	else 
	    if (u == u->padre->Hizq)  
		{
           u->padre->Hizq = v;
        } 
		else 
		{
          u->padre->Hder = v;
        }

    if (v != nullptr) 
	{
        v->padre = u->padre;
    }
}

pNodoRN BinarioRN::Minimo(pNodoRN nodo) 
{
    while (nodo->Hizq != nullptr) 
	{
        nodo = nodo->Hizq;
    }
    return nodo;
}

void BinarioRN::ArreglaEliminacion(pNodoRN x) 
{
    while (x != raiz && x->color == false) 
	{
        if (x->padre == nullptr) 
		   break;
        
        if (x == x->padre->Hizq) 
		{
            pNodoRN w = x->padre->Hder;
            
            // Caso 1: hermano es rojo
            if (w != nullptr && w->color == true) 
			{
                w->color = false;
                x->padre->color = true;
                RotIzquierda(x->padre);
                w = x->padre->Hder;
            }
            
            if (w == nullptr) 
			{
                x = x->padre;
                continue;
            }
            
            // Caso 2: hermano es negro y ambos hijos del hermano son negros
            if ((w->Hizq == nullptr || w->Hizq->color == false) && (w->Hder == nullptr || w->Hder->color == false)) 
			{
                w->color = true;
                x = x->padre;
            } 
			else 
			{
                // Caso 3: hermano es negro, hijo derecho del hermano es negro, hijo izquierdo es rojo
                if (w->Hder == nullptr || w->Hder->color == false) 
				{
                    if (w->Hizq != nullptr) 
                        w->Hizq->color = false;
                    w->color = true;
                    RotDerecha(w);
                    w = x->padre->Hder;
                }
                
                // Caso 4: hermano es negro, hijo derecho del hermano es rojo
                if (w != nullptr) 
				{
                    w->color = x->padre->color;
                    x->padre->color = false;
                    if (w->Hder != nullptr) 
                        w->Hder->color = false;
                    RotIzquierda(x->padre);
                }
                x = raiz;
            }
        } 
		else 
		{
            // Casos simetricos (x es hijo derecho)
            pNodoRN w = x->padre->Hizq;
            
            // Caso 1 simetrico
            if (w != nullptr && w->color == true) 
			{
                w->color = false;
                x->padre->color = true;
                RotDerecha(x->padre);
                w = x->padre->Hizq;
            }
            
            if (w == nullptr) 
			{
                x = x->padre;
                continue;
            }
            
            // Caso 2 simetrico
            if ((w->Hder == nullptr || w->Hder->color == false) &&(w->Hizq == nullptr || w->Hizq->color == false)) 
			{
                w->color = true;
                x = x->padre;
            } else {
                // Caso 3 simetrico
                if (w->Hizq == nullptr || w->Hizq->color == false) 
				{
                    if (w->Hder != nullptr) 
                        w->Hder->color = false;
                    w->color = true;
                    RotIzquierda(w);
                    w = x->padre->Hizq;
                }
                
                // Caso 4 simetrico
                if (w != nullptr) 
				{
                    w->color = x->padre->color;
                    x->padre->color = false;
                    if (w->Hizq != nullptr) 
                        w->Hizq->color = false;
                    RotDerecha(x->padre);
                }
                x = raiz;
            }
        }
    }
    
    if (x != nullptr) 
        x->color = false;
}
