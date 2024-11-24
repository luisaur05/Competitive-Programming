/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCION--------
EL progrma resuelve el problema de encontrar el número de nodos requeridos en un 
recorrido DFS a través de un grafo dado. 

Para cada caso:
1. Lee el numero de nodos y el numero de nodos requeridos.
2. Construye el grafo dads las aristas. 
3. Se realiza un recorrido DFS desde el nodo 1 y se cuenta el número de nodos visitados. 
4. Si la cantidad de nodos visitados es menor que la cantidad requerida, 
se devuelve 1. Si no, se suman los nodos visitados y se imprime el resultado junto con el número de caso.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> grafo(1024); 
int nodos; 


int DFS(int inicio, int fin){
    vector<int> hijos;
    // recorrmos los hijos del nodo actual
    for(int hijo : grafo[inicio]){
        if(hijo != fin){
            hijos.push_back(DFS(hijo, inicio)); 
        }
    }
    // Si hay menos hijos que nodos requeridos, se devuelve 1
    if(hijos.size() < nodos){
        return 1;
    }

    // se ordenann los hijos de forma descendente
    sort(hijos.begin(), hijos.end(), greater<int>());
    int suma = 1;

    // Sumamos los nodos 
    for(int i = 0; i < nodos; i++){
        suma += hijos[i];
    }
    return suma;
}

int main() {
    int T;
    int I = 1; 
    int n; 
    int res; 

    cin >> T;

    while(T--){
        for(int i = 0; i < 1024; i++){
            grafo[i].clear();
        }

        cin >> n >> nodos; 
        int u, v; 
        for(int i = 1; i < n; i++){
            cin >> u >> v;
            grafo[u].push_back(v);
            grafo[v].push_back(u);
        }

        //  DFS desde el nodo 1
        res = DFS(1, -1);
  
        cout << "Case " << I++ << ": " << res << "\n";
    }
    return 0;
}