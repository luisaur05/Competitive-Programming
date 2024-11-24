/*
LUIS ANGEL ARREDONDO URIBE
---------DESCRIPCIÓN--------
El programa busca la pelicula co mayor similitud a una serie de clips dados en una base de datos 
de firmas de peliculas. Para cada clip busca el indic de la pelicula con la similitud maxima y 
lo imprime.

Pasos:
1. Lee el numero de firmas de peliculas en la base de datos y consultas de clips.
2. Lee las firmas de peliculas.
3. Para cada consulta:
    - Lee el clip de consulta.
    - Itera sobre todas las peliculas en la base de datos.
    - Calcula la similitud entre el clip y cada pelicula.
    - Actualiza el indice de la pelcula con la similitud maxima encontrada hasta el momento.
    - Imprime el indice de la pelicula con la similitud máxima.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//calculaa la similitud entre dos cadenas binarias
int calcularSimilitud(const string& a, const string& b){
    int similitudMaxima=0;
    for(int i=0; i+b.length()<=a.length();i++){
        int conteoCoincidencias=0;
        for(int j=0; j<b.length();j++){
            if(a[i+j]==b[j]){
                conteoCoincidencias++;
            }
        }
        similitudMaxima=max(conteoCoincidencias, similitudMaxima);
    }
    return similitudMaxima;
}

//obtine los titulos de las peliculas de la base de datos
vector<string> obtenerTitulosPeliculas(int m){
    vector<string> titulos;
    for (int i=0;i<m;i++){
        string titulo;
        cin >> titulo;
        titulos.push_back(titulo);
    }

    return titulos;
}

//encuentra la pelicula con mayor similitud al clip dado
void encontrarMejorPelicula(const vector<string>& peliculas, const string& consulta, int q){
    for(int i=0; i<q;i++){
        string consultaClip;

        cin >> consultaClip;

        int mejorSimilitud;
        int mejorIndice;
        
        mejorSimilitud =0;
        mejorIndice = 1;

        for(int j=0; j<peliculas.size();j++){
            int similitud;

            similitud = calcularSimilitud(peliculas[j], consultaClip);

            if(similitud>mejorSimilitud){
                mejorSimilitud=similitud;
                mejorIndice= j+1;
            }
        }
        cout << mejorIndice << endl;
    }
}

int main(){
    int numPeliculas;
    int numConsultas;

    cin >> numPeliculas >> numConsultas;
    vector<string> titulosPeliculas;

    titulosPeliculas = obtenerTitulosPeliculas(numPeliculas);
    encontrarMejorPelicula(titulosPeliculas, "", numConsultas);

    return 0;
}