#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define TRUE 1
#define FALSE 0

enum { IZQUIERDO, DERECHO };

struct Nodo {
    int dato;
    int FE; 
    Nodo* derecho;
    Nodo* izquierdo;
    Nodo* padre;
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;


/* Insertar en arbol ordenado: */
void Insertar(Arbol* a, int dat);
/* Borrar un elemento: */
void Borrar(Arbol* a, int dat);
/* Funcion de busqueda: */
int Buscar(Arbol a, int dat);
/* Comprobar si es un nodo hoja: */
int EsHoja(pNodo r);
/* Contar numero de nodos: */
int NumeroNodos(Arbol a, int* c);
/* Calcular la altura de un arbol: */
int AlturaArbol(Arbol a, int* altura);
/* Calcular altura de un dato: */
int Altura(Arbol a, int dat);
/* Generar salida para Graphiz */
void PreOrden(Arbol, std::ofstream &fp);


// Funciones de equilibrado:
void Equilibrar(Arbol* raiz, pNodo nodo, int, int);
void RotaDerechaDerecha(Arbol* raiz, pNodo nodo);
void RotaIzquierdaIzquierda(Arbol* raiz, pNodo nodo);
void RotaDerechaIzquierda(Arbol* raiz, pNodo nodo);
void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo);

/* Funciones auxiliares */
void Podar(Arbol* a);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);

// Declaración de la función modificar
void modificar(Arbol* a, int dat);

void MenuPrincipal();
void GenerarGrafo(Arbol);

int main() {
    Arbol ArbolInt = NULL;
    int opcion = 0;
    int valor;

    while (opcion != 6) {
        MenuPrincipal();
        std::cout << "Ingrese su opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese su numero: ";
                std::cin >> valor;
                Insertar(&ArbolInt, valor);
                break;
            case 2:
                std::cout << "Ingrese su numero a buscar: ";
                std::cin >> valor;
                if (Buscar(ArbolInt, valor)) {
                    std::cout << "El numero " << valor << " se encuentra en el árbol." << std::endl;
                } else {
                    std::cout << "El numero " << valor << " no se encuentra en el árbol." << std::endl;
                }
                break;
            case 3:
                std::cout << "Ingrese su numero a eliminar: ";
                std::cin >> valor;
                Borrar(&ArbolInt, valor);
                break; 
            case 4:
                std::cout << "Ingrese su numero a modificar: ";
                std::cin >> valor;
                modificar(&ArbolInt, valor);
                break; 
            case 5:
                GenerarGrafo(ArbolInt);
                break;
        }
    }

    /* Liberar memoria asociada al arbol. */
    Podar(&ArbolInt);
    return 0;
}

void GenerarGrafo(Arbol ArbolInt) {
    std::ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=yellow];\n";

    if (ArbolInt) {
        fp << "nullraiz [shape=point];\n";
        fp << "nullraiz->" << ArbolInt->dato << " [label=" << ArbolInt->FE << "];\n";
        PreOrden(ArbolInt, fp);
    }

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

void MenuPrincipal() {
    std::cout << "\n";
    std::cout << "<1> Ingresar numero\n";
    std::cout << "<2> Busqueda numero\n";
    std::cout << "<3> Eliminar numero\n";
    std::cout << "<4> Modificar elemento ingresado\n";
    std::cout << "<5> Generar Grafo\n";
    std::cout << "<6> Salir\n";
    std::cout << "\n";
}

void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        delete *a;
        *a = NULL;
    }
}

void Insertar(Arbol* a, int dat) {
    pNodo padre = NULL;
    pNodo actual = *a;

    while (actual != NULL && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
    }

    if (actual != NULL)
        return;

    if (padre == NULL) {
        *a = new Nodo{ dat, 0, NULL, NULL, NULL };
    } else if (dat < padre->dato) {
        actual = new Nodo{ dat, 0, NULL, NULL, padre };
        padre->izquierdo = actual;
        Equilibrar(a, padre, IZQUIERDO, TRUE);
    } else if (dat > padre->dato) {
        actual = new Nodo{ dat, 0, NULL, NULL, padre };
        padre->derecho = actual;
        Equilibrar(a, padre, DERECHO, TRUE);
    }
}

void Equilibrar(Arbol* a, pNodo nodo, int rama, int nuevo) {
    int salir = FALSE;

    while (nodo && !salir) {
        if (nuevo) {
            if (rama == IZQUIERDO) {
                nodo->FE -= 1;
            } else {
                nodo->FE += 1;
            }
        } else {
            if (rama == IZQUIERDO) {
                nodo->FE += 1;
            } else {
                nodo->FE -= 1;
            }
        }

        if (nodo->FE == 0)
            salir = TRUE;
        else if (nodo->FE == -2) {
            if (nodo->izquierdo->FE == 1)
                RotaIzquierdaDerecha(a, nodo);
            else
                RotaIzquierdaIzquierda(a, nodo);
            salir = TRUE;
        } else if (nodo->FE == 2) {
            if (nodo->derecho->FE == -1)
                RotaDerechaIzquierda(a, nodo);
            else
                RotaDerechaDerecha(a, nodo);
            salir = TRUE;
        }

        if (nodo->padre) {
            if (nodo->padre->derecho == nodo) {
                rama = DERECHO;
            } else {
                rama = IZQUIERDO;
            }
        }
        nodo = nodo->padre;
    }
}

