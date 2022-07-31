/*	ENUNCIADO

Afiancemos nuestros conocimientos del iterador externo con este ejercicio. Tenemos una lista de entrenadores, y queremos saber cuál es el que ganó más batallas. 
En caso de que dos entrenadores hayan ganado la misma cantidad de batallas, se debe devolver el que menos batallas perdió de los dos. Al igual que en el 
ejercicio anterior, se recibe el iterador de la lista.

La estructura del entrenador se encuentra en el archivo solucion.h. No olvidar revisar los parámetros recibidos! Se puede recorrer una lista con el iterador, 
si ese iterador es nulo? En caso de recibirse un parámetro NULL, devolver NULL.

*/

//	RESOLUCION

#include "solucion.h"

entrenador_t* comparar(entrenador_t* actual, entrenador_t* anterior){
    entrenador_t* nuevo_ganador = NULL;
    if(actual->b_ganadas == anterior->b_ganadas && actual->b_perdidas < anterior->b_perdidas){
        nuevo_ganador = actual;
    }else if(actual->b_ganadas > anterior->b_ganadas){
        nuevo_ganador = actual;
    }else{
        nuevo_ganador = anterior;
    }

    return nuevo_ganador;
}

entrenador_t* entrenador_con_mas_victorias(lista_iterador_t* it_lista){
    if(!it_lista){
        return NULL;
    }
    entrenador_t* ganador = lista_iterador_elemento_actual(it_lista);
    while( lista_iterador_tiene_siguiente(it_lista)){
        if(lista_iterador_avanzar(it_lista)){
            entrenador_t* actual = lista_iterador_elemento_actual(it_lista);
            ganador = comparar(actual,ganador);
        }
    }
    return ganador;
}