/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
Este programa resuelve el problema del estacionamiento en un lote circular.
Los dats de entrada consisten en la posicion inicial de los autos en espera 
y las posiciones que se van desocupando. Determina la posicion final de cada 
auto mediante reglasdadas.

1. Lee el numero de casos de prueba
2. Para cada caso:
    - Lee las posiciones iniciales. 
    - Lee las posiciones desocupadas. 
    - Asigna un lugar de estacionamiento.
    - Determina la posicion mas cercana y actualiza las posiciones restantes.
    - Imprime las posiciones finales de los autos o indica si no se estacionaron.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>

using namespace std;

typedef pair<int, int> Posicion;
typedef vector<Posicion> VecPosiciones;

void leerPosicionesAutos(VecPosiciones &posiciones, vector<int> &autosEnEspera){
    int p;

    while(cin >> p &&p!=99){ 
        autosEnEspera.push_back(p); //adregar la posicion a la lista de autos en espera
        posiciones.push_back(Posicion(p, p)); 
    }
}

void actualizarPosiciones(VecPosiciones &posiciones, int distancia){
    for(auto &pos : posiciones){ //actualizaq cada pos
        pos.first += distancia; 

        if(pos.first>20){ 
            pos.first %= 20;
        }
    }

    sort(posiciones.begin(), posiciones.end()); //ordena las posiciones
}

int encontrarPosicionMasCercana(const VecPosiciones &posiciones, int lugar){
    int posicionMasCercana = -1;
    for(int i=0; i< posiciones.size(); ++i){ 
        if(posiciones[i].first > lugar){ 
            if(i == 0){
                posicionMasCercana = posiciones.size()-1;
            }
            else{ 
                posicionMasCercana = i - 1;
            }
            break; 
        }

        if (i+1 == posiciones.size()){
            posicionMasCercana = posiciones.size() - 1;
        }
    }

    return posicionMasCercana; //indice de la posicion mas cercana
}

void procesarEstacionamiento(VecPosiciones &posiciones, int lugar, int *lugarEstacionamiento){
    int posicionMasCercana = encontrarPosicionMasCercana(posiciones, lugar); 
    lugarEstacionamiento[posiciones[posicionMasCercana].second]=lugar; 

    int distancia = 0;
    if(posiciones[posicionMasCercana].first<=lugar){ //calcular distancia
        distancia = lugar - posiciones[posicionMasCercana].first;
    }
    else{
        distancia =lugar+20- posiciones[posicionMasCercana].first;
    }

    posiciones.erase(posiciones.begin() + posicionMasCercana); 
    actualizarPosiciones(posiciones, distancia); //actualiza las posiciones restantes
}

void imprimirResultados(const vector<int> &autosEnEspera, int *lugarEstacionamiento){
    for(int autoInicial :autosEnEspera){ 
        cout << "Original position " << autoInicial; 
        if(lugarEstacionamiento[autoInicial] ==-1){ //ver si no se estaciono
            cout << " did not park\n";
        }
        else{ //posicion finla
            cout << " parked in " << lugarEstacionamiento[autoInicial] << "\n";
        }
    }
}

void procesarCasosPrueba(int casosDePrueba){
    int lugarEstacionamiento[21];
    string line;

    while(casosDePrueba--){
        VecPosiciones posiciones;
        vector<int> autosEnEspera;
        leerPosicionesAutos(posiciones, autosEnEspera); // posiciones iniciales

        sort(posiciones.begin(), posiciones.end()); 
        memset(lugarEstacionamiento, -1, sizeof(lugarEstacionamiento)); 
        getline(cin, line);

        while(getline(cin, line)&& !line.empty()){ 
            int lugar;
            istringstream entrada(line);
            entrada >> lugar; 
            procesarEstacionamiento(posiciones, lugar, lugarEstacionamiento); 
        }

        imprimirResultados(autosEnEspera, lugarEstacionamiento); //imprimir los resultados

        if(casosDePrueba){ // linea en blanco entre casos de prueba
            cout << "\n";
        }

    }
}

int main(){
    int T;
    cin >> T; 
    
    procesarCasosPrueba(T); 

    return 0;
}