void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo R = Q->derecho;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre) {
        if (Padre->derecho == nodo) {
            Padre->derecho = R;
        } else {
            Padre->izquierdo = R;
        }
    } else {
        *raiz = R;
    }

    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;

    switch (R->FE) {
        case -1: Q->FE = 0; P->FE = 1; break;
        case 0: Q->FE = 0; P->FE = 0; break;
        case 1: Q->FE = -1; P->FE = 0; break;
    }

    R->FE = 0;
}

void RotaDerechaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo R = Q->izquierdo;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre) {
        if (Padre->derecho == nodo) {
            Padre->derecho = R;
        } else {
            Padre->izquierdo = R;
        }
    } else {
        *a = R;
    }

    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;

    switch (R->FE) {
        case -1: P->FE = 0; Q->FE = 1; break;
        case 0: P->FE = 0; Q->FE = 0; break;
        case 1: P->FE = -1; Q->FE = 0; break;
    }

    R->FE = 0;
}

void RotaDerechaDerecha(Arbol* raiz, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;

    if (Padre) {
        if (Padre->derecho == nodo) {
            Padre->derecho = Q;
        } else {
            Padre->izquierdo = Q;
        }
    } else {
        *raiz = Q;
    }

    P->derecho = Q->izquierdo;
    Q->izquierdo = P;

    Q->padre = Padre;
    P->padre = Q;

    if (P->derecho) P->derecho->padre = P;

    switch (Q->FE) {
        case 1: P->FE = 0; Q->FE = 0; break;
        case 0: P->FE = 1; Q->FE = 0; break;
        case -1: P->FE = 0; Q->FE = -1; break;
    }
}

void RotaIzquierdaIzquierda(Arbol* raiz, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;

    if (Padre) {
        if (Padre->derecho == nodo) {
            Padre->derecho = Q;
        } else {
            Padre->izquierdo = Q;
        }
    } else {
        *raiz = Q;
    }

    P->izquierdo = Q->derecho;
    Q->derecho = P;

    Q->padre = Padre;
    P->padre = Q;

    if (P->izquierdo) P->izquierdo->padre = P;

    switch (Q->FE) {
        case -1: P->FE = 0; Q->FE = 0; break;
        case 0: P->FE = -1; Q->FE = 0; break;
        case 1: P->FE = 0; Q->FE = 1; break;
    }
}

void PreOrden(Arbol a, std::ofstream& fp) {
    if (a) {
        fp << a->dato << ";\n";
        if (a->izquierdo) {
            fp << a->dato << " -> " << a->izquierdo->dato << ";\n";
            PreOrden(a->izquierdo, fp);
        }
        if (a->derecho) {
            fp << a->dato << " -> " << a->derecho->dato << ";\n";
            PreOrden(a->derecho, fp);
        }
    }
}
// para buscar algun numero
int Buscar(Arbol a, int dat) {
    if (a == NULL) return 0;
    if (a->dato == dat) return 1;
    if (dat < a->dato) return Buscar(a->izquierdo, dat);
    return Buscar(a->derecho, dat);
}
//buscar y eliminar el numero
void Borrar(Arbol* a, int dat) {
    if (*a == NULL) {
        std::cout << "La información no se encuentra en el árbol." << std::endl;
        return;
    }

    pNodo nodo = *a;
    pNodo nodoPadre = NULL;
    while (nodo != NULL && dat != nodo->dato) {
        nodoPadre = nodo;
        if (dat < nodo->dato) {
            nodo = nodo->izquierdo;
        } else {
            nodo = nodo->derecho;
        }
    }

    if (nodo == NULL) {
        std::cout << "La información no se encuentra en el árbol." << std::endl;
        return; 
    }

   
    if (nodo->izquierdo != NULL && nodo->derecho != NULL) {
       
        pNodo sucesor = nodo->derecho;
        while (sucesor->izquierdo != NULL) {
            sucesor = sucesor->izquierdo;
        }
     
        nodo->dato = sucesor->dato;

       
        Borrar(&nodo->derecho, sucesor->dato);
    } else {
    
        pNodo hijo = (nodo->izquierdo != NULL) ? nodo->izquierdo : nodo->derecho;
       
        if (nodoPadre == NULL) {
            *a = hijo;
        } else if (nodoPadre->izquierdo == nodo) {
            nodoPadre->izquierdo = hijo;
        } else {
            nodoPadre->derecho = hijo;
        }

        delete nodo; 
    }

    if (nodoPadre != NULL) {
        Equilibrar(a, nodoPadre, (nodoPadre->izquierdo == nodo) ? IZQUIERDO : DERECHO, false);
    }
}
//ocupa la funcion de buscar para modificar el valor
void modificar(Arbol* a, int dat) {
    if (*a == NULL) {
        std::cout << "El árbol está vacío. No se puede modificar." << std::endl;
        return;
    }

    if (Buscar(*a, dat)) {
        std::cout << "Ingrese el nuevo valor: ";
        int nuevoValor;
        std::cin >> nuevoValor;
        Borrar(a, dat);
        Insertar(a, nuevoValor); 
        std::cout << "Valor modificado de " << dat << " a " << nuevoValor << std::endl;
    } else {
        std::cout << "El valor " << dat << " no se encuentra en el árbol." << std::endl;
    }
}

