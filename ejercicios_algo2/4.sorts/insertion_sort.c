/*	ENUNCIADO
Para finalizar los tres métodos de ordenamiento que se ven en Algo1, se pide implementar el método de inserción.

Si no lo conocen, aquí les dejamos un link de la explicación del mismo de Algo1Mendez https://www.youtube.com/watch?v=NkRFb9t0OXI&ab_channel=algo1mendez

A saber,
Un string ordenado ascendentemente es "ABCDEF", mientras que uno ordenado de manera descendente es "FEDCBA".


*/

//	RESOLUCION

#include <stdbool.h>
#define MAX_VECTOR 20

void llenar_vector(char vector_desordenado[MAX_VECTOR], char vector_ordenado[MAX_VECTOR], int tope){
    for(int i =0 ; i < tope; i++){
        vector_ordenado[i] = vector_desordenado[i];
    }
}

void insertion_sort(char vector_desordenado[MAX_VECTOR], char vector_ordenado[MAX_VECTOR], int tope, bool ascendente){
    char aux;
    int j;
    for (int i = 1; i < tope; i++) {
        j=i;
        aux = vector_desordenado[i];
        while (j > 0 && ((ascendente && aux < vector_desordenado[j-1])|| (!ascendente && aux > vector_desordenado[j-1]))){
            vector_desordenado[j] = vector_desordenado[j-1];
            j--;
        }
        vector_desordenado[j] = aux;
    }
    llenar_vector(vector_desordenado, vector_ordenado, tope);
}