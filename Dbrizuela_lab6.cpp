#include <iostream>
#include <cstdlib>
#include <ctime>   
#include <limits>

using namespace std;

// Declaraciones anticipadas de funciones
void inicializar_matriz(int** M, int N);
void leer_nodos(char* V, int N);
void aplicar_dijkstra(char* V, char* S, char* VS, int* D, int** M, int N);
void actualizar_VS(char* V, char* S, char* VS, int N);
int buscar_indice_caracter(char* V, char caracter, int N);
void agrega_vertice_a_S(char* S, char vertice, int N);
int elegir_vertice(char* VS, int* D, char* V, int N);
void actualizar_pesos(int* D, char* VS, int** M, char* V, char v, int N);
int calcular_minimo(int dw, int dv, int mvw);
void imprimir_vector_caracter(char* vector, int N, const char* nomVector);
void imprimir_vector_entero(int* vector, int N);
void imprimir_matriz(int** matriz, int N);
void imprimir_grafo(int** matriz, char* vector, int N);
bool busca_caracter(char c, char* vector, int N);

// Inicializa la matriz de adyacencia.
void inicializar_matriz(int** M, int N) {
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

// Lee datos de los nodos y los inicializa con ASCII.
void leer_nodos(char* vector, int N) {
    for (int i = 0; i < N; i++) {
        vector[i] = 'a' + i; 
    }
}

// Aplica el algoritmo de Dijkstra.
void aplicar_dijkstra(char* V, char* S, char* VS, int* D, int** M, int N) {
    int v;
    inicializar_matriz(M, N);
    
    // Inicializa D[] según M[][].
    for (int i = 0; i < N; i++) {
        D[i] = M[0][i];
    }

    cout << "--------- Estados iniciales ---------------------------------------\n";
    imprimir_matriz(M, N);
    cout << "\n";
    imprimir_vector_caracter(S, N, "S");
    imprimir_vector_caracter(VS, N, "VS");
    imprimir_vector_entero(D, N);
    cout << "------------------------------------------------------------------\n\n";

    // Agrega el primer vértice.
    cout << "> agrega primer valor V[0] a S[] y actualiza VS[]\n\n";
    agrega_vertice_a_S(S, V[0], N);
    imprimir_vector_caracter(S, N, "S");

    actualizar_VS(V, S, VS, N);
    imprimir_vector_caracter(VS, N, "VS");
    imprimir_vector_entero(D, N);

    for (int i = 1; i < N; i++) {
        cout << "\n> elige vértice menor en VS[] según valores en D[]\n";
        cout << "> Lo agrega a S[] y actualiza VS[]\n";
        v = elegir_vertice(VS, D, V, N);

        agrega_vertice_a_S(S, v, N);
        imprimir_vector_caracter(S, N, "S");

        actualizar_VS(V, S, VS, N);
        imprimir_vector_caracter(VS, N, "VS");

        actualizar_pesos(D, VS, M, V, v, N);
        imprimir_vector_entero(D, N);
    }
}

// Actualiza los pesos en D[].
void actualizar_pesos(int* D, char* VS, int** M, char* V, char v, int N) {
    int indice_v = buscar_indice_caracter(V, v, N);

    for (int i = 0; i < N; i++) {
        if (VS[i] != ' ' && VS[i] != v) {
            int indice_w = buscar_indice_caracter(V, VS[i], N);
            D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
        }
    }
}

// Calcula el mínimo entre tres valores.
int calcular_minimo(int dw, int dv, int mvw) {
    if (dw == -1) {
        return (dv != -1 && mvw != -1) ? dv + mvw : -1;
    } else {
        if (dv != -1 && mvw != -1) {
            return (dw <= (dv + mvw)) ? dw : (dv + mvw);
        } else {
            return dw;
        }
    }
}

// Agrega un vértice a S[].
void agrega_vertice_a_S(char* S, char vertice, int N) {
    for (int i = 0; i < N; i++) {
        if (S[i] == ' ') {
            S[i] = vertice;
            return;
        }
    }
}

// Elige el vértice con menor peso en VS[].
int elegir_vertice(char* VS, int* D, char* V, int N) {
    int menor = numeric_limits<int>::max();
    int vertice = -1;

    for (int i = 0; i < N; i++) {
        if (VS[i] != ' ') {
            int peso = D[buscar_indice_caracter(V, VS[i], N)];
            if (peso < menor && peso > 0) {
                menor = peso;
                vertice = VS[i];
            }
        }
    }
    printf("\nvertice: %c\n\n", vertice);
    return vertice;
}

// Retorna el índice del carácter consultado.
int buscar_indice_caracter(char* V, char caracter, int N) {
    for (int i = 0; i < N; i++) {
        if (V[i] == caracter) {
            return i;
        }
    }
    return -1;
}

// Actualiza VS[] cada vez que se agrega un elemento a S[].
void actualizar_VS(char* V, char* S, char* VS, int N) {
    int k = 0;
    for (int j = 0; j < N; j++) {
        if (!busca_caracter(V[j], S, N)) {
            VS[k++] = V[j];
        }
    }
}

// Busca la aparición de un carácter en un vector.
bool busca_caracter(char c, char* vector, int N) {
    for (int j = 0; j < N; j++) {
        if (c == vector[j]) {
            return true;
        }
    }
    return false;
}

// Imprime el contenido de un vector de caracteres.
void imprimir_vector_caracter(char* vector, int N, const char* nomVector) {
    for (int i = 0; i < N; i++) {
        printf("%s[%d]: %c ", nomVector, i, vector[i]);
    }
    printf("\n");
}

// Imprime un vector de enteros.
void imprimir_vector_entero(int* vector, int N) {
    for (int i = 0; i < N; i++) {
        printf("D[%d]: %d ", i, vector[i]);
    }
    printf("\n");
}

// Imprime el contenido de una matriz de enteros.
void imprimir_matriz(int** matriz, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

// Genera y muestra el grafo a partir de una matriz.
void imprimir_grafo(int** matriz, char* vector, int N) {
    FILE *fp = fopen("grafo.txt", "w");

    fprintf(fp, "digraph G {\n");
    fprintf(fp, "graph [rankdir=LR];\n");
    fprintf(fp, "node [style=filled fillcolor=yellow];\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j && matriz[i][j] > 0) {
                fprintf(fp, "%c -> %c [label=%d];\n", vector[i], vector[j], matriz[i][j]);
            }
        }
    }
    fprintf(fp, "}\n");
    fclose(fp);

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <N>\n";
        return 1; 
    }

    int N = atoi(argv[1]); 

    char* V = new char[N];
    char* S = new char[N];
    char* VS = new char[N];
    int* D = new int[N];
    int** M = new int*[N];
    for (int i = 0; i < N; i++) {
        M[i] = new int[N];
    }

    srand(time(0)); 
    leer_nodos(V, N);
    aplicar_dijkstra(V, S, VS, D, M, N);
    imprimir_grafo(M, V, N);

    // Liberar memoria
    delete[] V;
    delete[] S;
    delete[] VS;
    delete[] D;
    for (int i = 0; i < N; i++) {
        delete[] M[i];
    }
    delete[] M;

    return 0;
}
