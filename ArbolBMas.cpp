#include "ArbolBMas.h"


ArbolBMas::ArbolBMas(int orden) : orden(orden), gradoMinimo(orden / 2 - 1), gradoMaximo(orden - 1), raiz(new NodoBMas(true)) {}


void ArbolBMas::eliminar(const vector<string> &clave)
{
    eliminarDeNodo(raiz, clave);
    // Si la raíz queda sin claves, ajustamos la raíz
    if (!raiz->esHoja && raiz->claves.empty())
    {
        NodoBMas *viejaRaiz = raiz;
        raiz = raiz->hijos[0];
        delete viejaRaiz;
    }
}

// Muestra en la consola el comando simulado de inserción con columnas y valores dados
void ArbolBMas::insertar(const std::string &tabla, const std::vector<std::string> &columnas, const std::vector<std::string> &valores)
{
    std::cout << "Ejecutando: INSERT INTO " << tabla << " (";
    // Itera y muestra cada columna, separadas por comas
    for (size_t i = 0; i < columnas.size(); ++i)
    {
        std::cout << columnas[i];
        if (i < columnas.size() - 1)
            std::cout << ", ";
    }
    std::cout << ") VALUES (";
    // Itera y muestra cada valor, separadas por comas
    for (size_t i = 0; i < valores.size(); ++i)
    {
        std::cout << valores[i];
        if (i < valores.size() - 1)
            std::cout << ", ";
    }
    std::cout << ")\n";

    if (raiz->claves.size() == orden - 1)
    {
        NodoBMas *nuevaRaiz = new NodoBMas(false);
        nuevaRaiz->hijos.push_back(raiz);
        dividir(nuevaRaiz, 0);
        raiz = nuevaRaiz;
    }

    insertarAux(raiz, valores);
}

void ArbolBMas::imprimirArbol(NodoBMas *nodo, int nivel)
{
    if (nodo == nullptr)
        return;
    for (int i = 0; i < nivel; i++)
        cout << "  ";
    for (const auto &clave : nodo->claves)
    {
        cout << "[" << clave[0] << "] ";
    }
    cout << endl;
    if (!nodo->esHoja)
    {
        for (auto hijo : nodo->hijos)
        {
            imprimirArbol(hijo, nivel + 1);
        }
    }
}

void ArbolBMas::select(const std::vector<std::string> &campos)
{
    if (raiz)
    {
        // SQL> SELECT (nombre, edad) FROM clientes
        cout << "SQL> SELECT (";
        for (string columna : campos)
        {
            cout << columna << ",";
        }
        cout << ") FROM clientes" << endl;
        recorrerSelect(raiz, campos);
    }
    else
    {
        std::cout << "El árbol está vacío." << std::endl;
    }
}

// Método para actualizar un registro que cumpla con el criterio
void ArbolBMas::update(const string &nombre, const string &nuevaEdad, const string &condicion)
{
    if(condicion == "nombre"){
        //uPDATE clientes SET edad=31 WHERE nombre="Juan"
        cout << "UPDATE clientes SET edad=" << nuevaEdad << " WHERE nombre=" << nombre << endl;
    } else{
        cout << "UPDATE clientes SET nombre=" << nuevaEdad << " WHERE edad=" << nombre << endl;
    }
    casoBaseUpdate();
    bool actualizado = updateEnNodo(raiz, nombre, nuevaEdad, condicion);
    comprobarUpdate(actualizado);
}

// void update(int edad, string nuevoNombre)
// {
//     casoBaseUpdate();
//     bool actualizado = updateEnNodo(raiz, edad, nuevoNombre);
//     comprobarUpdate(actualizado);
// }

void ArbolBMas::eliminarDeNodo(NodoBMas *nodo, const vector<string> &clave)
{
    // Buscamos la posición de la clave usando el primer elemento de cada vector<string>
    int indice = -1; // Inicializa el índice con -1 para indicar "no encontrado"
    for (int i = 0; i < nodo->claves.size(); ++i)
    {
        if (nodo->claves[i][0] >= clave[0])
        {
            indice = i;
            break; // Sale del bucle en cuanto encuentra la posición
        }
    }
    if (indice == -1)
    {
        indice = nodo->claves.size(); // Si no se encontró, se inserta al final
    }

    if (nodo->esHoja)
    {
        // Caso 1: Nodo hoja
        if (indice < nodo->claves.size() && nodo->claves[indice][0] == clave[0])
        {
            nodo->claves.erase(nodo->claves.begin() + indice);
        }
    }
    else
    {
        // Caso 2: Nodo interno
        if (indice < nodo->claves.size() && nodo->claves[indice][0] == clave[0])
        {
            // Clave encontrada en nodo interno
            eliminarClaveNodoInterno(nodo, clave, indice);
        }
        else
        {
            // No se encontró en el nodo interno, ir al hijo adecuado
            bool necesitaFusion = nodo->hijos[indice]->claves.size() < gradoMinimo;
            eliminarDeNodo(nodo->hijos[indice], clave);

            if (necesitaFusion && nodo->hijos[indice]->claves.size() < gradoMinimo)
            {
                manejarFusionRedistribucion(nodo, indice);
            }
        }
    }
}

