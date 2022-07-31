#ifndef CANTIDAD_OBJETOS_H_
#define CANTIDAD_OBJETOS_H_
#include "hash.h"
#include "sala.h"
#include "lista.h"

struct sala {
    hash_t*objetos;
    int cantidad_objetos;
    hash_t *objetos_conocidos;
    int cantidad_objetos_conocidos;
    hash_t *objetos_en_posecion;
    int cantidad_objetos_en_posecion;
    lista_t *interacciones;
    int cantidad_interacciones;
    bool escapar;
};

/*
 * devuelve la cantidad de objetos conocidos por el jugador en la sala de escape.
 *
 */
size_t cantidad_objetos(sala_t *sala);


/*
 * devuelve la cantidad de objetos poseidos por el jugador en la sala_t *sala de escape.
 *
 */
size_t cantidad_interacciones(sala_t *sala);

#endif // CANTIDAD_OBJETOS_H_
