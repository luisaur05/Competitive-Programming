/*
LUIS ANGEL ARREDONDO URIBE

---------DESCRIPCION--------
El programa calcula el numero minimo de antenas necesarias para cubrir todos los puntos de interes en 
diferentes escenarios en Suecia. El progama usa coincidencia bipartita para encontrar la coincidencia 
maxima entre los puntos de interes que luego se resta del nmero total de puntos para determinar el 
numero minim.

1. Lee el numero de escenarios.
2. Para cada escenario:
- Lee las dimensiones de la cuadricula.
- Lee la cuadricuula e inicializa listas de adyacencia.
- Inicializa BFS desde cada punto de interes para encontrar los puntos alcanzables.
- Encuentra la coincidencia maxima entre los puntos de interes.
- Calcular el numero minimo restando la coincidencia maxima deln total de puntos de interes.
- Imprime  el resultado.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <cstring>

using namespace std;

const int MAXN = 50;
const int MAXV = 400;
const int BLANCO = 0;
const int GRIS = 1;
const int NEGRO = 2;

vector<int> listaAdyacencia[MAXV];
bitset<MAXV> visitado;
char tablero[MAXN][15];
int filas, columnas, totalNodos;
int indiceCelda[MAXN][15], colorCelda[MAXN][15];
int dirFila[] = {1, 0, -1, 0};
int dirCol[] = {0, 1, 0, -1};
int Nodo_mat[MAXV];

// encuntra celdas alcanzables desde un punto de interes
void inicializarBFS(int filaInicial, int colInicial){
    queue<int> colaCeldas;
    colorCelda[filaInicial][colInicial] = GRIS;
    colaCeldas.push(filaInicial);
    colaCeldas.push(colInicial);

    while(!colaCeldas.empty()){
        int deFila = colaCeldas.front(); colaCeldas.pop();
        int deCol = colaCeldas.front(); colaCeldas.pop();

        for(int direccion = 0; direccion < 4; direccion++){
            int aFila = deFila + dirFila[direccion];
            int aCol = deCol + dirCol[direccion];

            // Ve si la celda adyacente es valida y contiene un punto 
            if(aFila >= 0 && aFila < filas && aCol >= 0 && aCol < columnas && tablero[aFila][aCol] == '*'){
                // Si la celda adyacente no ha sido visitada se marca como visitada y se agrega a la cola
                if(colorCelda[aFila][aCol] == BLANCO){
                    colaCeldas.push(aFila);
                    colaCeldas.push(aCol);
                }

                // Conecta la celda actual con la celda adyacente en la lista de adyacencia
                if(colorCelda[deFila][deCol] == GRIS){
                    colorCelda[aFila][aCol] = NEGRO;
                    listaAdyacencia[indiceCelda[deFila][deCol]].push_back(indiceCelda[aFila][aCol]);
                } 

                else{
                    colorCelda[aFila][aCol] = GRIS;
                    listaAdyacencia[indiceCelda[aFila][aCol]].push_back(indiceCelda[deFila][deCol]);
                }
            }
        }
    }
}

// encuentra un camino aumentante usando DFS en el rafo bipartito
bool encontrarEmpar(int nodo){
    visitado.set(nodo);

    for(int nodoAdyacente : listaAdyacencia[nodo]){
        if(Nodo_mat[nodoAdyacente] == -1 || (!visitado.test(Nodo_mat[nodoAdyacente]) && encontrarEmpar(Nodo_mat[nodoAdyacente]))){
            Nodo_mat[nodoAdyacente] = nodo;
            return true;
        }
    }

    return false;
}

void procesarCaso(){
    totalNodos = 0;
    string line;

    cin >> filas >> columnas;

    getline(cin, line); // Ignora salto de linea 

    // Lee la cuadricula 
    for(int i = 0; i < filas; i++){
        cin.getline(tablero[i], 15);
    }

    // Asigna indices a las celdas que contienen puntos de interes
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(tablero[i][j] == '*'){
                indiceCelda[i][j] = totalNodos++;
            }
        }
    }

    // Usa el arreglo de colores para BFS
    memset(colorCelda, 0, sizeof(colorCelda));

    // Inicializa las listas de adyacencia 
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(tablero[i][j] == '*' && colorCelda[i][j] == BLANCO){
                inicializarBFS(i, j);
            }
        }
    }

    int totalEstrellas = 0;
    int maxEmparejamientos = 0;

    memset(Nodo_mat, -1, sizeof(int) * totalNodos);

    // Itera sobre cada celda que contiene un punto de interes
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(tablero[i][j] == '*'){
                totalEstrellas++;
                // Si la celda es alcanzable encuentra un camino aumentante usando DFS
                if(colorCelda[i][j] == GRIS){
                    visitado.reset();
                    if(encontrarEmpar(indiceCelda[i][j])){
                        maxEmparejamientos++;
                    }
                }
            }
        }
    }

    
    cout << (totalEstrellas - maxEmparejamientos) << endl;

    // limpiar
    for(int i = 0; i < totalNodos; i++){
        listaAdyacencia[i].clear();
    }
}

int main(){
    int T;
    cin >> T;

    while(T--){
        procesarCaso();
    }

    return 0;
}
