/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa resulve consultas sobre si es posible formar un palindromo con las letras de los vertices de un arbol

1. Lee la entrada que contiene la descripccion del arbol y las consultas
2. Calcula la profundidad de cada vertice del arbol y se encuentra el hijo pesdo de cada vertice. 
3. Realiza un recorrido DFS del rbol para procesar las consultas 
    - Dentro del BFS se actualizan las frecuencias de las letras de los vértices y se determina si 
    es posible formar un palindromo on estas letras
4. Imprime el resultado de cada consulta
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 500005;
const int maxe = 500005;

bool respuesta[maxn];
int total, hijo[maxe], siguiente[maxe], enlace[maxn];
int n, q, s[maxn], num[maxn][26];
int profundidad[maxn], H_hijo[maxn], peso[maxn];
bool xHijo[maxn];

struct datos{
    int dep, id;
    datos(){}
    datos(int _x, int _y):dep(_x),id(_y){}
};

vector<datos> V[maxn];

// agregar arista al atbol
void agregar(int x, int y){
    hijo[++total]=y; 
    siguiente[total]= enlace[x]; 
    enlace[x]=total; // actualiza el enlace del nodo x al nodo y
}

void obtenerHijoPesado(int x){
    H_hijo[x] = 0; 
    peso[x] = 1; 

    for(int j = enlace[x]; j; j = siguiente[j]){
        profundidad[hijo[j]] = profundidad[x] + 1; 

        obtenerHijoPesado(hijo[j]); 
        peso[x] += peso[hijo[j]];

        if(!H_hijo[x]||peso[H_hijo[x]]<peso[hijo[j]]){ 
            H_hijo[x] = hijo[j]; 
        }
    }
}

// actualizar las frecuencias al recorrer el árbol
void cambiar(int x, int w){
    num[profundidad[x]][s[x]] +=w; 
    for(int j = enlace[x]; j; j=siguiente[j]){ 
        if(!xHijo[hijo[j]]){ 
            cambiar(hijo[j], w); 
        }
    }
}

// procesa ls consultas y determin si se puede formar un palíndromo
void dfs(int x, bool mantener){
    for(int j = enlace[x]; j; j = siguiente[j]){ 
        if(hijo[j] != H_hijo[x]){ 
            dfs(hijo[j],0); // recursiva para procesar el hijo actual
        }
    }

    if(H_hijo[x]){ 
        dfs(H_hijo[x],1); 
        xHijo[H_hijo[x]] = 1; // marca el hijo pesado como visitado
    }

    cambiar(x, 1); // actualiza frecuencias del subárbol con raíz en x
    xHijo[H_hijo[x]] = 0; 

    for(int i=0; i < V[x].size(); i++){ 
        int total = 0;

        for(int j=1; j <=26; j++){ 
            if(num[V[x][i].dep][j]&1){ 
                total++; 
            }
        }

        respuesta[V[x][i].id] = (total<=1); 
    }

    if(!mantener){ 
        cambiar(x,-1); 
    }

}

void impri_resp(){
    for(int i = 1; i<= q;i++){ 
        cout <<(respuesta[i] ? "Yes" : "No") << endl; // Se imprime el resultado de la consulta como se pide
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    //recibe la estructura del árbol
    for(int i=2, fa; i <= n; i++){
        cin >> fa;
        agregar(fa, i);
    }

    for(int i=1; i <=n; i++){
        char ch;
        cin >> ch;
        s[i] = ch- 'a' + 1;
    }

    // consultas
    for(int i=1; i <= q; i++){
        int x;
        int y;
        cin >> x >> y;

        V[x].push_back(datos(y, i));

    }

    //inicializaa profundidad y calculo del hjo pesado
    profundidad[1]= 1;
    obtenerHijoPesado(1);

    // Procesmiento de las consultas
    dfs(1,0);
    
    impri_resp();

    return 0;
}