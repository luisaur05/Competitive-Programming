/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa calcula la suma de combinaciones de derangements para un n y un m que es la cantidad 
de elementos fijos.Produce la suma requerida utilizand derangements y coeficientes binomiales precalculados.

1. Pre calcula los derangements para todos los n desde 0 hasta 20.
2. Pre calcula los coeficientes binomiales para todos los n y r desde 0 hasta 20.
3. Lee los valores n y m de la entrada estandar.
4. Calcula la suma de las combinaciones de derangements para cada par n y m.
5. Imprime el resultado para cada par n y m.
*/

#include <iostream>
#include <vector>

using namespace std;

//calcula los nueros de derangements
vector<long long int> calcularDerangements(int maxN){
    vector<long long int> derangements(maxN + 1, 0);
    derangements[0] = 1; 
    derangements[1] = 0;

    if(maxN>=2){
        derangements[2]=1;
    }

    for(int i=3; i<=maxN;i++){
        //recurrencia para derangements
        derangements[i]=(i-1)* (derangements[i -1]+ derangements[i -2]);
    }

    return derangements;
}

//calcula los coeficientes binomiales
vector<vector<long long int>> calcularCoefBinomiales(int maxN){
    vector<vector<long long int>> coefBinomiales(maxN + 1, vector<long long int>(maxN + 1, 0));

    for(int n=0;n<=maxN;n++){
        coefBinomiales[n][0] = 1; 
        coefBinomiales[n][n] = 1; 
    }

    for(int n=1;n<=maxN;n++){
        for(int r= 1; r< n;r++){
            //recurrencia para coeficientes binomiales
            coefBinomiales[n][r]= coefBinomiales[n-1][r] + coefBinomiales[n -1][r - 1];
        }
    }

    return coefBinomiales;
}

int main() {
    int n;
    int m;
    const int MAX_N = 20;


    vector<long long int> derangements=calcularDerangements(MAX_N);
    vector<vector<long long int>> coefBinomiales= calcularCoefBinomiales(MAX_N);

    while(cin >> n >>m){
        long long int suma;
        suma = 0;

        for(int i=0;i<= m;i++){
            //calcula la suma de combinaciones de derangements
            suma+=coefBinomiales[n][i] *derangements[n -i];
        }

        cout <<suma << endl;
    }

    return 0;
}