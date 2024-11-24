/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa calcula la cantidad de cadenas validas de longitud n que contienen transiciones de 
H consecutivas. Usa programacion dinamica para realizar este calculo. El programa lee 
multiples casos de prueba desde la entrda estandar hasta el final. 

1. Inicializa los arreglos dp y sumas con valores base para la programacion dinamica.
2. Actualiza los arreglos dp ysumas atraves de transiciones.
3. Calcula las sumas acumuladas en sumas para todas las longitudes y colas posibles.
4. Lee los valores de lonitud y colas desde la entrada estandar.
5. Imprime el resultado calculado para cada par de longitud y colas.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 105;
const int MAX_DIGITOS = 40;

short dp[MAX_N][MAX_N][MAX_N][MAX_DIGITOS];
short sumas[MAX_N][MAX_N][MAX_DIGITOS];

//actualiz el arreglo dp
void actualizarDP(int longitud,int maxCola,int cola,const short valor[MAX_DIGITOS]){
    for(int d=0; d<MAX_DIGITOS; d++){
        dp[longitud][maxCola][cola][d] += valor[d];

        if(dp[longitud][maxCola][cola][d]>=10){
            dp[longitud][maxCola][cola][d + 1]+=dp[longitud][maxCola][cola][d]/10;
            dp[longitud][maxCola][cola][d] %=10;
        }
    }
}

//actualizar el arreglo de sumas
void actualizarSumas(int longitud,int colas,const short valor[MAX_DIGITOS]){
    for(int d=0;d<MAX_DIGITOS;d++){
        sumas[longitud][colas][d]+=valor[d];

        if(sumas[longitud][colas][d]>=10){
            sumas[longitud][colas][d+1]+=sumas[longitud][colas][d]/10;
            sumas[longitud][colas][d]%= 10;
        }
    }
}

void calcular(){
    dp[0][0][0][0]=1;

    for(int longitud=0; longitud<=100;longitud++){

        for(int maxCola=0;maxCola<= longitud;maxCola++){

            for(int cola=0; cola<=longitud;cola++){

                //añande el valor actual de dp a sumas
                actualizarSumas(longitud,maxCola,dp[longitud][maxCola][cola]);

                //añade H
                actualizarDP(longitud+1,max(maxCola,cola+1),cola+1,dp[longitud][maxCola][cola]);

                //añade T
                actualizarDP(longitud+1,maxCola,0,dp[longitud][maxCola][cola]);
            }
        }
    }

    for(int longitud=0;longitud<=100;longitud++){

        for(int colas=longitud;colas>=0;colas--){

            for(int d=0;d<MAX_DIGITOS;d++){

                sumas[longitud][colas][d] += sumas[longitud][colas + 1][d];

                if(sumas[longitud][colas][d]>=10){
                    sumas[longitud][colas][d+1]+=sumas[longitud][colas][d]/10;
                    sumas[longitud][colas][d]%=10;
                }
            }
        }
    }
}

void imprimirResultado(int longitud,int colas){
    int d;
    d=MAX_DIGITOS-1;
    while(d>0 && sumas[longitud][colas][d]==0){
        d--;
    }

    while(d>=0){
        cout << sumas[longitud][colas][d];
        
        d--;
    }

    cout<<endl;
}

int main(){
    int longitud;
    int colas;

    calcular();

    while(cin >>longitud>> colas){
        imprimirResultado(longitud, colas);
    }

    return 0;
}