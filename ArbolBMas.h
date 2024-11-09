#ifndef ARBOL_BMAS_H
#define ARBOL_BMAS_H

#include <string>    // Biblioteca para manejar cadenas de texto (std::string)
#include <vector>    // Biblioteca para manejar listas de elementos (std::vector)
#include <map>       // Biblioteca para manejar pares clave-valor (std::map)
#include <iostream>  // Biblioteca para operaciones de entrada y salida (std::cout)
#include <algorithm>
#include "NodoBMas.h"

// Clase ArbolBPlus simula un árbol B+ con métodos básicos para las operaciones de SQL.
class ArbolBMas {
public:
    ArbolBMas(int orden);

    NodoBMas *raiz;
    int orden;
    int gradoMinimo;
    int gradoMaximo;
    // Método para simular la inserción en el árbol B+
    // Recibe el nombre de la tabla, una lista de columnas y una lista de valores
    void insertar(const std::string &tabla, const std::vector<std::string> &columnas, const std::vector<std::string> &valores);

    // Método para simular la selección de datos en el árbol B+
    // Recibe el nombre de la tabla y una lista de columnas
    void select(const std::vector<std::string> &campos);

    // Método para simular la actualización de datos en el árbol B+
    // Recibe el nombre de la tabla, un mapa de asignaciones (columna=valor), y una condición
    void update(const string& nombre, const string& nuevaEdad, const string& campoCambio);

    // Método para simular la eliminación de datos en el árbol B+
    // Recibe el nombre de la tabla y una condición para eliminar filas que la cumplan
    void eliminar(const vector<string> &clave);

    void imprimirArbol(NodoBMas *nodo, int nivel = 0);

private: 

    void eliminarDeNodo(NodoBMas *nodo, const vector<string> &clave);
    void eliminarClaveNodoInterno(NodoBMas *nodo, const vector<string> &clave, int indice);
    vector<string> obtenerPredecesor(NodoBMas *nodo);
    vector<string> obtenerSucesor(NodoBMas *nodo);
    void manejarFusionRedistribucion(NodoBMas *nodo, int indice);
    void fusionarNodos(NodoBMas *padre, int indice);
    void redistribuirIzquierda(NodoBMas *padre, int indice);
    void redistribuirDerecha(NodoBMas *padre, int indice);

    void insertarAux(NodoBMas *nodo, const vector<string> &clave);
    void dividir(NodoBMas *padre, int indice);

    void recorrerSelect(NodoBMas *nodo, const std::vector<std::string> &campos);
    void mostrarRegistro(const vector<string> registro, const std::vector<std::string> &campos);
    
    void casoBaseUpdate();
    void comprobarUpdate(bool actualizado);
    bool updateEnNodo(NodoBMas* nodo, const std::string& valorABuscar, const std::string& nuevoValor, const std::string& criterio);

};

#endif