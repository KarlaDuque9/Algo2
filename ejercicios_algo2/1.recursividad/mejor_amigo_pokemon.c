/*	ENUNCIADO

Ash Ketchum quiere convertirse en Maestro Pokémon, el más alto grado de entrenamiento Pokémon, para lograrlo necesita entrenar a sus pokémones en batallas 
y estar también físicamente en forma, para lograrlo decide seguir el consejo del doctor Proctor, hacer sentadillas y la cantidad que debe hacer tiene que 
ser un números primo. Como a veces se olvida si un número es primo o no, te pide ayuda, para que crees un programa en el cual, le diga a Ash si la cantidad 
de sentadillas que desea realizar es un número primo en ese caso la función devolverá cero, y si no lo es, el próximo primo de la cantidad ingresada.

*/
//	RESOLUCION

#include "solucion.h"

size_t es_numero_primo(size_t cantidad_ingresada, size_t i){
    if(i >= cantidad_ingresada)
            return 0;
    else if( cantidad_ingresada ==0 || cantidad_ingresada == 1)
            return 0;
    else if(cantidad_ingresada % i ==0)
            return -1;
    return es_numero_primo(cantidad_ingresada, i+1);
}

size_t buscar_siguiente_numero_primo(size_t cantidad_ingresada){
    if(es_numero_primo(cantidad_ingresada, 2)==0)
            return cantidad_ingresada;
    return buscar_siguiente_numero_primo(cantidad_ingresada+1);
}

int devuelve_siempre_numero_primo(size_t cantidad_ingresada) {
    if(es_numero_primo(cantidad_ingresada, 2)==0)
            return 0;
    return (int)buscar_siguiente_numero_primo(cantidad_ingresada+1);
}

