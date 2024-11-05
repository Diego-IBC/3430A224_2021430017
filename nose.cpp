
#include <iostream>
#include <limits>   // Para utilizar int_max como infinito
#include <cstdlib>  // Para system()
#include <cstdio>   // Para manejo de archivos
#include <vector>

using namespace std;

#define INF std::numeric_limits<int>::max() // Representa infinito

// Prototipos de funciones
void leerMatriz(int N, vector<vector<int>>& M);
void inicializar_vector_D(int N, vector<int>& D, const vector<vector<int>>& M, int origen);
void aplicarDijkstra(int N, vector<int>& D, vector<bool>& visitado, const vector<vector<int>>& M, int origen);
int encontrarMinimo(const vector<int>& D, const vector<bool>& visitado, int N);
void imprimirGrafo(int N, const vector<vector<int>>& M);
void imprimirDistancias(const vector<int>& D, int N, int origen);

int main() {
    int N; // Número de nodos
    int origen; // Vértice origen
    
    // Leer número de nodos y verificar que sea válido
    cout << "Ingrese el número de nodos (mayor que 2): ";
    cin >> N;
    
    if (N <= 2) {
        cout << "Error: El número de nodos debe ser mayor que 2." << endl;
        return 1;
    }
    
    // Crear la matriz de distancias
    vector<vector<int>> M(N, vector<int>(N));

    // Leer la matriz de distancias
    leerMatriz(N, M);

    // Leer el vértice origen y verificar que sea válido
    cout << "Ingrese el vértice de origen (entre 0 y " << N-1 << "): ";
    cin >> origen;
    
    if (origen < 0 || origen >= N) {
        cout << "Error: El vértice de origen debe estar entre 0 y " << N-1 << "." << endl;
        return 1;
    }

    // Inicializar el vector de distancias y el vector de nodos visitados
    vector<int> D(N);
    vector<bool> visitado(N, false);
    
    // Aplicar el algoritmo de Dijkstra
    inicializar_vector_D(N, D, M, origen);
    aplicarDijkstra(N, D, visitado, M, origen);
    
    // Imprimir el resultado
    imprimirDistancias(D, N, origen);

    // Imprimir el grafo resultante utilizando Graphviz
    imprimirGrafo(N, M);

    return 0;
}

// Función para leer la matriz de distancias desde la terminal
void leerMatriz(int N, vector<vector<int>>& M) {
    cout << "Ingrese la matriz de distancias (use " << INF << " para infinito):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "M[" << i << "][" << j << "]: ";
            cin >> M[i][j];
        }
    }
}

// Inicializa el vector de distancias desde el vértice origen
void inicializar_vector_D(int N, vector<int>& D, const vector<vector<int>>& M, int origen) {
    for (int i = 0; i < N; ++i) {
        D[i] = M[origen][i]; // Distancias iniciales desde el origen
    }
    D[origen] = 0; // Distancia al mismo origen es 0
}

// Función principal que implementa el algoritmo de Dijkstra
void aplicarDijkstra(int N, vector<int>& D, vector<bool>& visitado, const vector<vector<int>>& M, int origen) {
    for (int i = 0; i < N - 1; ++i) {
        int u = encontrarMinimo(D, visitado, N); // Encuentra el nodo con la distancia mínima
        visitado[u] = true; // Marca el nodo como visitado

        // Actualiza las distancias a los nodos adyacentes
        for (int v = 0; v < N; ++v) {
            if (!visitado[v] && M[u][v] != INF && D[u] != INF && D[u] + M[u][v] < D[v]) {
                D[v] = D[u] + M[u][v];
            }
        }
    }
}

