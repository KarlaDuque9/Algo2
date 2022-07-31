/*	ENUNCIADO

Habiendo repasado los iteradores de la lista, pasamos ahora al iterador de árbol. Misma idea que para los iteradores de lista; cuando usamos el árbol, 
no podemos acceder a la estructura del mismo. Entonces, si queremos aplicar cierta función a cada nodo del árbol, tenemos el iterador de abb.

Empecemos con algo simple. Tenemos un árbol de números (ints), y queremos meter los números impares en un nuevo árbol.

Aviso, este ejercicio no implica manejo de memoria dinámica. No te preocupes por crear o liberar memoria, nosotros nos ocupamos de eso.

No olvides revisar los parámetros!

*/

//	RESOLUCION

#include "solucion.h"


bool insertar_en_abb(void *elemento, void *extra)
{
    abb_t *aux = extra;
    if(elemento != NULL){
        int *valor = elemento;
        if((*valor)%2 != 0){
            arbol_insertar(aux, elemento);
        }
    }
    return true;
}

void elementos_impares(abb_t* abb_original, abb_t* abb_impares){
    if(abb_original == NULL || abb_impares == NULL)
        return;

    abb_con_cada_elemento(abb_original, 0, insertar_en_abb, abb_impares);
}