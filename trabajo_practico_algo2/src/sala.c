#include "estructuras.h"
#include "objeto.h"
#include "interaccion.h"
#include "sala.h"
#include "lista.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define MAX_LECTURA 1024 


struct sala {
	hash_t*objetos;
	int cantidad_objetos;
	hash_t *objetos_conocidos;
	hash_t *objetos_en_posecion;
	lista_t *interacciones;
	int cantidad_interacciones;
	bool escapar;
};

struct vector_array{
		char **array;
		size_t cantidad;
		int tamanio_array;
};

typedef struct interaccion_aux{
	struct interaccion interaccion;
	bool interaccion_valida;
}interaccion_aux_t;
/*recibe un hash de objetos, la cantidad de objetos en el hash  y un puntero al archivo de objetos,
 *se encarga de leer el cada linea del archivo y llenando el hash de objetos con lo que lee del archivo usando memoria dinámica,
 *se utiliza en la función sala_sala_crear_desde_archivos. El vector es liberado antes de finalizar el programa
 *hash_t *crear_objetos_desde_archivo(hash_t *objetos, int *cantidad_objetos, FILE *arch_objetos, sala_t *sala)
 */
hash_t *crear_objetos_desde_archivo(hash_t *objetos, int *cantidad_objetos, FILE *arch_objetos, sala_t *sala)
{	
		objetos = hash_crear((size_t)(*cantidad_objetos));
		if(!objetos)
				return NULL;
		struct objeto  *objeto_auxiliar;
		char leer_objeto[MAX_LECTURA];
		char *linea = fgets(leer_objeto,MAX_LECTURA,arch_objetos);
		while(linea){
				objeto_auxiliar = objeto_crear_desde_string(leer_objeto);
				if(objeto_auxiliar == NULL)
						return NULL;	
				objetos = hash_insertar(objetos,objeto_auxiliar->nombre,objeto_auxiliar, NULL);
				if(hash_cantidad(sala->objetos_conocidos)==0){
						hash_insertar(sala->objetos_conocidos, objeto_auxiliar->nombre,objeto_auxiliar,NULL);
				}
				if(!objetos){
					free(objetos);
					return NULL;
				}
				sala->cantidad_objetos++;
				linea = fgets(leer_objeto,MAX_LECTURA,arch_objetos);	
		}
		if(hash_cantidad(objetos) ==0){
			free(objetos);
			return NULL;
		}

		return objetos;

}

/*recibe un vector de interacciones y un puntero al archivo de interacciones,
 *se encarga de leer cada linea del archivo y llenando la lista de interacciones con lo que lee del archivo usando memoria dinámica, 
 *se utiliza en la función sala_sala_crear_desde_archivos. El vector es liberado antes de finalizar el programa
 */
lista_t *crear_interacciones_desde_archivo(lista_t *interacciones,FILE *arch_interacciones)
{
		interacciones = lista_crear();
		struct interaccion  *interaccion_auxiliar;
		char leer_interaccion[MAX_LECTURA];
		char *linea = fgets(leer_interaccion,MAX_LECTURA,arch_interacciones);
		while(linea){
				interaccion_auxiliar = interaccion_crear_desde_string(leer_interaccion);
				if(interaccion_auxiliar == NULL)
						return NULL;
				interacciones =  lista_insertar(interacciones,interaccion_auxiliar);
				if(!interacciones)
						return NULL;
				linea = fgets(leer_interaccion,MAX_LECTURA,arch_interacciones);	
		}
		if(lista_vacia(interacciones)){
			free(interacciones);
			return NULL;
		}

		return interacciones;
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	FILE *arch_interacciones = fopen(interacciones,"r");
		if(!arch_interacciones)
				return NULL;		

		FILE *arch_objetos = fopen(objetos,"r");
		if(!arch_objetos){
				fclose(arch_interacciones);
				return NULL;
		}
		sala_t *sala = calloc(1,sizeof(sala_t));
		if(sala == NULL){
				fclose(arch_objetos);
				fclose(arch_interacciones);
				return NULL;
		}
		sala->objetos_conocidos = hash_crear((size_t)(sala->cantidad_objetos));
		sala->objetos_en_posecion = hash_crear((size_t)(sala->cantidad_objetos));
		sala->objetos = crear_objetos_desde_archivo((sala->objetos),&(sala->cantidad_objetos),arch_objetos, sala);
		if(!sala->objetos || !sala->objetos_conocidos || !sala->objetos_en_posecion ){
				free(sala);
				fclose(arch_objetos);
				fclose(arch_interacciones);
				return NULL;
		}
		sala->interacciones = crear_interacciones_desde_archivo(sala->interacciones,arch_interacciones);
		if(!sala->interacciones){
				sala_destruir(sala);
				fclose(arch_objetos);
				fclose(arch_interacciones);
				return NULL;
		}

		fclose(arch_objetos);
		fclose(arch_interacciones);
		return sala;
}

 /* Funcion que recibe una clave, el elmento y un vector, se encargallena el vector en el mismo 
  *como segundo parámetro con el elemento
  * devuelve false en caso de no poder llenar mas el vector y true en caso contrario
  */
