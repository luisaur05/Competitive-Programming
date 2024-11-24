/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------

El programa utiliza dos búsquedas binarias para encontrar la cantidad total de unidades 
tal que su precio sea igual a A, y la cantidad de unidades a pagar tal que la diferencia 
de precios entre esa cantidad de unidades y las restantes sea igual a B.

1. Lee el par de numeros A y B.
2. Verifca si ambos numeros son cero, en cuyo caso se termina el programa.
3. Inicializalos limites inferior y superior para realiar la busqueda binaria.
4. Hce una busqueda binaria para encontrar la cantidad total de unidades tal que su precio sea igual a A.
   - Calcula la cantidad total de unidades n función de un valor medio dentro de los límites l y r.
   - Determina si el precio calculado es menor, igual o mayor que A, y se actualizan los límites en consecuencia.
5. Realiza una segunda bisqueda binaria para encontrar la cantidad de unidades a pagar .
   - Calcula la diferencia de precios entre la cantidad de unidades a pagar y las restantes.
   - Determina si la diferencia es igual, mayor o menor que B, y se actualizan los límites en consecuencia.
6. Imprime el precio de las unidades a pagar.
*/

#include <iostream>
using namespace std;

#define NIL -1
#define MAX INT_MAX
#define INF 99999999

long long a, b;

long long calcularPrecio(long long m){
    long long precio;
    long long v;

    precio = 0;

    v = min(100LL, m); 
    m -= v;
    precio += 2 * v;
    v = min(9900LL, m); 
    m -= v;
    precio += 3*v;
    v = min(990000LL, m); 
    m -= v;
    precio+=5*v + 7 * m;

    return precio;
}

int calcularUnidadTotal(long long m){
    long long precio;
    
    precio = calcularPrecio(m);
    if(precio<a){
        return 0;
    }
    else{ 
        if (precio == a){ 
            return 1;
        }
        else{ 
            return 2;
        }
    }
}

int encontrarSolucion(long long m, long long unit){
    long long precio1;
    long long precio2;

    long long diferencia;

    precio1 = calcularPrecio(m);
    precio2 = calcularPrecio(unit - m);
    diferencia = abs(precio1 - precio2);

    if(diferencia==b){
        return 0;
    }

    if(diferencia>b){
        return 1;
    }
    else{
        return 2;
    }
}

int main(){
    long long unidadesAPagar;
    long long l;
    long long r;
    long long mid;
    long long unit;
    long long resultado;

    while(cin>> a >>b){
        if (a==0&& b==0){
            break;
        }

        //busqeuda binaria para encontrar la cantidad total de unidades tal que su precio sea igual a A
        l = 1;
        r = 1e12;

        while(l<= r){
            mid=(l+r) >> 1;

            resultado = calcularUnidadTotal(mid);

            if(resultado==1){
                unit = mid;
                break;
            }
            else{
                if(resultado==2){
                    r=mid -1;
                }
                else{ 
                    if(resultado == 0){
                        l=mid +1;
                    }
                }
            }
        }

    
        l = 1;
        r = unit;

        while(l<= r){
            mid=(l+r) >> 1;

            resultado = encontrarSolucion(mid, unit);

            if(resultado==0){
                unidadesAPagar = mid;
                r=mid - 1;
            }
            else{ 
                if(resultado==1){
                    l=mid +1;
                }
                else{
                r =mid-1;
                }
            }
        }

        //muestraa el precio de las unidades a pagar 
        cout << calcularPrecio(unidadesAPagar) << endl;
    }

    return 0;
}