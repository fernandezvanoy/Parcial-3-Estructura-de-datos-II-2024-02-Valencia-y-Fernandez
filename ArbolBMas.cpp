#include "ArbolBMas.h"

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