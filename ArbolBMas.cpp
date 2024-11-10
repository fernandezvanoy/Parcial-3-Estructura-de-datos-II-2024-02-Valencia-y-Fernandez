#include "ArbolBMas.h"

// Constructor de la clase ArbolBMas
// Inicializa la raiz, el grado minimo, el grado maximo y las columnas para el arbol
ArbolBMas::ArbolBMas(int orden, string nombreArbol, vector<string> columnas) : raiz(new NodoBMas(true)), gradoMinimo(orden / 2), orden(orden), gradoMaximo(orden - 1), columnas(columnas), nombreArbol(nombreArbol) {}

// Metodo para insertar una clave en el arbol
void ArbolBMas::insertar(const std::string &tabla, const std::vector<std::string> &columnas, const std::vector<std::string> &valores)
{
    // Imprime el comando de insercion simulado
    std::cout << "Ejecutando: INSERT INTO " << tabla << " (";
    // Itera y muestra cada columna separadas por comas
    for (size_t i = 0; i < columnas.size(); ++i)
    {
        std::cout << columnas[i];
        if (i < columnas.size() - 1)
            std::cout << ", ";
    }
    std::cout << ") VALUES (";
    // Itera y muestra cada valor separado por comas
    for (size_t i = 0; i < valores.size(); ++i)
    {
        std::cout << valores[i];
        if (i < valores.size() - 1)
            std::cout << ", ";
    }
    std::cout << ")\n";

    // Si la raiz esta llena, dividirla y ajustar la raiz
    if (raiz->claves.size() == orden - 1)
    {
        NodoBMas *nuevaRaiz = new NodoBMas(false);
        nuevaRaiz->hijos.push_back(raiz);
        dividir(nuevaRaiz, 0);
        raiz = nuevaRaiz;
    }

    // Llama a la funcion auxiliar para insertar en el nodo correspondiente
    insertarAux(raiz, valores);
}

// Metodo auxiliar para insertar una clave en un nodo especifico
void ArbolBMas::insertarAux(NodoBMas *nodo, const vector<string> &clave)
{
    if (nodo->esHoja)
    {
        // Inserta la clave en un nodo hoja y ordena las claves
        nodo->claves.push_back(clave);
        std::sort(nodo->claves.begin(), nodo->claves.end(),
                  [](const vector<string> &a, const vector<string> &b)
                  {
                      return a[0] < b[0];
                  });
    }
    else
    {
        // Encuentra el hijo adecuado para insertar la clave
        int i = nodo->claves.size() - 1;
        while (i >= 0 && clave[0] < nodo->claves[i][0])
        {
            i--;
        }
        i++;

        // Llama recursivamente para insertar en el hijo correcto
        insertarAux(nodo->hijos[i], clave);

        // Si el hijo esta lleno, dividirlo
        if (nodo->hijos[i]->claves.size() > orden - 1)
        {
            dividir(nodo, i);
            if (clave[0] > nodo->claves[i][0])
            {
                i++;
            }
        }
    }
}

// Divide un nodo lleno en dos y ajusta el padre
void ArbolBMas::dividir(NodoBMas *padre, int indice)
{
    NodoBMas *lleno = padre->hijos[indice];
    NodoBMas *nuevoHijo = new NodoBMas(lleno->esHoja);

    int midIndex = (lleno->claves.size() / 2);

    // Promueve la clave del medio al padre
    padre->claves.insert(padre->claves.begin() + indice, lleno->claves[midIndex]);

    // Asigna el nuevo hijo al padre
    padre->hijos.insert(padre->hijos.begin() + indice + 1, nuevoHijo);

    // Asigna claves al nuevo nodo
    nuevoHijo->claves.assign(lleno->claves.begin() + midIndex + 1, lleno->claves.end());
    lleno->claves.resize(midIndex);

    // Si el nodo no es hoja, ajusta los hijos
    if (!lleno->esHoja)
    {
        nuevoHijo->hijos.assign(lleno->hijos.begin() + midIndex + 1, lleno->hijos.end());
        lleno->hijos.resize(midIndex + 1);
    }
    else
    {
        // Ajusta los punteros entre hojas
        nuevoHijo->siguienteHoja = lleno->siguienteHoja;
        lleno->siguienteHoja = nuevoHijo;
    }
}

// Metodo para eliminar una clave del arbol
void ArbolBMas::eliminar(const vector<string> &clave)
{
    std::cout << "Ejecutando: ELIMINAR (";

    for(int i = 0; i < clave.size(); i++){
        cout << clave[i] << " ";
    }

    cout << ")" << endl;

    eliminarDeNodo(raiz, clave);
    // Si la raiz queda vacia, ajusta la raiz
    if (!raiz->esHoja && raiz->claves.empty())
    {
        NodoBMas *viejaRaiz = raiz;
        raiz = raiz->hijos[0];
        delete viejaRaiz;
    }
}

