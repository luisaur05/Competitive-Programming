/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa calcula las coordenadas cartesianas de un punto movindose a lo largo 
de un circulo dada la posicion inicial del punto, el radio y el perpodo de tiempo.

1. Lee el umero de mediciones y el tiempo total.
2. Inicializa la posicion actual del punto en el origen.
3. Para cada emdicion:
   - Calculan las nuevas coordenadas del punto en funcion del radio y el período de tiempo.
   - Actualiza la posicion actual del punto sumando las nuevas coordenadas.
   - Imprime la distancia al origen.
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point{
    double x;
    double y;
};

//calcula las coordenadas cartesianas del punto en función del radio y el periodo de tiempo
Point calcularCoordenadas(double radio,double periodo,int tiempo){
    double angulo;

    angulo = 2.0 * M_PI * (double) tiempo/periodo;
    
    return {radio * cos(angulo), radio * sin(angulo)};
}

int main() {
    int n;
    int T;

    while(cin >> n>> T){
        Point posicionActual = {0, 0}; //pos actual del punto en el origen

        for(int i=0; i<n;i++){
            if(i>0){
                cout << " ";
            }

            double r;
            double t;

            cin >> r >> t;

            Point nuevaPosicion = calcularCoordenadas(r, t, T);

            posicionActual.x +=nuevaPosicion.x; //actualiza la pos
            posicionActual.y +=nuevaPosicion.y;

            cout << fixed<< setprecision(4) << sqrt(posicionActual.x*posicionActual.x + posicionActual.y*posicionActual.y);
        }
        cout << "\n";
    }
    return 0;
}