/*
LUIS ANGEL ARREDONDO URIBE

---------DESCRIPCIÓN--------
El programa calcula el numero total de personas en un arbol genealgico pra varios casos de prueba
y lo hace excluyendo los descendientes redundantes.

1. Lee el numero de casos de prueba.
2. Para cada caso:
    - Lee los valores de N,A y B.
    - Calcula la profundidad de los nodos A yB.
    - Calcula la población total del árbol hasta N generaciones.
    - Calcula laredundancia de los nodos A y B.
    - Resta la redundancia min de la población total
    - Imprime el resultado
*/

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;


void procesarCaso(){
    int generaciones;
    int hermanoA;
    int hermanoB;

    cin >> generaciones >> hermanoA >> hermanoB;

    int profundidadA=0;
    int profundidadB= 0;
    int tempA=hermanoA;
    int tempB =hermanoB;

    //profundidad de hermano A
    while(tempA>1){
        if(tempA% 2 !=0){
            tempA--;
        }

        tempA /= 2;

        profundidadA++;
    }

    //profundidad de hermano B
    while(tempB>1){
        if(tempB% 2 != 0){
            tempB--;
        }

        tempB /= 2;

        profundidadB++;
    }

    long long poblacionTotal;
    long long redundanciaNodo1;
    long long redundanciaNodo2;

    poblacionTotal =(1LL << generaciones)-1;
    redundanciaNodo1 =(1LL << (generaciones-profundidadA)) - 2;
    redundanciaNodo2 =(1LL << (generaciones-profundidadB)) - 2;

    cout << poblacionTotal - min(redundanciaNodo1, redundanciaNodo2) << endl;
}

int main() {
    int T;
    cin >> T;

    for(int i=0;i<T;i++){
        procesarCaso();
    }

    return 0;
}