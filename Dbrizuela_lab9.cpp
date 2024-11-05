#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
using namespace std;

// Valor que indica una posición vacía en la tabla hash
const int VACIO = -1; 

// Función hash básica que utiliza el módulo del tamaño de la tabla
int hashFunction(int key, int tableSize) {
    return key % tableSize;  
}

int hashFunction2(int key, int tableSize) {
    return 1 + (key % (tableSize - 1));
}

// Inserta un nuevo elemento en la tabla hash usando prueba lineal
void Insert_lineal(std::vector<int>& hashTable, int tableSize, int key) {
    int index = hashFunction(key, tableSize);
    int originalIndex = index;
    int displacement = 0;
    bool collision = false;

    // Detectar colisión en la posición inicial
    if (index >= 0 && index < hashTable.size()) {
        if (hashTable[index] != VACIO) {
            std::cout << "Colisión detectada en índice " << index 
                      << " al insertar " << key << std::endl;
            collision = true;
        }

        while (hashTable[index] != VACIO) {
            index = (index + 1) % tableSize;
             // Si volvemos al inicio
            if (index == originalIndex) {  
                std::cout << "No hay espacio en la tabla hash para " << key << std::endl;
                return;
            }
        }

    // Insertar el nuevo elemento
        hashTable[index] = key;
        std::cout << std::setw(30) << std::left << (collision ? "Insertado con colisión:" : "Insertado:")
                  << key << " en posición " << index << std::endl;
    } else {
        std::cout << "Índice fuera de rango. Debe estar entre 0 y " << hashTable.size() - 1 << "." << std::endl;
    }
}

// Busca un elemento en la tabla hash usando prueba lineal
void buscar_lineal(const std::vector<int>& hashTable, int tableSize, int key) {
    int index = hashFunction(key, tableSize);
    int originalIndex = index;  

    // Buscar el elemento usando prueba lineal hasta que vuelva al índice original
    while (hashTable[index] != VACIO) {
        if (hashTable[index] == key) {
            std::cout << std::setw(30) << std::left << "Encontrado:"
                      << "La información " << key 
                      << " está en la posición " << index 
                      << std::endl;
            return;
        }
        index = (index + 1) % tableSize;  
         // Si volvemos al inicio
        if (index == originalIndex) {  
            break;
        }
    }
    std::cout << std::setw(30) << std::left << "No encontrado:"
              << "La información " << key << " no se encuentra en el arreglo" << std::endl;
}

void Insert_dobledirecion(vector<int>& hashTable, int key, int tableSize) {
    int index = hashFunction(key, tableSize);
    int index2 = hashFunction2(key, tableSize);
    int displacement;
// //Esto implica usar dos funciones hash para calcular dos índices hasta encontrar un espacio vacío.
    while (hashTable[index] != VACIO) {
        index = (index + index2) % tableSize;
        displacement++;
        if (displacement >= tableSize) {
            cout << "No hay espacio para " << key << endl;
            return;
        }
    }
    hashTable[index] = key;
    cout << "Insertado " << key << " en posición " << index << endl;
}

// Inserción con encadenamiento
void insert_encadenamiento(vector<list<int>>& hashTable, int key, int tableSize) {
    int index = hashFunction(key, tableSize);
    hashTable[index].push_back(key);
    cout << "Insertado " << key << " en índice " << index << endl;
}

void buscar_encadenamiento(const vector<list<int>>& hashTable, int tableSize, int key) {
    int index = hashFunction(key, tableSize);
    //Usa una lista enlazada para manejar las colisiones
    for (const auto& elem : hashTable[index]) {
        if (elem == key) {
            cout << "Encontrado: La información " << key << " está en el índice " << index << endl;
            return;
        }
    }
    cout << "No encontrado: La información " << key << " no se encuentra en el arreglo" << endl;
}

