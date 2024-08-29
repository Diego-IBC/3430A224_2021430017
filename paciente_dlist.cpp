#include <iostream>
#include <string>

struct Paciente {
    std::string nombre;
    int edad;
    int peso;
    float altura;
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

    // Función para imprimir la lista
    void imprimir() const {
        Nodo* actual = cabeza;
        while (actual) {
            std::cout << "Nombre: " << actual->paciente.nombre << std::endl;
            std::cout << "Edad: " << actual->paciente.edad << std::endl;
            std::cout << "Peso: " << actual->paciente.peso << " kg" << std::endl;
            std::cout << "Altura: " << actual->paciente.altura << " m" << std::endl;
            std::cout << std::endl;
            actual = actual->siguiente;
        }
    }

    // Función para eliminar un nodo de la lista
    void eliminar(const std::string& nombre) {
        Nodo* actual = cabeza;
        while (actual) {
            if (actual->paciente.nombre == nombre) {
                if (actual->anterior) {
                    actual->anterior->siguiente = actual->siguiente;
                } else {
                    cabeza = actual->siguiente;
                }
                if (actual->siguiente) {
                    actual->siguiente->anterior = actual->anterior;
                } else {
                    cola = actual->anterior;
                }
                delete actual;
                return;
            }
            actual = actual->siguiente;
        }
        std::cout << "Paciente no encontrado." << std::endl;
    }

    // Destructor para liberar la memoria
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
    Paciente p2 = {"Pedro", 22, 50, 1.80};
    Paciente p3 = {"Maria", 24, 70, 2.10};

    // Agregar pacientes a la lista
    lista.agregar(p1);
    lista.agregar(p2);
    lista.agregar(p3);

    // Imprimir la lista de pacientes
    std::cout << "Lista de pacientes:" << std::endl;
    lista.imprimir();

    // Eliminar un paciente
    lista.eliminar("Pedro");

    // Imprimir la lista después de eliminar un paciente
    std::cout << "Lista después de eliminar a Pedro:" << std::endl;
    lista.imprimir();

    return 0;
}
