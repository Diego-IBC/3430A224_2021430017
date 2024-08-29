#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

// Estructura para almacenar la información del paciente
struct Paciente {
    std::string nombre;
    int edad;
    int peso;   // en kilogramos
    double altura; // en metros
};

// Lista de nombres
std::vector<std::string> nombres = {
    "Ana", "Pedro", "María", "Juan", "Laura", "Luis", "Isabel", "Andrés", "Carmen", "Javier",
    "Paula", "Francisco", "Teresa", "Manuel", "Rosa", "Jorge", "Elena", "Sergio", "Marta", "David",
    "Carolina", "Pablo", "Beatriz", "Alberto", "María José", "Miguel", "Alicia", "Fernando", "Dolores",
    "Enrique", "Raquel", "Gonzalo", "Patricia", "Óscar", "Silvia", "Tomás", "Sara", "Ramón", "Laura",
    "Víctor", "Juana", "Andrés", "Marta", "Guillermo", "Mariana", "Roberto", "Nuria", "Ángel", "Sonia",
    "Iván", "Claudia", "Iván", "Teresa", "Valentín", "Olga", "César", "Alicia", "Hugo", "Adriana",
    "Luis Miguel", "Fabiola", "Rubén", "María del Carmen", "Juan Carlos", "Marta", "Carlos", "Mónica",
    "Sergio", "Juanita", "Gabriel", "Amelia", "Luis Antonio", "Celia", "Mario", "Lorena", "Simón",
    "Claudia", "José Luis", "Carolina", "Emiliano", "Rosa María", "Felipe", "Isabel", "Javier", "Daniela",
    "Hugo", "Patricia", "Adrián", "Verónica", "Francisco Javier", "Lucía", "Roberto", "Claudia", "Sergio",
    "Mireya", "Luis", "Beatriz", "Daniel", "Gabriela", "Juan Pablo"
};

// Función para generar un nombre aleatorio
std::string generarNombre() {
    int index = std::rand() % nombres.size();
    return nombres[index];
}

// Función para generar un peso aleatorio
int generarPeso() {
    return 50 + std::rand() % 51; // peso entre 50 y 100 kg
}

// Función para generar una altura aleatoria
double generarAltura() {
    return 1.50 + (std::rand() % 16) / 100.0; // altura entre 1.50 y 1.65 metros
}

int main() {
    std::ofstream archivo("pacientes.csv");

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo para escribir.\n";
        return 1;
    }

    archivo << "Nombre,Edad,Peso,Altura\n"; // Encabezados del CSV

    std::srand(std::time(0)); // Inicializa la semilla para la generación de números aleatorios

    for (int i = 1; i <= 100; ++i) {
        Paciente paciente;
        paciente.nombre = generarNombre();
        paciente.edad = 18 + std::rand() % 63; // edad entre 18 y 80 años
        paciente.peso = generarPeso();
        paciente.altura = generarAltura();

        archivo << paciente.nombre << ","
                << paciente.edad << ","
                << paciente.peso << ","
                << paciente.altura << "\n";
    }

    archivo.close();
    std::cout << "Archivo CSV creado con éxito.\n";

    return 0;
}