// Encuentra el nodo no visitado con la distancia mínima
int encontrarMinimo(const vector<int>& D, const vector<bool>& visitado, int N) {
    int min = INF;
    int minIndex = -1;

    for (int v = 0; v < N; ++v) {
        if (!visitado[v] && D[v] <= min) {
            min = D[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Imprime el grafo resultante utilizando Graphviz
void imprimirGrafo(int N, const vector<vector<int>>& M) {
    FILE* fp = fopen("grafo.dot", "w");
    fprintf(fp, "digraph G {\n");
    fprintf(fp, "graph [rankdir=LR];\n");
    fprintf(fp, "node [style=filled fillcolor=yellow];\n");

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (M[i][j] != INF && i != j) {
                fprintf(fp, "%d -> %d [label=%d];\n", i, j, M[i][j]);
            }
        }
    }

    fprintf(fp, "}\n");
    fclose(fp);
    
    // Generar la imagen del grafo
    system("dot -Tpng grafo.dot -o grafo.png");
    cout << "El grafo ha sido generado como 'grafo.png'." << endl;
}

// Imprime las distancias mínimas desde el origen a todos los nodos
void imprimirDistancias(const vector<int>& D, int N, int origen) {
    cout << "Distancias mínimas desde el vértice " << origen << ":" << endl;
    for (int i = 0; i < N; ++i) {
        if (D[i] == INF) {
            cout << "Vértice " << i << ": INF (inaccesible)" << endl;
        } else {
            cout << "Vértice " << i << ": " << D[i] << endl;
        }
    }
}





 * g++ ejemplo_matriz.cpp -o matriz




#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 0
#define FALSE 1
#define N 5

void leer_nodos (char vector[N]);
void inicializar_vector_D (int D[N], int M[N][N]);
void inicializar_vector_caracter (char vector[N]);
void aplicar_dijkstra (char V[N], char S[N], char VS[N], int D[N], int M[N][N]);
void actualizar_VS(char V[N], char S[N], char VS[N]);
int buscar_indice_caracter(char V[N], char caracter);
void agrega_vertice_a_S(char S[N], char vertice);
int elegir_vertice(char VS[N], int D[N], char V[N]);
void actualizar_pesos (int D[N], char VS[N], int M[N][N], char V[N], char v);
int calcular_minimo(int dw, int dv, int mvw);
void imprimir_vector_caracter(char vector[N], char *);
void imprimir_vector_entero(int vector[N]);
void imprimir_matriz(int matriz[N][N]);
void imprimir_grafo(int matriz[N][N], char vector[N]);

// copia contenido inicial a D[] desde la matriz M[][].
void inicializar_vector_D (int D[N], int M[N][N]) {
  int col;
  
  for (col=0; col<N; col++) {
    D[col] = M[0][col];
  }
}

// inicializa con espacios el arreglo de caracteres.
void inicializar_vector_caracter (char vector[N]) {
  int col;
  
  for (col=0; col<N; col++) {
    vector[col] = ' ';
  }
}

// aplica el algoritmo.
void aplicar_dijkstra (char V[N], char S[N], char VS[N], int D[N], int M[N][N]) {
  int i;
  int v;
  
  // inicializar vector D[] segun datos de la matriz M[][] 
  // estado inicial.
  inicializar_vector_D(D, M);

  //
  printf("---------Estados iniciales ---------------------------------------\n");
  imprimir_matriz(M);
  printf("\n");
  imprimir_vector_caracter(S, "S");
  imprimir_vector_caracter(VS, "VS");
  imprimir_vector_entero(D);
  printf("------------------------------------------------------------------\n\n");

  // agrega primer véctice.
  printf("> agrega primer valor V[0] a S[] y actualiza VS[]\n\n");
  agrega_vertice_a_S (S, V[0]);
  imprimir_vector_caracter(S, "S");
  //
  actualizar_VS (V, S, VS);
  imprimir_vector_caracter(VS, "VS");
  imprimir_vector_entero(D);

  //
  for (i=1; i<N; i++) {
    // elige un vértice en v de VS[] tal que D[v] sea el mínimo 
    printf("\n> elige vertice menor en VS[] según valores en D[]\n");
    printf("> lo agrega a S[] y actualiza VS[]\n");
    v = elegir_vertice (VS, D, V);

    //
    agrega_vertice_a_S (S, v);
    imprimir_vector_caracter(S, "S");

    //
    actualizar_VS (V, S, VS);
    imprimir_vector_caracter(VS, "VS");

    //
    actualizar_pesos(D, VS, M, V, v);
    imprimir_vector_entero(D);
  }
}

//
void actualizar_pesos (int D[N], char VS[N], int M[N][N], char V[N], char v) {
  int i = 0;
  int indice_w, indice_v;

  printf("\n> actualiza pesos en D[]\n");
  
  indice_v = buscar_indice_caracter(V, v);
  while (VS[i] != ' ') {
    if (VS[i] != v) {
      indice_w = buscar_indice_caracter(V, VS[i]);
      D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
    }
    i++;
  }
}

//
int calcular_minimo(int dw, int dv, int mvw) {
  int min = 0;

  //
  if (dw == -1) {
    if (dv != -1 && mvw != -1)
      min = dv + mvw;
    else
      min = -1;

  } else {
    if (dv != -1 && mvw != -1) {
      if (dw <= (dv + mvw))
        min = dw;
      else
        min = (dv + mvw);
    }
    else
      min = dw;
  }
  
  printf("dw: %d dv: %d mvw: %d min: %d\n", dw, dv, mvw, min);

  return min;
}

// agrega vértice a S[].
void agrega_vertice_a_S(char S[N], char vertice) {
  int i;
  
  // recorre buscando un espacio vacio.
  for (i=0; i<N; i++) {
    if (S[i] == ' ') {
      S[i] = vertice;
      return;
    }
  }  
}

// elige vértice con menor peso en VS[].
// busca su peso en D[].
int elegir_vertice(char VS[N], int D[N], char V[N]) {
  int i = 0;
  int menor = 0;
  int peso;
  int vertice;

  while (VS[i] != ' ') {
    peso = D[buscar_indice_caracter(V, VS[i])];
    // descarta valores infinitos (-1) y 0.
    if ((peso != -1) && (peso != 0)) {
      if (i == 0) {
        menor = peso;
        vertice = VS[i];
      } else {
        if (peso < menor) {
          menor = peso;
          vertice = VS[i];
        }
      }
    }

    i++;
  }
  
  printf("\nvertice: %c\n\n", vertice);
  return vertice;
}

// retorna el índice del caracter consultado.
int buscar_indice_caracter(char V[N], char caracter) {
  int i;
  
  for (i=0; i<N; i++) {
    if (V[i] == caracter)
      return i;
  }
  
  return i;
}

// busca la aparición de un caracter en un vector de caracteres.
int busca_caracter(char c, char vector[N]) {
  int j;
  
  for (j=0; j<N; j++) {
    if (c == vector[j]) {
      return TRUE;
    }
  }
  
  return FALSE;
}

// actualiza VS[] cada ves que se agrega un elemnto a S[].
void actualizar_VS(char V[N], char S[N], char VS[N]) {
  int j;
  int k = 0;
  
  inicializar_vector_caracter(VS);
  
  for (j=0; j<N; j++){
    // por cada caracter de V[] evalua si está en S[],
    // Sino está, lo agrega a VS[].
    if (busca_caracter(V[j], S) != TRUE) {
      VS[k] = V[j];
      k++;
    }
  }
}

// lee datos de los nodos.
// inicializa utilizando código ASCII.
void leer_nodos (char vector[N]) {
  int i;
  int inicio = 97;
  
  for (i=0; i<N; i++) {
    vector[i] = inicio+i;
  }
}

// imprime el contenido de un vector de caracteres.
void imprimir_vector_caracter(char vector[N], const char *nomVector) {
    int i;
    
    for (i = 0; i < N; i++) {
        printf("%s[%d]: %c ", nomVector, i, vector[i]);
    }
    printf("\n");
}


//
void imprimir_vector_entero(int vector[N]) {
  int i;
  
  for (i=0; i<N; i++) {
    printf ("D[%d]: %d ", i, vector[i]);
  }
  printf ("\n");
}

// imprime el contenido de una matriz bidimensional de enteros.
void imprimir_matriz(int matriz[N][N]) {
  int i, j;
  
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      printf ("matriz[%d,%d]: %d ", i, j, matriz[i][j]);
    }
    printf ("\n");
  }
}

