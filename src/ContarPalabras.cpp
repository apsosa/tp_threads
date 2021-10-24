#include <iostream>
#include "HashMapConcurrente.hpp"
#include "CargarArchivos.hpp"
#include "ListaAtomica.hpp"
#include <mutex>       // std::mutex

std::mutex mutex_insert;
int main(int argc, char **argv) {

    HashMapConcurrente hM;

    hM.incrementar("aaa");
    hM.incrementar("aaa");
    hM.incrementar("aaa");
    hM.incrementar("aaa");
    hM.incrementar("aaa");
    hM.incrementar("be");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("estegosaurio");
    hM.incrementar("estegosaurio");
    hM.incrementar("bbb");

    hashMapPair actual = hM.maximoParalelo(3);

    std::cout << "actual maximo: " << actual.second << std::endl;
    /*
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
    */

    return 0;
}
