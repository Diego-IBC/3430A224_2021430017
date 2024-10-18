#include <iostream>
#include <climits>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define INF INT_MAX
//La clase principal que gestiona la representación del grafo.
class Grafo {
public:
    int numVertices;
    // Matriz de adyacencia dinámica
    int** matrizAdyacencia;  
    // Arreglo para guardar los arcos mínimos 
    pair<int, int>* ordenMin; 

    Grafo(int n) : numVertices(n) {
        // Crear la matriz de adyacencia dinámicamente
        matrizAdyacencia = new int*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            matrizAdyacencia[i] = new int[numVertices];
            for (int j = 0; j < numVertices; ++j) {
                 if (i == j) {
                    matrizAdyacencia[i][j] = 0; 
                } else {
                    matrizAdyacencia[i][j] = INF;  
                }
            }
        }
        // Arreglo para almacenar los arcos del minimo
        ordenMin = new pair<int, int>[numVertices - 1]; 
    }

    ~Grafo() {
        // Liberar la memoria de la matriz de adyacencia y ordenMin
        for (int i = 0; i < numVertices; ++i) {
            delete[] matrizAdyacencia[i];
        }
        delete[] matrizAdyacencia;
        delete[] ordenMin;
    }
    //Este método agrega una arista entre dos nodos u y v
    void agregarArcos(int u, int v, int peso) {
        matrizAdyacencia[u][v] = peso;
        matrizAdyacencia[v][u] = peso;
    }

    void prim() {
        // Clave de cada vértice 
        int* clave = new int[numVertices];    
        // Vértice padre
        int* padre = new int[numVertices];
        // Indica si el vértice ya está en el Min
        bool* NM = new bool[numVertices];  

        for (int i = 0; i < numVertices; ++i) {
            clave[i] = INF;
            padre[i] = -1;
            NM[i] = false;
        }
        clave[0] = 0; 
        //seleciona el nodo a poner
        for (int count = 0; count < numVertices - 1; ++count) {
            int u = -1;
            for (int i = 0; i < numVertices; ++i) {
                if (!NM[i] && (u == -1 || clave[i] < clave[u])) {
                    u = i;
                }
            }

            NM[u] = true; 
            //Actualiza las claves de los nodos adyacentes al nodo seleccionado si las aristas que los conectan tienen un peso menor que el valor actual de la clave
            for (int v = 0; v < numVertices; ++v) {
                int peso = matrizAdyacencia[u][v];
                if (peso != INF && !NM[v] && peso < clave[v]) {
                    clave[v] = peso;
                    padre[v] = u;
                }
            }
        }
        //guarda el orden
        for (int i = 1; i < numVertices; ++i) {
            ordenMin[i - 1] = {padre[i], i};
        }

        delete[] clave;
        delete[] padre;
        delete[] NM;
    }

    void imprimir_grafo(char vector[]) {
        FILE* fp = fopen("grafo_original.dot", "w");
        fprintf(fp, "graph G {\nnode [style=filled fillcolor=yellow];\n");

        for (int i = 0; i < numVertices; i++) {
            for (int j = i + 1; j < numVertices; j++) {
                if (matrizAdyacencia[i][j] != INF) {
                    fprintf(fp, "%c -- %c [label=%d];\n", vector[i], vector[j], matrizAdyacencia[i][j]);
                }
            }
        }

        fprintf(fp, "}\n");
        fclose(fp);
        system("dot -Tpng -ografo_original.png grafo_original.dot");
        system("eog grafo_original.png &");
    }

    void imprimir_grafo_MST(char vector[]) {
    FILE* fp = fopen("mst.dot", "w");
    fprintf(fp, "graph MST {\nnode [style=filled fillcolor=lightblue];\n");

    // Dibujar los arcos usando ordenMin y mostrar las distancias
    for (int i = 0; i < numVertices - 1; i++) {
        int u = ordenMin[i].first;  
        int v = ordenMin[i].second; 
        int peso = matrizAdyacencia[u][v]; 
        fprintf(fp, "%c -- %c [label=%d];\n", vector[u], vector[v], peso);
    }

    fprintf(fp, "}\n");
    fclose(fp);

    system("dot -Tpng -omst.png mst.dot");
    system("eog mst.png &");
}

    //imprime los pares de nodos conectados 
    void imprimirConjuntoL() {
        cout << "Conjunto L (arcos del MST):" << endl;
        for (int i = 0; i < numVertices - 1; ++i) {
            cout << "(" << ordenMin[i].first << ", " << ordenMin[i].second << ")" << endl;
        }
    }
};
//etiqueta los nodos
void leer_nodos(char* vector, int N) {
    for (int i = 0; i < N; i++) {
        vector[i] = 'A' + i;
    }
}
//llena la matriz con numeros aleatorios
void leer_matriz(int** M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                M[i][j] = 0;
            } else {
                M[i][j] = (rand() % 10) + 1; 
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <N>\n";
        return 1;
    }
    
    int N = atoi(argv[1]);
    
    if (N < 2) {
        cout << "El número de nodos debe ser mayor que 2.\n";
        return 1;
    }

    int** M = new int*[N];
    for (int i = 0; i < N; i++) {
        M[i] = new int[N];
    }

    char* nombresVertices = new char[N];
    srand(time(0)); 
    leer_nodos(nombresVertices, N);
    leer_matriz(M, N);

    Grafo g(N);

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            g.agregarArcos(i, j, M[i][j]);
        }
    }

    g.imprimir_grafo(nombresVertices); 
    g.prim(); 
    g.imprimir_grafo_MST(nombresVertices); 
    g.imprimirConjuntoL();  

    for (int i = 0; i < N; i++) {
        delete[] M[i];
    }
    delete[] M;
    delete[] nombresVertices;

    return 0;
}
