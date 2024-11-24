/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCION--------
El programa encuentra y muestra los indices de los edificios Ultra en un perfil de montaña dado.

Para cada caso:
1. Lee los datos
2. Calcula alturas minimas:
   - Se calculan las alturas mínimas de los edificios Ultra utilizando una pila.
   - La pila de pares de enteros pmantiene las alturas de los puntos y sus alturas mínimas.
   - Se recorre el perfil de izquierda a derecha, y para cada punto se actualizan las alturas mínimas de los edificios Ultra que incluyen ese punto.
   - Luego hacemos el paso anteriror pero de derecha a izquierda.

3. Identifica los Edificios Ultra:
4. Imprime en la salida estándar los índices de los edificios "Ultra" encontrados en el perfil.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <utility>

using namespace std;

int num;
vector<int> heights, altered;
stack<pair<int, int>> st;

// Calcula las alturas minimas
void calcMinHeights(){
    for(int i = 0; i < num; ++i){
        while(!st.empty() && st.top().first <= heights[i]){
            pair<int, int> p = st.top();
            st.pop();

            if(!st.empty()){
                st.top().second = min(st.top().second, p.second);
            }
        }

        if(!st.empty()){
            altered[i] = min(altered[i], heights[i] - st.top().second);
        }

        st.push(make_pair(heights[i], heights[i]));
    }
}

// Calcula las alturas minimas en orden inverso
void calcMinHeightsRev() {
    for(int i = num - 1; i >= 0; --i){
        while(!st.empty() && st.top().first <= heights[i]){
            pair<int, int> p = st.top();
            st.pop();
            if(!st.empty()){
                st.top().second = min(st.top().second, p.second);
            }
        }

        if(!st.empty()){
            altered[i] = min(altered[i], heights[i] - st.top().second);
        }

        st.push(make_pair(heights[i], heights[i]));
    }
}

// Encuentra los edificios Ultra
vector<int> findUnsafeBuildings(const vector<int>& hts){
    vector<int> riskyBuildings;

    for(int i = 0; i < num; ++i){
        if(hts[i] >= 150000){
            riskyBuildings.push_back(i + 1);
        }
    }

    return riskyBuildings;
}

// Imprime el resultado
void printOut(const vector<int>& riskyBuildings){
    int f = 0;
    for(int i = 0; i < riskyBuildings.size(); ++i){
        if(f++){
            cout << " ";
        }
        cout << riskyBuildings[i];
    }
    cout << endl;
}

int main() {
    while(cin >> num){
        heights.resize(num);
        altered.resize(num);

        // Recibir los valores
        for(int i = 0; i < num; ++i){
            cin >> heights[i];
            altered[i] = heights[i];
        }

        // Calcular alturas miinimas
        calcMinHeights();

        while (!st.empty()){
            st.pop();
        }

        // Calcular alturas minimas en orden inverso
        calcMinHeightsRev(); 

        // Encontrar edificios y mostrar resultados
        vector<int> riskyBuildings = findUnsafeBuildings(altered);
        printOut(riskyBuildings);
    }

    return 0;
}