// genera y muestra apartir de una matriz bidimensional de enteros
// el grafo correspondiente.
void imprimir_grafo(int matriz[N][N], char vector[N]) {
  int i, j;
  FILE *fp;
  
  fp = fopen("grafo.txt", "w");
  fprintf(fp, "%s\n", "digraph G {");
  fprintf(fp, "%s\n", "graph [rankdir=LR]");
  fprintf(fp, "%s\n", "node [style=filled fillcolor=yellow];");
  
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      // evalua la diagonal principal.
      if (i != j) {
        if (matriz[i][j] > 0) {
          fprintf(fp, "%c%s%c [label=%d];\n", vector[i],"->", vector[j], matriz[i][j]);
        }
      }
    }
  }
  
  fprintf(fp, "%s\n", "}");
  fclose(fp);

  system("dot -Tpng -ografo.png grafo.txt");
  system("eog grafo.png &");
}

int main(int argc, char **argv) {
    const int SIZE = 10; // Tamano del arreglo
    int arr[SIZE];

    // Inicializa la semilla para numeros aleatorios
    srand(static_cast<unsigned int>(time(0)));



    char V[N], S[N], VS[N];
    int D[N];

  // valores de prueba1.
  int M[N][N] = {{ 0, 4, 11, -1, -1},
                 {-1, 0, -1,  6,  2},
                 {-1 ,3,  0,  6, -1},
                 {-1,-1, -1,  0, -1},
                 {-1,-1,  5,  3,  0}};
  

  inicializar_vector_caracter(V);
  inicializar_vector_caracter(S);
  inicializar_vector_caracter(VS);
  leer_nodos(V);
  aplicar_dijkstra (V, S, VS, D, M);
  imprimir_grafo(M, V);
    return 0;
}

















