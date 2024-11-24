/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
Elprograma calcula el costo total basado en una secuencia generada de numeros enteros.
El costo total se calcula como la suma de las diferencias entre numeros consecutivos 
multiplicadas por su posicion relativa.

1. Lee el numero de casos de pruba.
2. Genera una secuencia de numeros.
3. Ordea la secuencia.
4. Calcula el costo total basado en las diferencias entre numeros consecutivos.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000007;

//genera la secuencia de numeros
vector<long long> generarSecuencia(int K,int C,int N,long long inicial){
    vector<long long> numeros(N);

    numeros[0] = inicial;

    for(int i=1;i<N;i++){
        numeros[i]=(K * numeros[i-1]+C) % MOD;
    }

    return numeros;
}

//calcular el costo total
long long calcularCostoTotal(const vector<long long>& numeros){
    long long diffAnterior =0, total=0;

    for(int i=1;i<numeros.size();i++){
        diffAnterior+=(numeros[i]-numeros[i - 1]) *i;
        total += diffAnterior;
    }

    return total;
}

int main(){
    int T;  //casos de prueba

    cin >> T;

    for(int t=1;t<=T;t++){
        int K;
        int C;
        int N;
        long long inicial;

        cin >> K >> C >> N >> inicial;

        //secuencia de numeros
        vector<long long> numeros=generarSecuencia(K,C,N,inicial);

        //ordena la secuencia
        sort(numeros.begin(),numeros.end());

        //calcula el costo total
        long long total;
        total = calcularCostoTotal(numeros);

        //imprime el resultado
        cout << "Case " << t << ": "<<total << '\n';
    }

    return 0;
}