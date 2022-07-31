#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"
#define MAX_VECTOR 30


struct vector_pruebas{
		int vector[MAX_VECTOR];
		int tope;
};
int comparar_enteros(void *c1, void *c2)
{
	int *cosa1 = c1;
	int *cosa2 = c2;
	return (*cosa1) - (*cosa2);
}

void crear_una_ABB_me_devuelve_una_tamanio_0_y_un_ABB_vacio()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		pa2m_afirmar(arbol !=NULL , "El ABB se creo correctamente.");
		pa2m_afirmar(abb_vacio(arbol) == true, "El arbol creado esta vacio.");
		pa2m_afirmar(abb_tamanio(arbol) == 0,"El tamanio de un arbol vacio es 0.");
		abb_destruir(arbol);
}
void insertar_en_un_ABB_NULL_es_un_error()
{
		int numero = 7;
		pa2m_afirmar(abb_insertar(NULL,&numero) ==NULL, "No se puede insertar en un ABB NULL");
}

void insertar_en_un_ABB_aumenta_el_tamanio_y_lo_agrega_al_ABB()
{		
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 6;
		int numero4 = 9;
		pa2m_afirmar(abb_vacio(arbol) == true, "El arbol todavvia esta vacio por no haber insrtado elementos.");
		pa2m_afirmar(abb_tamanio(arbol) == 0,"El tamanio de un arbol vacio es 0.");		
		pa2m_afirmar(abb_insertar(arbol,&numero1) !=NULL, "Se puede insertar en un ABB vacio.");
		pa2m_afirmar(abb_tamanio(arbol) == 1,"El tamanio del abb aumento a 1.");

		pa2m_afirmar(abb_insertar(arbol,&numero2) !=NULL, "Se puede insertar otro elemento en el ABB.");
		pa2m_afirmar(abb_tamanio(arbol) == 2,"El tamanio del abb aumento a 2.");

		pa2m_afirmar(abb_insertar(arbol,&numero3) !=NULL, "Se puede insertar otro elemento en el ABB.");
		pa2m_afirmar(abb_tamanio(arbol) == 3,"El tamanio del abb aumento a 3.");

		pa2m_afirmar(abb_insertar(arbol,&numero4) !=NULL, "Se puede insertar otro elemento en el ABB.");
		pa2m_afirmar(abb_tamanio(arbol) == 4,"El tamanio del abb aumento a 4.");


		abb_destruir_todo(arbol, NULL);

}
void eliminar_en_un_ABB_NULL_es_un_error()
{
	int numero = 5;
	pa2m_afirmar(abb_quitar(NULL,&numero)==NULL,"No puedo quitar un elemento de un arbol NULL.");

}

void eliminar_en_un_ABB_disminuye_el_tamanio_y_devuelve_el_elemento_a_eliminar()
{		
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 6;
		int numero4 = 2;
		int numero5 = 4;
		int numero6 = 1;
		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero4);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);

		pa2m_afirmar(abb_tamanio(arbol) == 6,"El tamanio del abb es 6.");
		pa2m_afirmar(abb_quitar(arbol,&numero4) == &numero4,"Puedo eliminar un nodo con un hijo.");
		pa2m_afirmar(abb_tamanio(arbol) == 5,"El tamanio del abb luego de eliminar es 5");

		pa2m_afirmar(abb_quitar(arbol,&numero2) == &numero2,"Puedo eliminar un nodo con dos hijos.");
		pa2m_afirmar(abb_tamanio(arbol) == 4,"El tamanio del abb luego de eliminar es 4");

		pa2m_afirmar(abb_quitar(arbol,&numero6) == &numero6,"Puedo eliminar un nodo hoja.");
		pa2m_afirmar(abb_tamanio(arbol) == 3,"El tamanio del abb luego de eliminar es 3");

		pa2m_afirmar(abb_quitar(arbol,&numero1) == &numero1,"Puedo eliminar la raiz del ABB.");
		pa2m_afirmar(abb_tamanio(arbol) == 2,"El tamanio del abb luego de eliminar es 2");

		abb_destruir(arbol);

}

