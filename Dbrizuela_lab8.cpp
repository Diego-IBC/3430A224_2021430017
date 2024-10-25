#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <chrono>
#include <vector>
using namespace std;
//Esta función recibe un vector llamado M y un entero N. Genera N números aleatorios entre 1 y 50
void inicializar_arreglo(vector<int>& M, int N) {
    for (int i = 0; i < N; i++) {
        M.push_back((rand() % 50) + 1);
    }
}
//Esta función inicializa valores de num1 y num2, la almacenar para hacer el cambio. 
void swap(int& num1, int& num2){
    int auxiliar = num1;
    num1 = num2;
    num2 = auxiliar;
}

void selectionSort(vector<int>& arreglo){
    int indice_menor;
    for(int i = 0; i < arreglo.size()-1; i++){
        //por cada i se aume que es el menor 
        indice_menor = i;
        for(int j = i + 1; j < arreglo.size(); j++){
            if(arreglo[j] < arreglo[indice_menor]){
                indice_menor = j;
            //actualiza el valor minimo
            }
        }
        swap(arreglo[i], arreglo[indice_menor]);
    }
}
//imprime el arreglo en una linea
void imprimirArreglo(const vector<int>& arreglo){
    for(int i = 0; i < arreglo.size(); i++){
        cout << arreglo[i] << " ";
    }
    cout << endl;
}

int particion(vector<int>& arreglo, int inicio, int fin){
    //se seleciona el pivote
    int pivote = arreglo[inicio];
    //se marca donde poner los valores menores de pivote
    int i = inicio + 1;
    for(int j = i; j <= fin; j++){
        if(arreglo[j] < pivote){
            swap(arreglo[i], arreglo[j]);
            i++;
        }
    }
    //Al final, coloca el pivote en su posición correcta
    swap(arreglo[inicio], arreglo[i-1]);
    return i-1;
}

void quickSort(vector<int>& arreglo, int inicio, int fin){
    //Divide la lista con particion y coloca el pivote en su posición
    if(inicio < fin){
        int pivote = particion(arreglo, inicio, fin);
        //se llama a la izquierda y derecha
        quickSort(arreglo, inicio, pivote-1);
        quickSort(arreglo, pivote+1, fin);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <N>\n";
        return 1;
    }

    int N = atoi(argv[1]);
    
    srand(time(0));

    vector<int> test1;
    inicializar_arreglo(test1, N);

    imprimirArreglo(test1);

    cout << "-----------------------------------------" << endl;
    cout << "Metodo         | Tiempo" << endl;
    cout << "-----------------------------------------" << endl;

    auto start1 = std::chrono::high_resolution_clock::now();
    selectionSort(test1);
    auto end1 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double>duration1 = ((end1 - start1)*1000);
    cout << "Seleccion      | " << duration1.count() << " milisegundos" << endl;

    vector<int> sortedSelection = test1;


    auto start2 = std::chrono::high_resolution_clock::now();
    quickSort(test1, 0, test1.size()-1);
    auto end2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double>duration2 = ((end2 - start2)*1000);
    cout << "Quicksort      | " << duration2.count() << " milisegundos" << endl;
    cout << "-----------------------------------------" << endl;

    cout << "Seleccion ";
    imprimirArreglo(sortedSelection);

    cout << "Quicksort ";
    imprimirArreglo(test1);

    return 0;
}