#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <vector>
#include <limits>

using namespace std;

#define N 5

// Declaraciones anticipadas de funciones
void inicializar_matriz(vector<vector<int>>& M);
void leer_nodos(char V[N]);
void aplicar_dijkstra(char V[N], char S[N], char VS[N], vector<int>& D, vector<vector<int>>& M);
void actualizar_VS(char V[N], char S[N], char VS[N]);
int buscar_indice_caracter(char V[N], char caracter);
void agrega_vertice_a_S(char S[N], char vertice);
int elegir_vertice(char VS[N], vector<int>& D, char V[N]);
void actualizar_pesos(vector<int>& D, char VS[N], vector<vector<int>>& M, char V[N], char v);
int calcular_minimo(int dw, int dv, int mvw);
void imprimir_vector_caracter(char vector[N], const char* nomVector);
void imprimir_vector_entero(const vector<int>& vector);
void imprimir_matriz(const vector<vector<int>>& matriz);
void imprimir_grafo(const vector<vector<int>>& matriz, char vector[N]);
bool busca_caracter(char c, char vector[N]); // Declaración anticipada

// Inicializa la matriz de adyacencia.
void inicializar_matriz(vector<vector<int>>& M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                M[i][j] = 0; // No hay costo para llegar a sí mismo.
            } else {
                M[i][j] = (rand() % 10) + 1; // Asigna pesos aleatorios entre 1 y 10.
            }
        }
    }
}

// Lee datos de los nodos y los inicializa con ASCII.
void leer_nodos(char vector[N]) {
    for (int i = 0; i < N; i++) {
        vector[i] = 'a' + i; // ASCII para 'a' es 97
    }
}

