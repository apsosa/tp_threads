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
    return 0;
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

void HashMapConcurrente::maximoFila(hashMapPair &max,ListaAtomica<hashMapPair>& tabla,std::mutex &mutexMaximoParalelo){
    mutexMaximoParalelo.lock();
    hashMapPair min = std::make_pair("", 0);

    for (unsigned int i = 0; i < tabla.longitud(); i++) {
        std::cout<< tabla[i].first<< " " << tabla[i].second<< std::endl;
        if (tabla[i].second > min.second) {
            max.first = tabla[i].first;
            max.second = tabla[i].second;
            min.second = tabla[i].second;
        }
    }
    std::cout<< "calculo maximo fila" << std::endl;
    mutexMaximoParalelo.unlock();    
}


void HashMapConcurrente::maximoFila2(std::vector<hashMapPair> &maximos,ListaAtomica<hashMapPair> *tabla[],std::pair<int,int>& intervalo,std::mutex &mutexMaximoParalelo){
    mutexMaximoParalelo.lock();

    //std::cout<< "calculo maximo fila"<< std::endl;
    //std::cout<<"Intervalo: "<< intervalo.first<< ","<< intervalo.second<< std::endl;
    for (int i = intervalo.first; i < intervalo.second; i++) {
        for (auto &p : *tabla[i]) {
            if (p.second > maximos[i].second) {
                maximos[i].first = p.first;
                maximos[i].second = p.second;
            }
        }
    }
    mutexMaximoParalelo.unlock();    
}


/*
t1 => maxifila => longitud => 0
t2 => maxifila => longitud => 5

*/
hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {

    // Completar (Ejercicio 3)
    std::vector<hashMapPair> maximos(cantLetras);
    std::vector<std::thread> threads(cant_threads);
    std::vector<std::pair<int,int>> intervalos(cant_threads); // [inicio,fin)

    for (unsigned int i = 1; i < maximos.size(); i++) {
        maximos[i]= std::make_pair("", 0);
    }

    int cantListasAProcesar = cant_threads >= cantLetras ? cantLetras : cantLetras/cant_threads;
    int inicio= 0;
    int fin = cantListasAProcesar;

    for (unsigned int i = 0; i < cant_threads; i++) {
        intervalos[i].first = inicio;
        intervalos[i].second = fin;
        inicio = cantListasAProcesar;
        fin = cantListasAProcesar + cantListasAProcesar;
    }

    unsigned int diferecia = 26 - cantListasAProcesar * cant_threads;

    for (unsigned int i = 0; i < diferecia; i++) {
        intervalos[cant_threads-1].second += 1;   
    }

    for (unsigned int i = 0; i < cant_threads; i++) {
        auto &t = threads[i];
        t = std::thread(maximoFila2, std::ref(maximos), std::ref(this->tabla),std::ref(intervalos[i]),std::ref(mutexMaximoParalelo));
    }   

    for (auto &t : threads) {
        t.join();
    }

    mutexMaximoParalelo.lock();
    hashMapPair max = maximos[0];

    for (unsigned int i = 1; i < maximos.size(); i++) {
        if (maximos[i].second > max.second) {
            max.first = maximos[i].first;
            max.second = maximos[i].second;
        }
    }

    mutexMaximoParalelo.unlock();
    return max;
}

#endif

