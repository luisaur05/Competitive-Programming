/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa calcula un valor v basado en dos números enteros m y x, y lo imprime. 
Si v no existe, se imprime Not found.

1. Lee la inversion m y la tasa x de cada linea de entrada.
2. Ve si se alcanzo el final de la entrada si m y x son ambos cero.
3. Calcula el ingreso basado en la inversión y la tasa.
4. Si la tasa es 100 imprime Not found.
5. Si la tasa no es 100 calcula e imprme el ingreso.
*/

#include <iostream>

using namespace std;

long long calcularIngreso(long long inversion,int tasa){
    long long ingreso;
    
    ingreso=(inversion-1)*100 / (100-tasa);
    
    if((inversion-1) * 100 % (100 - tasa)==0){
        ingreso-=1;
    }

    return ingreso;
}

void calcularYImprimirIngreso(long long capital, int tasa){
    long long ingreso=0;

    //si la tasa es 100 no se puede calcular el ingreso
    if(tasa!=100){
        ingreso=calcularIngreso(capital, tasa);
    }
    
    if(ingreso<capital){
        cout << "Not found" << endl;
    } 
    else{
        cout << ingreso << endl;
    }
}

int main(){
    long long inversion;
    int tasa;

    while(cin >> inversion >> tasa){

        if(inversion==0 && tasa==0){
            break;
        }
        
        calcularYImprimirIngreso(inversion,tasa);
    }
    return 0;
}