void pruebas_buscar()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 6;
		int numero4 = 2;
		int numero5 = 4;
		int numero6 = 1;
		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero4);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);
		pa2m_afirmar(abb_buscar(NULL,&numero2) == NULL,"No puedo buscar en un arbol NULL.");
		pa2m_afirmar(abb_buscar(arbol,&numero2) == &numero2,"Puedo encontrar un elemento en un nodo que tiene dos hijos.");
		pa2m_afirmar(abb_buscar(arbol,&numero6) == &numero6,"Puedo encontrar un elemento en un nodo hoja.");
		pa2m_afirmar(abb_buscar(arbol,&numero4) == &numero4,"Puedo encontrar un elemento en un nodo que tiene un hijo.");
		abb_destruir(arbol);

}



void pruebas_recorrido_interno_postorden_con_el_tamanio_del_array_mas_pequenio_que_los_elementos_del_arbol()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 1;
		int numero5 = 4;
		int numero6 = 15;
		int numero7 = 9;
		int numero8 = 7;

		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);
		abb_insertar(arbol,&numero7);
		abb_insertar(arbol,&numero8);
		int *array[4]; 
		size_t valor = abb_recorrer(arbol, POSTORDEN,(void **)array ,4);
		pa2m_afirmar(valor == 4,"Recorre un abb con mas elementos que posiciones en el array y se devuelve el tope del array.");
		pa2m_afirmar(array[0] == &numero3,"El primer elemento del array es el correcto");
		pa2m_afirmar(array[1] == &numero5,"El segundo elemento del array es el correcto");
		pa2m_afirmar(array[2] == &numero8,"El tercer elemento del array es el correcto");
		pa2m_afirmar(array[3] == &numero7,"El cuarto elemento del array es el correcto");


		abb_destruir(arbol);

}
void pruebas_recorrido_interno_postorden_con_el_tamanio_del_array_mas_grande_que_los_elementos_del_arbol()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 1;
		int numero5 = 4;
		int numero6 = 15;
		int numero7 = 9;
		int numero8 = 7;

		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);
		abb_insertar(arbol,&numero7);
		abb_insertar(arbol,&numero8);
		int *array[20]; 
		size_t valor = abb_recorrer(arbol, POSTORDEN,(void **)array ,20);
		pa2m_afirmar(valor == 7,"Recorre un abb con menos elementos que posiciones en el array y se devuelve la cantidad correcta.");
		pa2m_afirmar(array[0] == &numero3,"El primer elemento del array es el correcto");
		pa2m_afirmar(array[1] == &numero5,"El segundo elemento del array es el correcto");
		pa2m_afirmar(array[2] == &numero8,"El tercer elemento del array es el correcto");
		pa2m_afirmar(array[3] == &numero7,"El cuarto elemento del array es el correcto");

		abb_destruir(arbol);
}
void pruebas_recorrido_interno_postorden()
{
	pruebas_recorrido_interno_postorden_con_el_tamanio_del_array_mas_pequenio_que_los_elementos_del_arbol();
	pruebas_recorrido_interno_postorden_con_el_tamanio_del_array_mas_grande_que_los_elementos_del_arbol();


}

void pruebas_recorrido_interno_inorden_con_el_tamanio_del_array_mas_pequenio_que_los_elementos_del_arbol()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 1;
		int numero5 = 4;
		int numero6 = 15;
		int numero7 = 9;
		int numero8 = 7;

		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);
		abb_insertar(arbol,&numero7);
		abb_insertar(arbol,&numero8);
		int *array[4]; 
		size_t valor =  abb_recorrer(arbol, INORDEN,(void **)array ,4);
		pa2m_afirmar(valor == 4,"Recorre un abb con mas elementos que posiciones en el array y se devuelve el tope del array.");
		pa2m_afirmar(array[0] == &numero3,"El primer elemento del array es el correcto");
		pa2m_afirmar(array[1] == &numero1,"El segundo elemento del array es el correcto");
		pa2m_afirmar(array[2] == &numero5,"El tercer elemento del array es el correcto");
		pa2m_afirmar(array[3] == &numero2,"El cuarto elemento del array es el correcto");

		abb_destruir(arbol);

}

