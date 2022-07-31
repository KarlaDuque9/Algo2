/*	ENUNCIADO

Continuamos con strings, pero ahora con una vuelta de tuerca. Recibimos un string desordenado y debemos ordenarlo de 
manera ascendente o descendente según el booleano pasado por parámetro. El string ordenado se devuelve en el segundo vector pasado por parámetro.

Recordemos que un string ordenado ascendentemente es "ABCDEF".
Mientras que uno ordenado de manera descendente es "FEDCBA".

*/

//	RESOLUCION

#include <stdbool.h>
#include <string.h>
#define MAX_VECTOR 20


void bubble_sort_aux(char vector_desordenado[MAX_VECTOR], char vector_ordenado[MAX_VECTOR], int tope, bool ascendente){
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



void bubble_sort(char string_desordenado[MAX_VECTOR], char string_ordenado[MAX_VECTOR], bool ascendente){
    int tope =(int) strlen(string_desordenado);
    bubble_sort_aux(string_desordenado,string_ordenado, tope, ascendente);
}