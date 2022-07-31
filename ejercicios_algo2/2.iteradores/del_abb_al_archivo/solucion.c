/*	ENUNCIADO
Terminemos la guía a lo grande. Se tiene un árbol que contiene pokemones. Se pide escribirlos en el archivo pasado por parámetro con el siguiente formato:

nombre_del_pokemon;nivel;fuerza;inteligencia;carisma\n

Un ejemplo sería
Pikachu;5;20;18;40

Hacer uso del iterador interno del abb para modifcar el archivo pasado por parámetro y escribir en él los pokemones contenidos en el árbol, en orden 
alfabético.

No olvides revisar los parámetros!
*/

//	RESOLUCION

#include "solucion.h"

typedef struct vector{
    pokemon_t**array;
    int capacidad;
    int tope;
}vector_t;

bool escribir_pokemones(void *elemento, void *extra)
{
    vector_t *vector = extra;
    if(elemento != NULL){
        pokemon_t *aux = elemento;
        if(vector->capacidad == vector->tope){
            void** bloque = realloc(vector->array,sizeof(void*)*(vector->capacidad+1));
            if(!bloque)
                return false;
            vector->array  = bloque; 
        }
        vector->array[vector->tope] = aux;
        vector->tope++;
    }
    
    return true;
}

void escribir_pokemones_en_archivo(abb_t* pokemones, FILE* archivo){
    if(pokemones == NULL || archivo == NULL)
        return;
    vector_t *vector = calloc(1,sizeof(vector_t));
    abb_con_cada_elemento(pokemones, 0, escribir_pokemones, vector);

    for(int i =0; i < vector->tope; i++){
        pokemon_t *aux = vector->array[i];
        fprintf(archivo,"%s;%i;%i;%i;%i",aux->nombre,aux->nivel,aux->fuerza, aux->inteligencia, aux->carisma);
    }
    free(vector->array);
    free(vector);
}