void ArbolBMas::eliminarClaveNodoInterno(NodoBMas *nodo, const vector<string> &clave, int indice)
{
    NodoBMas *hijoPredecesor = nodo->hijos[indice];
    if (hijoPredecesor->claves.size() >= gradoMinimo)
    {
        vector<string> clavePredecesor = obtenerPredecesor(hijoPredecesor);
        nodo->claves[indice] = clavePredecesor;
        eliminarDeNodo(hijoPredecesor, clavePredecesor);
    }
    else
    {
        NodoBMas *hijoSucesor = nodo->hijos[indice + 1];
        if (hijoSucesor->claves.size() >= gradoMinimo)
        {
            vector<string> claveSucesor = obtenerSucesor(hijoSucesor);
            nodo->claves[indice] = claveSucesor;
            eliminarDeNodo(hijoSucesor, claveSucesor);
        }
        else
        {
            fusionarNodos(nodo, indice);
            eliminarDeNodo(hijoPredecesor, clave);
        }
    }
}

vector<string> ArbolBMas::obtenerPredecesor(NodoBMas *nodo)
{
    while (!nodo->esHoja)
        nodo = nodo->hijos.back();
    return nodo->claves.back();
}

vector<string> ArbolBMas::obtenerSucesor(NodoBMas *nodo)
{
    while (!nodo->esHoja)
        nodo = nodo->hijos[0];
    return nodo->claves[0];
}

void ArbolBMas::manejarFusionRedistribucion(NodoBMas *nodo, int indice)
{
    if (indice > 0 && nodo->hijos[indice - 1]->claves.size() > gradoMinimo)
    {
        // Redistribuir con el hermano izquierdo
        redistribuirIzquierda(nodo, indice);
    }
    else if (indice + 1 < nodo->hijos.size() && nodo->hijos[indice + 1]->claves.size() > gradoMinimo)
    {
        // Redistribuir con el hermano derecho
        redistribuirDerecha(nodo, indice);
    }
    else
    {
        // Fusionar con un hermano
        if (indice > 0)
        {
            fusionarNodos(nodo, indice - 1);
        }
        else
        {
            fusionarNodos(nodo, indice);
        }
    }
}

void ArbolBMas::fusionarNodos(NodoBMas *padre, int indice)
{
    NodoBMas *izquierdo = padre->hijos[indice];
    NodoBMas *derecho = padre->hijos[indice + 1];
    izquierdo->claves.push_back(padre->claves[indice]);

    izquierdo->claves.insert(izquierdo->claves.end(), derecho->claves.begin(), derecho->claves.end());
    if (!izquierdo->esHoja)
    {
        izquierdo->hijos.insert(izquierdo->hijos.end(), derecho->hijos.begin(), derecho->hijos.end());
    }

    delete derecho;
    padre->claves.erase(padre->claves.begin() + indice);
    padre->hijos.erase(padre->hijos.begin() + indice + 1);
}

void ArbolBMas::redistribuirIzquierda(NodoBMas *padre, int indice)
{
    NodoBMas *izquierdo = padre->hijos[indice - 1];
    NodoBMas *actual = padre->hijos[indice];

    actual->claves.insert(actual->claves.begin(), padre->claves[indice - 1]);
    padre->claves[indice - 1] = izquierdo->claves.back();
    izquierdo->claves.pop_back();

    if (!actual->esHoja)
    {
        actual->hijos.insert(actual->hijos.begin(), izquierdo->hijos.back());
        izquierdo->hijos.pop_back();
    }
}

void ArbolBMas::redistribuirDerecha(NodoBMas *padre, int indice)
{
    NodoBMas *derecho = padre->hijos[indice + 1];
    NodoBMas *actual = padre->hijos[indice];

    actual->claves.push_back(padre->claves[indice]);
    padre->claves[indice] = derecho->claves[0];
    derecho->claves.erase(derecho->claves.begin());

    if (!actual->esHoja)
    {
        actual->hijos.push_back(derecho->hijos[0]);
        derecho->hijos.erase(derecho->hijos.begin());
    }
}

