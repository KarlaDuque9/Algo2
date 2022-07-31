/*	ENUNCIADO
Lo prometido es deuda, aquí está el link de introducción de Algo1Mendez:
https://www.youtube.com/watch?v=aXhsI_8KUy0&ab_channel=algo1mendez

Ahora sí, empecemos con el método de ordenamiento más conocido: Bubblesort.

Se recibe un vector de caracteres, que deseo ordenar de manera ascendente o descendente, dependiendo del booleano pasado por parámetro. 
También se recibe el vector donde quiero que estén los elementos ordenados.

Por si no tienen ni idea de sobre qué les estoy hablando, acá les dejo un video de Algo1Mendez donde se explica este algoritmo: 
https://www.youtube.com/watch?v=QgU47ejV7mg&ab_channel=algo1mendez

A saber, un string ordenado ascendentemente es "ABCDEF", mientras que uno ordenado de manera descendente es "FEDCBA".


*/

//	RESOLUCION

#include <stdbool.h>
#define MAX_VECTOR 20



void bubble_sort(char vector_desordenado[MAX_VECTOR], char vector_ordenado[MAX_VECTOR], int tope, bool ascendente){
    for(int j =0; j< tope; j++){
		for(int i = 0; i <tope-j-1; i++){
            if((ascendente && vector_desordenado[i] > vector_desordenado[i+1]) || (!ascendente &&vector_desordenado[i] < vector_desordenado[i+1])){
                char aux = vector_desordenado[i+1];
                vector_desordenado[i+1] = vector_desordenado[i];
                vector_desordenado[i] = aux;                    
             } 
		}
        vector_ordenado[tope-j-1] = vector_desordenado[tope-j-1];
	}
}