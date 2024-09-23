#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm> 
#include <ctime>     
#include <cstdlib>   
#include <limits>    
using namespace std;

// Estructura del nodo
struct Node {
    int info;
    Node* left;
    Node* right;

    Node(int data) : info(data), left(nullptr), right(nullptr) {}
};

// Clase del Árbol Binario de Búsqueda
class ArbolBinario {
private:
    Node* root;
    // Función para insertar un nodo en el árbol
    Node* insertar(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }
        if (data < node->info) {
            node->left = insertar(node->left, data);
        } else if (data > node->info) { 
            node->right = insertar(node->right, data);
        }
        return node;
    }
    // Función para construir un árbol balanceado a partir de una lista ordenada
    Node* construirBalanceado(const vector<int>& datos, int inicio, int fin) {
        if (inicio > fin) return nullptr;

        int medio = inicio + (fin - inicio) / 2;
        Node* nodo = new Node(datos[medio]);

        nodo->left = construirBalanceado(datos, inicio, medio - 1);
        nodo->right = construirBalanceado(datos, medio + 1, fin);

        return nodo;
    }
    // Funciones de recorrido
    void preOrden(Node* node, string& resultado) const {
        if (node == nullptr) return;
        resultado += to_string(node->info) + " - ";
        preOrden(node->left, resultado);
        preOrden(node->right, resultado);
    }

    void inOrden(Node* node, string& resultado) const {
        if (node == nullptr) return;
        inOrden(node->left, resultado);
        resultado += to_string(node->info) + " - ";
        inOrden(node->right, resultado);
    }

    void posOrden(Node* node, string& resultado) const {
        if (node == nullptr) return;
        posOrden(node->left, resultado);
        posOrden(node->right, resultado);
        resultado += to_string(node->info) + " - ";
    }

    // Funcion para eliminación
    Node* eliminar(Node* node, int data) {
        if (node == nullptr) return node;

        if (data < node->info) {
            node->left = eliminar(node->left, data);
        } else if (data > node->info) {
            node->right = eliminar(node->right, data);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minimo(node->right);
            node->info = temp->info;
            node->right = eliminar(node->right, temp->info);
        }
        return node;
    }

    Node* minimo(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
    // Función para recorrer el árbol y generar el archivo para Graphviz
    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << "    " << node->info << " -> " << node->left->info << ";\n";
                recorrer(node->left, fp);
            } else {
                fp << "    \"" << node->info << "i\" [shape=point];\n";
                fp << "    " << node->info << " -> \"" << node->info << "i\";\n";
            }

            if (node->right != nullptr) {
                fp << "    " << node->info << " -> " << node->right->info << ";\n";
                recorrer(node->right, fp);
            } else {
                fp << "    \"" << node->info << "d\" [shape=point];\n";
                fp << "    " << node->info << " -> \"" << node->info << "d\";\n";
            }
        }
    }

    // Función para liberar memoria
    void liberarMemoria(Node* node) {
        if (node != nullptr) {
            liberarMemoria(node->left);
            liberarMemoria(node->right);
            delete node;
        }
    }

