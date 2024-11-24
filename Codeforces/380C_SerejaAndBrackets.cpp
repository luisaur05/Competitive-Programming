/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa resuelve consultas sobre un conjunto de paréntesis. Primero, construye un Arbol de 
segmentos que contiene informacion sobre el nuumero de parentesis abiertos y cerrados en diferentes 
rangos de la cadena de entrada.

1.  El programa construye un arbol de segmentos a partir de la cadena de entrada. 
    - Cada nodo del árbol contiene información sobre el número de paréntesis abiertos 
    y cerrados en un rango específico de la cadena.
2. Para cada consulta, el programa uiliza el árbol de segmentos para determinar la cantidad 
mínima de operaciones necesarias para equilibrar los paretesis dentro del rango dado.
    - Lo hace mediante un recorrido descendente en el arbol de segmentos donde se combinan 
    los resultados a los subrangos que cubren la consulta.
3. Imprime la respuesta de cada consulta en el orden de entrada.
*/


#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <bitset>
#include <cstring>


using namespace std;

int len; 
const int MAX_LEN = 1e6 + 7;

struct Nodo{
    int res = 0; // Respuesta de la consulta
    int abre = 0; // Contador de parentesis abiertos
    int cierra = 0; // Contador de parentesis cerrados
    Nodo(){}
};

Nodo arbol[2 * MAX_LEN]; // arbol de segmentos

int consulta(int izq, int der){
    Nodo nodoIzq, nodoDer; 
    for(izq += len, der += len; izq < der; izq >>= 1, der >>= 1){
        // Si el indice izquierdo es impar, procesar el nodo y avanzar al siguiente 
        if(izq & 1){
            int minimo = min(nodoIzq.abre, arbol[izq].cierra);
            nodoIzq.res += arbol[izq].res + (2 * minimo);
            nodoIzq.abre += arbol[izq].abre - minimo;
            nodoIzq.cierra += arbol[izq].cierra - minimo;
            izq++;
        }

        // Si el indice derecho es impar, procesar el nodo y retroceder al anterior índice
        if(der & 1){
            der--;
            int minimo = min(arbol[der].abre, nodoDer.cierra);
            nodoDer.res += arbol[der].res + (2 * minimo);
            nodoDer.abre += arbol[der].abre - minimo;
            nodoDer.cierra += arbol[der].cierra - minimo;
        }

    }

    // Calcular la respuesta combinando la informacioon de izquierda y derecha
    int minimo = min(nodoIzq.abre, nodoDer.cierra);

    Nodo nodoMerge;

    nodoMerge.res = nodoIzq.res + nodoDer.res + (2 * minimo);
    nodoMerge.abre = nodoIzq.abre + nodoDer.abre - minimo;
    nodoMerge.cierra = nodoIzq.cierra + nodoDer.cierra - minimo;

    return nodoMerge.res;
}

int main(){
    string str;
    cin >> str; 
    len = str.length(); 

    for(int i = 0; i < len; i++){
        arbol[i +len].res = 0;
        arbol[i +len].abre = (str[i] == '(');
        arbol[i +len].cierra = (str[i] == ')');
    }
    
    for(int i =len - 1; i> 0;i--){
        int minimo = min(arbol[i << 1].abre, arbol[i << 1 | 1].cierra);

        arbol[i].res = arbol[i << 1].res + arbol[i << 1 | 1].res + (2 * minimo);
        arbol[i].abre = arbol[i << 1].abre + arbol[i << 1 | 1].abre - minimo;
        arbol[i].cierra = arbol[i << 1].cierra + arbol[i << 1 | 1].cierra - minimo;
    }

    // Realizar las consultas especificadas en la entrada
    int consultas;
    cin >> consultas;

    while(consultas--){
        int izq, der;
        cin >> izq >> der;
        izq--, der--; // que los indices para que comiencen en cero,
        cout << consulta(izq, der + 1) << endl; 
    }

    return 0;
}