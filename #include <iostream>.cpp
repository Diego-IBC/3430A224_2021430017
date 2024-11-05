#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <fstream>

using namespace std;

sem_t empty_slots, full_slots; 
vector<string> buffer;        
int buffer_capacity;         
pthread_mutex_t buffer_mutex;  

string generar_dato(int productor_id, int numero_elemento) {
    return to_string(productor_id) + "_" + to_string(numero_elemento);
}

class Productor {
private:
    int id;
    int numero_producciones;
    ofstream registro;

public:
    Productor(int id, int producciones) : id(id), numero_producciones(producciones) {
        registro.open("registro_productor_" + to_string(id) + ".txt");
    }

    void producir() {
        for (int i = 1; i <= numero_producciones; ++i) {
            string dato = generar_dato(id, i);

            sem_wait(&empty_slots); 

            pthread_mutex_lock(&buffer_mutex); 

            buffer.push_back(dato);
            cout << "Productor " << id << " inserta: " << dato << endl;
            registro << "Productor " << id << " generó: " << dato << " - Inserción exitosa" << endl;
            
            //importar a txt añadido

            pthread_mutex_unlock(&buffer_mutex); 

            sem_post(&full_slots);

            this_thread::sleep_for(chrono::seconds(rand() % 5));
        }
        registro.close();
    }
};

class Consumidor {
private:
    int id;
    int numero_consumos;
    ofstream registro;

public:
    Consumidor(int id, int consumos) : id(id), numero_consumos(consumos) {
        registro.open("registro_consumidor_" + to_string(id) + ".txt");
    }

    void consumir() {
        for (int i = 1; i <= numero_consumos; ++i) {

            sem_wait(&full_slots);
            pthread_mutex_lock(&buffer_mutex); 

            string dato = buffer.front();
            buffer.erase(buffer.begin()); 
            cout << "Consumidor " << id << " consume: " << dato << endl;
            registro << "Consumidor " << id << " eliminó: " << dato << " - Eliminado con éxito" << endl; 

            pthread_mutex_unlock(&buffer_mutex); 

            sem_post(&empty_slots); 

            this_thread::sleep_for(chrono::seconds(rand() % 4));
        }
        registro.close();
    }
};

int main(int argc, char *argv[]) {
    if (argc != 6) {
        cerr << "Uso: " << argv[0] << " <NP> <NC> <BC> <NPP> <NCC>" << endl;
        return 1;
    }

    int NP = stoi(argv[1]);   
    int NC = stoi(argv[2]);  
    buffer_capacity = stoi(argv[3]); 
    int NPP = stoi(argv[4]);  
    int NCC = stoi(argv[5]);  

    buffer.reserve(buffer_capacity);

    sem_init(&empty_slots, 0, buffer_capacity);
    sem_init(&full_slots, 0, 0);

    pthread_mutex_init(&buffer_mutex, nullptr);

    vector<thread> productores;
    for (int i = 0; i < NP; ++i) {
        productores.push_back(thread(&Productor::producir, Productor(i + 1, NPP)));
    }

    vector<thread> consumidores;
    for (int i = 0; i < NC; ++i) {
        consumidores.push_back(thread(&Consumidor::consumir, Consumidor(i + 1, NCC)));
    }

    for (auto &productor : productores) {
        productor.join();
    }
    for (auto &consumidor : consumidores) {
        consumidor.join();
    }

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&buffer_mutex);

    return 0;
}
