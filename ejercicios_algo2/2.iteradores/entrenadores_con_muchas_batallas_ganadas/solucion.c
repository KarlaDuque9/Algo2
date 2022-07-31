/*  ENUNCIADO

Último ejercicio con iterador interno. Ahora, queremos buscar los entrenadores que ganaron más de cierta cantidad de batallas. Para eso, 
se recibe la lista de todos los entrenadores y una lista vacía a la cual se le 
debe agregar cada entrenador que cumpla las condiciones. Ah, que cuántas batallas tienen que haber ganado? Eso lo recibís por parámetro ;)

No olvides revisar los parámetros! Si alguna de las listas es NULL, no se realiza ninguna operación. Si la cantidad de batallas es menor a 0, 
tampoco se realiza ninguna operación. Por último, este ejercicio no requiere que pidas ni liberes memoria dinámica, así que no te preocupes por eso, 
nosotros lo resolvemos.
*/

//  RESOLUCION


#include "solucion.h"

typedef struct victorias{
    lista_t* entrenadores_ganadores;
    int batallas_ganadas;
}victorias_t;

bool comparar(void *_actual, void * _victorias)
{   
    int cantidad;
    entrenador_t* actual =  _actual;
    victorias_t* ganadores = _victorias;

    if(actual->b_ganadas > ganadores->batallas_ganadas)
            cantidad = lista_insertar(ganadores->entrenadores_ganadores, actual);
            
    if(cantidad == -1)
            return false;

    return true;
}


void entrenadores_con_muchas_victorias(lista_t* entrenadores, lista_t* entrenadores_ganadores, int batallas_ganadas){
    if(!entrenadores || !entrenadores_ganadores || batallas_ganadas  < 0)
        return;
    victorias_t victorias;
    victorias.entrenadores_ganadores = entrenadores_ganadores;
    victorias.batallas_ganadas = batallas_ganadas;
    lista_con_cada_elemento(entrenadores,comparar,&victorias);
}