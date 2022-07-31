#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define CAPACIDAD_MINIMA 3
#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U
#define FACTOR_REHASH 0.70

typedef struct par{
	void *elemento;
	char *clave;
}par_t;

struct hash {
	lista_t** tabla;
	size_t capacidad;
	size_t cant_elementos;
};


// La funcion de hash fue obtenida del link: http://ctips.pbworks.com/w/page/7277591/FNV%20Hash

size_t FNV32(const char *s)
{
    size_t hash = FNV_OFFSET_32, i;
    size_t len = strlen(s);
    for(i = 0; i < len; i++){
        hash = hash ^(size_t) (s[i]); // xor next byte into the bottom of the hash
        hash = hash * FNV_PRIME_32; // Multiply by prime number found to work well
    }
    return hash;
} 
/*
 * funcion que recibe una clave y devuelve una copia de dicha clave 
 */
char *duplicar_clave(const char *_clave)
{
	if (!_clave)
		return NULL;

	char *clave = malloc(strlen(_clave) + 1);
	if (!clave)
		return NULL;

	strcpy(clave, _clave);
	return clave;
}
hash_t *hash_crear(size_t capacidad)
{
		struct hash *hash = malloc(sizeof(struct hash));
		if(hash == NULL)
				return NULL;
		hash->capacidad  = capacidad < CAPACIDAD_MINIMA ? CAPACIDAD_MINIMA : capacidad;
		hash->cant_elementos = 0;
		hash->tabla = malloc(hash->capacidad*sizeof(lista_t*));
		if(!hash->tabla)
				return NULL;
		bool hay_error = false;
		size_t j=0;
		while(j <hash->capacidad){
				hash->tabla[j] = lista_crear();
				if(hash->tabla[j] == NULL)
						hay_error = true;
				j++;
		}
		if(hay_error == true){
			hash_destruir(hash);
			return NULL;
		}

		return hash;
}
/*
 * funcion que recibe una clave y se encarga de devolver un numero 
 * 
 */
size_t funcion_hash(const char *clave)
{
	
	return FNV32(clave);
}
/*
 * funcion que recibe un elemento y una clave y devuelve 0 si la clave coincide con la clave del elemento
 *  o devuelve < o > 0 si son distintas.
 */
int comparador(void *elemento, void *_clave)
{
		par_t *actual = elemento;
		char **clave = _clave;
		return strcmp(actual->clave,*clave);
}
/*
 * funcion que recibe un elemento y una clave y devuelve true si la clave del elemento es distna a la pasada por parametro
 *  o false en caso contrario
 */
bool comparar_clave (void * elemento , void *clave){
	return comparador(elemento,clave) != 0;
}
/*
 * funcion que recibe un elemento y una clave y se encarga de crear memoria para un part_t pidiendo memoria necesaria para el 
 *  y se le asigna el elmento del par el elmento pasado por pararmetro y tambien la clave del par con la clave pasada por parametro
 */
par_t *part_crear(void *elemento, const char *clave)
{
	par_t *nuevo = malloc(sizeof(par_t));
	if(!nuevo)
			return NULL;
	nuevo->elemento = elemento;
	nuevo->clave = duplicar_clave (clave);
	if (!nuevo->clave){
			free(nuevo);
			return NULL;
	}
	return nuevo;
}

/*
 * funcion que recibe un hash y un par(elemento,valor) y consiste insertar dicho par en el hash
 *  
 */
hash_t *hash_insertar_en_lista(hash_t *hash, par_t *nuevo_elemento)
{
	size_t posicion = funcion_hash(nuevo_elemento->clave)%hash->capacidad;
	hash->tabla[posicion] = lista_insertar_en_posicion(hash->tabla[posicion], nuevo_elemento,0);
	hash->cant_elementos++;
	return hash;
}
/*
 * funcion que recibe lista , un hash y se encarga de insertar todos los elementos que estan en la lista  en el hash pasado por 
 *  parametro.y devuelve el hash en caso de poder insertar o NULL en caso de error.
 */
hash_t *rehashear_lista(lista_t *lista, hash_t *hash_nuevo)
{
		size_t tamanio = lista_tamanio(lista);
		size_t i =0 ; 
		bool hay_error = false;
		while(i < tamanio && !hay_error){
				par_t *elemento = lista_quitar_de_posicion(lista, 0);
				hash_nuevo =  hash_insertar_en_lista(hash_nuevo,elemento);
				if(!hash_nuevo){
						hay_error = true;
					}
				i++;
		}

		if(hay_error){
			hash_destruir(hash_nuevo);
			return NULL;
		}
		return hash_nuevo;
}
/*
 * funcion que recibe un hash y se encarga de crear uno nuevo con mas capacidad y llenar el nuevo hash con el viejo 
 *  devuelve el nuevo hash o NULL en caso de error.
 */
