#ifndef CHM_CPP
#define CHM_CPP

#include <thread>
// alternativamente #include <pthread.h>
#include <mutex>
#include <iostream>
#include <fstream>
#include <mutex>

#include "HashMapConcurrente.hpp"

std::mutex incrementarYAgregar;

HashMapConcurrente::HashMapConcurrente() {
    sem_init(&incrementarYMaximo, 0, 1);

    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    // Completar (Ejercicio 2)
    unsigned int index = hashIndex(clave);

    if (index >= cantLetras)
        return;

    sem_wait(&incrementarYMaximo);
    mutexIncrementar.lock();

    bool existeClave = false;

    for (auto &p : *tabla[index]) {
        if (!p.first.compare(clave)) {
            p.second += 1;
            existeClave = true;
            break;
        } 
    }

    if (!existeClave) {
        tabla[index]->insertar(std::make_pair(clave, 1));
    }

    mutexIncrementar.unlock();
    sem_post(&incrementarYMaximo);
}

std::vector<std::string> HashMapConcurrente::claves() {
    // Completar (Ejercicio 2)
    std::vector<std::string> claves;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (auto &p : *tabla[index]) {
            claves.push_back(p.first);
        }
    }

    return claves;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    // Completar (Ejercicio 2)
    unsigned int index = hashIndex(clave);

    for (auto &p : *tabla[index]) {
        if (!p.first.compare(clave))
            return p.second;
    }
}

hashMapPair HashMapConcurrente::maximo() {
    sem_wait(&incrementarYMaximo);
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (auto &p : *tabla[index]) {
            if (p.second > max->second) {
                max->first = p.first;
                max->second = p.second;
            }
        }
    }
    sem_post(&incrementarYMaximo);

    return *max;
}

void HashMapConcurrente::maximoFila(hashMapPair* max, int index){
    for (auto &p : *tabla[index]) {
        if (p.second > max->second) {
            max->first = p.first;
            max->second = p.second;
        }
    }
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {

    // Completar (Ejercicio 3)
    std::vector<hashMapPair> maximos(cantLetras);
    std::vector<std::thread> threads(cant_threads);
    if (cant_threads >= cantLetras){
        cant_threads = cantLetras;
        while (cant_threads != 0)
        {
            auto &t = threads[cant_threads-1];
            t = std::thread(maximoFila, maximos[cant_threads-1], cant_threads-1);
            cant_threads--;
        }
    }else{
        /*
        La cantidad de thread es menor a la cantidad de filas 
        0 => maximo en la fila 0 
        1 => maximo en la fila 1 
        ....

        10 => maximo en la fila 10

        0 => maximo en la fila 11 
        */ 
        int indexThreads = 0; // 10
        int filas = cantLetras-1;
        while (filas != 0)
        {
            auto &t = threads[indexThreads];
            t = std::thread(HashMapConcurrente::maximoFila, maximos[filas], cant_threads-1);
            filas--;
            indexThreads = (indexThreads + 1) % cant_threads;
        }
    }
    for (auto &t : threads) { 
        t.join();
    }
    hashMapPair max = maximos[0];
    for (int i = 1; i < maximos.size(); i++)
    {
        hashMapPair p = maximos[i];
        if (p.second > max.second) {
            max.first = p.first;
            max.second = p.second;
        }
    }
    return max;
}

#endif

