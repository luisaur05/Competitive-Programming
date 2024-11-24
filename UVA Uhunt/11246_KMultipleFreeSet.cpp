/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa calcula el tamaño del subconjunto más grande de numeros del 1 al n 
que no son mltiplos de k. Itera atraves de los numros del 1 al n, contando aquellos 
que no son divisibles por k. El resultado es el tamaño de este subconjunto.

1. Lee el numero de casos.
2. Para cada caso:
   - Lee los valores de n y k.
   - Calcula el tamaño del subconjnto de números del 1 al n que no son multiplos de k.
   - Imprime el tamaño del subconjunto.
*/

#include <iostream>

using namespace std;

//calcula el tamaño del subconjunto libre de multiplos de k
int calcularTamanoSubconjunto(int n, int k){
    int tamano = 0;

    //recorre los numeros del 1 al n
    for(long long powK=1; powK<= n; powK *= k*k){
        //calcula cuántos números son divisibles por k
        int M;

        M = n / powK;
        //tamaño del subconjunto la cantidad de numeros no divisibles por k
        tamano += M-M / k;
    }

    return tamano;
}

int main(){
    int T;
    cin >> T;

    while(T--){
        int n;
        int k;

        cin >> n >> k;

        //calcula el tamaño del subconjunto
        int tamanoSubconjunto = calcularTamanoSubconjunto(n,k);
        
        cout << tamanoSubconjunto << endl;
    }

    return 0;
}