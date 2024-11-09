#include <iostream>        // Para entrada y salida estándar
#include <string>          // Para manejo de cadenas de texto
#include "ArbolBMas.h"    // Encabezado del árbol B+, para operaciones SQL simuladas

int main()
{
    ArbolBMas arbol(4);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Alice", "30"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Bob", "25"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Charlie", "35"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"David", "20"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Eve", "40"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Frank", "22"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Grace", "28"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Hank", "31"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Isaac", "31"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Juan", "27"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Kyle", "27"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Luis", "27"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.insertar("usuarios", {"nombre", "edad"}, {"Matt", "27"});
    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    vector<string> clave = {"Charlie", "35"}; // clave a eliminar

    arbol.eliminar(clave);

    cout << "Estado del arbol B+: " << endl;
    arbol.imprimirArbol(arbol.raiz);

    arbol.select({"nombre", "edad"});

    
    arbol.update("Bob", "10", "nombre");
    arbol.update("20", "N/A", "edad");

    arbol.select({"nombre", "edad"});
    arbol.eliminar({"Matt", "27"});
    

    return 0;
}
