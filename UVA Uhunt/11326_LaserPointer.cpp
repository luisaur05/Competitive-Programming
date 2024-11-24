/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
Ell programa calcula una medida de seguridad para un avion que despega de una 
pista en un angulo determinad y el angulo de despegue especificado en grados.

1. Lee el numero de casos de prueba.
2. Para cada caso:
   - Lee la longitud, el ancho y el ángulo de despegue.
   - Convierte el angulo de grados a radianes.
   - Calcula la medida de seguridad.
   - Imprime la medida de seguridad.
*/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <iomanip>

using namespace std;

double calcularMedidaSeguridad(int L, int W, int angleGrad){
    double y;
    double h;
    double s;
    double x;
    int k;
    double resultado;

    //grados a radianes
    double angle = 2 * acos(0) * angleGrad / 180.0;

    if (angle == 0){
        return 1.000;
    }

    x = W / tan(angle);
    k=1;
    while(x*k <= L){
        k++;
    }

    //altura h y distancia s
    y = L - (k - 1) * x;
    h = (k % 2 ==0)?(W-y * tan(angle)) : (y *tan(angle));
    s = y / cos(angle);

    //medida de seguridad
    resultado = W / sin(angle) * (k - 1) + s;
    resultado /= sqrt(h * h + L * L);

    return resultado;
}

int main(){
    int T;
    cin >> T;

    cout << fixed << setprecision(3); //precision de salida a tres decimales

    while(T--){
        int L;
        int W;
        int angl;

        cin >> L >> W >> angl;

        cout << calcularMedidaSeguridad(L,W,angl) << endl;
    }
    return 0;
}