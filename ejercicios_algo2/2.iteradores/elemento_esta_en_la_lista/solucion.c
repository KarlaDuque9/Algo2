/*	ENUNCIADO

Entendemos que el concepto de iterador, y su uso, es difícil de entender al principio. Por eso, dedicamos una guía especialmente para ellos.

En este primer ejercicio, resulta que tenemos una lista de números, y queremos saber si el número pasado por parámetro está en ella. Peeero, no tenemos 
acceso a la lista, directamente recibimos un iterador. Más específicamente, el iterador externo. Las funciones del iterador externo se muestran en el .h correspondiente.

No olvidar verificar los parámetros. Si el it_lista pasado es NULL, devolver false.

Aclaración: el iterador pasado por parámetro ya fue creado previamente, y no se debe destruir en esta función. Nosotros nos ocupamos de eso ;)
/*

//	RESOLUCION

#include "solucion.h"

/* funcion que compara  dos elementos y devuelve true si son iguales y false si son distintos 
*/
bool comparar_elementos(void* actual, int numero)
{
    int valor = *(int*)actual;
    return (valor == numero);
}

bool se_encuentra_el_elemento(lista_iterador_t* it_lista, int numero)
{
    bool encontrado = false;
    if(it_lista == NULL)
            return encontrado;
    while(lista_iterador_tiene_siguiente(it_lista)  && !encontrado){
            
            if(comparar_elementos(lista_iterador_elemento_actual(it_lista), numero))
                    encontrado =  true;
            lista_iterador_avanzar(it_lista);
    }
    return encontrado;
}