void ArbolBMas::insertarAux(NodoBMas *nodo, const vector<string> &clave)
{
    if (nodo->esHoja)
    {
        // Insertar en un nodo hoja
        nodo->claves.push_back(clave);
        std::sort(nodo->claves.begin(), nodo->claves.end(),
                  [](const vector<string> &a, const vector<string> &b)
                  {
                      return a[0] < b[0];
                  });
    }
    else
    {
        // Encontrar el hijo adecuado
        int i = nodo->claves.size() - 1;
        while (i >= 0 && clave[0] < nodo->claves[i][0])
        {
            i--;
        }
        i++;
        // Si el hijo está lleno, dividirlo
        if (nodo->hijos[i]->claves.size() >= orden - 1)
        {
            dividir(nodo, i);
            // Ajustar el índice si la clave es mayor que la clave promovida
            if (clave[0] > nodo->claves[i][0])
            {
                i++;
            }
        }
        insertarAux(nodo->hijos[i], clave);
    }
}

void ArbolBMas::dividir(NodoBMas *padre, int indice)
{
    NodoBMas *lleno = padre->hijos[indice];
    NodoBMas *nuevoHijo = new NodoBMas(lleno->esHoja);

    int midIndex = lleno->claves.size() / 2; // Cambiar para el tamaño del nodo lleno

    // Promover la clave del medio al padre
    padre->claves.insert(padre->claves.begin() + indice, lleno->claves[midIndex]);

    // Asignar el nuevo hijo al padre
    padre->hijos.insert(padre->hijos.begin() + indice + 1, nuevoHijo);

    // Asignar claves al nuevo nodo
    nuevoHijo->claves.assign(lleno->claves.begin() + midIndex + 1, lleno->claves.end());
    lleno->claves.resize(midIndex); // Recortar claves en el nodo lleno

    // Asignar hijos si no es un nodo hoja
    if (!lleno->esHoja)
    {
        nuevoHijo->hijos.assign(lleno->hijos.begin() + midIndex + 1, lleno->hijos.end());
        lleno->hijos.resize(midIndex + 1); // Esto debe coincidir con el número de claves
    }
    else
    {
        // Mantener punteros en las hojas
        nuevoHijo->siguienteHoja = lleno->siguienteHoja;
        lleno->siguienteHoja = nuevoHijo;
    }
}

void ArbolBMas::recorrerSelect(NodoBMas *nodo, const std::vector<std::string> &campos)
{
    if (nodo->esHoja)
    {
        for (const auto &registro : nodo->claves)
        {
            mostrarRegistro(registro, campos);
        }
    }
    else
    {
        for (size_t i = 0; i < nodo->claves.size(); ++i)
        {
            if (nodo->hijos[i])
            {
                recorrerSelect(nodo->hijos[i], campos);
            }
            mostrarRegistro(nodo->claves[i], campos);
        }
        if (nodo->hijos.back())
        {
            recorrerSelect(nodo->hijos.back(), campos);
        }
    }
}

void ArbolBMas::mostrarRegistro(const vector<string> registro, const std::vector<std::string> &campos)
{
    for (const auto &campo : campos)
    {
        if (campo == "nombre")
        {
            std::cout << "Nombre: " << registro[0] << " ";
        }
        else if (campo == "edad")
        {
            std::cout << "Edad: " << registro[1] << " ";
        }
    }
    std::cout << std::endl;
}

void ArbolBMas::casoBaseUpdate()
{
    if (!raiz)
    {
        cout << "El arbol está vacio" << endl;
    }
}

void ArbolBMas::comprobarUpdate(bool actualizado)
{
    if (actualizado)
    {
        cout << "Registro actualizado correctamente" << endl;
    }
    else
    {
        cout << "No se encontro el registro con la condicion especificada" << endl;
    }
}

// bool updateEnNodo(NodoBMas* nodo, const std::string& valorABuscar, const std::string& nuevoValor, const std::string& criterio) {
//     // Determinamos si buscamos por nombre o edad
//     int indiceBusqueda = (criterio == "nombre") ? 0 : 1;  // 0 para nombre, 1 para edad
//     int indiceActualizacion = (criterio == "nombre") ? 1 : 0;  // Cambia el otro campo

