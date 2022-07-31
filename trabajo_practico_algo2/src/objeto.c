#include "objeto.h"
#include "estructuras.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXIMO 10
#define FORMATO_DE_OBJETO "%[^;];%[^;];%[^\n]\n"

struct objeto *objeto_crear_desde_string(const char *string)
{		

	if(string == NULL || strcmp(string , "")==0)
				return NULL;
		char nombre_objeto[MAX_NOMBRE];
		char descripcion[MAX_TEXTO];
		char es_asible[MAXIMO];
		bool aux;

		int leidos = sscanf(string,FORMATO_DE_OBJETO,nombre_objeto,descripcion,es_asible);

		if(3 != leidos)
				return NULL;

		if(strcmp(es_asible,"false")==0)
				aux = false;
		else if(strcmp(es_asible,"true")==0)
				aux = true;
		else
				return NULL;

		struct objeto *objeto = malloc(sizeof(struct objeto));

		if(objeto == NULL)
				return NULL;

		strcpy(objeto->nombre , nombre_objeto);
		strcpy(objeto->descripcion , descripcion);
		objeto->es_asible = aux;

		return objeto;
}
