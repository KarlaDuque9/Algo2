#include "abb.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

abb_t *abb_crear(abb_comparador comparador)
{
		abb_t *abb_nuevo = calloc(1, sizeof(abb_t));
		if(abb_nuevo == NULL)
				return NULL;
		abb_nuevo->comparador = comparador;
		return abb_nuevo;
}

nodo_abb_t *insertar_nodo(nodo_abb_t *nodo_raiz, void *elemento ,abb_comparador comparador, size_t *tamanio )
{	
		if(nodo_raiz == NULL){
				nodo_abb_t *nuevo_nodo = calloc(1, sizeof(nodo_abb_t));
				if(nuevo_nodo== NULL)
						return NULL;
				nuevo_nodo->elemento = elemento;
				(*tamanio)++;
				return nuevo_nodo;
		}

		int comparacion = comparador(elemento,nodo_raiz->elemento);
		if(comparacion <= 0){
				nodo_raiz->izquierda = insertar_nodo(nodo_raiz->izquierda, elemento, comparador, tamanio);
		}else{
				nodo_raiz->derecha = insertar_nodo(nodo_raiz->derecha, elemento, comparador, tamanio);
		}	
		return nodo_raiz;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
		if(arbol == NULL)
				return NULL;
		if(arbol->comparador ==  NULL)
				return NULL;		
		arbol->nodo_raiz = insertar_nodo(arbol->nodo_raiz, elemento, arbol->comparador, &arbol->tamanio);

	return arbol;
}
nodo_abb_t *extraer_mas_derecho(nodo_abb_t *nodo_raiz,nodo_abb_t **extraido)
{
		if(nodo_raiz->derecha == NULL){
				*extraido = nodo_raiz;
				return nodo_raiz->izquierda;
		}
		nodo_raiz->derecha = extraer_mas_derecho(nodo_raiz->derecha,extraido);
		return nodo_raiz;
}