// Aplica el algoritmo de Dijkstra.
void aplicar_dijkstra(char V[N], char S[N], char VS[N], vector<int>& D, vector<vector<int>>& M) {
    int v;
    inicializar_matriz(M);
    
    // Inicializa D[] según M[][].
    for (int i = 0; i < N; i++) {
        D[i] = M[0][i];
    }

    cout << "--------- Estados iniciales ---------------------------------------\n";
    imprimir_matriz(M);
    cout << "\n";
    imprimir_vector_caracter(S, "S");
    imprimir_vector_caracter(VS, "VS");
    imprimir_vector_entero(D);
    cout << "------------------------------------------------------------------\n\n";

    // Agrega el primer vértice.
    cout << "> Agrega primer valor V[0] a S[] y actualiza VS[]\n\n";
    agrega_vertice_a_S(S, V[0]);
    imprimir_vector_caracter(S, "S");

    actualizar_VS(V, S, VS);
    imprimir_vector_caracter(VS, "VS");
    imprimir_vector_entero(D);

    for (int i = 1; i < N; i++) {
        cout << "\n> Elige vértice menor en VS[] según valores en D[]\n";
        cout << "> Lo agrega a S[] y actualiza VS[]\n";
        v = elegir_vertice(VS, D, V);

        agrega_vertice_a_S(S, v);
        imprimir_vector_caracter(S, "S");

        actualizar_VS(V, S, VS);
        imprimir_vector_caracter(VS, "VS");

        actualizar_pesos(D, VS, M, V, v);
        imprimir_vector_entero(D);
    }
}

