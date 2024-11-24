/* 
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCION--------
Se tiene que encontrar los dos planes de conexion mas baratos entre las escuelas de una ciudad,
de manera que todas las escuelas esten conectadas a una estacion de energia y entre si.

1. Lee el numero de casos de prueba.
2. En acda caso:
   - Lee el numero de escuelas y el numero de posibles conexiones entre ellas.
   - Lee las conexiones entre las escuelas y su costo.
   - Ordena las conexiones por su costo de manera ascendente.
   - Usa Kruskal para encontrar el primer plan de conexion mas barato.
   - Para cada conexion en el primer plan, encuentra el segundo plan de conexion mas barato, excluyendo esa conexion.
   - Imprime los costos s1 y s2 mas baratos para el caso actual.

Entonces, el codigo encuentra los dos planes de conexion mas baratos entre nodos con aristas con peso.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define Minimo 1 << 30 

using namespace std;


typedef pair<int, int> conexion; // conexion entre dos escuelas
typedef pair<int, conexion> elemento; // peso y una conexion
vector<elemento> elementos; 
int Pad[1000002]; 
int NVer[1000002]; 
int conjunto;


int encontrar(int x){
    // encontrar el conjunto al que pertenece un elemento
    return (x == Pad[x])? x : Pad[x] = encontrar(Pad[x]);
}

int main(){
    int T; // Numero de casos
    cin >> T;

    int N; // Numero de escuelas
    int M; // Numero de conexiones posibles

    for(int i = 0; i < T; i++){
        cin >> N >> M; 

        for (int j = 0; j < M; j++){
            int A; // Escuelas
            int B; 
            int C; // Costo de la conexion
            cin >> A >> B >> C;
            elementos.push_back(elemento(C, conexion(A,B))); // Agregar el elemento al vector de elementos
        }
        
        vector<elemento> escuelas_orden; // Vector para guardar las conexiones que forman el arbol de expansion minima

        conjunto = N; 
        for (int j = 0; j <= N; j++){
            Pad[j] = j; 
            NVer[j] = 1; // numero de vertices de cada conjunto
        }

        sort(elementos.begin(), elementos.end()); // Ordenar los elementos dados por su costo

        // Construccion del arbol de expansion minima
        for (int j = 0; j < elementos.size(); j++){
            int C2;
            int A2;
            int B2;

            C2 = elementos[j].first; 
            A2 = elementos[j].second.first; 
            B2 = elementos[j].second.second; 

            bool igualdad;
            igualdad = encontrar(A2) == encontrar(B2); 

            if (!igualdad){ // Si no pertenecen al mismo conjunto, agregar la conexion al arbol de exp min
                escuelas_orden.push_back(elemento(C2, conexion(A2, B2)));

                int xR;
                int yR;
                xR = encontrar(A2); 
                yR = encontrar(B2); 
                bool igu;
                igu = encontrar(xR) == encontrar(yR); 
                if (!igu){
                    NVer[yR] += NVer[xR]; 
                    Pad[xR] = yR; 
                    conjunto--; 
                }
            }
        }

        int S1;
        int S2;

        S1 = 0;
        S2 = Minimo;
        for(int j = 0; j < escuelas_orden.size(); j++){
            int S2_second = 0;

            conjunto = N;
            for (int k = 0; k <= N; k++) {
                Pad[k] = k;
                NVer[k] = 1;
            }

            // Construccion del segundo plan de conexion
            for (int k = 0; k < elementos.size(); k++){
                int A3;
                int B3;

                A3 = elementos[k].second.first;
                B3 = elementos[k].second.second;

                if(A3 == escuelas_orden[j].second.first && B3 == escuelas_orden[j].second.second){
                    continue;
                }
                bool igualdad;

                igualdad = encontrar(A3) == encontrar(B3); 
                if(!igualdad){
                    int xR;
                    int yR;
                    xR = encontrar(A3); 
                    yR = encontrar(B3); 
                    bool igu;
                    igu = encontrar(xR) == encontrar(yR);
                    if (!igu){
                        NVer[yR] += NVer[xR]; 
                        Pad[xR] = yR; 
                        conjunto--; 
                    }
                    S2_second += elementos[k].first; 
                }
            }
            if(conjunto != 1){ 
                S2_second = Minimo; 
            }

            S2 = min(S2, S2_second); // Actualizar el costo de s2
            S1 += escuelas_orden[j].first; // Sumar el costo de la conexion a s1
        }


        if (S2 == Minimo){ 
            cout << S1 << " " << S1 << endl; 
        }
        else{
            cout << S1 << " " << S2 << endl; 
        }

        // Limpiar el vector de elementos
        elementos.clear();
    }

    return 0;
}