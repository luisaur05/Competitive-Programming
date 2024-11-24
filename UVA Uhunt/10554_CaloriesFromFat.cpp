/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa da el porcentaje de calorias provenientes de la grasa para cada caso de prueba. 
Lee las lineas de entrada hasta encontrar un guion (-), procesa los datos de cada linea y calcula 
el porcentaje de calorías de grasa. 

1. Lee las lineas de entrada hasta encontrar un guion.
2. Procesa los datos de cada línea.
3. Calcula el porcentaje de caloris de grasa y almacear el resultado.
4. Imprime el porcentaje de caloraas de grasa.
*/

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;


int calcularPorcentajeDeGrasa(string linea) {
    const double calorias[5] = {9, 4, 4, 4, 7};
    double totalGrasa = 0;
    double totalCalorias = 0;
    int porcen;

    do{
        istringstream in(linea);
        double subtotal = 0;
        double porcentajeTotal = 0;
        pair<double, char> datos[5];

        for(int i=0;i<5;i++){
            string informacion;
            in >> informacion;
            double cantidad =stod(informacion.substr(0, informacion.length() - 1));
            char unidad =informacion.back();

            if(unidad == 'C'){
                if (i == 0){
                    totalGrasa += cantidad;
                }
                subtotal += cantidad;
                totalCalorias += cantidad;
            } 
            else{
                if(unidad == '%'){
                    porcentajeTotal+=cantidad;
                } 
                else{
                    if(unidad== 'g'){
                        if(i==0){
                            totalGrasa+=cantidad * 9;
                        }
                        subtotal+=cantidad * calorias[i];
                        totalCalorias += cantidad * calorias[i];
                    }
                }
            }

            datos[i] = make_pair(cantidad, unidad);
        }

        //ajustar el totl de grasa y calorías segu el porcentaje
        if(datos[0].second== '%'){
            totalGrasa += datos[0].first * subtotal / (100.00 - porcentajeTotal);
        }
        
        totalCalorias += subtotal * porcentajeTotal / (100.00 - porcentajeTotal);
    }while(getline(cin, linea) and linea != "-");

    //calculaa el porcentaje de calorias provenientes de la grasa
    porcen = (int)round(totalGrasa / totalCalorias * 100.00);

    return porcen;
}

int main() {
    string linea;
    int porcentaje;

    //lee las lneas de entrada hasta encontrar un guion(-)
    while (getline(cin, linea) and linea != "-") {
        porcentaje = calcularPorcentajeDeGrasa(linea);

        cout << porcentaje << "%\n";
    }

    return 0;
}