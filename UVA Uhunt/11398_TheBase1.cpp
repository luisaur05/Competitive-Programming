/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa lee casos de numeros codificados en binario expandido. Cada caso 
termina con # y el último caso del archivo de entrada termina con un ~. El programa 
convierte la secuencia binaria expandida a su valor decimal y lo imprime.

1. Leer la entrada hasta encontrar un ~.
2. Recibe cada caso hasta encontrar un #.
3. Convierte la secuencia binaria expandida a decimal.
4. Imprime el valor decimal resultante para cada caso.
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//decodifica una cadena binaria a su valor decimal
long long decodificarBinario(const string& binario){
    long long valor;
    valor = 0;

    for (size_t i=0;i<binario.length();i++){
        if(binario[i]=='1'){
            valor+=(1LL<< i);
        }
    }

    return valor;
}


int main(){
    string entrada;

    while(cin>>entrada){
        //termina si la entrada es ~
        if(entrada == "~"){
            break;
        }

        string secuenciaBinaria;

        bool primeraIteracion;
        bool flag;

        primeraIteracion = true;
        flag = false;

        while(true){
            //lee la entrada hasta encontrar #
            if(!primeraIteracion){
                cin>>entrada;
            }
            primeraIteracion=false;

            if(entrada[0]=='#'){ 
                break;
            }

            if(entrada=="0"){
                flag = true;
            } 
            else{ 
                if(entrada=="00"){
                    flag = false;
                } 
                else{
                    int longitud;
                    longitud = entrada.size()-2;

                    secuenciaBinaria.append(longitud,flag?'1':'0');
                }
            }
        }

        reverse(secuenciaBinaria.begin(),secuenciaBinaria.end());

        long long resultado;

        resultado = decodificarBinario(secuenciaBinaria);
        cout << resultado << endl;
        
    }

    return 0;
}