// Elimina una clave de un nodo especifico
void ArbolBMas::eliminarDeNodo(NodoBMas *nodo, const vector<string> &clave)
{
    int indice = -1;
    for (int i = 0; i < nodo->claves.size(); ++i)
    {
        if (nodo->claves[i][0] >= clave[0])
        {
            indice = i;
            break;
        }
    }
    if (indice == -1)
    {
        indice = nodo->claves.size();
    }

    if (nodo->esHoja)
    {
        if (indice < nodo->claves.size() && nodo->claves[indice][0] == clave[0])
        {
            nodo->claves.erase(nodo->claves.begin() + indice);
        }
    }
    else
    {
        if (indice < nodo->claves.size() && nodo->claves[indice][0] == clave[0])
        {
            eliminarClaveNodoInterno(nodo, clave, indice);
        }
        else
        {
            bool necesitaFusion = nodo->hijos[indice]->claves.size() < gradoMinimo;
            eliminarDeNodo(nodo->hijos[indice], clave);

            if (nodo->hijos[indice]->claves.size() < gradoMinimo)
            {
                manejarFusionRedistribucion(nodo, indice);
            }
        }
    }
}

// Elimina una clave encontrada en un nodo interno
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

    if (nodo->hijos[indice]->claves.size() < gradoMinimo)
    {
        manejarFusionRedistribucion(nodo, indice);
    }
}

// Obtiene la clave predecesora de un nodo
vector<string> ArbolBMas::obtenerPredecesor(NodoBMas *nodo)
{
    while (!nodo->esHoja)
        nodo = nodo->hijos.back();
    return nodo->claves.back();
}

// Obtiene la clave sucesora de un nodo
vector<string> ArbolBMas::obtenerSucesor(NodoBMas *nodo)
{
    while (!nodo->esHoja)
        nodo = nodo->hijos[0];
    return nodo->claves[0];
}