void buscar_cuadratica(const std::vector<int>& hashTable, int key, int tableSize) {
    int index = hashFunction(key, tableSize);
    // Guardamos la posición original
    int originalIndex = index;
    // Para rastrear el desplazamiento
    int i = 0; 
    // Buscar el elemento usando prueba cuadratica
    while (hashTable[(index + i * i) % tableSize] != VACIO) {
        if (hashTable[(index + i * i) % tableSize] == key) {
            std::cout << std::setw(30) << std::left << "Encontrado:"
                      << "La información " << key 
                      << " está en la posición " << (index + i * i) % tableSize 
                      << std::endl;
            return;
        }
        // Incrementar el desplazamiento
        i++;  
        // Si volvemos al inicio
        if ((index + i * i) % tableSize == originalIndex) {
            break;
        }
    }
    std::cout << std::setw(30) << std::left << "No encontrado:"
              << "La información " << key << " no se encuentra en el arreglo "<< std::endl;
}


void insert_cuadratica(std::vector<int>& hashTable, int key, int tableSize, int userIndex) {
    int index = userIndex;  // Usar el índice proporcionado por el usuario
    int originalIndex = index;  
    int i = 0;
    bool collision = false;

    // Verificar si el índice inicial está en el rango
    if (index >= 0 && index < hashTable.size()) {
        while (hashTable[(index + i * i) % tableSize] != VACIO) {
            // Mostrar mensaje de colisión
            std::cout << "Colisión en posición " << (index + i * i) % tableSize << " para clave " << key << std::endl;
            // Marcar que hubo colisión
            collision = true;  
            i++;
            // Verificar si hemos recorrido toda la tabla
            if (i >= tableSize) {
                std::cout << "No hay espacio para " << key << std::endl;
                return;
            }
        }

        // Insertar clave cuando se encuentra un espacio vacío
        hashTable[(index + i * i) % tableSize] = key;
        std::cout << std::setw(30) << std::left << (collision ? "Insertado con colisión:" : "Insertado:")
                  << key << " en posición " << (index + i * i) % tableSize << std::endl;
    } else {
        std::cout << "Índice fuera de rango. Debe estar entre 0 y " << hashTable.size() - 1 << "." << std::endl;
    }
}



// Elimina un elemento de la tabla hash
void borrar(std::vector<int>& hashTable, int tableSize, int key) {
    int index = hashFunction(key, tableSize);
    int originalIndex = index; 


    while (hashTable[index] != VACIO) {
        if (hashTable[index] == key) {
            hashTable[index] = VACIO;  
            std::cout << std::setw(30) << std::left << "Eliminado:"
                      << "La información " << key << " fue eliminada de la posición " << index << std::endl;
            return;
        }
        index = (index + 1) % tableSize; 
        // Si volvemos al inicio
        if (index == originalIndex) {  
            break;
        }
    }
    std::cout << std::setw(30) << std::left << "No encontrado:"
              << "La información " << key << " no se encuentra en el arreglo " << std::endl;
}

//imprimr la tabla
void imprimirTablaHash(const std::vector<int>& hashTable) {
    std::cout << "Tabla hash con prueba lineal:" << std::endl;
    for (size_t i = 0; i < hashTable.size(); ++i) {
        if (hashTable[i] == VACIO) {
            std::cout << "Índice " << i << ": VACIO" << std::endl;
        } else {
            std::cout << "Índice " << i << ": " << hashTable[i] << std::endl;
        }
    }
}

