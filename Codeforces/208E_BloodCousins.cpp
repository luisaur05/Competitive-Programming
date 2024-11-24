/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa resuelve consultas sobre relaciones familiares en un abol genealogico.

1. Lee la entrada (número de personas en el árbol) seguido de los padres de cada persona.
2. Inicializa la tabla de elevación para la búsqueda binaria y calcula la profundidad de cada nodo en el árbol.
3. Lee las consultas de relaciones familiares, que consisten en pares de números que representan una persona y su ancestro deseado.
4. Resuelve cada consulta y almacena los resultados.
5. Imprime los resultados de las consultas.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e5 + 5;

int n, m, f[N][20], lg[N], siz[N], dep[N], sum[N], hijo[N], len[N], be[N];
bool vis[N];
vector<int> vec[N], ans[N], q[N];

void iniTablaDeElevacion(){
    // inicializatabla de elevacion para busqueda binaria
    for(int i =1; i <= 18;i++){
        for(int j= 1; j <= n; ++j){
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
    }

    // logaritmos para la tabla de elevacion
    for(int i = 2; i <= n; i++){
        lg[i] = lg[i >> 1] + 1;
    }
}

void dfs(int u){
    //recorrre en profundidad del arbol
    siz[u] = 1;
    for(int v : vec[u]){
        dep[v] = dep[u] + 1;
        dfs(v);
        siz[u] += siz[v];

        if(siz[hijo[u]] < siz[v]){
            hijo[u] = v;
        }
    }
}

void calcular(int u, int k){
    sum[dep[u]] += k;

    for(int v : vec[u]){
        if(vis[v]){ 
            continue;
        }

        calcular(v, k);
    }
}

void resolver(int u, int fa, int keep){
    // soluciona ls consultas recursivas
    for(int v :vec[u]){
        if(v==hijo[u]){
            continue;
        }

        resolver(v, u, 0);
    }

    if(hijo[u]){
        resolver(hijo[u], u, 1);
        vis[hijo[u]] = 1;
    }

    calcular(u, 1);

    if(hijo[u]){
        vis[hijo[u]] = 0;
    }

    for(int i=0; i < q[u].size(); i++){
        ans[u].push_back(sum[q[u][i]]);
    }

    if(!keep){
        calcular(u, -1);
    }
}

void leerConsultas(){
    // Lectura de consultas de relaciones familiares
    cin >> m;
    for(int i = 1; i <= m; i++){
        int x;
        int y;

        cin >> x >> y;
        if(y>=dep[x]){
            be[i] = 0;
        } 
        else{
            int z = dep[x];
            while(y){
                x = f[x][lg[y]];
                y -= (1 << lg[y]);
            }

            q[x].push_back(z);
            be[i] = x;
        }
    }
}

void imprimirResultados(){
    for(int i=1; i <= m;i++){
        if(be[i]){
            cout << ans[be[i]][len[be[i]]++] - 1 << " "; //eexcluir el propio nodo
        } 
        else{
            cout << "0 ";
        }
    }
    cout << endl;
}

int main(){
    cin >> n;

    for(int i=1; i<=n;i++){
        int padre;
        cin >> padre;
        f[i][0] = padre;
        vec[padre].push_back(i);
    }

    iniTablaDeElevacion(); // Inicialización de la tabla de elevación
    dfs(0); 
    leerConsultas(); 

    resolver(0, -1, 1); // solu de de consultas
    imprimirResultados(); 
    return 0;
}