// Maneja la fusion o redistribucion de nodos cuando un nodo tiene menos de grado minimo de claves
void ArbolBMas::manejarFusionRedistribucion(NodoBMas *nodo, int indice)
{
    if (indice > 0 && nodo->hijos[indice - 1]->claves.size() > gradoMinimo)
    {
        redistribuirIzquierda(nodo, indice);
    }
    else if (indice + 1 < nodo->hijos.size() && nodo->hijos[indice + 1]->claves.size() > gradoMinimo)
    {
        redistribuirDerecha(nodo, indice);
    }
    else
    {
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

// Fusiona dos nodos en uno solo
void ArbolBMas::fusionarNodos(NodoBMas *nodo, int indice)
{
    NodoBMas *izquierdo = nodo->hijos[indice];
    NodoBMas *derecho = nodo->hijos[indice + 1];
    izquierdo->claves.push_back(nodo->claves[indice]);
    izquierdo->claves.insert(izquierdo->claves.end(), derecho->claves.begin(), derecho->claves.end());

    if (!izquierdo->esHoja)
    {
        izquierdo->hijos.insert(izquierdo->hijos.end(), derecho->hijos.begin(), derecho->hijos.end());
    }

    if (izquierdo->esHoja)
    {
        izquierdo->siguienteHoja = derecho->siguienteHoja;
    }

    nodo->claves.erase(nodo->claves.begin() + indice);
    nodo->hijos.erase(nodo->hijos.begin() + indice + 1);
    delete derecho;
}

// Redistribuye claves desde el nodo izquierdo al nodo actual
void ArbolBMas::redistribuirIzquierda(NodoBMas *nodo, int indice)
{
    NodoBMas *izquierdo = nodo->hijos[indice - 1];
    NodoBMas *actual = nodo->hijos[indice];
    actual->claves.insert(actual->claves.begin(), nodo->claves[indice - 1]);
    nodo->claves[indice - 1] = izquierdo->claves.back();
    izquierdo->claves.pop_back();

    if (!actual->esHoja)
    {
        actual->hijos.insert(actual->hijos.begin(), izquierdo->hijos.back());
        izquierdo->hijos.pop_back();
    }
}

// Redistribuye claves desde el nodo derecho al nodo actual
void ArbolBMas::redistribuirDerecha(NodoBMas *nodo, int indice)
{
    NodoBMas *actual = nodo->hijos[indice];
    NodoBMas *derecho = nodo->hijos[indice + 1];
    actual->claves.push_back(nodo->claves[indice]);
    nodo->claves[indice] = derecho->claves.front();
    derecho->claves.erase(derecho->claves.begin());

    if (!derecho->esHoja)
    {
        actual->hijos.push_back(derecho->hijos.front());
        derecho->hijos.erase(derecho->hijos.begin());
    }
}

void ArbolBMas::actualizar(const vector<string> &claveBuscada, const vector<string> &nuevaClave)
{

    cout << "UPDATE " << nombreArbol<< " SET {";

    for(int i = 0; i < nuevaClave.size(); i++){

        cout << nuevaClave[i] << ", "; 

    }

    cout << "}";

    cout << "WHERE {";
    
    for(int i = 0; i < claveBuscada.size(); i++){

        cout << claveBuscada[i] << ", "; 

    }

    cout << "}";
    cout << endl;

    // Llama a la funcion auxiliar para buscar y actualizar la clave
    actualizarAux(raiz, claveBuscada, nuevaClave);
}

void ArbolBMas::actualizarAux(NodoBMas *nodo, const vector<string> &claveBuscada, const vector<string> &nuevaClave)
{
    if (nodo == nullptr)
        return; // Si el nodo es nulo, termina la funcion

    if (nodo->esHoja)
    {
        // Caso 1: Si es un nodo hoja
        for (auto &clave : nodo->claves)
        {
            if (clave == claveBuscada)
            {
                clave = nuevaClave; // Reemplaza la clave encontrada con la nueva
                return; // Termina la actualizacion
            }
        }
    }
    else
    {
        // Caso 2: Si es un nodo interno
        // Revisa si el nodo actual tiene la clave buscada
        for (auto &clave : nodo->claves)
        {
            if (clave == claveBuscada)
            {
                clave = nuevaClave; // Actualiza la clave si la encuentra
                return; // Termina la actualizacion
            }
        }

        // Si no encuentra la clave en el nodo actual, busca en los hijos
        int i = 0;
        while (i < nodo->claves.size() && claveBuscada[0] > nodo->claves[i][0])
        {
            i++; // Avanza hasta encontrar la posicion correcta
        }
        // Llama recursivamente en el hijo correspondiente
        actualizarAux(nodo->hijos[i], claveBuscada, nuevaClave);
    }
}

void ArbolBMas::seleccionar(const vector<string> &camposBuscados)
{
    cout << "Ejecutando: SELECCIONAR (";
        for(string columna : camposBuscados){
            cout << columna << ",";
        }
        cout << ") FROM " << nombreArbol << endl;

    // Llama a la funcion auxiliar para realizar la seleccion de campos
    vector<int> numeroCampo;

    // Identifica los indices de las columnas solicitadas
    for (int i = 0; i < camposBuscados.size(); i++)
    {
        for (int j = 0; j < this->columnas.size(); j++)
        {
            if (camposBuscados[i] == columnas[j])
            {
                numeroCampo.push_back(j); // Almacena el indice de la columna
            }
        }
    }

    // Llama a la funcion auxiliar para seleccionar e imprimir los campos
    seleccionarAux(raiz, numeroCampo);
}

void ArbolBMas::seleccionarAux(NodoBMas *nodo, const vector<int> &camposBuscados)
{
    if (nodo == nullptr)
        return; // Si el nodo es nulo, termina la funcion

    // Recorre cada clave en el nodo actual
    for (auto &clave : nodo->claves)
    {
        cout << "["; // Imprime el inicio del grupo de campos seleccionados
        for (int i = 0; i < camposBuscados.size(); i++)
        {
            cout << clave[camposBuscados[i]] << ","; // Imprime el valor del campo seleccionado
        }
        cout << "]" << endl; // Imprime el fin del grupo de campos seleccionados
    }

    // Llama recursivamente en cada hijo para continuar la seleccion en niveles mas bajos
    for (int i = 0; i < nodo->hijos.size(); i++)
    {
        seleccionarAux(nodo->hijos[i], camposBuscados);
    }
}

void ArbolBMas::imprimirArbol(NodoBMas *nodo, int nivel)
{
    if (nodo == nullptr)
        return; // Si el nodo es nulo, termina la funcion

    // Imprime los espacios correspondientes al nivel actual
    for (int i = 0; i < nivel; i++)
        cout << "  ";

    // Imprime las claves del nodo actual
    for (const auto &clave : nodo->claves)
    {
        cout << "[" << clave[0] << "] ";
    }
    cout << endl;

    // Llama recursivamente en cada hijo si el nodo no es una hoja
    if (!nodo->esHoja)
    {
        for (auto hijo : nodo->hijos)
        {
            imprimirArbol(hijo, nivel + 1); // Llama en el siguiente nivel
        }
    }
}