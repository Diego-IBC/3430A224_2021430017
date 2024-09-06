#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <queue>
#include <functional>
#include <unordered_set>  // Para evitar duplicados

struct Paciente {
    std::string nombre;
    int edad;
    float altura;  // en metros
    int peso;      // en kilogramos
    float Ac1;
    int prioridad;  // Prioridad del paciente

    Paciente(const std::string& n, int e, float a, int p, float ac1)
        : nombre(n), edad(e), altura(a), peso(p), Ac1(ac1), prioridad(0) {}
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
    // Para verificar duplicados por nombre
    std::unordered_set<std::string> nombres; 

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr) {}
    // Función para agregar un nodo al final de la lista    
    void agregar(const Paciente& p) {
        // Evitar duplicados al agregar pacientes
        if (nombres.find(p.nombre) != nombres.end()) {
            return; 
        }

        Nodo* nuevoNodo = new Nodo(p);
        if (!cabeza) {
            cabeza = cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
        nombres.insert(p.nombre);  
    }
    // Función para imprimir la lista y calcular el IMC de cada paciente
    void imprimirYCalcularIMC() const {
        Nodo* actual = cabeza;
        while (actual) {
            std::cout << "Nombre: " << actual->paciente.nombre << std::endl;
            std::cout << "Edad: " << actual->paciente.edad << std::endl;
            std::cout << "Peso: " << actual->paciente.peso << " kg" << std::endl;
            std::cout << "Altura: " << actual->paciente.altura << " m" << std::endl;
            std::cout << "Ac1: " << actual->paciente.Ac1 << std::endl;
            float imc = actual->paciente.peso / std::pow(actual->paciente.altura, 2);
            std::cout << "IMC: " << std::fixed << std::setprecision(2) << imc << std::endl;
            std::cout << std::endl;
            actual = actual->siguiente;
        }
    }
    //llenar la cola con los pacientes con prioridad gracias al comparador
    void llenarColaPrioridad(std::priority_queue<Paciente, std::vector<Paciente>, std::function<bool(Paciente, Paciente)>>& colaPrioridad) {
        Nodo* actual = cabeza;
        while (actual) {
            colaPrioridad.push(actual->paciente);
            actual = actual->siguiente;
        }
    }
    // asignar las prioridades 
    void determinarPrioridades() {
        Nodo* actual = cabeza;
        while (actual) {
            calcularPrioridad(actual->paciente);
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
    // Función para calcular el promedio de Aci1 del grupo
    float promedioAC1() const {
        Nodo* actual = cabeza;
        float sumaAC1 = 0.0;
        int contador = 0;

        while (actual) {
            sumaAC1 += actual->paciente.Ac1;
            contador++;
            actual = actual->siguiente;
        }
        return contador ? sumaAC1 / contador : 0.0;
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
                nombres.erase(nombre);  
                delete actual;
                return;
            }
            actual = actual->siguiente;
        }
        std::cout << "Paciente no encontrado." << std::endl;
    }
    //calcula la prioridad para determinar a las prioridades
    void calcularPrioridad(Paciente& p) {
    // Calcular IMC
    float imc = p.peso / std::pow(p.altura, 2);

    // Sumar peso, IMC y Ac1 para determinar la prioridad
    p.prioridad = static_cast<int>(p.peso + imc + p.Ac1);

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

// Comparador para la cola de prioridad
bool comparador(const Paciente& a, const Paciente& b) {
    return a.prioridad < b.prioridad;  
}

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
        float altura;
        int peso;
        float Ac1;

        // Leer nombre hasta la coma
        std::getline(ss, nombre, ',');

         // Leer edad
        if (!(ss >> edad)) {
            std::cerr << "Error al leer la edad para el paciente: " << nombre << std::endl;
            continue;
        }
        ss.ignore();  // Ignorar la coma después de la edad

         // Leer altura
        if (!(ss >> altura) || altura <= 0) {
            std::cerr << "Error al leer la altura para el paciente: " << nombre << std::endl;
            continue;
        }
        ss.ignore();  // Ignorar la coma después de la altura

         // Leer peso
        if (!(ss >> peso)) {
            std::cerr << "Error al leer el peso para el paciente: " << nombre << std::endl;
            continue;
        }
        ss.ignore();  // Ignorar la coma después de la peso
         // Leer Ac1
        if (!(ss >> Ac1) || Ac1 <= 0) {
            std::cerr << "Error al leer el valor de Ac1 para el paciente: " << nombre << std::endl;
            continue;
        }

        Paciente paciente = {nombre, edad, altura, peso, Ac1};
        lista.agregar(paciente);
    }

    archivo.close();
}
// Función del menú
void menu(ListaDoble& lista) {
    std::priority_queue<Paciente, std::vector<Paciente>, std::function<bool(Paciente, Paciente)>> colaPrioridad(comparador);

    char opcion;
    std::string nombre;
    int edad;
    float altura;
    int peso;
    float Ac1;

    // menu para seleccionar la opcion deseada 
    while (true) {
        lista.determinarPrioridades();
        // Reinicializar la cola 
        colaPrioridad = std::priority_queue<Paciente, std::vector<Paciente>, std::function<bool(Paciente, Paciente)>>(comparador);  
        lista.llenarColaPrioridad(colaPrioridad);

        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << "Bienvenido, ¿qué desea hacer?" << std::endl;
        std::cout << "A - Ver la lista de pacientes e IMC" << std::endl;
        std::cout << "B - Eliminar a un paciente" << std::endl;
        std::cout << "C - Agregar a un paciente" << std::endl;
        std::cout << "D - Ver la cola de atención por prioridad" << std::endl;
        std::cout << "E - Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        // ponemos la opcion de mayusculas y minusculas para evitar errores con el usuario
        switch (opcion) {
            case 'A':
            case 'a':
                std::cout << "Lista de pacientes e IMC:" << std::endl;
                lista.imprimirYCalcularIMC();
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
                std::cout << "Ingrese la altura del paciente (m): ";
                std::cin >> altura;
                std::cout << "Ingrese el peso del paciente (kg): ";
                std::cin >> peso;
                std::cout << "Ingrese el Ac1 del paciente: ";
                std::cin >> Ac1;
                lista.agregar({nombre, edad, altura, peso, Ac1});
                lista.determinarPrioridades();
                break;

            case 'D':
            case 'd':
                std::cout << "Cola de atención por prioridad:" << std::endl;
                while (!colaPrioridad.empty()) {
                    Paciente p = colaPrioridad.top();
                    std::cout << "Paciente: " << p.nombre << ", Prioridad: " << p.prioridad << std::endl;
                    colaPrioridad.pop();
                }
                break;

            case 'E':
            case 'e':
                return;

            default:
                std::cout << "Opción no válida." << std::endl;
        }
    }
}

int main() {
    ListaDoble lista;
    // Leer pacientes desde el archivo CSV
    leerPacientesDesdeCSV("patient_list.csv", lista);
    // Mostrar menú para interactuar con el usuario
    menu(lista);
    return 0;
}
