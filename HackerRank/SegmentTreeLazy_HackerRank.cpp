/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCION--------
El problema simula un arbol de segmentos con lazy propagation, en el cual se realizan 
operaciones de cambio, intercambio, suma y consulta de suma de unos en un rango.

Pasos:
1.- Lee el numero de casos a evaluar.
2.- Lee el numero de operaciones a realizar.
3.- Lee el numero de veces que se realizara la operacion y la operacion a realizar.
4.- Lee el tipo de operacion a realizar y el rango en el que se realizarala operacion.
6.- Realiza la operacn correspondiente.
7.- Imprime el resultado de la consulta.
8.- Limpia los arreglos y se repite el proceso para el siguiente caso.
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define optimizar_io ios_base::sync_with_stdio(0);cin.tie(0);
int arbol[6000000] = {0}; 


struct PendingTasks {
    int changes = 0;
    int changeValue = 0;   
    int multiplications = 0;
    int multiplyValue = -1;
    int additions = 0;
    int addValue = 0;    
    int pendientes = 0;

    //limp los valores de las tareas pendientes
    void limpiar(){
        changes = 0;  
        changeValue = 0;   
        multiplications = 0; 
        multiplyValue = 0;
        additions = 0;  
        addValue = 0;    
        pendientes = 0;
    }

    //sobrecrga del operador para combinar tareas pendientes
    PendingTasks &operator +=(PendingTasks &pend_tasks){
        if(pend_tasks.changes){
            this->limpiar();
            this->changes = pend_tasks.changes;
            this->changeValue = pend_tasks.changeValue;
            this->pendientes = 1;
        } else {
            if(this->changes && pend_tasks.multiplications){
                this->changeValue = (this->changeValue * -1) + 1;                
            } else {
                if(this->multiplications && pend_tasks.multiplications){
                    this->limpiar();
                } else {
                    if(this->pendientes == 0 && pend_tasks.multiplications){
                        this->limpiar();
                        this->multiplications = pend_tasks.multiplications;
                        this->additions = pend_tasks.additions;
                        this->changeValue = pend_tasks.changeValue;
                        this->multiplyValue = pend_tasks.multiplyValue;
                        this->pendientes = 1;
                    } 
                }
            }
        }
        return *this;
    }
};

//areas pendientes en cada nodo del arbol
PendingTasks treelaz[6000000]; 

void nueva_oper(int indice, int id, int val)
{
    if( id == 1 ){
        treelaz[indice].limpiar();
        treelaz[indice].changes = 1;
        treelaz[indice].changeValue = val;
        treelaz[indice].pendientes = 1;
    } else {
        if(treelaz[indice].changes && id == 2){
            treelaz[indice].changeValue = (treelaz[indice].changeValue * -1) + 1;                
        } else { 
            if(treelaz[indice].multiplications && id == 2){
                treelaz[indice].limpiar();
            } else { 
                if(treelaz[indice].pendientes == 0  && id == 2){
                    treelaz[indice].multiplications = 1;
                    treelaz[indice].multiplyValue = -1;
                    treelaz[indice].additions = 1;
                    treelaz[indice].addValue = 1;
                    treelaz[indice].pendientes = 1;
                }
            }
        }
    } 
}

int sumaunos(int nodoi, int nodof, int nodok, int l, int r){
    // Verificamos si hay acciones pendientes
    if (treelaz[nodoi].pendientes != 0 ){
        if (nodof != nodok){
            treelaz[nodoi*2 + 1] += treelaz[nodoi];
            treelaz[nodoi*2 + 2] += treelaz[nodoi];
        }

        // Si hay cambios pendientes, los realiza
        if(treelaz[nodoi].changes != 0){
            arbol[nodoi] = treelaz[nodoi].changeValue * (nodok-nodof+1);
            treelaz[nodoi].changeValue = 0;
        }

        // Si hay multiplicaciones pendientes las realiza     
        if(treelaz[nodoi].multiplications != 0){
            arbol[nodoi] = arbol[nodoi] * treelaz[nodoi].multiplyValue;
        }

        // Si hay sumas o adiciones pendientes, las realiza
        if(treelaz[nodoi].additions != 0){
            arbol[nodoi] = ((nodok-nodof+1) * 1) + arbol[nodoi]; 
        }

        treelaz[nodoi].limpiar();
    }
  
    // Fuera de rango
    if (nodof > nodok || nodof > r || nodok < l){
        return 0;
    }

    if (nodof >= l && nodok <= r){
        return arbol[nodoi];
    }

    // Si hay solapamiento con el rango dado
    int mid = (nodof + nodok) / 2;
    return sumaunos(2 * nodoi + 1, nodof, mid, l, r) +  sumaunos(2 * nodoi + 2, mid + 1, nodok, l, r);
}

