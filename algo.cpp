#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <chrono>
#include <vector>
using namespace std;

void inicializar_matriz(int* M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                M[i * N + j] = 0;  // Diagonal principal en 0
            } else {
                M[i * N + j] = (rand() % 10) + 1;
            }
        }
    }
}

void imprimir_matriz(int* M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << M[i * N + j] << " ";
        }
        cout << endl;
    }
}

void swap(int& num1, int& num2) {
    int auxiliar = num1;
    num1 = num2;
    num2 = auxiliar;
}

void selectionSort(vector<int>& arreglo) {
    int indice_menor;
    for (int i = 0; i < arreglo.size() - 1; i++) {
        indice_menor = i;
        for (int j = i + 1; j < arreglo.size(); j++) {
            if (arreglo[j] < arreglo[indice_menor]) {
                indice_menor = j;
            }
        }
        swap(arreglo[i], arreglo[indice_menor]);
    }
}

void imprimirArreglo(const vector<int>& arreglo) {
    for (int i = 0; i < arreglo.size(); i++) {
        cout << arreglo[i] << " ";
    }
    cout << endl;
}

int particion(vector<int>& arreglo, int inicio, int fin) {
    int pivote = arreglo[inicio];
    int i = inicio + 1;
    for (int j = i; j <= fin; j++) {
        if (arreglo[j] < pivote) {
            swap(arreglo[i], arreglo[j]);
            i++;
        }
    }
    swap(arreglo[inicio], arreglo[i - 1]);
    return i - 1;
}

void quickSort(vector<int>& arreglo, int inicio, int fin) {
    if (inicio < fin) {
        int pivote = particion(arreglo, inicio, fin);
        quickSort(arreglo, inicio, pivote - 1);
        quickSort(arreglo, pivote + 1, fin);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <N>\n";
        return 1;
    }

    int N = atoi(argv[1]);
    
    srand(time(0));
    int* M = new int[N * N];  // Matriz unidimensional de tamaño N*N

    inicializar_matriz(M, N);
    cout << "Matriz inicializada:\n";
    imprimir_matriz(M, N);

    // Convertir una fila de la matriz en un vector para aplicar los algoritmos
    vector<int> arreglo;
    for (int i = 0; i < N; i++) {
        arreglo.push_back(M[i]);  // Usar la primera fila
    }

    // Comparar tiempo de selección
    cout << "\n------Metodo de Seleccion-------" << endl;
    auto start1 = std::chrono::high_resolution_clock::now();
    selectionSort(arreglo);
    auto end1 = std::chrono::high_resolution_clock::now();

    imprimirArreglo(arreglo);
    std::chrono::duration<double> duration1 = (end1 - start1)*10000;
    std::cout << "\nTiempo de ejecucion de Selection Sort: " << duration1.count() << " segundos\n";

    // Restaurar el vector a su estado original para probar Quicksort
    for (int i = 0; i < N; i++) {
        arreglo[i] = M[i];
    }

    // Comparar tiempo de Quicksort
    cout << "\n------Metodo de Quicksort-------" << endl;
    auto start2 = std::chrono::high_resolution_clock::now();
    quickSort(arreglo, 0, arreglo.size() - 1);
    auto end2 = std::chrono::high_resolution_clock::now();

    imprimirArreglo(arreglo);
    std::chrono::duration<double> duration2 = (end2 - start2)*10000;
    std::cout << "\nTiempo de ejecucion de Quicksort: " << duration2.count() << " segundos\n";

    // Liberar memoria de la matriz unidimensional
    delete[] M;

    return 0;
}
