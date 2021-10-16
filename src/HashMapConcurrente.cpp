#ifndef CHM_CPP
#define CHM_CPP

#include <thread>
// alternativamente #include <pthread.h>
#include <iostream>
#include <fstream>

#include "HashMapConcurrente.hpp"

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    // Completar (Ejercicio 2)
    /*aplicar mutex al incrementar el valor*/
    mutexIncrementar.lock();
    int index = this->hashIndex(clave); 
    if (index >= 0 && index <= 26){
        bool find = false;
        for (auto &p : *tabla[index]) {
            if (clave.compare(p.first) == 0) {
               p.second++;
               find = true;
               break;
            }
        }
        if (!find)
            tabla[index]->insertar(std::make_pair(clave,1));
    }
    mutexIncrementar.unlock();
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
    int index = this->hashIndex(clave);
    unsigned int valor = 0; 
    if (index >= 0 && index <= 26){
        for (auto &p : *tabla[index]) {
            if (clave.compare(p.first) == 0) {
                valor = p.second;
            }
        }
    }
    return valor;
}

hashMapPair HashMapConcurrente::maximo() {
    /*agregar un semaforo compartido con incrementar*/
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

    return *max;
}



hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {
    // Completar (Ejercicio 3)
}

#endif
