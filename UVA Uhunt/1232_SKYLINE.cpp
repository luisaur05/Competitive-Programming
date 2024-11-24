/**
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
Ell programa resuelve el problema de encontrar el numero de superposiciones en un conjunto de edificios propuestos. 
Utiliza un Segment Tree con propagación lazy para manejar eficientemente las actualizaciones de intervalos y la 
consulta de alturas maximas. 

1. Lee el numero de conjuntos de datos.
2. Para cada conjunto de datos:
    - Lee el numero de edificios n en el conjunto actual.
    - Inicializa u nuevo arbol de segmentos.
    - Para cada edificio en l conjunto:
      - Lee las coordenadas del edificio: posicion izquierda l, posicion derecha r, y altura h.
      - Actualiza el abol de segmentos con la informacion del edificio.
      - Imprime la cantidad de superposiciones calculadas para el conjunto actual.
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define TAM_MAX 131073
#define INF_NEG -1

using namespace std;

struct ArbolSegmentos{
    int st[TAM_MAX << 2];
    int perezoso[TAM_MAX << 2];

    ArbolSegmentos(){
        memset(st, 0, sizeof(st));
        memset(perezoso, INF_NEG, sizeof(perezoso));
    }

    //propaga actualizaciones perezosas hacia abajo en el árbol
    void propagar(int nodo, int inicio, int fin){
        if(perezoso[nodo]!=INF_NEG){
            st[nodo]=max(st[nodo], perezoso[nodo]);
            if(inicio!=fin){ //no es un nodo hoja
                int izq=nodo <<1;
                int der=izq |1;

                perezoso[izq]= max(perezoso[izq], perezoso[nodo]);
                perezoso[der]= max(perezoso[der], perezoso[nodo]);
            }

            perezoso[nodo]=INF_NEG;
        }
    }

    //actualiza el arbol con la altura del edificio
    void actualizar(int nodo, int inicio, int fin, int l, int r, int valor, int &superposiciones){
        propagar(nodo, inicio, fin);
        if(inicio >r|| fin< l){
            return;
        }
        if(inicio>=l && fin<=r){
            perezoso[nodo] = max(perezoso[nodo], valor);
            propagar(nodo, inicio, fin);

            if(st[nodo]<=valor){
                if(inicio==fin){
                    superposiciones++; //aumenta la cantidad de superposiciones si estamos en un nodo hoja
                } 
                else{
                    int medio; 
                    int izq; 
                    int der;

                    medio =(inicio + fin)>> 1;
                    izq=nodo << 1;
                    der=izq | 1;

                    actualizar(izq, inicio, medio, l, r, valor, superposiciones);
                    actualizar(der, medio + 1, fin, l, r, valor, superposiciones);

                    st[nodo]=min(st[izq], st[der]);
                }
            }
            return;
        }
        int medio;
        int izq;
        int der;

        medio =(inicio + fin)>> 1;
        izq=nodo << 1;
        der=izq | 1;

        actualizar(izq, inicio, medio, l, r, valor, superposiciones);
        actualizar(der, medio + 1, fin, l, r, valor, superposiciones);

        st[nodo] = min(st[izq], st[der]);
    }
};

int main() {
    int T;
    cin >> T; //numero de conjuntos de datos

    while(T--){
        int n;
        int superposiciones;

        cin >> n; //lee el numero de edificios en el conjunto actual
        superposiciones=0;

        ArbolSegmentos arbol;
        for(int i=0; i<n;i++){
            int l;
            int r;
            int h;

            cin >> l >> r >> h;
            r--; // Ajustar r para ser inclusivo en el segmento

            arbol.actualizar(1, 1, TAM_MAX - 1, l, r, h, superposiciones); //actualiza el arbol para el edificio actual
        }

        cout << superposiciones << "\n"; 
    }

    return 0;
}