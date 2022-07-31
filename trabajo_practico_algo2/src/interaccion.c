#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FORMATO_DE_INTERACCION "%[^;];%[^;];%[^;];%c:%[^:]:%[^\n]\n"

struct interaccion *interaccion_crear_desde_string(const char *string)
{
		if(string == NULL)
				return NULL;
		struct interaccion aux;
		char accion;

		int leidos = sscanf(string,FORMATO_DE_INTERACCION,aux.objeto,aux.verbo,aux.objeto_parametro, &accion,aux.accion.objeto,aux.accion.mensaje);

		if(6 != leidos)
				return NULL;
		if(strcmp(aux.objeto_parametro, "_")==0)
				strcpy(aux.objeto_parametro,"");
		if(strcmp(aux.accion.objeto, "_")==0)
				strcpy(aux.accion.objeto,"");

		struct interaccion *interaccion = malloc(sizeof(struct interaccion));

		if(interaccion == NULL){
				return NULL;
		}


		switch(accion){
				case 'd':
						interaccion->accion.tipo = DESCUBRIR_OBJETO;
				break;
				case 'r':
						interaccion->accion.tipo = REEMPLAZAR_OBJETO;
				break;
				case 'e':
						interaccion->accion.tipo = ELIMINAR_OBJETO;
				break; 
				case 'm':
						interaccion->accion.tipo = MOSTRAR_MENSAJE;
				break;
				case 'g':
						interaccion->accion.tipo = ESCAPAR;
				break;
				default:
						return NULL;
				break;
		}
	

		strcpy(interaccion->objeto, aux.objeto);
		strcpy(interaccion->verbo, aux.verbo);
		strcpy(interaccion->objeto_parametro, aux.objeto_parametro);
		strcpy(interaccion->accion.objeto, aux.accion.objeto);
		strcpy(interaccion->accion.mensaje, aux.accion.mensaje);
		return interaccion;
}
