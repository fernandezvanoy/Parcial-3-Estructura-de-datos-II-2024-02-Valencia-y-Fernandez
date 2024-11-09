#include <vector>
#include <string>

using namespace std; 

class NodoBMas
{
public:
    bool esHoja;
    vector<vector<string>> claves; // Las claves ahora son vectores de strings
    vector<NodoBMas *> hijos;      // Punteros a los hijos
    NodoBMas *siguienteHoja;       // Puntero al siguiente nodo hoja (en caso de ser hoja)

    NodoBMas(bool esHoja);
};