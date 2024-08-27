#include <iostream>
#include <string>

struct Paciente{
    std::string nombre;
    int edad;
    int peso;
    int altura;
};

int main(){

    Paciente persona1;
    Paciente persona2;
    Paciente persona3;

   
    persona1.nombre = "kain";
    persona1.edad = 25;
    persona1.peso = 60;
    persona1.altura = 1.80;
    
    persona2.nombre = "Pedro";
    persona2.edad = 22;
    persona2.peso = 50;
    persona2.altura = 1.80;

    persona3.nombre = "maria";
    persona3.edad = 24;
    persona3.peso = 70;
    persona3.altura = 2.10;

    
}