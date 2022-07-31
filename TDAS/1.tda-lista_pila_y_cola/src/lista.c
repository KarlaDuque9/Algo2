#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

lista_t *lista_crear()
{
		lista_t *lista = calloc(1, sizeof(lista_t));
		return lista;
}


/**
 * Funcion que recibe un elemento y se encarga de crear un nodo y llenarlo con ese elemento pasado por parametro 
 *
 *Devuelve el nodo ya inicializado en caso de exito o NULL en caso de error.
 * Al finalizar el programa dicho nodo sera liberado.
 */
nodo_t *crear_nodo(void *elemento)
{
		nodo_t *nodo_aux = calloc(1,sizeof(nodo_t));
		if(nodo_aux  == NULL)
				return NULL;
		nodo_aux->elemento = elemento;
		return nodo_aux;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
		if(lista == NULL)
				return NULL;
				
		nodo_t *nodo_aux = crear_nodo(elemento);
		if(nodo_aux  == NULL){
				return NULL;
				lista_destruir(lista);
		}
		if(lista_vacia(lista)){
				lista->nodo_fin = nodo_aux;
				lista->nodo_inicio = nodo_aux;
				lista->cantidad =1;

		}else{
				lista->nodo_fin->siguiente = nodo_aux;
				lista->nodo_fin = nodo_aux;
				lista->cantidad++;
		}
		
		return lista;
}

/**
 * Inserta un elemento en la posicion indicada(a partir de 1), donde 1 es insertar
 * como segundo elemento y 2 es insertar luego del tercers elemento.  
 *
 * Devuelve la lista en caso de exito.
 */
lista_t *lista_insertar_en_posicion_arbitraria(lista_t *lista,
				    size_t posicion , nodo_t *nuevo_nodo)
{
		nodo_t *nodo_aux = lista->nodo_inicio;
		nodo_t *anterior= nodo_aux;
		for (int i = 0; i < posicion; i++){
				anterior = nodo_aux;
				nodo_aux = nodo_aux->siguiente;
		}
		nuevo_nodo->siguiente = nodo_aux;
		anterior->siguiente = nuevo_nodo;
		lista->cantidad++;
		return lista;
}


lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
		if(lista == NULL){
				lista_destruir(lista);
				return NULL;

		}else if(lista->cantidad <= posicion){
				lista = lista_insertar(lista, elemento);
				return lista;
		}
				nodo_t *nuevo_nodo = crear_nodo(elemento);
				if(nuevo_nodo == NULL)
						return NULL;
		if(posicion !=0){
				lista = lista_insertar_en_posicion_arbitraria(lista,posicion, nuevo_nodo);

		}else{
				nuevo_nodo->siguiente = lista->nodo_inicio;
				lista->nodo_inicio = nuevo_nodo;
				lista->cantidad++;
		}
		return lista;
}

void *lista_quitar(lista_t *lista)
{
	if(lista_vacia(lista))
			return NULL;

		void *elemento;
		nodo_t *nodo_aux = lista->nodo_inicio;
		nodo_t *anterior = nodo_aux;
		for (int i = 1 ; i < lista->cantidad; i++){
				anterior = nodo_aux;
				nodo_aux = nodo_aux->siguiente;
		}
		anterior->siguiente = NULL;
		elemento = lista->nodo_fin->elemento;
		lista->nodo_fin = anterior;
		free(nodo_aux);
		lista->cantidad--;
	
	return elemento;
}

/**
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada(a partir de 1), donde 1 es el segundo elemento de la lista.
 *
 * Devuelve el elemento removido de la lista. Antes de devolver el elemento libera el nodo que se queria eliminar 
 *
 */
