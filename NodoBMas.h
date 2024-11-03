#ifndef NODO_BMAS_H
#define NODO_BMAS_H

#include <vector>
#include <algorithm> // Para std::sort
#include <string>

using namespace std;

class NodoBMas {
    
public:
    vector<vector<string>> claves;               // Claves almacenadas en el nodo
    vector<NodoBMas*> hijos;          // Punteros a nodos hijos
    NodoBMas* siguiente;                   // Puntero al siguiente nodo (para nodos hoja)
    int maxClaves;                         // Máximo número de claves permitido en el nodo

    // Constructor que inicializa el nodo con el número máximo de claves permitido
    NodoBMas(int maxClaves);

    // Destructor para liberar la memoria de los nodos hijos
    ~NodoBMas();

    // Verifica si el nodo es una hoja (no tiene hijos)
    bool esHoja() const;

    // Verifica si el nodo está lleno (ha alcanzado el número máximo de claves)
    bool estaLleno() const;

    // Agrega una clave al nodo (método auxiliar)
    void agregarClave(vector<vector<string>> clave);

    // Obtiene las claves almacenadas en el nodo
    const vector<vector<string>>& obtenerClaves() const;

    // Configura el puntero al siguiente nodo
    void setSiguiente(NodoBMas* nodo);

    // Obtiene el puntero al siguiente nodo
    NodoBMas* getSiguiente() const;
};

#endif 
