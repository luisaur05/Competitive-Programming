/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa recibe N enteros como entrada y calcula cuantos numeros entre 1 
y N tienen un valor par de la función sigma.El resultado para cda numero se 
imprime en una linea separada.

1. Lee el numero de la entrada.
2. Calcula cuantos numeros entre 1 y N tienen un valor par de la funcion sigma.
3. Imprime el resultado.
*/

#include <iostream>
#include <cmath>

using namespace std;

//calcular la raiz cuadrada 
long long calcularRaizCuadrada(long long x){
    return static_cast<long long>(sqrt(x));
}

//cuenta los factores que contriuyen al valor pr de la funcion sigma
long long contarFactores(long long numero){
    long long totalFactores = calcularRaizCuadrada(numero);
    totalFactores += calcularRaizCuadrada(numero / 2);
    return totalFactores;
}

int main(){
    long long numeroEntrada;

    while(cin >>numeroEntrada&&numeroEntrada!=0){
        //calcula el resultado restando los factores al numero de entrada
        long long resultado;

        resultado = numeroEntrada-contarFactores(numeroEntrada);

        cout << resultado << "\n";
        
    }

    return 0;
}