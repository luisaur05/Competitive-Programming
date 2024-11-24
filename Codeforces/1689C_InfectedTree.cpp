/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El algoritmo determina el maximo numero de vetices que Misha puede salvar en un arbol binario dado.
Se utiliza un algoritmo de programación dinaica basado en DFS y se calcula el resultado para cada 
nodo del arbol considerando la cantidad de hijos de cada nodo.

1. Lee el numero de casos de prueba.
2. Para cada caso de prueba:
    - Lee la descripcion del arbol y construye la lista de adyacencia
    - Calcula el resultado maximo utilizando un algoritmo de programación dinamicausando DFS
    - Imprime el resultado para el caso de prueba actual.
*/


#include <iostream>
#include <vector>
using namespace std;

vector<int> resultado(300001); // almacena los resultados de cada nodo
vector<int> hijo(300001); //almacenala cantidad de hijos de cada nodo


void calcularResultado(int nodo, int padre, vector<vector<int>>& adyacencia){
    hijo[nodo] = 1;
    resultado[nodo] = 0;
    int suma = 0;
    
    for(int vecino : adyacencia[nodo]){
        if(vecino != padre){
            // calcular el resultado del nodo vecino.
            calcularResultado(vecino, nodo, adyacencia);
            //actualiza la suma de resultados y la cantidad de hijos del nodo actual
            suma += resultado[vecino];
            hijo[nodo] += hijo[vecino];
        }
    }
    //calcula el resultado final para el nodo actual
    for(int vecino :adyacencia[nodo]){
        if(vecino != padre){
            resultado[nodo] =max(resultado[nodo], suma - resultado[vecino]+hijo[vecino]-1);
        }
    }
}

int main() {
    int casos_prueba;
    cin >> casos_prueba;
    while(casos_prueba--){
        int n;
        cin >> n;
        vector<vector<int>> adyacencia(n + 1); 
    
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;

            adyacencia[u].push_back(v);
            adyacencia[v].push_back(u);
        }
        
        if(adyacencia[1].size()==1){
            cout << n - 2;
        } 
        else{
            calcularResultado(1, 0, adyacencia);

            cout << resultado[1];
        }
        
        cout << endl;
    }

    return 0;
}