bool llenar_array(const char *clave, void *elemento ,void *vector_array)
{
		if(!clave)
			return false;
		struct vector_array *vector = vector_array;
		struct objeto *objeto = elemento;
		if(vector->tamanio_array == vector->cantidad)
				return false;
		vector->array[vector->cantidad]= objeto->nombre;
		vector->cantidad++;
		return true;
}
char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if(!sala && cantidad){
				(*cantidad) = -1;
				return NULL;
		}else if(cantidad){
				(*cantidad) = sala->cantidad_objetos;
		}
		struct vector_array nombres;
		nombres.array = calloc((unsigned long int)sala->cantidad_objetos, sizeof(char*));
		nombres.tamanio_array = sala->cantidad_objetos;
		nombres.cantidad =0; 
		hash_con_cada_clave(sala->objetos, llenar_array, &nombres);

		return nombres.array ;

}
 /* Funcion que recibe  dos interacciones,
  * devuelve true si las interacciones son iguales y false en caso contrario
  */
bool comparar_interaccion(struct interaccion *interaccion_actual,struct interaccion interaccion )
{
	if(strcmp(interaccion_actual->verbo,interaccion.verbo) == 0 &&
		strcmp(interaccion_actual->objeto,interaccion.objeto) == 0 &&
		strcmp(interaccion_actual->objeto_parametro,interaccion.objeto_parametro) == 0)
			return true;
	return false; 
}
 /* Funcion que recibe  una interaccion y una interaccion aux, evalua si la interaccion es igual a la interaccion aux 
  * devuelve false si las interacciones son iguales y true en caso contrario
  */
bool es_interaccion_valida(void *_interaccion_actual, void *_interaccion)
{
	if(!_interaccion_actual)
			return false;
	struct interaccion *interaccion_actual = _interaccion_actual;
	interaccion_aux_t *auxiliar = _interaccion;
	if(comparar_interaccion(interaccion_actual,auxiliar->interaccion)){
			auxiliar->interaccion_valida = true;
				return false;
	}
	return true;

}


bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
		if(sala == NULL || verbo == NULL || objeto1 == NULL || objeto2 == NULL)
			return NULL;
	
		interaccion_aux_t elemento;
		strcpy(elemento.interaccion.verbo,verbo); 
		strcpy(elemento.interaccion.objeto,objeto1);
		strcpy(elemento.interaccion.objeto_parametro, objeto2);  
		elemento.interaccion_valida = false; 
		lista_con_cada_elemento(sala->interacciones, es_interaccion_valida, &elemento);
		return elemento.interaccion_valida;
}


void sala_destruir(sala_t *sala)
{
		hash_destruir_todo(sala->objetos,free);
		hash_destruir(sala->objetos_conocidos);
		hash_destruir(sala->objetos_en_posecion);
		lista_destruir_todo(sala->interacciones,free);
		free(sala);
}

bool sala_escape_exitoso(sala_t *sala)
{
		return !sala ? false : sala->escapar;
}

char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto){
	if(!sala || !nombre_objeto)
			return NULL;
	if(hash_contiene(sala->objetos_conocidos, nombre_objeto)){
			struct objeto *objeto = hash_obtener(sala->objetos_conocidos, nombre_objeto);
			return objeto->descripcion;
	}else if (hash_contiene(sala->objetos_en_posecion, nombre_objeto)){
			struct objeto *objeto = hash_obtener(sala->objetos_en_posecion, nombre_objeto);
			return objeto->descripcion;
	}
	return NULL;
}


bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if(!sala || !nombre_objeto)
			return false;
	struct objeto *objeto_actual = hash_obtener(sala->objetos_conocidos,nombre_objeto);
	if(!objeto_actual || !objeto_actual->es_asible)
			return false;
	hash_quitar(sala->objetos_conocidos,nombre_objeto);
	hash_insertar(sala->objetos_en_posecion, nombre_objeto,objeto_actual, NULL);
	return true;
}

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
		if(sala == NULL && cantidad != NULL){
				(*cantidad) = -1;
				return NULL;
		}else if(cantidad != NULL){
				(*cantidad) = (int)hash_cantidad(sala->objetos_conocidos) ;
		}
		struct vector_array objetos_conocidos;

		objetos_conocidos.tamanio_array =  (int)hash_cantidad(sala->objetos_conocidos);
		objetos_conocidos.cantidad = 0;
		objetos_conocidos.array = calloc((unsigned long int)hash_cantidad(sala->objetos_conocidos), sizeof(char*));
		hash_con_cada_clave(sala->objetos_conocidos, llenar_array, &objetos_conocidos);

		return objetos_conocidos.array;
}

char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
		if(sala == NULL && cantidad != NULL){
				(*cantidad) = -1;
				return NULL;
		}else if(cantidad != NULL){
				(*cantidad) = (int)hash_cantidad(sala->objetos_en_posecion);
		}
		struct vector_array objetos_poseidos;
		objetos_poseidos.tamanio_array =  (int)hash_cantidad(sala->objetos_conocidos)+1;
		objetos_poseidos.cantidad =0; 
		objetos_poseidos.array = calloc((unsigned long int)objetos_poseidos.tamanio_array,sizeof(char*));
		hash_con_cada_clave(sala->objetos_en_posecion, llenar_array, &objetos_poseidos);

		return objetos_poseidos.array;
}
 /* Funcion que recibe la sala,  una interaccion  y una funcion(mostrar_mensaje), si logra realizar la interaccion y la funcion mostar mensaje non es NULLse invocará
  * con el mensaje a mostrar, el tipo de acción que representa el
  * mensaje y un puntero auxiliar del usuario.
  * devuelve true si logra realizar la interaccion y false en caso contrario
  */
bool escapar(sala_t *sala,struct interaccion *interaccion_actual, void (*mostrar_mensaje)(const char *mensaje,enum tipo_accion accion,void *aux),void *aux)
{
		if(hash_contiene(sala->objetos_conocidos,interaccion_actual->objeto) || 
				hash_contiene(sala->objetos_en_posecion,interaccion_actual->objeto)){
				sala->escapar = true;
				if(mostrar_mensaje)
						mostrar_mensaje(interaccion_actual->accion.mensaje,interaccion_actual->accion.tipo, aux);
				return true;
		}
		return false;
}
 /* Funcion que recibe la sala,  una interaccion  y una funcion(mostrar_mensaje), si logra realizar la interaccion y la funcion mostar mensaje non es NULLse invocará
  * con el mensaje a mostrar, el tipo de acción que representa el
  * mensaje y un puntero auxiliar del usuario.
  * devuelve true si logra realizar la interaccion y false en caso contrario
  */
bool descubrir_objeto(sala_t *sala,struct interaccion *interaccion_actual, void (*mostrar_mensaje)(const char *mensaje,enum tipo_accion accion,void *aux),void *aux)
{
		if(!hash_contiene(sala->objetos_conocidos,interaccion_actual->accion.objeto) && 
				hash_contiene(sala->objetos,interaccion_actual->accion.objeto) &&
				!hash_contiene(sala->objetos_en_posecion,interaccion_actual->accion.objeto)){
				struct objeto *objeto_actual = hash_obtener(sala->objetos,interaccion_actual->accion.objeto);
				hash_insertar(sala->objetos_conocidos,objeto_actual->nombre ,objeto_actual, NULL);
				if(mostrar_mensaje)
						mostrar_mensaje(interaccion_actual->accion.mensaje,DESCUBRIR_OBJETO, aux);
				return true;
		}
		return false;
}
 /* Funcion que recibe la sala,  una interaccion  y una funcion(mostrar_mensaje), si logra realizar la interaccion y la funcion mostar mensaje non es NULLse invocará
  * con el mensaje a mostrar, el tipo de acción que representa el
  * mensaje y un puntero auxiliar del usuario.
  * devuelve true si logra realizar la interaccion y false en caso contrario
  */
