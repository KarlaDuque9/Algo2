#include "cantidad_objetos.h"

size_t cantidad_objetos(sala_t *sala)
{
    return hash_cantidad(sala->objetos);
}


/*
 * devuelve la cantidad de objetos poseidos por el jugador en la sala de escape.
 *
 */
size_t cantidad_interacciones(sala_t *sala)
{
    return lista_tamanio(sala->interacciones);
}

