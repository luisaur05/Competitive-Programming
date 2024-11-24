/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa lee una serie de cadenas de digitos y busca el número 
primo mas grande en cada una de ellas.

1. Inicializa un vector de booleanos.
2. Lee una cadena de digitos de la entrada estandar.
3. Iniciaiza una variable par almacenar el numero primo mas grande encontrado.
4. Recorre la cadena para formar todos los posibles numeros a patir de cada posicion.
5. Verifica si el numero formado es primo y si es mayor que el maximo actual.
6. Imprime el numero primo mas grande encontrado en la cadena.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;

int main(){
    vector<bool> criba(100005, true);

    //encuentra numeros primos
    criba[0] = criba[1] = false;

    for(int i=2; i*i<=100000;i++){
        if(criba[i]){
            for(int j=i*i; j<=100000; j+=i){
                criba[j]=false;
            }
        }
    }

    //lee la entrada
    char entrada[1024];
    while(cin >> entrada){
        if(entrada[0]=='0' && entrada[1]=='\0'){
            break;
        }
        
        int longitud = strlen(entrada);
        int maximoPrimo = 0;

        for(int i=0; i<longitud;i++){
            for(int j=1; j<=6 && i+j<=longitud;j++){
                int numeroActual = 0;

                for(int k=i;k<i+j;k++){
                    numeroActual=numeroActual * 10+(entrada[k]-'0');
                }

                if(numeroActual<=100000 && criba[numeroActual]){
                    maximoPrimo = max(maximoPrimo, numeroActual);
                }
            }
        }

        cout << maximoPrimo << endl;
    }

    return 0;
}