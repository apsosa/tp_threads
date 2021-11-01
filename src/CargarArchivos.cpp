#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
//#include <pthread.h>
#include <thread>
#include <iostream>
#include "CargarArchivos.hpp"
std::mutex mutexCargaParalela;
int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        // Completar (Ejercicio 4)
        hashMap.incrementar(palabraActual);
        cant++;
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}

void cargaDeArchivosPorThreads(HashMapConcurrente &hashMap,std::vector<std::string> &filePaths,std::pair<int,int>& intervalo){
    for (int i = intervalo.first; i < intervalo.second; i++) {
        cargarArchivo(hashMap,filePaths[i]);
    }
}

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {
    // Completar (Ejercicio 4)

    unsigned int cantDeArchivos = filePaths.size();
    if (cantThreads > cantDeArchivos) 
        cantThreads = cantDeArchivos;

    std::vector<std::thread> threads(cantThreads);
    std::vector<std::pair<int,int>> intervalos(cantThreads); // [inicio,fin)
    unsigned int cantDeArchivosPorThreads = cantDeArchivos / cantThreads;
    int inicio = 0;
    int fin = cantDeArchivosPorThreads;

    for (unsigned int i = 0; i < cantThreads; i++) {
        if (i == cantThreads- 1)
            fin = cantDeArchivos;

        intervalos[i].first = inicio;
        intervalos[i].second = fin;
        inicio += cantDeArchivosPorThreads;
        fin += cantDeArchivosPorThreads;
    }

    for (unsigned int i = 0; i < cantThreads; i++) {
        auto &t = threads[i];
        t = std::thread(cargaDeArchivosPorThreads, std::ref(hashMap), std::ref(filePaths),std::ref(intervalos[i]));
    }
    for (auto &t : threads) {
        t.join();
    }
}

#endif
