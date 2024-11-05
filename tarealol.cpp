#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Estructura del nodo
struct Node {
    int info;
    Node* left;
    Node* right;

    Node(int data) : info(data), left(nullptr), right(nullptr) {}
};

struct Node {
    string info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(const string& data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Clase del Árbol Binario de Búsqueda
class ArbolBinario {
private:
    Node* root;

    // Función para insertar un nuevo nodo en el ABB
    Node* insertar(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }
        if (data < node->info) {
            node->left = insertar(node->left, data);
        } else if (data > node->info) { // Para evitar duplicados
            node->right = insertar(node->right, data);
        }
        // Si data == node->info, no insertamos duplicados
        return node;
    }

    // Recorrido en Preorden
    void preOrden(Node* node, string& resultado) const {
        if (node == nullptr) return;
        resultado += to_string(node->info) + " - ";
        preOrden(node->left, resultado);
        preOrden(node->right, resultado);
    }

    // Recorrido en Inorden
    void inOrden(Node* node, string& resultado) const {
        if (node == nullptr) return;
        inOrden(node->left, resultado);
        resultado += to_string(node->info) + " - ";
        inOrden(node->right, resultado);
    }

    // Recorrido en Posorden
    void posOrden(Node* node, string& resultado) const {
        if (node == nullptr) return;
        posOrden(node->left, resultado);
        posOrden(node->right, resultado);
        resultado += to_string(node->info) + " - ";
    }

    // Función para eliminar un nodo (opcional)
    Node* eliminar(Node* node, int data) {
        if (node == nullptr) return node;

        if (data < node->info) {
            node->left = eliminar(node->left, data);
        }
        else if (data > node->info) {
            node->right = eliminar(node->right, data);
        }
        else {
            // Nodo con solo un hijo o sin hijos
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Nodo con dos hijos: obtener el inorden sucesor (mínimo en el subárbol derecho)
            Node* temp = minimo(node->right);

            // Copiar el contenido del inorden sucesor al nodo actual
            node->info = temp->info;

            // Eliminar el inorden sucesor
            node->right = eliminar(node->right, temp->info);
        }
        return node;
    }

    // Función para encontrar el nodo con el valor mínimo
    Node* minimo(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

public:
    // Constructor
    ArbolBinario() : root(nullptr) {}

    Arbol(Node* node) : root(node) {}

    // Recorrer el arbol en preorden y escribir en el archivo
    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << node->info << "->" << node->left->info << ";" << endl;
            } else {
                string cadena = node->info + "i";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            if (node->right != nullptr) {
                fp << node->info << "->" << node->right->info << ";" << endl;
            } else {
                string cadena = node->info + "d";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            recorrer(node->left, fp);
            recorrer(node->right, fp);
        }
    }

    // Generar y mostrar la visualizacion del arbol
    void visualize() {
        ofstream fp("arbol.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo arbol.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=yellow];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;

        fp.close();

        // Generar y mostrar la imagen del arbol
        system("dot -Tpng -o arbol.png arbol.txt");
        system("eog arbol.png");
    }
};

    // Función para insertar datos
    void insertar(int data) {
        root = insertar(root, data);
    }

    // Función para eliminar datos
    void eliminar(int data) {
        root = eliminar(root, data);
    }

    // Funciones para obtener los recorridos
    string obtenerPreOrden() const {
        string resultado;
        preOrden(root, resultado);
        if (!resultado.empty()) resultado.erase(resultado.size() - 3); // Eliminar el último " - "
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
};

int main() {
    ArbolBinario arbol;

    // Inserción de los valores iniciales en el ABB
    vector<int> valoresIniciales = {};
    for (int val : valoresIniciales) {
        arbol.insertar(val);
    }

    // Variables para el menú
    char opcion;
    int cosa;

    while(true){
        cout << "----------------------------------------------------------------------" << endl;
        cout << "Bienvenido, ¿qué desea hacer?" << endl;
        cout << "A - Ingresar contenido" << endl;
        cout << "B - Eliminar contenido" << endl;
        cout << "C - Imprimir recorridos" << endl;
        cout << "D - Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 'A':
            case 'a': {
                cout << "¿Cuántos valores desea ingresar? ";
                int cantidad;
                cin >> cantidad;
                for (int i = 0; i < cantidad; i++) {
                    cout << "Valor a ingresar: ";
                    cin >> cosa;
                    arbol.insertar(cosa);
                }
                break;
            }

            case 'B':
            case 'b': {
                cout << "Ingrese el valor a eliminar: ";
                cin >> cosa;
                arbol.eliminar(cosa);
                break;
            }

            case 'C':
            case 'c': {
                cout << "— Preorden—" << endl;
                cout << arbol.obtenerPreOrden() << endl;

                cout << "— Inorden—" << endl;
                cout << arbol.obtenerInOrden() << endl;

                cout << "— Posorden—" << endl;
                cout << arbol.obtenerPosOrden() << endl;
                break;
            }

            case 'D':
            case 'd':
                return 0;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    }
    return 0;
}



