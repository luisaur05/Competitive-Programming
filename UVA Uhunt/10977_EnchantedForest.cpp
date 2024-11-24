/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPTION--------
El prorama resuelve el problema del bosque encantado.Encuentra el camino ms corto
desde la esquina superior izquierda hasta la esquina inferior derecha evitando 
obsaculos y areas afectadas.

1. Lee el nnmero de filas y columna.
2. Lee las coordenadas de las celdas que son obstaculos.
3. Lee las coordenadas y radios de las areas afectadas.
4. Usa BFS para encontrar el camino mas corto desde la celda inicial hasta la celda final.
5. Imprime la longitud del camino mas corto o indica que es imposible si no.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//celda
struct Celda{
    int x;
	int y;
	int dist;

    Celda(int x, int y, int dist) :x(x),y(y),dist(dist) {}
};

int filas;
int columnas;

//vesi una celda está dentro de los límites y es accesible
bool esValida(int x, int y, const vector<vector<int>>& bosque){
    return x>=0 && x<filas && y>=0 && y< columnas && bosque[x][y]==0;
}

//usa BFS apara encontrar el camino más corto
int buscarCaminoMasCorto(vector<vector<int>>& bosque){
    if (bosque[0][0]==-1){ 
		return -1;
	}

    queue<Celda> cola;

    cola.push(Celda(0, 0, 1));
    bosque[0][0]=1;

    int movX[]={-1, 0, 1, 0};
    int movY[]={0, -1, 0, 1};

    while(!cola.empty()) {
        Celda actual=cola.front();
        cola.pop();

        for (int i=0; i<4; i++){
            int nuevoX;
            int nuevoY;

			nuevoX = actual.x + movX[i];
			nuevoY = actual.y + movY[i];

            if(esValida(nuevoX,nuevoY,bosque)){
                bosque[nuevoX][nuevoY]=actual.dist+1;
                cola.push(Celda(nuevoX, nuevoY, actual.dist + 1));

                if (nuevoX==filas-1 && nuevoY==columnas-1){
                    return bosque[nuevoX][nuevoY];
                }
            }
        }
    }

    return -1;
}

void procesarBosque(){
    int obstaculos;
    cin >> obstaculos;

    vector<vector<int>> bosque(filas,vector<int>(columnas, 0));

    for (int i=0;i<obstaculos;i++){
        int x;
		int y;
        cin >> x >> y;
        bosque[--x][--y] = -1;
    }

    int circulosMagicos;
    cin >> circulosMagicos;

    for(int i=0;i<circulosMagicos;i++){
        int x;
		int y;
		int radio;

        cin >> x >> y >> radio;
        --x, --y;

        for(int dx=-radio; dx<=radio;dx++){
            for(int dy=-radio;dy<=radio;dy++){
                if(dx * dx + dy * dy <= radio * radio){
                    int nuevoX;
                    int nuevoY;

					nuevoX = x + dx;
					nuevoY = y + dy;

                    if(nuevoX>=0 && nuevoX<filas && nuevoY>=0 && nuevoY<columnas){
                        bosque[nuevoX][nuevoY]=-1;
                    }
                }
            }
        }
    }

    int resultado =buscarCaminoMasCorto(bosque);
    if(resultado==-1){
        cout << "Impossible." << endl;
    } 
	else{
        cout << resultado-1 << endl;
    }
}

int main(){

    while(cin>>filas>>columnas,filas){
        procesarBosque();
    }

    return 0;
}