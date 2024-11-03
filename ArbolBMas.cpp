#include "ArbolBMas.h"
#include "NodoBMas.h"
#include <string>

//AGREGAR: NODOS, RAIZ, AUTOBALANCEO
NodoBMas* raiz;
vector<string> columnas;
int orden;


void ArbolBMas::insertarAux(NodoBMas* nodo, const std::vector<std::string>& clave) {
        if (nodo->esHoja()) {
            // Insertar en un nodo hoja
            nodo->claves.push_back(clave);
            // Ordenar el vector de claves basado en el primer elemento del vector<string>
            std::sort(nodo->claves.begin(), nodo->claves.end(),
                      [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                          return a[0] < b[0];
                      });
        } else {
            // Encontrar el hijo adecuado
            int i = nodo->claves.size() - 1;
            while(i >= 0 && clave[0] < nodo->claves[i][0]) {
                i--;
            }
            i++;
            // Si el hijo está lleno, dividirlo
            if(nodo->hijos[i]->claves.size() == orden - 1) {
                dividir(nodo, i);
                // Ajustar el índice si la clave es mayor que la clave promovida
                if (clave[0] > nodo->claves[i][0]) {
                    i++;
                }
            }
            insertarAux(nodo->hijos[i], clave);
        }
    }

    // Método para dividir un nodo lleno
    void ArbolBMas::dividir(NodoBMas* padre, int indice) {
        NodoBMas* lleno = padre->hijos[indice];
        NodoBMas* nuevoHijo = new NodoBMas(lleno->esHoja());
        int midIndex = orden / 2;

        // Promover la clave del medio al padre
        padre->claves.insert(padre->claves.begin() + indice, lleno->claves[midIndex]);
        padre->hijos.insert(padre->hijos.begin() + indice + 1, nuevoHijo);

        // Asignar claves al nuevo nodo
        nuevoHijo->claves.assign(lleno->claves.begin() + midIndex + 1, lleno->claves.end());
        lleno->claves.resize(midIndex);

        // Asignar hijos si no es un nodo hoja
        if (!lleno->esHoja()) {
            nuevoHijo->hijos.assign(lleno->hijos.begin() + midIndex + 1, lleno->hijos.end());
            lleno->hijos.resize(midIndex + 1);
        }
    }

// Implementación del método insertar
// Muestra en la consola el comando simulado de inserción con columnas y valores dados
void ArbolBMas::insertar(const std::string& tabla, const std::vector<std::string>& columnas, const std::vector<std::string>& valores) {
    std::cout << "Ejecutando: INSERT INTO " << tabla << " (";
    // Itera y muestra cada columna, separadas por comas
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }
    std::cout << ") VALUES (";
    // Itera y muestra cada valor, separadas por comas
    for (size_t i = 0; i < valores.size(); ++i) {
        std::cout << valores[i];
        if (i < valores.size() - 1) std::cout << ", ";
    }
    std::cout << ")\n";

    if (raiz->claves.size() == orden - 1) {
            NodoBMas* nuevaRaiz = new NodoBMas(false);
            nuevaRaiz->hijos.push_back(raiz);
            dividir(nuevaRaiz, 0);
            raiz = nuevaRaiz;
        }

        insertarAux(raiz, valores);

}

// Implementación del método seleccionar
// Muestra en la consola el comando simulado de selección con columnas especificadas
void ArbolBMas::seleccionar(const std::string& tabla, const std::vector<std::string>& columnas) {
    std::cout << "Ejecutando: SELECT ";
    // Itera y muestra cada columna seleccionada
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }
    std::cout << " FROM " << tabla << std::endl;
}

// Implementación del método actualizar
// Muestra en la consola el comando simulado de actualización con asignaciones y condición
void ArbolBMas::actualizar(const std::string& tabla, const std::map<std::string, std::string>& asignaciones, const std::string& condicion) {
    std::cout << "Ejecutando: UPDATE " << tabla << " SET ";
    size_t i = 0;
    // Itera y muestra cada asignación en el formato columna=valor
    for (const auto& asignacion : asignaciones) {
        std::cout << asignacion.first << " = " << asignacion.second;
        if (i < asignaciones.size() - 1) std::cout << ", ";
        ++i;
    }
    std::cout << " WHERE " << condicion << std::endl;
}

// Implementación del método eliminar
// Muestra en la consola el comando simulado de eliminación con la condición dada
void ArbolBMas::eliminar(const std::string& tabla, const std::string& condicion) {
    std::cout << "Ejecutando: DELETE FROM " << tabla << " WHERE " << condicion << std::endl;
}
