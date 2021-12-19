#include <iostream>
#include "HashMapConcurrente.hpp"
#include "CargarArchivos.hpp"
#include "ListaAtomica.hpp"
#include <mutex>       // std::mutex


std::mutex mutex_insert;
int main(int argc, char **argv) {

    if (argc < 5) {
        std::cout << "Error: faltan argumentos." << std::endl;
        std::cout << std::endl;
        std::cout << "Modo de uso: " << argv[0] << " <threads_lectura> <threads_maximo>" << std::endl;
        std::cout << "    " << "<archivo1> [<archivo2>...]" << std::endl;
        std::cout << std::endl;
        std::cout << "    threads_lectura: "
            << "Cantidad de threads a usar para leer archivos." << std::endl;
        std::cout << "    threads_maximo: "
            << "Cantidad de threads a usar para computar máximo." << std::endl;
        std::cout << "utilización de maximo paralelo o no" 
            << "sin concurrencia = 0" 
            << "con concurrencia = 1"<< std::endl;
        std::cout << "    archivo1, archivo2...: "
            << "Archivos a procesar." << std::endl;
        return 1;
    }


    int cantThreadsLectura = std::stoi(argv[1]);
    int cantThreadsMaximo = std::stoi(argv[2]);
    int concurrente = std::stoi(argv[3]);

    if (concurrente == 0) {
        /*
            ESTA OPCION ES PARA EJECUTAR MAXIMO SIN CONCURRENCIA
        */

        std::vector<std::string> filePaths = {};
        for (int i = 4; i < argc; i++) {
            filePaths.push_back(argv[i]);
        }

        HashMapConcurrente hashMap{}; // = HashMapConcurrente();
        cargarMultiplesArchivos(hashMap, cantThreadsLectura, filePaths);

        /*********************************************************/
        auto start = std::chrono::steady_clock::now();
        auto maximo = hashMap.maximo();
        auto end = std::chrono::steady_clock::now();
        /*********************************************************/

        double total_time = std::chrono::duration<double, std::milli>(end - start).count();
        std::clog << total_time << std::endl;
        std::cout << maximo.first << " " << maximo.second << std::endl;

    } else if (concurrente == 1) {
        /*
            ESTA OPCION ES PARA EJECUTAR MAXIMO CON CONCURRENCIA
        */

        std::vector<std::string> filePaths = {};
        for (int i = 4; i < argc; i++) {
            filePaths.push_back(argv[i]);
        }

        HashMapConcurrente hashMap{}; // = HashMapConcurrente();
        cargarMultiplesArchivos(hashMap, cantThreadsLectura, filePaths);

        /*********************************************************/
        auto start = std::chrono::steady_clock::now();
        auto maximo = hashMap.maximoParalelo(cantThreadsMaximo);
        auto end = std::chrono::steady_clock::now();
        /*********************************************************/

        double total_time = std::chrono::duration<double, std::milli>(end - start).count();
        std::clog << total_time << std::endl;
        std::cout << maximo.first << " " << maximo.second << std::endl;
 
    }

    ///*
    //std::vector<std::string> filePaths = {};
    //for (int i = 3; i < argc; i++) {
    //    filePaths.push_back(argv[i]);
    //}

    //HashMapConcurrente hashMap{}; // = HashMapConcurrente();
    //cargarMultiplesArchivos(hashMap, cantThreadsLectura, filePaths);
    //auto maximo = hashMap.maximoParalelo(cantThreadsMaximo);

    //std::cout << maximo.first << " " << maximo.second << std::endl;

    //if (threads_lectura == 1 && concurrente == 0) {
    //    /*  
    //        Utiliza el método máximo sin concurrencia y con un único thread de lectura
    //    */
    //    HashMapConcurrente hashMap{};
    //    for (int i = 3; i < argc; i++) { 
    //        // CARGAMOS EL RESTO DE ARCHIVOS
    //        cargarArchivo(hashMap,argv[i]);
    //    }

    //    auto maximo = hashMap.maximo();
    //    
    
    //    double total_time = std::chrono::duration<double, std::milli>(end - start).count();
    //    std::clog << total_time << std::endl;
    //    std::cout << maximo.first << " " << maximo.second << std::endl;
    //} else {
    //    /*
    //        Utiliza el método máximo con concurrencia
    //    */
    //    HashMapConcurrente hashMap{}; // = HashMapConcurrente();


    //    std::vector<std::string> filePaths = {};
    //    for (int i = 3; i < argc; i++) {
    //        filePaths.push_back(argv[i]);
    //    }

    //    cargarMultiplesArchivos(hashMap, threads_lectura, filePaths);
    //    auto start = std::chrono::steady_clock::now();
    //    auto maximo = hashMap.maximoParalelo(threads_maximo);
    //    auto end = std::chrono::steady_clock::now();
    //}

    return 0;
}
