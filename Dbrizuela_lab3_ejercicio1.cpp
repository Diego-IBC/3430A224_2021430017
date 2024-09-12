#include <iostream>
using namespace std;

class Pila {
private:
    int max;
    int tope;
    int* datos;  
    bool band;

public:
    // Iniciamos la pila
    Pila(int max_size) {
        max = max_size;
        tope = 0;
        datos = new int[max]; 
    }

    //para liberar espacio
    ~Pila() {
        delete[] datos;
    }

    // revizar si la pila esta vacia
    void Pila_vacia(bool &band) {
        if (tope == 0) {
            band = true;
        } else {
            band = false;
        }
    }

    // revizar si esta llena
    void Pila_llena(bool &band) {
        if (tope == max) {
            band = true;
        } else {
            band = false;
        }
    }

    // agregar un valor nuevo a la pila
    void Push(int dato) {
        Pila_llena(band);
        if (band) {
            std::cout << "Desbordamiento, pila llena" << std::endl;
        } else {
            datos[tope] = dato;
            tope++;
            std::cout << "Dato agregado: " << dato << std::endl;
        }
    }

    //elimina un elemento de la pila
    void Pop() {
        Pila_vacia(band);
        if (band) {
            std::cout << "Subdesbordamiento, pila vacia" << std::endl;
        } else {
            tope--;
            int dato = datos[tope];
            std::cout << "Dato extraído: " << dato << std::endl;
        }
    }

   //muestra los elementos de la pila
    void Ver_pila() {
        if (tope == 0) {
            std::cout << "La pila está vacía." << std::endl;
        } else {
            std::cout << "Elementos en la pila: ";
            for (int i = 0; i < tope; i++) {
                std::cout << datos[i] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    char opcion;
    int max;
    int dato;

    std::cout << "Ingrese el tamaño máximo de la pila: ";
    std::cin >> max;

    Pila pila(max);

    bool bucle = true;
    while (bucle) {
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << "Bienvenido, ¿qué desea hacer?" << std::endl;
        std::cout << "A - Ver la pila" << std::endl;
        std::cout << "B - Eliminar" << std::endl;
        std::cout << "C - Agregar" << std::endl;
        std::cout << "D - Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 'A':
            case 'a':
                pila.Ver_pila();
                break;

            case 'B':
            case 'b':
                pila.Pop();
                break;

            case 'C':
            case 'c':
                std::cout << "Ingrese el valor a agregar: ";
                std::cin >> dato;
                pila.Push(dato);
                break;

            case 'D':
            case 'd':
                bucle = false;
                break;

            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
                break;
        }
    }

    return 0;
}



