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
    NodoBMas *raiz;
    int orden;
    int gradoMinimo;
    int gradoMaximo;
    vector<string> columnas;
    string nombreArbol;

    //Constructor clase ArbolBMas
    ArbolBMas(int orden, string nombreArbol, vector<string> columnas);

    // Método para simular la inserción en el árbol B+ y sus funciones auxiliares
    void insertar(const std::string &tabla, const std::vector<std::string> &columnas, const std::vector<std::string> &valores);
    void insertarAux(NodoBMas *nodo, const vector<string> &clave);
    void dividir(NodoBMas *padre, int indice);

    // Método para simular la selección de datos en el árbol B+ y sus funciones auxiliares 
    void seleccionar(const vector<string>& camposBuscados);
    void seleccionarAux(NodoBMas* nodo, const vector<int>& camposBuscados);

    // Método para simular la actualización de datos en el árbol B+ y sus funciones auxiliares
    void actualizar(const vector<string>& claveBuscada, const vector<string>& nuevaClave);
    void actualizarAux(NodoBMas* nodo, const vector<string>& claveBuscada, const vector<string>& nuevaClave);

    // Método para simular la eliminación de datos en el árbol B+ y sus funciones auxiliares
    void eliminar(const vector<string> &clave);
    void eliminarDeNodo(NodoBMas *nodo, const vector<string> &clave);
    void eliminarClaveNodoInterno(NodoBMas *nodo, const vector<string> &clave, int indice);
    vector<string> obtenerPredecesor(NodoBMas *nodo);
    vector<string> obtenerSucesor(NodoBMas *nodo);
    void manejarFusionRedistribucion(NodoBMas *nodo, int indice);
    void fusionarNodos(NodoBMas *padre, int indice);
    void redistribuirIzquierda(NodoBMas *padre, int indice);
    void redistribuirDerecha(NodoBMas *padre, int indice);

    //Metodo para imprimir el arbol
    void imprimirArbol(NodoBMas *nodo, int nivel = 0);



};

#endif