void *lista_quitar_de_posicion_arbitraria(lista_t *lista, size_t posicion)
{
		void *elemento;
		nodo_t *nodo_aux = lista->nodo_inicio;
		nodo_t *anterior = nodo_aux;
		for (int i = 0; i < posicion; i++){
				anterior = nodo_aux;
				nodo_aux = nodo_aux->siguiente;
		}
		anterior->siguiente = nodo_aux->siguiente;
		elemento = nodo_aux->elemento;
		free(nodo_aux);
		lista->cantidad--;
		return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
		if(lista_vacia(lista))
				return NULL;
		void *elemento;
		if(posicion >= lista->cantidad -1){
				elemento = lista_quitar(lista);
		}else if(posicion !=0){
				elemento = lista_quitar_de_posicion_arbitraria(lista, posicion);
		}else{
				nodo_t *nodo_aux = lista->nodo_inicio;
				elemento = nodo_aux->elemento;
				lista->nodo_inicio = lista->nodo_inicio->siguiente;
				lista->cantidad--;
				free(nodo_aux);
		}
		return elemento;

}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
		if(lista == NULL)
				return NULL;
		if(lista->cantidad <= posicion)
				return NULL;
		nodo_t *nodo_aux = lista->nodo_inicio;
		for (int i = 0; i < posicion; i++){
				nodo_aux = nodo_aux->siguiente;
		}
		return nodo_aux->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
		if(lista_vacia(lista) || comparador == NULL)
				return NULL;
		void *elemento;
		nodo_t *nodo_aux = lista->nodo_inicio;
		bool encontrado = false;
		int i =0;
		while(i < lista->cantidad && encontrado == false){
				if(comparador(nodo_aux->elemento,contexto)==0){
						encontrado = true;
						elemento = nodo_aux->elemento;
				}
				nodo_aux = nodo_aux->siguiente;
				i++;
		}
		if(encontrado == false)
				return NULL;
		return elemento;
}

void *lista_primero(lista_t *lista)
{
		if(lista_vacia(lista))
				return NULL;
		else
				return lista->nodo_inicio->elemento;

}

void *lista_ultimo(lista_t *lista)
{
		if(lista_vacia(lista) || lista->nodo_fin == NULL)
				return NULL;
		else
				return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
		if(lista == NULL)
				return true;
		else if(lista->cantidad == 0)
				return true;
		else
				return false;

}

size_t lista_tamanio(lista_t *lista)
{
	if(lista== NULL)
			return 0;
	return (lista->cantidad);
}

void lista_destruir(lista_t *lista)
{
		if(lista == NULL)
				return;
		size_t i =0;
		while(i < lista->cantidad){
				nodo_t *nodo_aux = lista->nodo_inicio;
				lista->nodo_inicio = lista->nodo_inicio->siguiente;
				free(nodo_aux);
				i++;
		}
		free(lista);		
}


void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
		if(lista == NULL)
				return;
		if(funcion == NULL){
				lista_destruir(lista);
				return;
		}
		size_t i =0;
		while(i < lista->cantidad){
				nodo_t *nodo_aux = lista->nodo_inicio;
				lista->nodo_inicio = lista->nodo_inicio->siguiente;
				funcion(nodo_aux->elemento);
				free(nodo_aux);
				i++;
		}
		free(lista);
		
}


lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
		if(lista == NULL)
				return NULL;
		lista_iterador_t *lista_iteradora = calloc(1, sizeof(lista_iterador_t));
		if(lista_iteradora == NULL)
				return NULL;
		lista_iteradora->lista = lista;
		lista_iteradora->corriente = lista_iteradora->lista->nodo_inicio;
		return lista_iteradora;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{		if(iterador == NULL || lista_vacia(iterador->lista))
				return false;
		return (iterador->corriente!=NULL);
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{		

		if(iterador == NULL || lista_vacia(iterador->lista)){
				return false;
		}
		iterador->corriente = iterador->corriente->siguiente;
		if(lista_iterador_tiene_siguiente(iterador)){
				return true;
		}
		return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
		if(iterador == NULL || lista_vacia(iterador->lista) || iterador->corriente == NULL)
				return NULL;
		return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
		free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
		if(lista_vacia(lista) || funcion == NULL)
				return 0;
		size_t elementos_recorridos = 1;
		nodo_t *aux = lista->nodo_inicio;
		size_t i =0;
		while (i < lista->cantidad && funcion(aux->elemento,contexto) == true){
				elementos_recorridos++;
				aux = aux->siguiente;
				i++;
		}
		if(i == lista->cantidad)
				return (elementos_recorridos -1);

		return elementos_recorridos;
}

