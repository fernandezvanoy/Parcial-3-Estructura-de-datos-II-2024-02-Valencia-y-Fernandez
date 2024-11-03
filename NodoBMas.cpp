#include "NodoBMas.h"

NodoBMas::NodoBMas(int maxClaves) : siguiente(nullptr), maxClaves(maxClaves) {}

// Destructor para liberar la memoria de los hijos
NodoBMas::~NodoBMas() {
    for (NodoBMas* hijo : hijos) {
        delete hijo;
    }
}

// Devuelve true si el nodo es una hoja, es decir, no tiene hijos
bool NodoBMas::esHoja() const {
    return hijos.empty();
}

// Devuelve true si el nodo tiene el número máximo de claves permitido
bool NodoBMas::estaLleno() const {
    return claves.size() >= maxClaves;
}


// Devuelve las claves almacenadas en el nodo
const vector<vector<string>>& NodoBMas::obtenerClaves() const {
    return claves;
}

// Configura el puntero al siguiente nodo
void NodoBMas::setSiguiente(NodoBMas* nodo) {
    siguiente = nodo;
}

// Obtiene el puntero al siguiente nodo
NodoBMas* NodoBMas::getSiguiente() const {
    return siguiente;
}