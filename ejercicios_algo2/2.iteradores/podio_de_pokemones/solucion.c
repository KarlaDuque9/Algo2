/*	ENUNCIADO

Sigamos haciendo competir a nuestros pokemones. Para eso los capturan los entrenadores, no? Y de paso, practiquemos cómo usar el iterador interno.

Dado un grupo de pokemones, se quiere saber cuáles ganarían la medalla de oro, plata y bronce en una carrera. Cada pokemon tiene su nivel de rapidez y 
por supuesto, el que mayor nivel tenga, más rápido corre.

Para resolver el problema, se presenta la firma de una función que recibe el listado de todos los pokemones y una lista vacía donde se insertarán los 
pokemones que pertenecen al podio. Se pide que los pokemones del podio estén ordenados de la siguiente manera

medalla de oro - medalla de plata - medalla de bronce

No olvides revisar los parámetros! Si alguno de ellos es NULL, no se realiza ninguna operación. Por último, este ejercicio no requiere que utilices 
memoria dinámica de ningún tipo, así que no te preocupes por liberar memoria, nosotros nos encargamos de todo.

*/

//	RESOLUCION

#include "solucion.h"
void llenar_podio(lista_t *podio,pokemon_t *pokemon){
    size_t i =0;
    size_t tamanio = lista_elementos(podio);
    bool agregado = false;
    pokemon_t *podio_elemento;
    while(i < tamanio && !agregado){
        podio_elemento = lista_elemento_en_posicion(podio,i);
        if(tamanio == 3 && pokemon->rapidez > podio_elemento-> rapidez){
            agregado = true;
            lista_borrar(podio);
            lista_insertar_en_posicion(podio, pokemon, i);
        }else if( pokemon->rapidez > podio_elemento-> rapidez){
            lista_insertar_en_posicion(podio, pokemon, i);
            agregado = true;
        }
        i++;
    }
    if(!agregado && tamanio !=3){
        lista_insertar(podio, pokemon);
    }

}

bool comparar_elementos(void *elemento, void *_podio){
    if(!elemento)
        return false;
    pokemon_t *pokemon = elemento;
    lista_t *podio = _podio;
    llenar_podio(podio, pokemon);
    return true;
    
}

void podio_de_pokemones(lista_t* pokemones, lista_t* podio){
    if(!pokemones || !podio)
        return;
    lista_con_cada_elemento(pokemones, comparar_elementos, podio);
}