/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
Este programa procesa varios casos de prueba dnde se aplican operaciones de volteo
(flip) en matrices cuadradaspara anillos concéntricos. Las operaciones que hace son
volteo de arriba a abajo, de izquierda a derecha, a traves de la diagonal principal
y la diagonal inversa. Despues imprime la matriz resultante.


1. Leer el numero de casos.
2. Para cada caso:
    - Lee la dimencion de la matriz y la matriz misma.
    - Calcular el numero de anillos de la matriz.
    - Para cada anillo, leer el numero de acciones a realizar.
    - Para cada acción, determinar el tipo de volteo a aplicar y lo hace.
3. Imprime la matriz resultante.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//voltea de arriba a abajo 
void voltearVertical(vector<vector<int>>& matriz, int anillo){
    int tam = matriz.size();
    int limite = tam-anillo - 1;

    for(int i=anillo;i<=limite;i++){
        swap(matriz[anillo][i], matriz[limite][i]);
    }

    for(int i=anillo+ 1; (i* 2) < tam-1;i++){
        int l;
        
        l = tam-i-1;
        swap(matriz[i][anillo],matriz[l][anillo]);
        swap(matriz[i][limite], matriz[l][limite]);
    }
}

//voltea de izquierda a derecha 
void voltearHorizontal(vector<vector<int>>& matriz, int anillo){
    int tam;
    int limite;

    tam = matriz.size();
    limite = tam-anillo -1;

    for(int i=anillo; i<=limite; i++){
        swap(matriz[i][anillo], matriz[i][limite]);
    }

    for(int i=anillo+1; (i*2)< tam- 1;i++){
        int l;
        l = tam - i-1;

        swap(matriz[anillo][i], matriz[anillo][l]);
        swap(matriz[limite][i], matriz[limite][l]);
    }
}

//voltea a traves de la diagonal principal
void voltearDiagonalPrincipal(vector<vector<int>>& matriz, int anillo){
    int tam = matriz.size();
    int limite = tam - anillo - 1;
    for (int i = anillo + 1; i <= limite; ++i) {
        swap(matriz[anillo][i], matriz[i][anillo]);
        swap(matriz[limite][i], matriz[i][limite]);
    }
}

//voltear a través de la diagonal inversa 
void voltearDiagonalInversa(vector<vector<int>>& matriz, int anillo){
    int tam;
    int limite;

    tam = matriz.size();
    limite = tam-anillo -1;

    for(int i=limite- 1, j=anillo +1; i>=anillo; i--,j++){
        swap(matriz[anillo][i], matriz[j][limite]);
        swap(matriz[j][anillo], matriz[limite][i]);
    }
}


void aplicarAccionDeVolteo(vector<vector<int>>& matriz, int anillo, int accion){
    if(accion==1){
        voltearVertical(matriz,anillo);
    } 
    else{
        if(accion == 2){
            voltearHorizontal(matriz, anillo);
        } 
        else{
            if(accion==3){
                voltearDiagonalPrincipal(matriz, anillo);
            } 
            else{
                if(accion==4){
                    voltearDiagonalInversa(matriz, anillo);
                }
            }
        }
    }
}

void procesarCasosDePrueba(){
    int T;
    cin >> T;

    while(T--){
        int dimension;
        cin >> dimension;

        vector<vector<int>> matriz(dimension, vector<int>(dimension));

        //lee la matriz
        for(int i=0; i < dimension;i++){
            for(int j=0; j < dimension;j++){
                cin >> matriz[i][j];
            }
        }

        int numeroAnillos=(dimension / 2)+(dimension % 2);
        
        for(int anillo=0; anillo< numeroAnillos;anillo++){
            int numeroAcciones;
            cin >> numeroAcciones;

            for(int j=0; j<numeroAcciones;j++){
                int accion;
                cin >> accion;

                aplicarAccionDeVolteo(matriz, anillo, accion);
            }
        }

        // Imprimir el resultado
        for(const auto& fila :matriz){
            for(int j= 0; j<dimension;j++){
                cout << fila[j] << (j+1 < dimension ? " " : "\n");
            }
        }
    }
}

int main(){

    procesarCasosDePrueba();

    return 0;
}