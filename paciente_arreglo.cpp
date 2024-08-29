#include <iostream>
#include <string>

struct Paciente {
    std::string nombre;
    int edad;
    int peso;
    float altura; 
};

int main() {

    Paciente persona[3];
   
    persona[0].nombre = "Kain";
    persona[0].edad = 25;
    persona[0].peso = 60;
    persona[0].altura = 1.80;
    
    persona[1].nombre = "Pedro";
    persona[1].edad = 22;
    persona[1].peso = 50;
    persona[1].altura = 1.80;

    persona[2].nombre = "Maria";
    persona[2].edad = 24;
    persona[2].peso = 70;
    persona[2].altura = 2.10;

    for (int i = 0; i < 3; i++) {
        std::cout << "Paciente " << i + 1 << ": " << std::endl;
        std::cout << "Nombre: " << persona[i].nombre << std::endl;
        std::cout << "Edad: " << persona[i].edad << std::endl;
        std::cout << "Peso: " << persona[i].peso << " kg" << std::endl;
        std::cout << "Altura: " << persona[i].altura << " m" << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
