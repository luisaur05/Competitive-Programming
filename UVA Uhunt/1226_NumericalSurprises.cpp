/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
Este programa lee varios conjuntos de datos. Para cada conjunto, calcula el 
residuo cuando un número grande (representado como una cadena de dígitos) se 
divide por un divisor dado. Luego, imprime el residuo calculado.

1. Lee rl num fr casos de prueba.
2. Para cada caso:
    - Lee el divisor y el número grande como una cadena de digitos.
    - Encuentra el residuo del numero grande dividido por el divisor.
    - Imprime el residuo calculado.
*/


#include <iostream>
#include <string>

using namespace std;

//calcula el residuo de un número grande dividido por n
int calcularResiduo(const string& numeroGrande,int divisor){
    int residuo = 0;

    for(char digito:numeroGrande){
        residuo=residuo * 10+(digito-'0');
        residuo %= divisor;
    }

    return residuo;
}

int main() {
    int T;
    cin >> T;
    
    while(T--){
        int divisor;

        string numeroGrande;
        cin >> divisor >> numeroGrande;
        
        int resultado;
        
        resultado=calcularResiduo(numeroGrande, divisor);

        cout << resultado << endl;
    }
    
    
    return 0;
}