public:
    ArbolBinario() : root(nullptr) {}
    
    ~ArbolBinario() {
        liberarMemoria(root);
    }

    // Función para construir un árbol balanceado desde una lista de números
    void construirBalanceado(const vector<int>& datos) {
        if (datos.empty()) {
            root = nullptr;
            return;
        }

        // Primero, ordenar los datos
        vector<int> datosOrdenados = datos;
        sort(datosOrdenados.begin(), datosOrdenados.end());

        // Eliminar duplicados
        datosOrdenados.erase(unique(datosOrdenados.begin(), datosOrdenados.end()), datosOrdenados.end());

        // Construir el árbol balanceado
        root = construirBalanceado(datosOrdenados, 0, datosOrdenados.size() - 1);
    }

    // Función para insertar un solo dato 
    bool insertarDato(int data) {
        if (buscar(root, data)) {
            return false; 
        }
        root = insertar(root, data);
        return true;
    }

    // Función para eliminar un dato
    bool eliminarDato(int data) {
        if (!buscar(root, data)) {
            return false; 
        }
        root = eliminar(root, data);
        return true;
    }

    // Función para modificar un dato
    bool modificarDato(int viejo, int nuevo) {
        if (!buscar(root, viejo)) {
            return false; 
        }
        if (buscar(root, nuevo)) {
            return false; 
        }
        root = eliminar(root, viejo);
        root = insertar(root, nuevo);
        return true;
    }

    // Función para buscar un dato en el árbol
    bool buscar(Node* node, int data) const {
        if (node == nullptr) return false;
        if (data == node->info) return true;
        if (data < node->info)
            return buscar(node->left, data);
        else
            return buscar(node->right, data);
    }

    // Funciones para obtener los recorridos
    string obtenerPreOrden() const {
        string resultado;
        preOrden(root, resultado);
        if (!resultado.empty()) resultado.erase(resultado.size() - 3);
        return resultado;
    }

    string obtenerInOrden() const {
        string resultado;
        inOrden(root, resultado);
        if (!resultado.empty()) resultado.erase(resultado.size() - 3);
        return resultado;
    }

    string obtenerPosOrden() const {
        string resultado;
        posOrden(root, resultado);
        if (!resultado.empty()) resultado.erase(resultado.size() - 3);
        return resultado;
    }

    // Función para visualizar el árbol usando Graphviz
    void visualize() {
        ofstream fp("grafo.txt");
        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo grafo.txt" << endl;
            return;
        }
        fp << "digraph G {\n";
        fp << "    node [style=filled, fillcolor=yellow];\n"; 
        recorrer(root, fp);
        fp << "}\n";
        fp.close();

        
        system("dot -Tpng -ografo.png grafo.txt");
            system("eog grafo.png"); 
    }
};

// Función para mostrar el menú
void mostrarMenu() {
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Bienvenido, ¿qué desea hacer?" << endl;
    cout << "A - Insertar número" << endl;
    cout << "B - Eliminar número" << endl;
    cout << "C - Modificar número" << endl;
    cout << "D - Mostrar recorridos" << endl;
    cout << "E - Visualizar árbol" << endl;
    cout << "F - Salir" << endl;
    cout << "Seleccione una opción: ";
}

// Función para leer un número entero con validación
int leerNumero(const string& mensaje) {
    int numero;
    while (true) {
        cout << mensaje;
        if (cin >> numero) {
            break;
        } else {
            cout << "Entrada inválida." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
    return numero;
}

int main() {
    ArbolBinario arbol;
    char opcion;
    int numero, viejo, nuevo;

    while (true) {
        mostrarMenu();
        cin >> opcion;

        switch (toupper(opcion)) {
            case 'A':
            case 'a': {
                numero = leerNumero("Ingrese el número a insertar: ");
                if (arbol.insertarDato(numero)) {
                    cout << "Número insertado exitosamente." << endl;
                } else {
                    cout << "El número " << numero << " ya existe en el árbol." << endl;
                }

                string inorden = arbol.obtenerInOrden();
                vector<int> elementos;
                size_t pos = 0;

                while ((pos = inorden.find(" - ")) != string::npos) {
                    string numStr = inorden.substr(0, pos);
                    elementos.push_back(stoi(numStr));
                    inorden.erase(0, pos + 3);
                }
                if (!inorden.empty()) {
                    elementos.push_back(stoi(inorden));
                }

                arbol.construirBalanceado(elementos);
            

                break;
            }

            case 'B': 
            case 'b':{
                numero = leerNumero("Ingrese el número a eliminar: ");
                if (arbol.eliminarDato(numero)) {
                    cout << "Número eliminado exitosamente." << endl;
                } else {
                    cout << "El número " << numero << " no existe en el árbol." << endl;
                }
                break;
            }

            case 'C': 
            case 'c':{
                viejo = leerNumero("Ingrese el número a modificar: ");
                nuevo = leerNumero("Ingrese el nuevo número: ");
                if (arbol.modificarDato(viejo, nuevo)) {
                    cout << "Número modificado exitosamente." << endl;
                } else {
                    cout << "Error al modificar el número." << endl;
                }
                break;
            }

            case 'D': 
            case 'd':{
                cout << "— Preorden —" << endl;
                cout << arbol.obtenerPreOrden() << endl;
                cout << "— Inorden —" << endl;
                cout << arbol.obtenerInOrden() << endl;
                cout << "— Posorden —" << endl;
                cout << arbol.obtenerPosOrden() << endl;
                break;
            }

            case 'E': 
            case 'e':{
                arbol.visualize();
                break;
            }

            case 'F':
            case 'f':
                return 0;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    }
    return 0;
}
