#ifndef HMC_HPP
#define HMC_HPP

#include <mutex>
#include <array>
#include <atomic>
#include <string>
#include <vector>
#include <semaphore.h>

#include "ListaAtomica.hpp"

typedef std::pair<std::string, unsigned int> hashMapPair;

class HashMapConcurrente {
 public:
    static constexpr int cantLetras = 26;

    HashMapConcurrente();
    ~HashMapConcurrente();

    void incrementar(std::string clave);
    std::vector<std::string> claves();
    unsigned int valor(std::string clave);

    hashMapPair maximo();
    hashMapPair maximoParalelo(unsigned int cantThreads);
    static void maximoPorFila(ListaAtomica<hashMapPair>& lista, std::vector<hashMapPair>& maximos, unsigned int currentThread, std::mutex& paralelos, unsigned int& currentIndex);

 private:
    ListaAtomica<hashMapPair> *tabla[HashMapConcurrente::cantLetras];

    static void saludo(unsigned int numero);
    static unsigned int hashIndex(std::string clave);
    std::mutex mutexIncrementar;

    sem_t incrementarYMaximo;
};

#endif  /* HMC_HPP */

