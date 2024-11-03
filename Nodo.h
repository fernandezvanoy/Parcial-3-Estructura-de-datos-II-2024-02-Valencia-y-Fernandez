#ifndef NODO_H
#define NODO_H

#include <vector>
#include <memory> // Para std::shared_ptr

class NodoBMas {
private:
    std::vector<int> claves;                         // Claves almacenadas en el nodo
    std::vector<std::shared_ptr<NodoBMas>> hijos;    // Punteros a nodos hijos
    std::shared_ptr<NodoBMas> siguiente;             // Puntero al siguiente nodo (para nodos hoja)
    int maxClaves;                                   // Máximo número de claves permitido en el nodo

public:
    // Constructor que inicializa el nodo con el número máximo de claves permitido
    NodoBMas(int maxClaves);

    // Verifica si el nodo es una hoja (no tiene hijos)
    bool esHoja() const;

    // Verifica si el nodo está lleno (ha alcanzado el número máximo de claves)
    bool estaLleno() const;

    // Agrega una clave al nodo (método auxiliar)
    void agregarClave(int clave);

    // Obtiene las claves almacenadas en el nodo
    const std::vector<int>& obtenerClaves() const;

    // Configura el puntero al siguiente nodo
    void setSiguiente(const std::shared_ptr<NodoBMas>& nodo);

    // Obtiene el puntero al siguiente nodo
    std::shared_ptr<NodoBMas> getSiguiente() const;
};

#endif
    