hash_t *rehash(hash_t *hash)
{
		hash_t *hash_nuevo = hash_crear(hash->capacidad*2);
		if(!hash_nuevo)
				return NULL;
		bool hay_error = false;
		size_t i =0;
		while(i < hash->capacidad && !hay_error){
			hash_nuevo =  rehashear_lista(hash->tabla[i], hash_nuevo);
			if(!hash_nuevo){
					hay_error = true;

			}
			i++;
		}
		if(hay_error){
				hash_destruir(hash);
				return NULL;
		}
		hash_t temporal = *hash;
		*hash = *hash_nuevo;
		*hash_nuevo = temporal; 
		hash_destruir(hash_nuevo);
		return hash;

}


hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento, void **anterior)
{
	if(!hash || !clave)
			return NULL;
	if((float)hash->cant_elementos/(float)hash->capacidad >= FACTOR_REHASH)
			hash = rehash(hash);
	size_t posicion = funcion_hash(clave)%hash->capacidad;
	par_t *elemento_repetido = lista_buscar_elemento(hash->tabla[posicion],comparador,&clave);
	if(elemento_repetido){
			if(anterior)
					*anterior = elemento_repetido->elemento;
			elemento_repetido->elemento = elemento;
			return hash;
	}
	if(anterior)
			*anterior = *anterior ? NULL : *anterior;
			
	par_t *nuevo_elemento = part_crear(elemento, clave);
	if(!nuevo_elemento){
		hash_destruir(hash);
			return NULL;
	}
	hash =  hash_insertar_en_lista(hash,nuevo_elemento);
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
		if(!hash || !clave)
				return NULL;
		size_t posicion = funcion_hash(clave)%hash->capacidad;
		void *elemento = NULL;
		par_t *elemento_eliminado = lista_buscar_y_eliminar(hash->tabla[posicion],comparar_clave, &clave);
		if(!elemento_eliminado)
				return NULL;
		elemento = elemento_eliminado->elemento;
		free(elemento_eliminado->clave);
		free(elemento_eliminado);
		hash->cant_elementos--;

		return elemento;


}


void *hash_obtener(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
			return NULL;
	size_t posicion = funcion_hash(clave)%hash->capacidad;
	par_t *elemento_actual = lista_buscar_elemento(hash->tabla[posicion],comparador, &clave);
	return !elemento_actual ? NULL : elemento_actual->elemento;

}

bool hash_contiene(hash_t *hash, const char *clave)
{
	par_t *elemento_actual = hash_obtener(hash, clave);
	return elemento_actual ? true : false;
}

size_t hash_cantidad(hash_t *hash)
{
	return !hash ? 0 : hash->cant_elementos;
}

/*
 * Libera la memoria reservada por la lista pero además aplica la función
 * destructora dada (si no es NULL) a cada uno de los elementos presentes en la
 * lista.
 *  
 */
void destruir_lista(lista_t *lista, void (*destructor)(void *))
{
	
		size_t tamanio = lista_tamanio(lista);
		for(size_t i =0 ; i < tamanio ;i++){
				par_t *elemento = lista_quitar_de_posicion(lista, 0);
				if(destructor)
						destructor(elemento->elemento);
				free(elemento->clave);
				free(elemento);
		}
		free(lista);

}


void hash_destruir(hash_t *hash)
{

		hash_destruir_todo(hash, NULL);
}


void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if(!hash)
			return;
	for (int i = 0; i < hash->capacidad; ++i)
			destruir_lista(hash->tabla[i], destructor);
	free(hash->tabla);
	free(hash);
}
/**
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma como primer parámetro. Dicha función puede devolver true si se deben
 * seguir recorriendo elementos o false si se debe dejar de iterar elementos.
 *
 * El puntero aux se pasa como tercer argumento a la función del usuario.
 *
 */
void interar_con_cada_lista(lista_t *lista, size_t *cantidad_claves,
				bool (*f)(const char *clave, void *valor, void *aux),
				void *aux, bool *seguir_recorriendo )
{
		size_t tamanio = lista_tamanio(lista);
		size_t i =0;
		while( i < tamanio && *seguir_recorriendo){
				par_t *elemento = lista_elemento_en_posicion(lista, i);
				(*cantidad_claves)++;
				if(!f(elemento->clave,elemento->elemento, aux))
						*seguir_recorriendo = false;
				i++;				
		}
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
		if( !hash || !f)
				return 0;
		size_t cantidad_claves = 0; 
		bool seguir_recorriendo = true;
		size_t i =0;
		while( i < hash->capacidad && seguir_recorriendo){
				interar_con_cada_lista(hash->tabla[i],&cantidad_claves,f,aux, &seguir_recorriendo);
				i++;
		}
		return cantidad_claves;
}
