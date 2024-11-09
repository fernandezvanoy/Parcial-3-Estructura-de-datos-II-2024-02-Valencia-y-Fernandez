#include <iostream>        // Para entrada y salida estándar
#include <string>          // Para manejo de cadenas de texto
#include "ArbolBMas.h"    // Encabezado del árbol B+, para operaciones SQL simuladas

int main() {

    vector<string> columnas = {"Nombre", "Edad"};
    ArbolBMas arbol(5, columnas);
    
    arbol.insertar("usuarios", {"nombre", "edad"}, {"Alice", "30"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Bob", "25"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Charlie", "35"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"David", "20"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);


    arbol.insertar("usuarios", {"nombre", "edad"}, {"Eve", "40"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);
    
    arbol.insertar("usuarios", {"nombre", "edad"}, {"Frank", "22"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Grace", "28"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Hank", "31"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);


    arbol.insertar("usuarios", {"nombre", "edad"}, {"Isaac", "31"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Juan", "27"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Kyle", "27"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Luis", "27"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Matt", "27"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);
    
    

    vector<string> clave = {"Bob" , "35"}; //clave a eliminar

    arbol.eliminar(clave);
    
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Bob", "25"});
    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    vector<string> claveAntigua = {"Bob" , "25"};
    vector<string> claveNueva = {"Bobby" , "35"};

    arbol.actualizar(claveAntigua, claveNueva);

    cout << "Estado del árbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    vector<string> camposBuscados = {"Nombre", "Edad"};

    arbol.seleccionar(camposBuscados);

    return 0;
}