void mostrarMenu() {
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Bienvenido, ¿qué desea hacer?" << endl;
    cout << "A - Insertar" << endl;
    cout << "B - Eliminar" << endl;
    cout << "C - Buscar" << endl;    
    cout << "F - Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " {L|C|D|E}" << std::endl;
        return 1;
    }
    
    char opcion;
    std::vector<int> array = {23, 42, -1, 66, 14, 43, -1, 81, 37, -1, 28, 55, 94, 80, 64};
     // Tamaño de la tabla hash
    int tableSize = array.size(); 

    // Inicializar la tabla hash con VACIO
    std::vector<int> hashTable(tableSize, VACIO);
    std::vector<list<int>>hashTableChaining(tableSize);
    
    imprimirTablaHash(hashTable);
    
    if (argv[1][0] == 'L') {
        do {
            mostrarMenu();
            cin >> opcion;
            opcion = toupper(opcion);

            switch (opcion) {
                case 'A': {
                    int num;
                    int num2;
                    cout << "Ingrese donde lo quiere insertar: ";
                    cin >> num2;
                    cout << "Ingrese el número que quiere insertar: ";
                    cin >> num;
                    Insert_lineal(hashTable, tableSize, num); 
                    imprimirTablaHash(hashTable);
                    break;
                }

                case 'B': {
                    int num;
                    std::cout << "¿Qué número quiere eliminar?" << std::endl;
                    cin >> num;
                    borrar(hashTable, tableSize, num);
                    imprimirTablaHash(hashTable);
                    break;
                }

                case 'C': {
                    int num;
                    std::cout << "¿Qué número quiere buscar?" << std::endl;
                    cin >> num;
                    buscar_lineal(hashTable, tableSize, num);
                    break;
                }

                case 'F':
                    std::cout << "Adios" << std::endl;
                    break;

                default:
                    cout << "Opción no válida. Intente de nuevo." << endl;
                    break;
            }
        } while (opcion != 'F');
    }
    
    if (argv[1][0] == 'C') {

        do{ 
        mostrarMenu();
        cin >> opcion;

        switch (toupper(opcion)) {
            case 'A':
                int num, index;
                cout << "Ingrese el número que quiere insertar: ";
                cin >> num;
                cout << "Ingrese el índice en el que quiere insertar el número: ";
                cin >> index;
                insert_cuadratica(hashTable, num, tableSize, index); 
                imprimirTablaHash(hashTable); 
                break;

            case 'B': {
                int num; 
                std::cout << "¿Qué número quiere eliminar?" << std::endl;
                cin >> num; 
                borrar(hashTable,num, tableSize); 
                imprimirTablaHash(hashTable); 
                break;
            }

            case 'C': {
                int num; 
                std::cout << "¿Qué número quiere buscar?" << std::endl;
                cin >> num; 
                buscar_cuadratica(hashTable, tableSize, num); 
                break;
            }

            case 'F':
                std::cout << "Adios" << std::endl;
                return 0;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
            }
        } while (opcion != 'F');
    }
    
    if (argv[1][0] == 'D') {
        do {
            mostrarMenu();
            cin >> opcion;
            opcion = toupper(opcion);

            switch (opcion) {
                case 'A': {
                    int num;
                    int num2;
                    cout << "Ingrese donde lo quiere insertar: ";
                    cin >> num2;
                    cout << "Ingrese el número que quiere insertar: ";
                    cin >> num;
                    Insert_dobledirecion(hashTable, tableSize, num); 
                    imprimirTablaHash(hashTable);
                    break;
                }

                case 'B': {
                    int num;
                    std::cout << "¿Qué número quiere eliminar?" << std::endl;
                    cin >> num;
                    borrar(hashTable, tableSize, num);
                    imprimirTablaHash(hashTable);
                    break;
                }

                case 'C': {
                    int num;
                    std::cout << "¿Qué número quiere buscar?" << std::endl;
                    cin >> num;
                    
                    break;
                }

                case 'F':
                    std::cout << "Adios" << std::endl;
                    break;

                default:
                    cout << "Opción no válida. Intente de nuevo." << endl;
                    break;
            }
        } while (opcion != 'F');
    }

    if (argv[1][0] == 'E') {
        do {
            mostrarMenu();
            cin >> opcion;
            opcion = toupper(opcion);

            switch (opcion) {
                case 'A': {
                    int num;
                    int num2;
                    cout << "Ingrese donde lo quiere insertar: ";
                    cin >> num2;
                    cout << "Ingrese el número que quiere insertar: ";
                    cin >> num;
                    insert_encadenamiento(hashTableChaining, tableSize, num);
                    imprimirTablaHash(hashTable);
                    break;
                }

                case 'B': {
                    int num;
                    std::cout << "¿Qué número quiere eliminar?" << std::endl;
                    cin >> num;
                    borrar(hashTable, tableSize, num);
                    imprimirTablaHash(hashTable);
                    break;
                }

                case 'C': {
                    int num;
                    std::cout << "¿Qué número quiere buscar?" << std::endl;
                    cin >> num;
                    buscar_encadenamiento(hashTableChaining, tableSize, num);
                    break;
                }

                case 'F':
                    std::cout << "Adios" << std::endl;
                    break;

                default:
                    cout << "Opción no válida. Intente de nuevo." << endl;
                    break;
            }
        } while (opcion != 'F');
    }
    return 0;
}