void pruebas_recorrido_interno_inorden_con_el_tamanio_del_array_mas_grande_que_los_elementos_del_arbol()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 1;
		int numero5 = 4;
		int numero6 = 15;
		int numero7 = 9;
		int numero8 = 7;

		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);
		abb_insertar(arbol,&numero7);
		abb_insertar(arbol,&numero8);
		int *array[20]; 
		size_t valor = abb_recorrer(arbol, INORDEN,(void **)array ,20);
		pa2m_afirmar(valor == 7,"Recorre un abb con menos elementos que posiciones en el array y se devuelve la cantidad correcta.");
		pa2m_afirmar(array[0] == &numero3,"El primer elemento del array es el correcto");
		pa2m_afirmar(array[1] == &numero1,"El segundo elemento del array es el correcto");
		pa2m_afirmar(array[2] == &numero5,"El tercer elemento del array es el correcto");
		pa2m_afirmar(array[3] == &numero2,"El cuarto elemento del array es el correcto");

		abb_destruir(arbol);
}
void pruebas_recorrido_interno_inorden()
{
	pruebas_recorrido_interno_inorden_con_el_tamanio_del_array_mas_pequenio_que_los_elementos_del_arbol();
	pruebas_recorrido_interno_inorden_con_el_tamanio_del_array_mas_grande_que_los_elementos_del_arbol();


}
void pruebas_recorrido_interno_preorden_con_el_tamanio_del_array_mas_pequenio_que_los_elementos_del_arbol()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 1;
		int numero5 = 4;
		int numero6 = 15;
		int numero7 = 9;
		int numero8 = 7;

		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);
		abb_insertar(arbol,&numero7);
		abb_insertar(arbol,&numero8);
		int *array[4]; 
		size_t valor = abb_recorrer(arbol, PREORDEN,(void **)array ,4);
		pa2m_afirmar(valor == 4,"Recorre un abb con mas elementos que posiciones en el array y se devuelve el tope del array.");
		pa2m_afirmar(array[0] == &numero1,"El primer elemento del array es el correcto");
		pa2m_afirmar(array[1] == &numero3,"El segundo elemento del array es el correcto");
		pa2m_afirmar(array[2] == &numero2,"El tercer elemento del array es el correcto");
		pa2m_afirmar(array[3] == &numero5,"El cuarto elemento del array es el correcto");


		abb_destruir(arbol);

}
void pruebas_recorrido_interno_preorden_con_el_tamanio_del_array_mas_grande_que_los_elementos_del_arbol()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 1;
		int numero5 = 4;
		int numero6 = 15;
		int numero7 = 9;
		int numero8 = 7;

		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);
		abb_insertar(arbol,&numero7);
		abb_insertar(arbol,&numero8);
		int *array[20]; 
		size_t valor = abb_recorrer(arbol, PREORDEN,(void **)array ,20);
		pa2m_afirmar(valor == 7,"Recorre un abb con menos elementos que posiciones en el array y se devuelve la cantidad correcta.");
		pa2m_afirmar(array[0] == &numero1,"El primer elemento del array es el correcto");
		pa2m_afirmar(array[1] == &numero3,"El segundo elemento del array es el correcto");
		pa2m_afirmar(array[2] == &numero2,"El tercer elemento del array es el correcto");
		pa2m_afirmar(array[3] == &numero5,"El cuarto elemento del array es el correcto");

		abb_destruir(arbol);
}
void pruebas_recorrido_interno_preorden()
{
	pruebas_recorrido_interno_preorden_con_el_tamanio_del_array_mas_pequenio_que_los_elementos_del_arbol();
	pruebas_recorrido_interno_preorden_con_el_tamanio_del_array_mas_grande_que_los_elementos_del_arbol();
}
bool guardar_hasta_5(void *elemento, void *extra)
{
	
	if (elemento) {
		struct vector_pruebas *vector ;
		vector = (struct vector_pruebas *)extra;
		vector->vector[vector->tope] = *(int*) elemento;
		vector->tope++;
		if((*(int *)elemento) == 5)
			return false;
	}
	return true;
}
void pruebas_recorrer_inorden()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 1;
		int numero5 = 4;
		int numero6 = 15;
		int numero7 = 9;
		int numero8 = 7;

		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);
		abb_insertar(arbol,&numero7);
		abb_insertar(arbol,&numero8);

		struct vector_pruebas vector;
		vector.tope = 0;
		struct vector_pruebas *vector1 = &vector;
		pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, guardar_hasta_5 , (void *)vector1)== 4 ,"Recorre cada elemento y devuelve la cantidad correcta");
		pa2m_afirmar(vector1->vector[0] == numero3, "El primer elemento guardado esel correcto");
		pa2m_afirmar(vector1->vector[1] == numero1, "El primer elemento guardado esel correcto");
		pa2m_afirmar(vector1->vector[2] == numero5, "El primer elemento guardado esel correcto");
		pa2m_afirmar(vector1->vector[3] == numero2, "El primer elemento guardado esel correcto");

		abb_destruir(arbol);

}
void pruebas_recorrer_preorden()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 1;
		int numero5 = 4;
		int numero6 = 15;
		int numero7 = 9;
		int numero8 = 7;

		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);
		abb_insertar(arbol,&numero7);
		abb_insertar(arbol,&numero8);

		struct vector_pruebas vector;
		vector.tope = 0;
		struct vector_pruebas *vector1 = &vector;
		pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, guardar_hasta_5 , (void *)vector1)== 3 ,"Recorre cada elemento y devuelve la cantidad correcta");
		pa2m_afirmar(vector1->vector[0] == numero1, "El primer elemento guardado es el correcto");
		pa2m_afirmar(vector1->vector[1] == numero3, "El primer elemento guardado es el correcto");
		pa2m_afirmar(vector1->vector[2] == numero2, "El primer elemento guardado es el correcto");

		abb_destruir(arbol);
}

