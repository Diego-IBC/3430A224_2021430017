#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

struct Contenedor {
    int id;
    string empresa;
};

class PuertoSeco {
private:
    int maxPilas;
    int maxContenedores;
    vector<stack<Contenedor>> pilas;
public:

    PuertoSeco(int n, int m) : maxContenedores(n), maxPilas(m) {
        pilas.resize(m);
    }

     // Encontrar la próxima pila disponible con espacio
    int buscarPilaDisponible(int pilaActual) {
        for (int i = pilaActual + 1; i < maxPilas; ++i) {
            if (pilas[i].size() < maxContenedores) {
                return i;
            }
        }
        for (int i = 0; i < pilaActual; ++i) {  
            if (pilas[i].size() < maxContenedores) {
                return i;
            }
        }
        return -1;
    }

    // Ingreso automático de contenedor en la primera pila disponible
    void ingresarContenedorAutomatico(const Contenedor& contenedor) {
        for (int i = 0; i < maxPilas; ++i) {
            if (pilas[i].size() < maxContenedores) {
                pilas[i].push(contenedor);
                cout << "Contenedor ingresado : " << contenedor.id << "/" << contenedor.empresa << " en la pila " << i << endl;
                return;
            }
        }
        cout << "No hay espacio disponible para ingresar el contenedor." << endl;
    }

    //Retiro de un contenedor y es reubicado en la siguiente pila disponible
    //Muestra mensajes sobre el movimiento y la reubicación de los contenedores.
    void retirarContenedor(int contenedorId) {
        stack<Contenedor> pilaTemporal;  
        bool encontrado = false;
        int pilaOrigen = -1;

        // Buscar el contenedor en todas las pilas
        for (int i = 0; i < maxPilas; ++i) {
            while (!pilas[i].empty() && pilas[i].top().id != contenedorId) {
                pilaTemporal.push(pilas[i].top());
                cout << "Contenedor " << pilas[i].top().id << "/" << pilas[i].top().empresa << " movido de la pila " << i << endl;
                pilas[i].pop();
            }

            if (!pilas[i].empty() && pilas[i].top().id == contenedorId) {
                cout << "Contenedor " << contenedorId << " retirado de la pila " << i << endl;
                pilas[i].pop();
                encontrado = true;
                pilaOrigen = i;  
                break;
            }
        }

        if (!encontrado) {
            cout << "Contenedor no encontrado." << endl;
            return;
        }

        // Reubicar los contenedores movidos a otras pilas
        while (!pilaTemporal.empty()) {
            int siguientePila = buscarPilaDisponible(pilaOrigen);
            if (siguientePila == -1) {
                cout << "No hay suficiente espacio en ninguna pila para reubicar los contenedores temporales." << endl;
                return;
            }
            cout << "Restaurando contenedor " << pilaTemporal.top().id << "/" << pilaTemporal.top().empresa << " a la pila " << siguientePila << endl;
            pilas[siguientePila].push(pilaTemporal.top());
            pilaTemporal.pop();
        }
    }

    // Imprimir el estado de todas las pilas
    void imprimirEstado() {
        for (int i = 0; i < maxPilas; ++i) {
            cout << "Pila " << i << ": ";
            if (pilas[i].empty()) {
                cout << "(vacía)";
            } else {
                stack<Contenedor> copiaPila = pilas[i];
                while (!copiaPila.empty()) {
                    Contenedor contenedor = copiaPila.top();
                    cout << contenedor.id << "/" << contenedor.empresa;
                    copiaPila.pop();
                    if (!copiaPila.empty()) {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int n = 4;
    int m = 4;
   

    PuertoSeco puerto(n, m);

    char opcion;

    while(true){
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << "Bienvenido, ¿qué desea hacer?" << std::endl;
        std::cout << "A - Ingresar contenedor automáticamente" << std::endl;
        std::cout << "B - Retirar contenedor" << std::endl;
        std::cout << "C - Imprimir estado de las pilas" << std::endl;
        std::cout << "D - Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 'A':
            case 'a':
                puerto.ingresarContenedorAutomatico({1, "EMP1"});
                puerto.ingresarContenedorAutomatico({2, "EMP2"});
                puerto.ingresarContenedorAutomatico({3, "EMP3"});
                puerto.ingresarContenedorAutomatico({4, "EMP4"});
                break;

            case 'B':
            case 'b': {
                int id;
                cout << "Ingrese ID del contenedor a retirar: ";
                cin >> id;
                puerto.retirarContenedor(id); 
                break;
            }

            case 'C':
            case 'c':
                puerto.imprimirEstado(); 
                break;

            case 'D':
            case 'd':
                return 0;

            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
                break;
        }
    }

    return 0;
}
