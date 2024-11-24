/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa resuelve el problema de calcular el numero de partidos walkover en un torneo dado el numero 
de jugadors, el numero de rondas y los jugadores que se han retirado.

1. Lee el numero de cass de prueba.
2. Para cada caso:
    - Lee el número de rondas y el número de jugadores que se han retirado y nUmeros de los jugadores que se han retirado.
    - Inicializar los juadores disponibles como true usand un bitset.
    - Marca los jugadores que se han retirado como false en el bitset.
    - Calcular el nUmero de partidos para el torneo.
    - Utilza un algoritmo iterativo para simular el torneo.
3. Imprime el numero de partidos para cada caso de prueba.
*/

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;


//inicializa los jugadores disponibles
void inicializarJugadores(bitset<1024>& disponibles, int tam){
    for(int i=0; i <tam;i++){
        disponibles.set(i, true);
    }
}

//marcar jugadores ausentes
void marcarAusentes(bitset<1024>& disponibles, int numAusentes){
    for(int i= 0; i <numAusentes;i++){
        int jugador;
        cin >> jugador;
        disponibles.set(jugador -1, false);
    }
}

int calcularWalkOvers(bitset<1024>& disponibles, int tam){
    int walkOvers;

    walkOvers = 0;
    while(tam>1){
        for(int i = 0; i<tam;i+= 2) {
            bool jugador1;
            bool jugador2;

            jugador1 = disponibles[i];
            jugador2 = disponibles[i + 1];

            if(jugador1){
                if(!jugador2){
                    walkOvers++;
                }

                disponibles.set(i>> 1, true);
            } 
            else{
                if(jugador2){
                    walkOvers++;
                }

                disponibles.set(i >> 1, jugador2);
            }
        }

        tam >>=1;
    }

    return walkOvers;
}

void procesarCasosDePrueba(int numCasos){
    bitset<1024> disponibles;

    while(numCasos--){
        int rondas;
        int ausentes;

        cin >> rondas >> ausentes;

        int tam = 1 << rondas;

        inicializarJugadores(disponibles, tam);
        marcarAusentes(disponibles, ausentes);

        int walkOvers = calcularWalkOvers(disponibles, tam);
        cout << walkOvers << "\n";
    }
}

int main(){
    int T;

    cin >> T;
    procesarCasosDePrueba(T);

    return 0;
}