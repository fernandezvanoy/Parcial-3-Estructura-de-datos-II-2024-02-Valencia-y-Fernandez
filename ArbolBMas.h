#ifndef ARBOL_BMAS_H
#define ARBOL_BMAS_H

#include <string>    // Biblioteca para manejar cadenas de texto (std::string)
#include <vector>    // Biblioteca para manejar listas de elementos (std::vector)
#include <map>       // Biblioteca para manejar pares clave-valor (std::map)
#include <iostream>  // Biblioteca para operaciones de entrada y salida (std::cout)

// Clase ArbolBPlus simula un árbol B+ con métodos básicos para las operaciones de SQL.
class ArbolBMas {
public:
    // Método para simular la inserción en el árbol B+
    // Recibe el nombre de la tabla, una lista de columnas y una lista de valores
    void insertar(const std::string& tabla, const std::vector<std::string>& columnas, const std::vector<std::string>& valores);

    // Método para simular la selección de datos en el árbol B+
    // Recibe el nombre de la tabla y una lista de columnas
    void seleccionar(const std::string& tabla, const std::vector<std::string>& columnas);

    // Método para simular la actualización de datos en el árbol B+
    // Recibe el nombre de la tabla, un mapa de asignaciones (columna=valor), y una condición
    void actualizar(const std::string& tabla, const std::map<std::string, std::string>& asignaciones, const std::string& condicion);

    // Método para simular la eliminación de datos en el árbol B+
    // Recibe el nombre de la tabla y una condición para eliminar filas que la cumplan
    void eliminar(const std::string& tabla, const std::string& condicion);
};

#endif