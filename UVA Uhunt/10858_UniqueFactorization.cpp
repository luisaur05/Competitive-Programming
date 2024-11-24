/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El progrma recibe enteros positivos N y encuentra todas las maneras únicas de factorizar N
usando factores mayore que 1 y al menos dos números en cada factorizacion e imprime el numero de
factorizciones unicas y cada factorizacion en orden no decreciente.

1. Lee multiples enteros hasta encontrar un 0. 
2. Busca recursivamente todas las combinaciones u¿unicas de factores para un numero dado comenando desde un factor minimo.
3. Itera desde el factorMinimo hasta la raiz cuadrada del numero.
   - Si el nmero es divisible por el factor actual se divide el numero por el factor y se buscan combinaciones recursvas para el cociente.
   - Las combinacioes se almaenan y el factor actual se añade a cada combinacion.
3. Imprime el numero de combinaciones seguido por cada combincion en orden no decrecient.
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> obtenerCombinacionesFactores(int numero, int factorMinimo){
    vector<vector<int>> combinaciones;

    for(int factor=factorMinimo; factor<= sqrt(numero); factor++){
        if(numero % factor ==0){
            //busca combinaciones recursivamente para el cociente
            vector<vector<int>> subCombinaciones = obtenerCombinacionesFactores(numero/factor,factor);
            for(auto& combinacion :subCombinaciones){
                combinacion.push_back(factor);
                combinaciones.push_back(combinacion);
            }
            // Agregar la pareja directa
            combinaciones.push_back({numero/factor, factor});
        }
    }
    return combinaciones;
}

//imprime combinaciones de factores
void imprimirCombinacionesFactores(const vector<vector<int>>& combinaciones){
    cout << combinaciones.size() << endl;
    for(const auto& combinacion :combinaciones){
        for(auto it= combinacion.rbegin(); it!= combinacion.rend(); it++){
            cout << *it;
            if (it+ 1 !=combinacion.rend()){
                cout << " ";
            }
        }
        cout << endl;
    }
}

void procesarEntrada(){
    int numero;
    while(cin>> numero && numero !=0){
        vector<vector<int>> combinacionesFactores;
        combinacionesFactores = obtenerCombinacionesFactores(numero, 2);

        imprimirCombinacionesFactores(combinacionesFactores);
    }
}

int main() {

    procesarEntrada();

    return 0;
}