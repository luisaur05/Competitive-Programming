/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa resuelve un problema de coleccion de monedas.Calcula el maximo numero de 
monedas que se pueden recoger siguiendo un recorrido permitido en la cuadricula
y lo hace utilizando una técnica BFS para calcular la suma maxima de monedas.

1. Lee numero de casos de prueba.
2. Para cada caso:
   - Leer el tamaño de la cuadricula y el rango de movimiento.
   - Inicializar y leer la matriz de monedas.
   - Inicializar la matriz de DP con valores negativos grandes.
3. Calcula la suma maxima de monedas usando BFS.
4. Imprime el resultado.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN=103;
const int INF=-1e6;

int N; 
int K; 
int cuadricula[MAXN][MAXN]; //almacenar las monedas en la cuadrícula
int dp[MAXN][MAXN];

//BFS aparaa calcular la suma máxima de monedas
void calcularMaximoCamino(){
    //valores originales de la cuadrícula
    dp[1][1]=cuadricula[1][1];
    int sumaMaxima;

    sumaMaxima = dp[1][1];

    //BFS para calcular la suma máxima de monedas
    for(int valor=cuadricula[1][1];valor<=100;valor++){
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                if(cuadricula[i][j]!=valor){ 
                    continue;
                }

                //movim9iento en todas las direcciones dentro del rango de K
                for(int desplazamiento=-K; desplazamiento<=K;desplazamiento++){
                    int nuevaX=i+desplazamiento;
                    int nuevaY=j+desplazamiento;

                    if(nuevaY>0 && nuevaY<=N && cuadricula[i][j]<cuadricula[i][nuevaY]){
                        dp[i][nuevaY] = max(dp[i][nuevaY], dp[i][j] + cuadricula[i][nuevaY]);
                        sumaMaxima = max(sumaMaxima, dp[i][nuevaY]);
                    }

                    if(nuevaX>0 && nuevaX<=N && cuadricula[i][j]<cuadricula[nuevaX][j]){
                        dp[nuevaX][j]=max(dp[nuevaX][j], dp[i][j] + cuadricula[nuevaX][j]);
                        sumaMaxima= max(sumaMaxima, dp[nuevaX][j]);
                    }
                }
            }
        }
    }

    cout << sumaMaxima << endl;
}

int main(){
    int T;
    cin >> T;

    while(T--){
        cin >> N >> K;

        for(int i=1; i<=N;i++){
            for(int j=1;j<= N;j++){
                cin >> cuadricula[i][j];
                dp[i][j]=INF;
            }
        }

        calcularMaximoCamino();

        if(T){ 
            cout <<endl;
        }
    }

    return 0;
}