/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa calcula la distancia total recorrida por una particula que se mueve entre dos puntos 
dados atraves de dos angulos de dirección especificados en grados.

1. Lee los datos de entrada.
2. Calcula la distancia AB entre los dos puntos.
3. Calcula la distancia total recorrida por la partícula.
4. Imprime la distancia total con tres decimales.
*/

#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

struct Point {
    double x;
    double y;
};

//distancia euclidiana entre dos puntos
double calcularDistancia(const Point& p1,const Point& p2){
    double res;
    res = sqrt(pow(p1.x-p2.x, 2)+pow(p1.y - p2.y, 2));

    return res;
}

//distancia total recorrida
double calcularDistanciaTotal(const Point& p1,const Point& p2,double CMD,double ENF){
    double distanciaAB = calcularDistancia(p1, p2);

    return distanciaAB * (1 /tan(CMD*M_PI /180)+1/tan(ENF * M_PI/180));
}

int main(){
    Point puntoInicial;
    Point puntoFinal;

    double CMD;
    double ENF;
    
    while(cin >> puntoInicial.x >> puntoInicial.y >> puntoFinal.x >> puntoFinal.y>>CMD>>ENF){
        double distanciaTotal;

        distanciaTotal = calcularDistanciaTotal(puntoInicial,puntoFinal,CMD,ENF);
        
        cout << fixed<<setprecision(3)<< distanciaTotal << endl;
    }

    return 0;
}