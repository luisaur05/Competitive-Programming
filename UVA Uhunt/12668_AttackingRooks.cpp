/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCION--------
Ell programa resuelve el problema de colocar la mayor cantidad de torres en un tablero de ajedrez de N x N,
hay ciertas casillas que estan ocupadas por peones ('X') y no se pueden utilizar. Las torres deben colocarse
en casillas vacías y no deben atacarse entre sí. El programa lee varios casos de prueba, genera una
representacion del tablero y calcula el maximo numero de torres que se pueden colocar utilizando el algoritmo de
emparejamiento maximo en grafos bipartitos.

Para cada caso:
1. Leer el tamano del tablero y el tablero.
2. Generar las filas y columnas para el grafo bipatito.
3. Crea la matriz de adyacencia del grafo.
4. Aplica el algoritmo de emparejamiento maximo para encontrar el mayor numero de torres que se pueden colocar sin
   que se ataquen.
5. Imprime l resultado.
*/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 101; // Tamano maximo del tablero
const int MAXV = 5001; // Maximo numero de nodos

char tablero[MAXN][MAXN];
int matrizAdyacencia[MAXV][MAXV]; 
int n; 
int filas, columnas; 
int indiceFila[MAXN][MAXN];
int emparejamiento[MAXV];
bool visitado[MAXV]; 


bool encontrarEmparejamiento(int u){
    for(int v = 0; v <columnas; v++){
        if(matrizAdyacencia[u][v] && !visitado[v]){
            visitado[v] = true;
            // Si el nodo v no esta emparejado o se puede emparejar con otro nodo
            if(emparejamiento[v] < 0 || encontrarEmparejamiento(emparejamiento[v])){
                emparejamiento[v] = u; // Emparejar u con v
                return true;
            }
        }
    }
    return false; // No se encontro un emparejamiento
}


int obtenerMaximoEmparejamiento(){
    memset(emparejamiento, -1, sizeof(emparejamiento)); 
    int resultado = 0;

    for(int u = 0; u <filas; u++){
        memset(visitado, 0, sizeof(visitado)); // maca todos los nodos como no visitados
        if(encontrarEmparejamiento(u)){ 
            resultado++; // contador de emparejamientos
        }
    }
    return resultado; 
}


void generarFilas(){
    int ix;
    for(int i = 0; i < n; i++){
        ix = -1;

        for(int j = 0; j < n; j++){
            if(tablero[i][j] == 'X'){
                for (int w = ix + 1; w <= j- 1; w++){
                    indiceFila[i][w] = filas; 
                }
                if(j - 1 >= ix + 1) filas++; 
                ix = j;
            }
        }

        for(int w = ix + 1; w <= n -1; w++){
            indiceFila[i][w] = filas; 
        }

        if(n - 1 >= ix + 1){
            filas++; 
        }
    }
}

void generarColumnas(){
    int iy;
    for(int j = 0; j < n; j++){
        iy = -1;
        for(int i = 0; i < n; i++){
            if(tablero[i][j] == 'X'){
                for(int w = iy + 1; w<= i - 1; w++){
                    matrizAdyacencia[indiceFila[w][j]][columnas] = 1; //crear arista en el grafo bipartito
                }

                if(i - 1 >= iy + 1){
                    columnas++; // incrementar contador de columnas
                } 

                iy = i;
            }
        }
        for(int w = iy + 1; w <= n - 1; w++){
            matrizAdyacencia[indiceFila[w][j]][columnas] = 1; //creaa arista en el grafo bipartito
        }

        if(n - 1 >= iy + 1){
            columnas++;
        } 
    }
}


void procesarEntrada(){
    string line;
    filas = columnas = 0; // inicializa contadores de filas y columnas

    getline(cin, line); // Ignora salto de linea

    memset(matrizAdyacencia, 0, sizeof(matrizAdyacencia)); 
    memset(indiceFila, -1, sizeof(indiceFila)); 


    for(int i =0; i < n; i++){
        cin.getline(tablero[i], MAXN); 
    }
}

int main(){
    while(cin >> n){
        int resultado; 
        procesarEntrada(); 
        generarFilas(); 
        generarColumnas(); 

        resultado = obtenerMaximoEmparejamiento(); 

        // imprimios el resultado
        cout << resultado << endl;
    }
    return 0;
}