#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip> 

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

    // Función para imprimir la lista y calcular el IMC de cada paciente
    void imprimirYCalcularIMC() const {
        Nodo* actual = cabeza;
        while (actual) {
            std::cout << "Nombre: " << actual->paciente.nombre << std::endl;
            std::cout << "Edad: " << actual->paciente.edad << std::endl;
            std::cout << "Peso: " << actual->paciente.peso << " kg" << std::endl;
            std::cout << "Altura: " << actual->paciente.altura << " m" << std::endl;
            float imc = actual->paciente.peso / std::pow(actual->paciente.altura, 2);
            std::cout << "IMC: " << std::fixed << std::setprecision(2) << imc << std::endl;
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

    // Función para eliminar un paciente por nombre
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

    // Destructor para liberar memoria
    ~ListaDoble() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

// Función para leer pacientes desde un archivo CSV (separado por comas)
void leerPacientesDesdeCSV(const std::string& nombreArchivo, ListaDoble& lista) {
    std::ifstream archivo(nombreArchivo);
    std::string linea;

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo.\n";
        return;
    }

    // Leer la primera línea (encabezados) y descartarla
    std::getline(archivo, linea);

    // Leer el archivo línea por línea
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string nombre;
        int edad;
        int peso;
        float altura;

        // Leer nombre hasta la coma
        std::getline(ss, nombre, ',');

        // Leer edad
        if (!(ss >> edad)) {
            std::cerr << "Error al leer la edad para el paciente: " << nombre << std::endl;
            continue;
        }
        ss.ignore(); // Ignorar la coma después de la edad

        // Leer peso
        if (!(ss >> peso)) {
            std::cerr << "Error al leer el peso para el paciente: " << nombre << std::endl;
            continue;
        }
        ss.ignore(); // Ignorar la coma después del peso

        // Leer altura
        if (!(ss >> altura) || altura <= 0) {
            std::cerr << "Error al leer la altura para el paciente: " << nombre << std::endl;
            continue;
        }

        Paciente paciente = {nombre, edad, peso, altura};
        lista.agregar(paciente);

        // Imprime los datos leídos para depuración
        std::cout << "Datos leídos: Nombre=" << nombre << ", Edad=" << edad
                  << ", Peso=" << peso << ", Altura=" << altura << std::endl;
    }

    archivo.close();
}

// Función del menú
void menu(ListaDoble& lista) {
    char opcion;
    std::string nombre;
    int edad;
    int peso;
    float altura;
    // menu para seleccionar la opcion deseada 
    while (true) {
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << "Bienvenido, ¿qué desea hacer?" << std::endl;
        std::cout << "A - Ver la lista" << std::endl;
        std::cout << "B - Eliminar a un paciente" << std::endl;
        std::cout << "C - Agregar a un paciente" << std::endl;
        std::cout << "D - Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        // ponemos la opcion de mayusculas y minusculas para evitar errores con el usuario
        switch (opcion) {
            case 'A':
            case 'a':
                std::cout << "Lista de pacientes e IMC:" << std::endl;
                lista.imprimirYCalcularIMC();
                std::cout << "Promedio de edad: " << lista.promedioEdad() << " años" << std::endl;
                std::cout << "Promedio de peso: " << lista.promedioPeso() << " kg" << std::endl;

                break;

            case 'B':
            case 'b':
                std::cout << "Ingrese el nombre del paciente a eliminar: ";
                std::cin.ignore(); 
                std::getline(std::cin, nombre);
                lista.eliminar(nombre);
                break;

            case 'C':
            case 'c':
                std::cout << "Ingrese el nombre del paciente: ";
                std::cin.ignore(); 
                std::getline(std::cin, nombre);
                std::cout << "Ingrese la edad del paciente: ";
                std::cin >> edad;
                std::cout << "Ingrese el peso del paciente (kg): ";
                std::cin >> peso;
                std::cout << "Ingrese la altura del paciente (m): ";
                std::cin >> altura;
                lista.agregar({nombre, edad, peso, altura});
                break;

            case 'D':
            case 'd':
                return; // Salir del menú

            default:
                std::cout << "Opción no válida. Por favor, intente nuevamente." << std::endl;
                break;
        }
    }
}

int main() {
    ListaDoble lista;

    // Leer pacientes desde el archivo CSV
    leerPacientesDesdeCSV("pacientes.csv", lista);
    // Mostrar menú para interactuar con el usuario
    menu(lista);

   
    return 0;
}
