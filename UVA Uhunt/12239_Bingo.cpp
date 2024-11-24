/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCION--------
Descripción:
El codigo verifica si es posible llamar a todos los nmeros desde 0 hasta N,
utilizndo las bolas que quedan en la bolsa.

1. Lee el número de casos.
2. Para cada caso:
    - Lee las bolas que quedan en la bolsa y se almacenan en un vector.
    - Se verifica si todas las distancias entr las bolas son posibles.
    - Se imprime "Y" si es posible llamar a todos los numeros o "N" cuando no.
*/


#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int calcularAbsoluto(int a){
    return (a<0) ? -a : a;
}

bool todasDistanciasPosibles(const vector<int>& bolas, int numCasos){
    unordered_set<int> distancias;

    //distancias posibles entre las bolas
    for(int i=0; i <bolas.size();i++){
        for(int j = i + 1; j <bolas.size();j++){
            int distancia;

            distancia = calcularAbsoluto(bolas[i]-bolas[j]);
            distancias.insert(distancia);

        }
    }

    //ve si todas las distancias hasta numCasos son posibles
    for(int i=1; i <=numCasos;i++){
        if(distancias.find(i)==distancias.end()){
            return false;
        }
    }

    return true;
}

int main(){
    int numCasos;
    int numBolas;
    int bola;

  
    while(cin >> numCasos >> numBolas){
        bool todoPosible;

        if(numCasos==0 && numBolas == 0){ //ver si se tiene que hacer algo
            break;
        }

        //almacena las bolas
        vector<int> bolas;

        for(int i=0; i <numBolas; i++){
            cin >> bola;
            bolas.push_back(bola);
        }

        //ver si todas las distancias son posibles
        todoPosible = todasDistanciasPosibles(bolas, numCasos);

        //imprimw el resultado
        cout << (todoPosible ? "Y" : "N") << endl;

    }

    return 0;
}