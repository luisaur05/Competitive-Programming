/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCION--------
El programa calcula la distancia total recorrida por un camion de basura que recolecta en puntos 
especficos evitando exceder un peso maxiimo permitido. Utiliza las distancias entre puntos y la 
cantidad de basura recolectada para determinar la distancia recorrida.

1. Lee el numero de casos de prueba.
2. Para cada caso de prueba:
    - Se lee el peso maximo que puede llevar el camion.
    - Se lee el numero de puntos de recoleccion.
    - Se almacenan las distancias y la cantidad de basura de cada punto de recoleccion.
    - Se inicializa el eso actualdel camio y la distancia total recorrida.
    - Si agegar la basura del punto actual excede el peso maximo se vacia el camion y se suma la distancia de ida y vuelta.
    - Se añade la basura del punto actual al peso del camion.
    - Si el peso del camiOn alcanza el maximo permitido se vacia el camion y se suma la distancia de regreso.
    - Se suma la disancia al siguiente punto o la distanca de regreso si es l ltimo punto.
3. Imprime la distancia total calculada para el caso de prueba actual.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//estructura para almacenar los puntos de recoleccion
struct Punto{
    int distancia;
    int basura;
};

int procesarCaso(int pesoMaximo, const vector<Punto>& puntos){
    int pesoActual = 0;
    int distanciaTotal = puntos[0].distancia; 

    for(int i=0; i<puntos.size();i++){
        if(pesoActual +puntos[i].basura >pesoMaximo){
            pesoActual=0; // Reinicia el peso actual
            distanciaTotal +=(puntos[i].distancia * 2); 
        }

        pesoActual += puntos[i].basura; //agrega la basura del punto al peso ctual

        if(pesoActual ==pesoMaximo){
            distanciaTotal += puntos[i].distancia; // Agrega la distancia de regreso

            if(i +1 == puntos.size()){
                break;
            }

            pesoActual =0; //reinicia el peso actual
            distanciaTotal +=puntos[i].distancia; //regresa al punto de partida
        }


        if(i + 1 == puntos.size()){
            distanciaTotal +=puntos[i].distancia;
        }
        else{
            distanciaTotal +=(puntos[i + 1].distancia-puntos[i].distancia); 
        }
    }

    return distanciaTotal; //distancia total calculada
}


vector<Punto> procesarEntrada(int& pesoMaximo){
    int cantidadPuntos;
    cin >> pesoMaximo >> cantidadPuntos;

    vector<Punto> puntos(cantidadPuntos);

    //lee las distancias y la cantidad de basura de cada punto
    for(int i= 0; i < cantidadPuntos;i++){
        cin >> puntos[i].distancia >> puntos[i].basura;
    }
    
    return puntos; 
}

int main() {
    int T;
    cin >> T;


    while(T--){
        int pesoMaximo;
        int resultado;

        vector<Punto> puntos = procesarEntrada(pesoMaximo); 
        resultado = procesarCaso(pesoMaximo, puntos); 

        cout << resultado << "\n"; //imprime el resultado
    }

    return 0;
}