// Funcion recursiva para actualizar el arbol 
void actualizar(int nodoi, int nodof, int nodok, int l, int r, int operacion, int valor, int id){    
    if (treelaz[nodoi].pendientes != 0 ){
        if (nodof != nodok){
            treelaz[nodoi*2 + 1] += treelaz[nodoi];
            treelaz[nodoi*2 + 2] += treelaz[nodoi];
        }

        // Si hay cambios pendientes, los realiza
        if(treelaz[nodoi].changes != 0){
            arbol[nodoi] = treelaz[nodoi].changeValue * (nodok-nodof+1);
            treelaz[nodoi].changeValue = 0;
        }

        // Si hay multiplicaciones pendientes las realiza     
        if(treelaz[nodoi].multiplications != 0){
            arbol[nodoi] = arbol[nodoi] * treelaz[nodoi].multiplyValue;
        }

        // Si hay sumas o adiciones pendientes, las realiza
        if(treelaz[nodoi].additions != 0){
            arbol[nodoi] = ((nodok-nodof+1) * 1) + arbol[nodoi]; 
        }

        treelaz[nodoi].limpiar();
    }

    // Fuera de rango
    if (nodof > nodok || nodof > r || nodok < l){
        return; 
    }   
  
    // El segmento actual esta completamente en rango
    if (nodof >= l && nodok <= r){
        // Aplica la operacin con la que se actualizara
        if(operacion == 0){ // La operacion es cambiar
            arbol[nodoi] = valor * (nodok-nodof+1); 
        } else {
            if(operacion == 1){ // La operacion es intercambiar
                int part1 = arbol[nodoi] * -1;
                arbol[nodoi] = ((nodok-nodof+1) * 1) + part1;
            }
        }

     
        if (nodof != nodok){            
            // Heredamos la nueva operacion pendiente a los hijos         
            nueva_oper(nodoi*2 + 1, id, valor);
            nueva_oper(nodoi*2 + 2, id, valor);
        }
        return;
    }
  
    // Si no esta completamente en rango, pero se solapa, recurrimos para los hijos
    int mid = (nodof + nodok) / 2;

    actualizar(nodoi*2 + 1, nodof, mid, l, r, operacion, valor, id);
    actualizar(nodoi*2 + 2, mid + 1, nodok, l, r, operacion, valor, id);
  
    // Y usamos el resultado de las llamadas a los hijos para actualizar este nodo
    arbol[nodoi] = arbol[nodoi*2 + 1] + arbol[nodoi*2 + 2];
}

// Funcion para construir el arbol a partir de un arreglo dado
void construirArbol(int arre[], int nodof, int nodok, int nodoi){
    if(nodof > nodok){// Fuera de rango
        return;
    } 

    if(nodof == nodok){// Si es un nodo hojasolo lo metemos a su arreglo pues ya esta ordenado
        arbol[nodoi] = arre[nodof];
        return;
    }  
    
    int mid = (nodok + nodof) / 2;
    
    // Seguimos con el siguiente nivel
    construirArbol(arre, nodof, mid, ((2 * nodoi) + 1));    
    construirArbol(arre, mid + 1, nodok, ((2 * nodoi) + 2));

    arbol[nodoi] = arbol[nodoi*2 + 1] + arbol[nodoi*2 + 2];
}

int main(){
    int T;
    cin >> T;

    for(int i = 0; i < T; i++){
        int M;
        cin >> M;
        string cadena_final;

        for (int j = 0; j < M; j++){
            int veces;
            string cadena;

            cin >> veces;
            cin >> cadena;

            for (int k = 0; k < veces; k++){
                cadena_final.append(cadena); 
            }
        }

        int tam = cadena_final.size();

        int arregl[tam]; // Creamos un arreglo donde almacenaremos la cadena

        for (int j = 0; j < tam; j++){           
            arregl[j] = (cadena_final[j] - '0');
        }     

        construirArbol(arregl, 0, tam - 1, 0); 

        int Q;
        cin >> Q;

        for(int i = 0; i < Q; i++){
            string str1;
            int l;
            int r;

            cin >> str1 >> l >> r;

            if(str1 == "F"){
                actualizar(0, 0, tam - 1, l, r, 0, 1, 1);
            }
            else{
                if(str1 == "E"){
                    actualizar(0, 0, tam - 1, l, r, 0, 0, 1);
                }
                else{
                    if(str1 == "I"){
                        actualizar(0, 0, tam - 1, l, r, 1, 0, 2);
                    }
                    else{
                        if(str1 == "S"){
                            // Comprobar valores de entrada erroneos
                            if (l < 0 || r > tam - 1 || l > r){
                                return -1;
                            }

                            int suma;
                            suma = sumaunos(0, 0, tam - 1, l, r);
                            cout << suma << endl;
                        }
                    }
                }
            }
        }

        for (int j = 0; j < 6000000; j++){            
            arbol[j] = 0;
            if (treelaz[j].pendientes){
                treelaz[j].limpiar();
            }    
        }         
    }

    return 0;
}