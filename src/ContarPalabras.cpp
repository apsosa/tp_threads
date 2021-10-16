#include <iostream>
#include "HashMapConcurrente.hpp"
#include "CargarArchivos.hpp"
#include "ListaAtomica.hpp"
#include <mutex>       // std::mutex

std::mutex mutex_insert;
int main(int argc, char **argv) {
    mutex_insert.lock();
    ListaAtomica<int> list;
    list.insertar(5);
    list.insertar(2);
    list.insertar(3);
    for (unsigned int i = 0; i < list.longitud(); i++) {
        /* code */
        std::cout << list[i] << std::endl;
    }

    for(auto it = list.begin(); it.operator!=(list.end()) ; it.operator++()) {
        std::cout << it.operator*() << std::endl;
    }
    mutex_insert.unlock();

    
    if (argc < 4) {
        std::cout << "Error: faltan argumentos." << std::endl;
        std::cout << std::endl;
        std::cout << "Modo de uso: " << argv[0] << " <threads_lectura> <threads_maximo>" << std::endl;
        std::cout << "    " << "<archivo1> [<archivo2>...]" << std::endl;
        std::cout << std::endl;
        std::cout << "    threads_lectura: "
            << "Cantidad de threads a usar para leer archivos." << std::endl;
        std::cout << "    threads_maximo: "
            << "Cantidad de threads a usar para computar máximo." << std::endl;
        std::cout << "    archivo1, archivo2...: "
            << "Archivos a procesar." << std::endl;
        return 1;
    }
    int cantThreadsLectura = std::stoi(argv[1]);
    int cantThreadsMaximo = std::stoi(argv[2]);

    std::vector<std::string> filePaths = {};
    for (int i = 3; i < argc; i++) {
        filePaths.push_back(argv[i]);
    }

    HashMapConcurrente hashMap{}; // = HashMapConcurrente();
    cargarMultiplesArchivos(hashMap, cantThreadsLectura, filePaths);
    auto maximo = hashMap.maximoParalelo(cantThreadsMaximo);

    std::cout << maximo.first << " " << maximo.second << std::endl;

    return 0;
}
