/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa convierte un numero dado en una representacion de Zeckendorf, que es una forma 
de representar un numero como la suma de numeros de Fibonacci sin usar dos numeros 
consecutivos de Fibonacci.

1. Genera los primeros 45 numeros de Fibonacci, 
2. Cada numero de entrada N: 
    - Encuentra el mayor numero de Fibonacci menor o igual a N.
    - Si el numero de Fibonacci es menor o igual a N se agrega un 1 a la representacion de Zeckendorf 
      y se resta el numero de Fibonacci de N.
    - Si el numero de Fibonacci es mayor a N se agrega un 0 a la representacion de Zeckendorf.
*/

#include <iostream>
#include <vector>

using namespace std;

//generar los primeros 45 numeros de Fibonacci
vector<int> generarFibonacci(int limite){
    vector<int> fibonacci(limite);

    fibonacci[0] = 1;
    fibonacci[1] = 2;

    for(int i=2;i<limite;i++){
        fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
    }

    return fibonacci;
}

//convierte un numero a su representación de Zeckendorf
string representarZeckendorf(int numero,const vector<int>& fibonacci){
    string representacion;
    int indice;

    indice = fibonacci.size()-1;

    while(fibonacci[indice]>numero){
        indice--;
    }

    for(; indice>=0;indice--){
        if(fibonacci[indice]<=numero){
            representacion+= '1';
            numero-=fibonacci[indice];
        } 
        else{
            representacion+= '0';
        }
    }

    return representacion;
}

int main() {
    vector<int> fibonacci;
    int casos;

    fibonacci= generarFibonacci(45);
    cin >> casos;

    while(casos--){
        int numero;
        cin >> numero;

        string resultado=representarZeckendorf(numero, fibonacci);
        cout <<resultado << "\n";
    }

    return 0;
}