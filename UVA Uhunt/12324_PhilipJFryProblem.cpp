/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa calcula el tiempo minimo para completr una serie de viajes daos los 
tiempos de descanso y las distancias.

1. Lee el numero de viajes.
2. Inicializa la tabla de memoisacion.
3. Calcula la distancia y el tiempo.
4. Utilia la funcion recursiva para determinar el tiempo minimo con o sin descanso.
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

const int MAX_VIAJES = 110;
const int MAX_TIEMPO = MAX_VIAJES * 10;
int tablaMemo[MAX_VIAJES][MAX_TIEMPO];

vector<int> distancias(MAX_VIAJES);
vector<int> tiempos(MAX_VIAJES);
int numeroViajes;

//calcula el tiempo minimo de viaje
int calcularTiempoMinimo(int viaje,int tiempoRestante){
    int tiempoConDescanso;
    int tiempoSinDescanso;

    //si se completan todos los viajes
    if(viaje==numeroViajes){
        return 0;
    }

    //si el resultado ya está computado
    if(tablaMemo[viaje][tiempoRestante]!=-1){
        return tablaMemo[viaje][tiempoRestante];
    }
    
    tiempoConDescanso = INT_MAX;

    //tiempo de descanso
    if(tiempoRestante>0){
        tiempoConDescanso =calcularTiempoMinimo(viaje+1,tiempoRestante + tiempos[viaje]-1)+distancias[viaje] /2;
    }

    tiempoSinDescanso= calcularTiempoMinimo(viaje+1,tiempoRestante+tiempos[viaje])+distancias[viaje];

    //min de ambas opciones
    int tiempoMinimo;
    tiempoMinimo =min(tiempoConDescanso,tiempoSinDescanso);

    tablaMemo[viaje][tiempoRestante]=tiempoMinimo;

    return tiempoMinimo;
}

int main(){
    while (true){
        cin >> numeroViajes;

        if(numeroViajes== 0){
            break;
        }

        //tabla de memoizacion
        memset(tablaMemo,-1,sizeof(tablaMemo));

        //distancias y tiempos de cada viaje
        for(int i=0;i< numeroViajes;i++){
            cin >> distancias[i] >>tiempos[i];
        }

        //tiempo minimo para los viajes
        cout << calcularTiempoMinimo(0,0) << endl;
    }

    return 0;
}