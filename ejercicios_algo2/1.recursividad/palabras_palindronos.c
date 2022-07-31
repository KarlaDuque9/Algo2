/*	ENUNCIADO

Meowth, que es un Pokémon muy inteligente, se dio cuenta, mientras aprendía a leer, que hay palabras que leyéndolas de izquierda a derecha o 
derecha a izquierda tienen el mismo significado y se leen igual. Las tiene escritas en una libreta, pero como no confía qué tan bien escribe, 
te pide que confecciones una función para que le diga si es una palabra palíndromo o no.

*/

//	RESOLUCION
#include "solucion.h"

bool buscar_polindromo(const char *cadena, size_t inicio, size_t fin){
        if(cadena[inicio] != cadena[fin])
                return false;
        else if(inicio > fin)
                return true;
        return buscar_polindromo(cadena, inicio+1, fin -1);
}