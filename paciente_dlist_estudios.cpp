#include <iostream>
#include <string>
#include <cmath>

struct Paciente {
    std::string nombre;
    int edad;
    int peso;  // en kilogramos
    float altura;  // en metros
};

struct Nodo {
    Paciente paciente;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(const Paciente& p) : paciente(p), siguiente(nullptr), anterior(nullptr) {}
};

class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr) {}

    // Función para agregar un nodo al final de la lista
    void agregar(const Paciente& p) {
        Nodo* nuevoNodo = new Nodo(p);
        if (!cabeza) {
            cabeza = cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
    }

    // Función para imprimir la lista y calcular el IMC de cada paciente
    void imprimirYCalcularIMC() const {
        Nodo* actual = cabeza;
        while (actual) {
            std::cout << "Nombre: " << actual->paciente.nombre << std::endl;
            std::cout << "Edad: " << actual->paciente.edad << std::endl;
            std::cout << "Peso: " << actual->paciente.peso << " kg" << std::endl;
            std::cout << "Altura: " << actual->paciente.altura << " m" << std::endl;
            float imc = actual->paciente.peso / std::pow(actual->paciente.altura, 2);
            std::cout << "IMC: " << imc << std::endl;
            std::cout << std::endl;
            actual = actual->siguiente;
        }
    }

    // Función para calcular el promedio de edad del grupo
    float promedioEdad() const {
        Nodo* actual = cabeza;
        int sumaEdad = 0;
        int contador = 0;
        while (actual) {
            sumaEdad += actual->paciente.edad;
            contador++;
            actual = actual->siguiente;
        }
        return contador ? static_cast<float>(sumaEdad) / contador : 0.0;
    }

    // Función para calcular el promedio de peso del grupo
    float promedioPeso() const {
        Nodo* actual = cabeza;
        int sumaPeso = 0;
        int contador = 0;
        while (actual) {
            sumaPeso += actual->paciente.peso;
            contador++;
            actual = actual->siguiente;
        }
        return contador ? static_cast<float>(sumaPeso) / contador : 0.0;
    }

    ~ListaDoble() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

int main() {
    ListaDoble lista;

    // Ejemplos de pacientes
    Paciente p1 = {"Kain", 25, 60, 1.80};
    Paciente p2 = {"Pedro", 22, 50, 1.75};
    Paciente p3 = {"Maria", 24, 70, 1.60};

    // Agregar pacientes a la lista
    lista.agregar(p1);
    lista.agregar(p2);
    lista.agregar(p3);

    // Imprimir la lista y calcular el IMC de cada paciente
    std::cout << "Lista de pacientes e IMC:" << std::endl;
    lista.imprimirYCalcularIMC();

    // Calcular y mostrar el promedio de edad y peso
    std::cout << "Promedio de edad: " << lista.promedioEdad() << " años" << std::endl;
    std::cout << "Promedio de peso: " << lista.promedioPeso() << " kg" << std::endl;

    return 0;
}