bool eliminar_objeto(sala_t *sala,struct interaccion *interaccion_actual, void (*mostrar_mensaje)(const char *mensaje,enum tipo_accion accion,void *aux),void *aux)
{
		if(hash_contiene(sala->objetos_en_posecion, interaccion_actual->accion.objeto) ||
				hash_contiene(sala->objetos_conocidos, interaccion_actual->accion.objeto) ){
				hash_quitar(sala->objetos_conocidos,interaccion_actual->accion.objeto);
				hash_quitar(sala->objetos_en_posecion,interaccion_actual->accion.objeto);
				struct objeto *objeto_a_eliminar =  hash_quitar(sala->objetos,interaccion_actual->accion.objeto);
				sala->cantidad_objetos--;
				free(objeto_a_eliminar);
				if(mostrar_mensaje)
						mostrar_mensaje(interaccion_actual->accion.mensaje,interaccion_actual->accion.tipo, aux);
				return true;
		}
		return false;
}
 /* Funcion que recibe la sala, una interaccion  y una funcion(mostrar_mensaje), si logra realizar la interaccion y la funcion mostar mensaje non es NULLse invocará
  * con el mensaje a mostrar, el tipo de acción que representa el
  * mensaje y un puntero auxiliar del usuario.
  * devuelve true si logra realizar la interaccion y false en caso contrario
  */
bool reemplazar_objeto(sala_t *sala,struct interaccion *interaccion_actual, void (*mostrar_mensaje)(const char *mensaje,enum tipo_accion accion,void *aux),void *aux)
{
		if(hash_contiene(sala->objetos_en_posecion, interaccion_actual->objeto)){
				struct objeto *objeto_actual = hash_obtener(sala->objetos,interaccion_actual->accion.objeto);
				hash_insertar(sala->objetos_conocidos,interaccion_actual->accion.objeto ,objeto_actual, NULL);
				hash_quitar(sala->objetos_conocidos,interaccion_actual->objeto_parametro);
				struct objeto *objeto_eliminado =  hash_quitar(sala->objetos,interaccion_actual->objeto_parametro);
				free(objeto_eliminado);
				sala->cantidad_objetos--;
				if(mostrar_mensaje)
						mostrar_mensaje(interaccion_actual->accion.mensaje,interaccion_actual->accion.tipo, aux);
				return true;
		}
		return false;
}
 /* Funcion que recibe  una interaccion, cantidad de interraciones hechas, y una funcion(mostrar_mensaje)
  * se encarga de realizar la interaccion en caso de ser valida e invoca a mostrar mensaje que se invocará
  * (si no es NULL) con el mensaje a mostrar, el tipo de acción que representa el
  * mensaje y un puntero auxiliar del usuario.
  */
void realizar_interaccion(struct interaccion *interaccion_actual,sala_t *sala, int *cantidad_interacciones, void (*mostrar_mensaje)(const char *mensaje,enum tipo_accion accion,void *aux),void *aux)
{

	switch(interaccion_actual->accion.tipo){
			case DESCUBRIR_OBJETO:
					if(descubrir_objeto(sala,interaccion_actual,mostrar_mensaje,aux))
							(*cantidad_interacciones)++;

					
			break;
			case ESCAPAR:
					if(escapar(sala,interaccion_actual,mostrar_mensaje,aux))
							(*cantidad_interacciones)++;
			break;
			case ELIMINAR_OBJETO:
					if(eliminar_objeto(sala,interaccion_actual,mostrar_mensaje,aux))
							(*cantidad_interacciones)++;
			break;
			case REEMPLAZAR_OBJETO:
					if(reemplazar_objeto(sala,interaccion_actual,mostrar_mensaje,aux))
							(*cantidad_interacciones)++;
			break;
			case MOSTRAR_MENSAJE:
					if(hash_contiene(sala->objetos_conocidos, interaccion_actual->objeto) && mostrar_mensaje != NULL){
						mostrar_mensaje(interaccion_actual->accion.mensaje,MOSTRAR_MENSAJE,aux);
						(*cantidad_interacciones)++;
					}
			default:
					return;
			break;

	}

		

}


int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,const char *objeto1, const char *objeto2,
	void (*mostrar_mensaje)(const char *mensaje,enum tipo_accion accion,void *aux),
			      void *aux)
{
		if(!sala || !verbo || !objeto1 || !objeto2 )
				return 0;
		lista_iterador_t *it = NULL;
		int cantidad_interacciones = 0;
		struct interaccion interaccion;
		strcpy(interaccion.objeto,objeto1);
		strcpy(interaccion.verbo,verbo);
		strcpy(interaccion.objeto_parametro,objeto2);
		if(hash_contiene(sala->objetos_conocidos,objeto1) || hash_contiene(sala->objetos_en_posecion,objeto1)){
				for( it =lista_iterador_crear(sala->interacciones) ; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)){
						struct interaccion *interaccion_actual = lista_iterador_elemento_actual(it);
						if(comparar_interaccion(interaccion_actual, interaccion)){
								realizar_interaccion(interaccion_actual,sala, &cantidad_interacciones, mostrar_mensaje, aux);
						}
				}
		}
		lista_iterador_destruir(it);
		return cantidad_interacciones;

}
