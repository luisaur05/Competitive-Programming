/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa da el numero minimo de movimientos necesarios para que la reina 
pueda visitar todo un tablero de ajedrez, si es posible. Cada casilla 
del tablero puede estar o no vacia. La reina puede moverse horizontalmente, 
verticalmente o en diagonal.

1. Lee el numero de casos de prueba.
2. Para cada caso de prueba:
    - Lee las dimensiones del tablero.
    - Lee el tablero.
    - Calcula las distancias mnimas hasta la tienda mas cercna en cada fila del tablero.
    - Calcular la suma de las distancias mínimas en cada columna.
    - Determina si es posible que la reina visite todos los espacios.
      - Si es posible, da el numero mínimo de movimientos necesarios; 
	  - En caso contrario establecer el resultado como -1.
    - Imprimw l resultado para el casactual.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

//calcula la distancia hasta el 0 as cercano en cada fila
vector<vector<int>> calcularDistancias(int filas, int columnas, vector<string>& grid){
    vector<vector<int>> distancias(filas, vector<int>(columnas, columnas));

    for(int i=0; i<filas; i++){
        int prevZero;
		
		prevZero = columnas;
        stack<int> prevOne;
        for(int j=0;j<columnas; j++){
            if(grid[i][j]=='0'){
                distancias[i][j]=0;
                prevZero=j;

                while(!prevOne.empty()){
                    distancias[i][prevOne.top()] = min(distancias[i][prevOne.top()], j - prevOne.top());
                    prevOne.pop();
                }

            } 
			else{
                prevOne.push(j);

                if(prevZero!=columnas){
                    distancias[i][j] = min(distancias[i][j], j - prevZero);
				}
            }
        }
    }

    return distancias;
}

int main(){
    int T;

    cin >> T;
    int casos_actuales = 1;
    while(T--){
        int filas;
		int columnas;

        cin >> filas >> columnas;
        vector<string> grid(filas);

        for(int i=0; i<filas;i++){
            cin >> grid[i];
        }

        //clculaa las distancias hasta el 0 mas cercano en cada fila
        vector<vector<int>> distancias;
		distancias = calcularDistancias(filas, columnas, grid);

        int resultado;
		resultado = INT_MAX;
        bool valido;
		valido = true;

        //calcul la suma de las distancias mínimas en cada columna
        for(int col=0; col<columnas && valido;col++){
            int suma;
			suma=0;
            for(int fila=0; fila<filas && valido;fila++){
                if(distancias[fila][col]== columnas){
					valido = false;
				}
                else{ 
					suma+=distancias[fila][col];
				}
            }
            resultado = min(resultado, suma);
        }

        cout << "Case " << casos_actuales++ << ": " << (valido ? to_string(resultado) : "-1") << endl;
    }

    return 0;
}