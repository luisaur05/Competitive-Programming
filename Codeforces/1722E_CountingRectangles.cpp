/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El cpdigo procesa consultas sobre areas de rectangulos en una cuadricua bidimenional.

1. Lee el numero total de casos de prueba.
2. Por cada caso de prueba:
    - Lee el número de rectangulos y consultas.
    - Inicializa la cuadricula con ceros.
    - Lee las dimensiones de cada rectangulo y actualiza la cuadricula con el area de cada rectangulo.
    - Calcula las areas acumuladas.
    - Por cada consulta:
        - Lee las coordenadas de los dos puntos que describen el rectangulo de la consulta.
        - Ajusta las coordenadas del punto inferior derecho del rectangulo para que coincidancon la cuadricula.
        - Calcula la suma de las áreas de los rectaangulos que se superponen con la consulta usando sumas acumulativas.
        - Imprim el resultado de la consulta.
3. Imprime los resultados de las consultas.
*/

#include <iostream>
#include <cstring>
using namespace std;

const int TAM_MAX = 1005;
long long cuadricula[TAM_MAX][TAM_MAX];

void procesarConsultasYImprimir(int casos_prueba){
    while(casos_prueba--){
        int n;
        int q;
        cin >> n >> q;
        memset(cuadricula, 0, sizeof(cuadricula));
        
        // Lectura de dimensiones de los rectangulos y actualización de la cuadricula
        for(int i =1; i<=n; i++){
            long long x, y;
            cin >> x >> y;
            cuadricula[x][y] += x * y;
            // cout << x;
        }
        
        // Precálculo de áreas acumuladas
        for(int x=1; x< TAM_MAX; x++){
            for(int y=1; y < TAM_MAX; y++){
                cuadricula[x][y] += cuadricula[x - 1][y] + cuadricula[x][y - 1] - cuadricula[x - 1][y - 1];
            }
        }
        
        // Procesamiento de las consultas y salida de resultados
        while(q--){
            int h1;
            int w1;
            int h2;
            int w2;

            cin >> h1 >> w1 >> h2 >> w2;

            h2--; // reducir la coordenada x y y en 1 para ajustarse a la representación en la cuadrícula
            w2--; 
            cout << cuadricula[h2][w2] - cuadricula[h1][w2] - cuadricula[h2][w1] + cuadricula[h1][w1] << endl;
        }
    }
}

int main() {
    int T;
    cin >> T;

    procesarConsultasYImprimir(T);

    return 0;
}