//     if (nodo->esHoja) {
//         for (auto& registro : nodo->claves) {
//             // Compara el valor de acuerdo al índice de búsqueda
//             if (registro[indiceBusqueda] == valorABuscar) {
//                 cout << registro[indiceActualizacion] << "<- cosaEnVector == nuevo Valor: " << nuevoValor << endl;
//                 registro[indiceActualizacion] = nuevoValor;  // Actualiza el otro campo
//                 return true;  // Registro encontrado y actualizado
//             }
//         }
//     } else {
//         // Si no es hoja, busca en el hijo correspondiente según el índice de búsqueda
//         for (size_t i = 0; i < nodo->claves.size(); i++) {
//             if (valorABuscar < nodo->claves[i][indiceBusqueda]) {
//                 cout << "valor a buscar: " << valorABuscar << endl;
//                 return updateEnNodo(nodo->hijos[i], valorABuscar, nuevoValor, criterio);
//             }
//         }
//         // Si el valor es mayor a todas las claves del nodo actual, explora el último hijo
//         return updateEnNodo(nodo->hijos.back(), valorABuscar, nuevoValor, criterio);
//     }

//     return false;  // Registro no encontrado en este nodo
// }

bool ArbolBMas::updateEnNodo(NodoBMas *nodo, const std::string &valorABuscar, const std::string &nuevoValor, const std::string &criterio)
{
    // Determinamos si buscamos por nombre o edad
    int indiceBusqueda = (criterio == "nombre") ? 0 : 1;      // 0 para nombre, 1 para edad
    int indiceActualizacion = (criterio == "nombre") ? 1 : 0; // Cambia el otro campo

    cout << "Buscando por criterio: " << criterio << endl;
    cout << "Indice de busqueda: " << indiceBusqueda << ", Indice de actualizacion: " << indiceActualizacion << endl;

    if (nodo->esHoja)
    {
        cout << "Nodo es hoja, buscando en claves..." << endl;
        for (auto &registro : nodo->claves)
        {
            cout << "Comparando: " << registro[indiceBusqueda] << " con: " << valorABuscar << endl;
            // Compara el valor de acuerdo al índice de búsqueda
            if (registro[indiceBusqueda] == valorABuscar)
            {
                cout << "Valor encontrado: " << registro[indiceActualizacion] << "<- Actualizando a: " << nuevoValor << endl;
                registro[indiceActualizacion] = nuevoValor; // Actualiza el otro campo
                return true;                                // Registro encontrado y actualizado
            }
        }
    }
    else
    {
        cout << "Nodo no es hoja, buscando en hijos..." << endl;
        // Si no es hoja, busca en el hijo correspondiente según el índice de búsqueda
        for (size_t i = 0; i < nodo->claves.size(); i++)
        {
            if (criterio == "nombre")
            {
                cout << "Comparando con nodo " << i << ": " << nodo->claves[i][indiceBusqueda] << endl;
                if (valorABuscar < nodo->claves[i][indiceBusqueda])
                {
                    cout << "Valor a buscar: " << valorABuscar << " es menor que: " << nodo->claves[i][indiceBusqueda] << endl;
                    return updateEnNodo(nodo->hijos[i], valorABuscar, nuevoValor, criterio);
                }
            }
            if (criterio == "edad")
            {
                cout << "Comparando con nodo " << i << ": " << nodo->claves[i][indiceBusqueda] << endl;
                int edadABuscar = stoi(valorABuscar); // Convertir el valor a buscar a int
                int edadEnNodo = stoi(nodo->claves[i][indiceBusqueda]); // Convertir el valor en el nodo a int
                if (edadEnNodo == edadABuscar) // Comparación exacta para edad
                {
                    cout << "Valor a buscar: " << valorABuscar << " es igual a: " << nodo->claves[i][indiceBusqueda] << endl;
                    return updateEnNodo(nodo->hijos[i], valorABuscar, nuevoValor, criterio);
                }
                else if (edadEnNodo > edadABuscar) // Si la edad en el nodo es mayor, buscar en el hijo anterior
                {
                    cout << "Valor a buscar: " << valorABuscar << " es menor que: " << nodo->claves[i][indiceBusqueda] << endl;
                    return updateEnNodo(nodo->hijos[i], valorABuscar, nuevoValor, criterio);
                }
            }
        }
        // Si el valor es mayor a todas las claves del nodo actual, explora el último hijo
        cout << "Buscando en el último hijo..." << endl;
        return updateEnNodo(nodo->hijos.back(), valorABuscar, nuevoValor, criterio);
    }

    return false; // Registro no encontrado en este nodo
}