void pruebas_recorrer_postorden()
{
		abb_t *arbol = abb_crear(comparar_enteros);
		int numero1 = 3;
		int numero2 = 5;
		int numero3 = 1;
		int numero5 = 4;
		int numero6 = 15;
		int numero7 = 9;
		int numero8 = 7;

		abb_insertar(arbol,&numero1);
		abb_insertar(arbol,&numero2);
		abb_insertar(arbol,&numero3);
		abb_insertar(arbol,&numero5);
		abb_insertar(arbol,&numero6);
		abb_insertar(arbol,&numero7);
		abb_insertar(arbol,&numero8);

		struct vector_pruebas vector;
		vector.tope = 0;
		struct vector_pruebas *vector1 = &vector;
		pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, guardar_hasta_5 , (void *)vector1)== 6 ,"Recorre cada elemento y devuelve la cantidad correcta");
		pa2m_afirmar(vector1->vector[0] == numero3, "El primer elemento guardado es el correcto");
		pa2m_afirmar(vector1->vector[1] == numero5, "El primer elemento guardado es el correcto");
		pa2m_afirmar(vector1->vector[2] == numero8, "El primer elemento guardado es el correcto");
		pa2m_afirmar(vector1->vector[3] == numero7 , "El primer elemento guardado es el correcto");

		abb_destruir(arbol);
}
int main()
{
		pa2m_nuevo_grupo("Pruebas de ABB");
		pa2m_nuevo_grupo("Pruebas de ABB crear");
		crear_una_ABB_me_devuelve_una_tamanio_0_y_un_ABB_vacio();
		pa2m_nuevo_grupo("pruebas de ABB insertar");
		insertar_en_un_ABB_NULL_es_un_error();
		insertar_en_un_ABB_aumenta_el_tamanio_y_lo_agrega_al_ABB();
		pa2m_nuevo_grupo("pruebas de ABB quitar.");
		eliminar_en_un_ABB_NULL_es_un_error();
		eliminar_en_un_ABB_disminuye_el_tamanio_y_devuelve_el_elemento_a_eliminar();
		pa2m_nuevo_grupo("Pruebas de buscar.");
		pruebas_buscar();
		pa2m_nuevo_grupo("Pruebas de recorrido con array.");
		pa2m_nuevo_grupo("recorrido postorden.");
		pruebas_recorrido_interno_postorden();
		pa2m_nuevo_grupo("recorrido inorden.");
		pruebas_recorrido_interno_inorden();
		pa2m_nuevo_grupo("recorrido preorden.");
		pruebas_recorrido_interno_preorden();

		pa2m_nuevo_grupo("recorrido con cada elemento inorden.");
		pruebas_recorrer_inorden();
		pa2m_nuevo_grupo("recorrido con cada elemento preorden.");
		pruebas_recorrer_preorden();
		pa2m_nuevo_grupo("recorrido con cada elemento postorden.");
		pruebas_recorrer_postorden();

		return pa2m_mostrar_reporte();
}