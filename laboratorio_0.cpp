#include <iostream>
#include <string>  // Incluir la biblioteca para usar strings

std::string par(int numero) {
    std::string respuesta;  // Variable para almacenar "par" o "impar"
    
    if (numero % 2 == 0) {  // Verificar si el número es divisible por 2
        respuesta = "par";
    } else {
        respuesta = "impar";
    }
    
    return respuesta;  // Devolver el resultado
}

int contar(std::string palabra) {
    int contador = 0;  // Variable para almacenar la cuenta de caracteres

    // Recorrer la cadena y contar cada caracter
    for (char c : palabra) {
        contador++;
    }
    // return palabra.length(); 
    return contador;  // Devolver el resultado
}
int main() {
    int numero;
    std::string palabra;

    // Pedir al usuario que ingrese un número
    std::cout << "Por favor, ingresa un número: ";
    std::cin >> numero;

    // Pedir al usuario que ingrese una cadena de texto
    std::cout << "Por favor, ingresa una palabra: ";
    std::cin >> palabra;

    // Mostrar si el número es par o impar
    std::cout << "El número que ingresaste es: " << numero << " y es " << par(numero) << std::endl;

    // Mostrar la cantidad de caracteres en la cadena
    std::cout << "La palabra que ingresaste tiene " << contar(palabra) << " caracteres." << std::endl;

    return 0;
}