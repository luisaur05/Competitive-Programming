/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCION--------
El programa resuelve el problema de asignacion de miembros de un consejo a diferentes clubes, 
asegurando que cada club este representado por un miembro sin vilar las restricciones de partidos políticos.
Usamos el algoritmo de flujo maximo para determinar la asignacion ooptima.

1. Lee los datos de entrada.
2. Cra un grafo con
   - Un nodo fuente esta conectado a todos los clubes.
   - Cada club esta conectado a las personas que pertenecen a el.
   - Cada persona esta conectada al partido al que pertenece.
   - Los partidos estan conectados a un nodo.
3. Aplica el algoritmo de flujo maximo para encontrar la maxima asignacion posible.
4. Si es posible formar el consejo, imprime los miembros del consejo y los clubes que representan y sii no es posible, imprime "Impossible".
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <sstream>
#include <climits>

#define INF INT_MAX

using namespace std;

class RedFlujo{
public:
    int totalNodos;
    vector<vector<int>> listaAdyacencia;
    vector<vector<int>> matrizCapacidad;

    RedFlujo(int nodos): totalNodos(nodos), listaAdyacencia(nodos), matrizCapacidad(nodos, vector<int>(nodos)){}

    // enlace entre dos nodos 
    void agregarEnlace(int desde, int hasta, int capacidad){
        listaAdyacencia[desde].push_back(hasta);
        listaAdyacencia[hasta].push_back(desde);
        matrizCapacidad[desde][hasta] = capacidad;
    }

    // Encuentra el flujo máximo desde el origen hasta el  fin
    int encontrarFlujoMaximo(int origen, int fin){
        int flujoTotal = 0, flujo;
        vector<int> padre(totalNodos);

        while((flujo = bfs(origen, fin, padre))!= 0){
            flujoTotal += flujo;
            int actual = fin;

            while (actual != origen){
                int previo = padre[actual];
                matrizCapacidad[previo][actual] -= flujo;
                matrizCapacidad[actual][previo] += flujo;
                actual = previo;
            }
        }
        return flujoTotal;
    }

private:
    int bfs(int origen, int sumidero, vector<int>& padre){
        fill(padre.begin(), padre.end(), -1);
        padre[origen] = origen;
        queue<pair<int, int>> cola;
        cola.push({origen, INF});

        while(!cola.empty()){
            int nodo = cola.front().first;
            int flujo = cola.front().second;
            cola.pop();

            for(int vecino : listaAdyacencia[nodo]){
                if(padre[vecino] == -1 && matrizCapacidad[nodo][vecino] > 0){
                    padre[vecino] = nodo;
                    int nuevoFlujo = min(flujo, matrizCapacidad[nodo][vecino]);
                    if(vecino == sumidero){
                         return nuevoFlujo;
                    }
                    cola.push({vecino, nuevoFlujo});
                }
            }
        }

        return 0;
    }
};


void resolverCaso(){
    map<string, int> idClubes, idPartidos, idPersonas;
    map<int, string> nombreClubes, nombrePersonas, nombrePartidos;
    vector<pair<int, int>> clubPersona, personaPartido;

    string linea, persona, partido, club;

    // Leer y procesar datos de entrada
    while(getline(cin, linea) && !linea.empty()){
        istringstream in(linea);
        in >> persona >> partido;

        if(idPersonas.find(persona) == idPersonas.end()){
            int id = idPersonas.size();
            idPersonas[persona] = id;
            nombrePersonas[id] = persona;
        }

        if(idPartidos.find(partido) ==idPartidos.end()){
            int id = idPartidos.size();
            idPartidos[partido] = id;
            nombrePartidos[id] = partido;
        }

        int indicePersona= idPersonas[persona];
        int indicePartido=idPartidos[partido];
        personaPartido.emplace_back(indicePersona, indicePartido);

        while(in >> club){
            if(idClubes.find(club) == idClubes.end()){
                int id = idClubes.size();
                idClubes[club] = id;
                nombreClubes[id] = club;
            }

            int indiceClub =idClubes[club];
            clubPersona.emplace_back(indiceClub, indicePersona);
        }
    }

    int numClubes =idClubes.size();
    int numPersonas = idPersonas.size();
    int numPartidos = idPartidos.size();
    int fuente = 0;
    int fin = numClubes + numPersonas + numPartidos + 1;

    RedFlujo red(fin + 1);

    for(int i =0; i < numClubes; ++i){
        red.agregarEnlace(fuente, i + 1, 1);
    }

    for(const auto& enlace : clubPersona){
        red.agregarEnlace(enlace.first + 1, enlace.second + numClubes + 1, 1);
    }

    for(const auto& enlace : personaPartido){
        red.agregarEnlace(enlace.first + numClubes + 1, enlace.second + numClubes + numPersonas + 1, 1);
    }

    for(int i = 0; i < numPartidos; ++i){
        red.agregarEnlace(i + numClubes + numPersonas + 1, fin, (numClubes - 1) / 2);
    }

    // Calcular el flujo max
    int flujoMaximo = red.encontrarFlujoMaximo(fuente, fin);

    if(flujoMaximo ==numClubes){
        for (int indicePersona = 0; indicePersona < numPersonas; ++indicePersona){
            int nodoPersona = indicePersona + numClubes + 1;
            for(int indiceClub = 0; indiceClub < numClubes; ++indiceClub){
                int nodoClub = indiceClub + 1;
                if(red.matrizCapacidad[nodoPersona][nodoClub] == 1){
                    cout << nombrePersonas[indicePersona] << " " << nombreClubes[indiceClub] << "\n";
                    break;
                }
            }
        }
    } 
    else{
        cout << "Impossible.\n"; // asi se indicoq ue se debe imprimir cuando no se puede
    }
}

int main(){
    int T;
    string line;    

    cin >> T;

    getline(cin, line); // Leer la linea en blanco 
    getline(cin, line); // Leer la linea en blanco 

    while(T--){
        resolverCaso();
        if(T){
            cout << "\n"; // Imprimir una linea en blanco entre los casos
        }
    }

    return 0;
}