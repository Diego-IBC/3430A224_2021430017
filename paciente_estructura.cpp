#include <iostream>
#include <string>

struct Paciente{
    std::string nombre;
    int edad;
    int peso;
    float altura; //cambio a float para eviatar errores
};

int main(){

    Paciente persona1;
    Paciente persona2;
    Paciente persona3;
   
    persona1.nombre = "Kain";
    persona1.edad = 25;
    persona1.peso = 60;
    persona1.altura = 1.80;
    
    persona2.nombre = "Pedro";
    persona2.edad = 22;
    persona2.peso = 50;
    persona2.altura = 1.80;

    persona3.nombre = "Maria";
    persona3.edad = 24;
    persona3.peso = 70;
    persona3.altura = 2.10;

    std::cout << "Paciente 1: " << std::endl;
    std::cout << "Nombre: " << persona1.nombre << std::endl;
    std::cout << "Edad: " << persona1.edad << std::endl;
    std::cout << "Peso: " << persona1.peso << " kg" << std::endl;
    std::cout << "Altura: " << persona1.altura << " m" << std::endl;

    std::cout << "\nPaciente 2: " << std::endl;
    std::cout << "Nombre: " << persona2.nombre << std::endl;
    std::cout << "Edad: " << persona2.edad << std::endl;
    std::cout << "Peso: " << persona2.peso << " kg" << std::endl;
    std::cout << "Altura: " << persona2.altura << " m" << std::endl;

    std::cout << "\nPaciente 3: " << std::endl;
    std::cout << "Nombre: " << persona3.nombre << std::endl;
    std::cout << "Edad: " << persona3.edad << std::endl;
    std::cout << "Peso: " << persona3.peso << " kg" << std::endl;
    std::cout << "Altura: " << persona3.altura << " m" << std::endl;

    return 0;
}