// Actualiza los pesos en D[].
void actualizar_pesos(vector<int>& D, char VS[N], vector<vector<int>>& M, char V[N], char v) {
    int indice_v = buscar_indice_caracter(V, v);

    for (int i = 0; i < N; i++) {
        if (VS[i] != ' ' && VS[i] != v) {
            int indice_w = buscar_indice_caracter(V, VS[i]);
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
void agrega_vertice_a_S(char S[N], char vertice) {
    for (int i = 0; i < N; i++) {
        if (S[i] == ' ') {
            S[i] = vertice;
            return;
        }
    }
}

// Elige el vértice con menor peso en VS[].
int elegir_vertice(char VS[N], vector<int>& D, char V[N]) {
    int menor = numeric_limits<int>::max();
    int vertice = -1;

    for (int i = 0; i < N; i++) {
        if (VS[i] != ' ') {
            int peso = D[buscar_indice_caracter(V, VS[i])];
            if (peso < menor && peso > 0) {
                menor = peso;
                vertice = VS[i];
            }
        }
    }

    return vertice;
}

// Retorna el índice del carácter consultado.
int buscar_indice_caracter(char V[N], char caracter) {
    for (int i = 0; i < N; i++) {
        if (V[i] == caracter) {
            return i;
        }
    }
    return -1; // Retorna -1 si no se encuentra
}

// Actualiza VS[] cada vez que se agrega un elemento a S[].
void actualizar_VS(char V[N], char S[N], char VS[N]) {
    int k = 0;
    for (int j = 0; j < N; j++) {
        if (!busca_caracter(V[j], S)) {
            VS[k++] = V[j];
        }
    }
    for (int j = k; j < N; j++) {
        VS[j] = ' '; // Rellena el resto del vector con espacios
    }
}

// Busca la aparición de un carácter en un vector.
bool busca_caracter(char c, char vector[N]) {
    for (int j = 0; j < N; j++) {
        if (c == vector[j]) {
            return true;
        }
    }
    return false;
}

// Imprime el contenido de un vector de caracteres.
void imprimir_vector_caracter(char vector[N], const char* nomVector) {
    for (int i = 0; i < N; i++) {
        printf("%s[%d]: %c ", nomVector, i, vector[i]);
    }
    printf("\n");
}

// Imprime un vector de enteros.
void imprimir_vector_entero(const vector<int>& vector) {
    for (int i = 0; i < N; i++) {
        printf("D[%d]: %d ", i, vector[i]);
    }
    printf("\n");
}

// Imprime el contenido de una matriz de enteros.
void imprimir_matriz(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (const auto& valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }
}

// Genera y muestra el grafo a partir de una matriz.
void imprimir_grafo(const vector<vector<int>>& matriz, char vector[N]) {
    FILE *fp = fopen("grafo.txt", "w");
    if (fp == nullptr) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

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
    char V[N], S[N] = {' '}, VS[N] = {' '};
    vector<int> D(N);
    vector<vector<int>> M(N, vector<int>(N));

    cout << "Seleccione un tamaño ";
    cin >> N;

    srand(time(0)); 
    leer_nodos(V);
    aplicar_dijkstra(V, S, VS, D, M);
    imprimir_grafo(M, V);

    return 0;
}






void shellsort(int A[],int N){
  int INT = N+1:
  while(INT > 1){
    INT = INT /2;
    bool BAND = true;

    while(BAND){
      BAND = false;
      intI = 0;
      while((I + INT) < N){
        if (A(I) > A(I + INT))
        int AUX = A[i];
        A[I] = A[I+INT];
        A[I + INT] = AUX;
        BAND = true;
      }
    }
  }
}

int main(){
  std::const<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA N >10\n\n" << std::endl;
  const int MAX_SIZE = 10;
  int A[MAX_SIZE] = [1,2,3,4,5,6];
  int N = 9;

  shellsort(A,N);
  std::cout <<"\n [Info]yupiiiiiiiiiiiiiiiiiiiiiiiiiiii"<< std::endl;
  for(int 1=0; i<N; i++){
    std::cout << " ";
  }
  std::cout << std::endl;
  return 0;
}


















































#include <iostream>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <ctime>  

using namespace std;

#define INF INT_MAX

class Grafo {
public:
    int numVertices;
    int** matrizAdyacencia;  // Matriz de adyacencia dinámica
    pair<int, int>* ordenMin; // Arreglo para guardar los arcos mínimos del MST

    Grafo(int n) : numVertices(n) {
        // Crear la matriz de adyacencia dinámicamente
        matrizAdyacencia = new int*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            matrizAdyacencia[i] = new int[numVertices];
            for (int j = 0; j < numVertices; ++j) {
                if (i == j) {
                    matrizAdyacencia[i][j] = 0;  // Costo cero a sí mismo
                } else {
                    matrizAdyacencia[i][j] = INF;  // Inicialmente, no hay arcos entre diferentes vértices
                }
            }
        }

        ordenMin = new pair<int, int>[numVertices - 1];  // Array para almacenar los arcos del MST
    }

    ~Grafo() {
        // Liberar la memoria de la matriz de adyacencia y ordenMin
        for (int i = 0; i < numVertices; ++i) {
            delete[] matrizAdyacencia[i];
        }
        delete[] matrizAdyacencia;
        delete[] ordenMin;
    }

    void agregarArcos(int u, int v, int peso) {
        matrizAdyacencia[u][v] = peso;
        matrizAdyacencia[v][u] = peso;  // El grafo es no dirigido
    }

    void prim() {
        int* clave = new int[numVertices];    // Clave de cada vértice (distancia mínima al MST)
        int* padre = new int[numVertices];    // Vértice padre en el MST
        bool* enMST = new bool[numVertices];  // Indica si el vértice ya está en el MST

        // Inicializar todos los vértices
        for (int i = 0; i < numVertices; ++i) {
            clave[i] = INF;        // Inicialmente, todas las claves son infinitas
            padre[i] = -1;         // Inicialmente, no hay padres
            enMST[i] = false;      // Ningún vértice está en el MST al inicio
        }

        clave[0] = 0;  // El primer vértice se toma como origen

        for (int count = 0; count < numVertices - 1; ++count) {
            // Encontrar el vértice con la clave mínima que no está en el MST
            int u = -1;
            for (int i = 0; i < numVertices; ++i) {
                if (!enMST[i] && (u == -1 || clave[i] < clave[u])) {
                    u = i;
                }
            }

            enMST[u] = true;  // Incluir el vértice seleccionado en el MST

            // Actualizar las claves de los vértices adyacentes
            for (int v = 0; v < numVertices; ++v) {
                int peso = matrizAdyacencia[u][v];
                if (peso != INF && !enMST[v] && peso < clave[v]) {
                    clave[v] = peso;
                    padre[v] = u;
                }
            }
        }

        // Guardar los arcos en ordenMin
        for (int i = 1; i < numVertices; ++i) {
            ordenMin[i - 1] = {padre[i], i};  // Almacenar el arco (padre[i], i)
        }

        delete[] clave;
        delete[] padre;
        delete[] enMST;
    }

    void imprimir_grafo(char vector[]) {
        // Imprimir grafo original
        FILE* fp = fopen("grafo_original.dot", "w");

        fprintf(fp, "graph G {\n");
        fprintf(fp, "node [style=filled fillcolor=yellow];\n");

        for (int i = 0; i < numVertices; i++) {
            for (int j = i + 1; j < numVertices; j++) {
                if (matrizAdyacencia[i][j] != INF) {
                    fprintf(fp, "%c -- %c [label=%d];\n", vector[i], vector[j], matrizAdyacencia[i][j]);
                }
            }
        }

        fprintf(fp, "}\n");
        fclose(fp);

        // Generar imagen del grafo original
        system("dot -Tpng -ografo_original.png grafo_original.dot");
        system("eog grafo_original.png &");
    }

    void imprimir_grafo_MST(char vector[]) {
        // Imprimir el MST
        FILE* fp = fopen("mst.dot", "w");

        fprintf(fp, "graph MST {\n");
        fprintf(fp, "node [style=filled fillcolor=lightblue];\n");

        // Dibujar los arcos del MST usando ordenMin
        for (int i = 0; i < numVertices - 1; i++) {
            fprintf(fp, "%c -- %c;\n", vector[ordenMin[i].first], vector[ordenMin[i].second]);
        }

        fprintf(fp, "}\n");
        fclose(fp);

        // Generar imagen del MST
        system("dot -Tpng -omst.png mst.dot");
        system("eog mst.png &");
    }
};

void leer_nodos(char* vector, int N) {
    for (int i = 0; i < N; i++) {
        vector[i] = 'A' + i;  // Asignar letras desde 'A'
    }
}

void inicializar_matriz(int** M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                M[i][j] = 0;
            } else {
                M[i][j] = (rand() % 10) + 1;  // Generar un peso aleatorio entre 1 y 10
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <N>\n";
        return 1;
    }
    
    int N = atoi(argv[1]); // Número de nodos
    
    if (N <= 0) {
        cout << "El número de nodos debe ser mayor que 0.\n";
        return 1;
    }

    int** M = new int*[N];
    for (int i = 0; i < N; i++) {
        M[i] = new int[N];
    }

    char* nombresVertices = new char[N];

    srand(time(0));  // Semilla para generar números aleatorios

    leer_nodos(nombresVertices, N);  // Asignar nombres a los nodos
    inicializar_matriz(M, N);        // Inicializar la matriz de adyacencia con valores aleatorios

    Grafo g(N);

    // Insertar los valores de la matriz aleatoria en el grafo
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            g.agregarArcos(i, j, M[i][j]);
        }
    }

    // Imprimir grafo original
    g.imprimir_grafo(nombresVertices);

    // Ejecutar el algoritmo de Prim
    g.prim();

    // Imprimir el MST
    g.imprimir_grafo_MST(nombresVertices);

    // Liberar memoria dinámica
    for (int i = 0; i < N; i++) {
        delete[] M[i];
    }
    delete[] M;
    delete[] nombresVertices;

    return 0;
}