nodo_abb_t *quitar_nodo_abb(nodo_abb_t *nodo_raiz, void *elemento, abb_comparador comparador, void **elemento_a_quitar,  size_t *tamanio)
{	


		if(nodo_raiz == NULL)
				return NULL;
		int comparacion = comparador(elemento,nodo_raiz->elemento);
		if(comparacion == 0){

				nodo_abb_t *derecha = nodo_raiz->derecha;
				nodo_abb_t *izquierda = nodo_raiz->izquierda;

				if(derecha !=NULL && izquierda !=NULL){

						nodo_abb_t *extraido = NULL;
						nodo_raiz->izquierda = extraer_mas_derecho(nodo_raiz->izquierda,&extraido);
						*elemento_a_quitar = nodo_raiz->elemento;
						nodo_raiz->elemento = extraido->elemento;
						(*tamanio)--;
						free(extraido);
						return nodo_raiz;
				}else if(derecha != NULL){
						*elemento_a_quitar = nodo_raiz->elemento;
						free(nodo_raiz);
						(*tamanio)--;
						return derecha;
				}else if(izquierda != NULL){
						*elemento_a_quitar = nodo_raiz->elemento;
						free(nodo_raiz);
						(*tamanio)--;
						return izquierda;
				}else{
						*elemento_a_quitar = nodo_raiz->elemento;
						(*tamanio)--;
						free(nodo_raiz);
						return NULL;
				}
		}
		if(comparacion <0)
				nodo_raiz->izquierda = quitar_nodo_abb(nodo_raiz->izquierda, elemento, comparador,elemento_a_quitar, tamanio);
		nodo_raiz->derecha = quitar_nodo_abb(nodo_raiz->derecha, elemento, comparador, elemento_a_quitar, tamanio);
		return nodo_raiz;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{

		if(arbol == NULL)
				return NULL;
		if(arbol->comparador == NULL)
				return NULL;
		void *elemento_a_quitar = NULL;
		arbol->nodo_raiz = quitar_nodo_abb(arbol->nodo_raiz,elemento, arbol->comparador,&elemento_a_quitar, &arbol->tamanio);

	return elemento_a_quitar;
}
void *abb_buscar_en_nodos(nodo_abb_t *nodo_raiz, void *buscado,abb_comparador comparador)
{
		if(nodo_raiz == NULL)
				return NULL;
		int comparacion = comparador(buscado, nodo_raiz->elemento);
		if(comparacion == 0)
				return nodo_raiz->elemento;
		else if(comparacion < 0)
				return abb_buscar_en_nodos(nodo_raiz->izquierda, buscado, comparador);
		return abb_buscar_en_nodos(nodo_raiz->derecha, buscado, comparador);

}
void *abb_buscar(abb_t *arbol, void *elemento)
{
		if(arbol == NULL)
				return NULL;
		if(arbol->comparador == NULL)
				return NULL;
		return abb_buscar_en_nodos(arbol->nodo_raiz,elemento, arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
		if(arbol == NULL)
				return true;
		else if(arbol->tamanio == 0)
				return true;
		return false;
}

size_t abb_tamanio(abb_t *arbol)
{
		if(abb_vacio(arbol))
				return 0;
		return arbol->tamanio;
}
void destruir_nodos_abb( nodo_abb_t *nodo_raiz)
{
		if(nodo_raiz == NULL)
				return;
		destruir_nodos_abb(nodo_raiz->izquierda);
		destruir_nodos_abb(nodo_raiz->derecha);
		free(nodo_raiz);
}

void abb_destruir(abb_t *arbol)
{
		if(arbol == NULL)
				return;
		destruir_nodos_abb(arbol->nodo_raiz);
		free(arbol);																													
}
void destruir_nodos_y_elementos( nodo_abb_t *nodo_raiz, void (*destructor)(void *))
{
		if(nodo_raiz == NULL)
				return;
		destruir_nodos_y_elementos(nodo_raiz->izquierda, destructor);
		destruir_nodos_y_elementos(nodo_raiz->derecha, destructor);
		if(destructor !=NULL)
				destructor(nodo_raiz->elemento);
		free(nodo_raiz);
		
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
		if(arbol == NULL)
				return;
		destruir_nodos_y_elementos(arbol->nodo_raiz, destructor);
		free(arbol);
}
void abb_con_cada_elemento_inorden(nodo_abb_t *nodo_raiz,bool (*funcion)(void *, void *), void *aux, size_t *cantidad,bool *seguir_recorriendo)
{
		if(nodo_raiz == NULL || *seguir_recorriendo == false)
				return;
		abb_con_cada_elemento_inorden(nodo_raiz->izquierda,funcion, aux, cantidad,seguir_recorriendo);
		if(*seguir_recorriendo == false)
				return;
		if(funcion(nodo_raiz->elemento, aux) == false)
				*seguir_recorriendo = false;
		(*cantidad)++;
		abb_con_cada_elemento_inorden(nodo_raiz->derecha,funcion, aux, cantidad,seguir_recorriendo);
}


void abb_con_cada_elemento_preorden(nodo_abb_t *nodo_raiz,bool (*funcion)(void *, void *), void *aux, size_t *cantidad,bool *seguir_recorriendo)
{
		if(nodo_raiz == NULL || *seguir_recorriendo == false)
				return;
		if(funcion(nodo_raiz->elemento, aux) == false)
				*seguir_recorriendo = false;
		(*cantidad)++;
		abb_con_cada_elemento_preorden(nodo_raiz->izquierda,funcion, aux, cantidad, seguir_recorriendo);
		abb_con_cada_elemento_preorden(nodo_raiz->derecha,funcion, aux, cantidad, seguir_recorriendo);
}


void  abb_con_cada_elemento_postorden(nodo_abb_t *nodo_raiz,bool (*funcion)(void *, void *), void *aux, size_t *cantidad , bool *seguir_recorriendo)
{
		if(nodo_raiz == NULL || *seguir_recorriendo ==false)
				return;

		abb_con_cada_elemento_postorden(nodo_raiz->izquierda,funcion, aux, cantidad, seguir_recorriendo);
		abb_con_cada_elemento_postorden(nodo_raiz->derecha,funcion, aux, cantidad, seguir_recorriendo);
		if(*seguir_recorriendo ==false)
				return;
		if(funcion(nodo_raiz->elemento, aux)== false)
				*seguir_recorriendo = false;
		(*cantidad)++;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
		bool seguir_recorriendo = true;
		size_t cantidad =0;
		if(arbol == NULL || funcion == NULL)
				return 0;

		switch (recorrido){
				case INORDEN:
						abb_con_cada_elemento_inorden(arbol->nodo_raiz,funcion,aux, &cantidad, &seguir_recorriendo);
						break;
				case PREORDEN:
						abb_con_cada_elemento_preorden(arbol->nodo_raiz,funcion,aux, &cantidad, &seguir_recorriendo);
						break;
				case POSTORDEN:
						abb_con_cada_elemento_postorden(arbol->nodo_raiz,funcion,aux, &cantidad, &seguir_recorriendo);
						break;
				default:
						break;
		}
	return cantidad;
}


void abb_recorrer_inorden(nodo_abb_t *nodo_raiz,void **array, size_t tamanio_array, size_t *cantidad)
{
		if(nodo_raiz == NULL)
				return;
		if(tamanio_array -1 == (*cantidad) )
				return;
		abb_recorrer_inorden(nodo_raiz->izquierda,array, tamanio_array, cantidad);
		array[*cantidad] = nodo_raiz->elemento;
		(*cantidad)++;
		abb_recorrer_inorden(nodo_raiz->derecha,array, tamanio_array, cantidad);
}


void abb_recorrer_preorden(nodo_abb_t *nodo_raiz,void **array, size_t tamanio_array, size_t *cantidad)
{
		if(nodo_raiz == NULL)
				return;
		if(tamanio_array -1 == (*cantidad) )
				return;
		array[*cantidad] = nodo_raiz->elemento;
		(*cantidad)++;
		abb_recorrer_preorden(nodo_raiz->izquierda,array, tamanio_array, cantidad);
		abb_recorrer_preorden(nodo_raiz->derecha,array, tamanio_array, cantidad);
}


void abb_recorrer_postorden(nodo_abb_t *nodo_raiz,void **array, size_t tamanio_array, size_t *cantidad)
{
		if(nodo_raiz == NULL)
				return;
		if(tamanio_array -1 == (*cantidad) )
				return;
		abb_recorrer_postorden(nodo_raiz->derecha,array, tamanio_array, cantidad);
		array[*cantidad] = nodo_raiz->elemento;
		(*cantidad)++;
		abb_recorrer_postorden(nodo_raiz->izquierda,array, tamanio_array, cantidad);
}



size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
		size_t cantidad =0;
		if(arbol == NULL || array == NULL || tamanio_array == 0)
				return 0;

		switch (recorrido){
				case INORDEN:
						abb_recorrer_inorden(arbol->nodo_raiz,array, tamanio_array, &cantidad);
						break;
				case PREORDEN:
						abb_recorrer_preorden(arbol->nodo_raiz,array, tamanio_array, &cantidad);
						break;
				case POSTORDEN:
						abb_recorrer_postorden(arbol->nodo_raiz,array, tamanio_array, &cantidad);
						break;
				default:
						break;
		}
	return cantidad;
}
