#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

void crear_una_lista_me_devuelve_una_tamanio_0_y_nodo_apuntando_a_NULL()
{
        lista_t *lista =  lista_crear();

        pa2m_afirmar(lista !=NULL,"La lista se creo correctamente.");
        pa2m_afirmar(lista_primero(lista) ==NULL,"La lista creada tiene el nodo inicio NULL.");
        pa2m_afirmar(lista_vacia(lista) == true, "La lista creada esta vacia.");
        pa2m_afirmar(lista_ultimo(lista) ==NULL,"La lista creada tiene el nodo fin  NULL.");
        pa2m_afirmar(lista_tamanio(lista) ==0,"La lista creada tiene cantidad  0.");

        lista_destruir(lista);
}

void lista_vacia_con_lista_NULL_debe_devolver_true()
{
        pa2m_afirmar(lista_vacia(NULL)== true, "La lista no puede estar con elementos si es lista NULL.");
}
void lista_tamanio_si_la_lista_es_NULL_devuelve_0(){
        pa2m_afirmar(lista_tamanio(NULL) ==0,"La lista NULL no tiene tiene cantidad.");
}

void lista_primero_si_la_lista_es_NULL_devuelve_NULL(){
        pa2m_afirmar(lista_primero(NULL) ==NULL,"La lista NULL no tiene nodo primero.");
}
void lista_ultimo_si_la_lista_es_NULL_devuelve_NULL(){
        pa2m_afirmar(lista_ultimo(NULL) ==NULL,"La lista NULL no tiene nodo primero.");
}

void insertar_en_una_lista_nula_es_un_error()
{
        char valor = 'z';
        pa2m_afirmar(lista_insertar_en_posicion(NULL,&valor, 6) == NULL,"No puedo insertar elementos en una lista NULL.");
}

void insertar_un_elemento_nulo_inserta_el_elemento(){
        lista_t *lista =  lista_crear(); 
        pa2m_afirmar(lista_insertar(lista,NULL) !=NULL,"Puedo insertar un elemento NULL.");
        pa2m_afirmar(lista_tamanio(lista) ==1,"El valor de cantidad es el correcto.");
        pa2m_afirmar(lista_ultimo(lista) == NULL,"El tope de la lista es el correcto.");

        lista_destruir(lista);
}


void quitar_elementos_al_final_de_una_lista_nula_es_un_error()
{
        pa2m_afirmar(lista_quitar(NULL)== NULL,"No puedo quitar elementos en una lista NULL.");
}


void insertar_elementos_al_final_de_la_lista_aumenta_la_cantidad_y_el_nodo_ultimo()
{
        lista_t *lista =  lista_crear();
        char valor1 = 'd';
        char valor2 = 'h';
        char valor3 = 'x';
        char valor4 = 'y'; 
        char valor5 = 't';
        char valor6 = 'k'; 
  
        pa2m_afirmar(lista_insertar(lista,&valor1) !=NULL,"Puedo insertar un elemento con la lista vacia.");
        pa2m_afirmar(lista_tamanio(lista)== 1,"El valor de cantidad es 1.");
        pa2m_afirmar(lista_ultimo(lista) == &valor1,"El ultimo elemento de la lista es el correcto.");
        pa2m_afirmar(lista_primero(lista) == &valor1,"El primer elemento de la lista es el correcto.");
        pa2m_afirmar(lista_vacia(lista) == false, "La lista ya no esta vacia.");

        pa2m_afirmar(lista_insertar(lista,&valor2) !=NULL ,"Puedo insertar dos elementos en la lista");
        pa2m_afirmar(lista_tamanio(lista)== 2,"El valor de cantidad es 2");
        pa2m_afirmar(lista_ultimo(lista) == &valor2,"El ultimo elemento de la lista es el correcto.");
       
        pa2m_afirmar(lista_insertar(lista,&valor3) !=NULL,"Puedo insertar tres elementos en la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 3,"El valor de cantidad es 3.");
        pa2m_afirmar(lista_ultimo(lista) == &valor3,"El ultimo elemento de la lista es el correcto.");
        
        pa2m_afirmar(lista_insertar(lista,&valor4) != NULL,"Puedo insertar cuatro elementos en la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 4,"El valor de cantidad es 4.");
        pa2m_afirmar(lista_ultimo(lista) == &valor4,"El ultimo elemento de la lista es el correcto.");

        pa2m_afirmar(lista_insertar(lista,&valor5) != NULL,"Puedo insertar cinco elementos en la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 5,"El valor de cantidad es 5.");
        pa2m_afirmar(lista_ultimo(lista) == &valor5,"El ultimo elemento de la lista es el correcto.");

        pa2m_afirmar(lista_insertar(lista,&valor6) !=NULL,"Puedo insertar otro elemento.");
        pa2m_afirmar(lista_tamanio(lista)== 6,"El valor de cantidad es 6.");
        pa2m_afirmar(lista_ultimo(lista) == &valor6,"El ultimo elemento de la lista es el correcto.");
        lista_destruir(lista);

}
void quitar_elementos_en_posiciones_arbitrarias_de_una_lista_nula_es_un_error()
{
        pa2m_afirmar(lista_quitar_de_posicion(NULL,5) ==NULL,"No puedo quitar un elemento en posicion arbitraria de la lista si la lista es NULL.");
}
void insertar_elementos_en_posiciones_arbitrarias_de_la_lista_aumenta_la_cantidad()
{
        lista_t *lista =  lista_crear();
        char valor1 = 'd';
        char valor2 = 'h';
        char valor3 = 'x';
        char valor4 = 'y'; 
        char valor5 = 't';
        char valor6 = 'k'; 
        pa2m_afirmar(lista_vacia(lista) == true, "La lista esta vacia.");
        pa2m_afirmar(lista_insertar_en_posicion(lista,&valor1,0) !=NULL,"Puedo insertar un elemento en la  posicion 0 en una lista vacia.");
        pa2m_afirmar(lista_tamanio(lista)== 1,"El valor de cantidad es 1.");
        pa2m_afirmar(lista_ultimo(lista) == &valor1,"El ultimo elemento de la lista es el correcto.");
        pa2m_afirmar(lista_primero(lista) == &valor1,"El primer elemento de la lista es el correcto.");
        pa2m_afirmar(lista_vacia(lista) == false, "La lista ya no esta vacia.");

        pa2m_afirmar(lista_insertar_en_posicion(lista,&valor2,0) !=NULL ,"puedo insertar otro elemento en la posicion 0.");
        pa2m_afirmar(lista_tamanio(lista)== 2,"El valor de cantidad es 2");
        pa2m_afirmar(lista_primero(lista) == &valor2,"El primer elemento es el que se acaba de insertar.");
       
        pa2m_afirmar(lista_insertar_en_posicion(lista,&valor3, 6) !=NULL,"No puedo insertar el elemento en una posicion invalida y lo inserta al final.");
        pa2m_afirmar(lista_tamanio(lista)== 3,"El valor de cantidad es 3.");
        pa2m_afirmar(lista_ultimo(lista) == &valor3,"El ultimo elemento de la lista es el correcto.");
        
        pa2m_afirmar(lista_insertar_en_posicion(lista,&valor4, 0) != NULL,"Puedo insertar un elemento en la  posicion 0 en una lista no vacia.");
        pa2m_afirmar(lista_tamanio(lista)== 4,"El valor de cantidad es 4.");
        pa2m_afirmar(lista_primero(lista) == &valor4,"El primer elemento de la lista es el correcto.");

        pa2m_afirmar(lista_insertar_en_posicion(lista,&valor5, 1) != NULL,"Puedo insertar un elemento en una posicion arbitraria en la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 5,"El valor de cantidad es 5.");

        pa2m_afirmar(lista_insertar_en_posicion(lista,&valor6,5) !=NULL,"Puedo insertar otro elemento en una posicion arbitraria.");
        pa2m_afirmar(lista_tamanio(lista)== 6,"El valor de cantidad es 6.");
        lista_destruir(lista);

}


void quitar_elementos_al_final_de_la_lista_cambia_la_cantidad_y_cambia_el_nodo_ultimo()
{
        lista_t *lista =  lista_crear();
        char valor1 = 'd';
        char valor2 = 'h';
        char valor3 = 'x';
        char valor4 = 'y'; 
        char valor5 = 't';
        char valor6 = 't'; 
        lista_insertar(lista,&valor1);
        lista_insertar(lista,&valor2);
        lista_insertar(lista,&valor3);
        lista_insertar(lista,&valor4);
        lista_insertar(lista,&valor5);
        lista_insertar(lista,&valor6);

        pa2m_afirmar(lista_quitar(lista) ==&valor6 , "Puedo quitar el ultimo elemento de la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 5,"El valor de cantidad disminuye a 5.");
        pa2m_afirmar(lista_ultimo(lista) == &valor5,"El ultimo elemento despues de borrar el ultimo de la lista es el correcto.");

        pa2m_afirmar(lista_quitar(lista) ==&valor5 , "Puedo quitar otro elemento de la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 4,"El valor de cantidad disminuye a 4.");
        pa2m_afirmar(lista_ultimo(lista) == &valor4,"El ultimo elemento despues de borrar el ultimo de la lista es el correcto.");;

        pa2m_afirmar(lista_quitar(lista) ==&valor4,"Puedo quitar un elemento en posicion arbitraria de la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 3,"El valor de cantidad disminuye a 3.");
        pa2m_afirmar(lista_ultimo(lista) == &valor3,"El ultimo elemento despues de borrar el ultimo de la lista es el correcto.");

        pa2m_afirmar(lista_quitar(lista) ==&valor3,"Puedo quitar el elemento de la posicion 0 de la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 2,"El valor de cantidad disminuye a 2.");
        pa2m_afirmar(lista_ultimo(lista) == &valor2,"El ultimo elemento despues de borrar el ultimo de la lista es el correcto.");

        pa2m_afirmar(lista_quitar(lista) ==&valor2,"No puedo quitar un elemento en una posicion invalida de la lista, quita el ultimo elemento XD.");
        pa2m_afirmar(lista_tamanio(lista) ==1,"El valor de cantidad disminuye a 1.");
        pa2m_afirmar(lista_ultimo(lista) == &valor1,"El ultimo elemento despues de borrar el ultimo de la lista es el correcto.");

        pa2m_afirmar(lista_quitar(lista) ==&valor1,"Puedo quitar el ultimo elemento de la lista..");
        pa2m_afirmar(lista_tamanio(lista) ==0,"Tengo 0 elementos por eliminar todos los elementos.");
        pa2m_afirmar(lista_ultimo(lista) == NULL,"Con la lista vacia, ultimo elemento deberia ser NULL.");  
        pa2m_afirmar(lista_vacia(lista) == true,"La lista quedo vacia por eliminar todos los elementos.");

        lista_destruir(lista);

}
void quitar_elementos_en_posicion_arbitraria_de_la_lista_disminuye_la_cantidad_y_cambia_el_nodo_ultimo()
{
        lista_t *lista =  lista_crear();
        char valor1 = 'd';
        char valor2 = 'h';
        char valor3 = 'x';
        char valor4 = 'y'; 
        char valor5 = 't';
        char valor6 = 't'; 
        lista_insertar(lista,&valor1);
        lista_insertar(lista,&valor2);
        lista_insertar(lista,&valor3);
        lista_insertar(lista,&valor4);
        lista_insertar(lista,&valor5);
        lista_insertar(lista,&valor6);

        pa2m_afirmar(lista_quitar(lista) ==&valor6 , "Puedo quitar el ultimo elemento de la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 5,"El valor de cantidad disminuye a 5.");
        pa2m_afirmar(lista_ultimo(lista) == &valor5,"El ultimo elemento despues de borrar el ultimo de la lista es el correcto.");


        pa2m_afirmar(lista_quitar_de_posicion(lista,0) !=NULL , "Puedo quitar el elemento de la posicion 0 de la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 4,"El valor de cantidad disminuye a 4.");
        pa2m_afirmar(lista_primero(lista) == &valor2,"El primer elemento despues de borrar el que estaba de primer de la lista es el correcto.");

        pa2m_afirmar(lista_quitar_de_posicion(lista,1) !=NULL,"Puedo quitar un elemento en posicion arbitraria de la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 3,"El valor de cantidad disminuye a 3.");

        pa2m_afirmar(lista_quitar_de_posicion(lista,0) !=NULL,"Puedo quitar el elemento de la posicion 0 de la lista.");
        pa2m_afirmar(lista_tamanio(lista)== 2,"El valor de cantidad disminuye a 2.");
        pa2m_afirmar(lista_primero(lista) == &valor4,"El primer elemento despues de borrar el que estaba de primer de la lista es el correcto.");

        pa2m_afirmar(lista_quitar_de_posicion(lista,5) !=NULL,"No puedo quitar un elemento en una posicion invalida de la lista, quita el ultimo elemento.");
        pa2m_afirmar(lista_tamanio(lista) ==1,"El valor de cantidad disminuye a 1.");
        pa2m_afirmar(lista_ultimo(lista) == &valor4,"El ultimo elemento despues de borrar el ultimo de la lista es el correcto.");

        pa2m_afirmar(lista_quitar_de_posicion(lista,1) !=NULL,"Puedo quitar el ultimo elemento de la lista..");
        pa2m_afirmar(lista_tamanio(lista) ==0,"Tengo 0 elementos por eliminar todos los elementos.");
        pa2m_afirmar(lista_vacia(lista) == true,"La lista quedo vacia por eliminar todos los elementos.");

        lista_destruir(lista);

}
void probar_operaciones_destructor_lista()
{
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int)))!=NULL , "Puedo insertar un bloque reservado con malloc.");
        pa2m_afirmar(lista_tamanio(lista)== 1,"El valor de cantidad aumenta a 1.");

        pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int)))!=NULL , "Puedo insertar otro bloque reservado con malloc.");
        pa2m_afirmar(lista_tamanio(lista)== 2,"El valor de cantidad aumenta a 2.");

        pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int)))!=NULL , "Puedo insertar otro bloque reservado con malloc.");
        pa2m_afirmar(lista_tamanio(lista)== 3,"El valor de cantidad disminuye a 3.");

        lista_destruir_todo(lista, free);
}

void crear_iterador_externo_con_lista_NULL_es_un_error()
{
        pa2m_afirmar( lista_iterador_crear(NULL) == NULL, "No puedo crear el iterador externo con lista NULL.");
}

void pruebas_del_iterador_externo()
{
        lista_t *lista =  lista_crear();

        lista_iterador_t *iterador = lista_iterador_crear(lista);
        pa2m_afirmar( iterador != NULL, "Puedo crear el iterador externo correctamente.");
        pa2m_afirmar(lista_iterador_crear(NULL) == NULL, "No puedo crear el iterador externo con una lista NULL.");
        pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == false, "Un iterador valido puede tener un nodo siguiente al actual pero es NULL.");
        pa2m_afirmar(lista_iterador_tiene_siguiente(NULL) == false, "Un iterador NULL no puede tener un nodo siguiente al actual.");
       
        lista_destruir(lista);
        lista_iterador_destruir(iterador);
}

void prueba_iterador_externo()
{
        lista_t *lista = lista_crear();
        char valor1 = 'd';
        char valor2 = 'h';
        char valor3 = 'x';
        char valor4 = 'y'; 
        char valor5 = 't';
        char valor6 = 't'; 
        lista_insertar(lista,&valor1);
        lista_insertar(lista,&valor2);
        lista_insertar_en_posicion(lista,&valor3, 6);
        lista_insertar_en_posicion(lista,&valor4, 0);
        lista_insertar_en_posicion(lista,&valor5, 3);
        lista_insertar(lista,&valor6);
        int cantidad =0; 
        lista_iterador_t *it = NULL;
        for (it = lista_iterador_crear(lista);
                lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)){
                cantidad++;
        }
        pa2m_afirmar(cantidad == 6 , "El iterador externo puede iterar toda la lista.");
        lista_iterador_destruir(it);
        lista_destruir(lista);
}

void desencolar_en_una_cola_NULL_es_un_error()
{
        pa2m_afirmar(cola_desencolar(NULL) ==NULL, "No puedo desencolar con una cola NULL."); 
}

void prueba_elemento_en_posicion()
{
        lista_t *lista = lista_crear();
        char valor1 = 'd';
        char valor2 = 'h';
        char valor3 = 'x';
        char valor4 = 'y'; 
        char valor5 = 't';
        char valor6 = 'k'; 
        lista_insertar(lista,&valor1);
        lista_insertar(lista,&valor2);
        lista_insertar_en_posicion(lista,&valor3, 6);
        lista_insertar_en_posicion(lista,&valor4, 0);
        lista_insertar_en_posicion(lista,&valor5, 3);
        lista_insertar(lista,&valor6);

        pa2m_afirmar(lista_elemento_en_posicion(lista,3) == &valor5, "Puedo encontrar un elemento en una posicion que existe en la lista");
        pa2m_afirmar(lista_elemento_en_posicion(lista,7) ==NULL , "No puedo encontrar un elemento en una posicion que no existe en la lista");
        pa2m_afirmar(lista_elemento_en_posicion(NULL,1) ==NULL , "No puedo encontrar un elemento si la lista es NULL");
        lista_destruir(lista);

}

int elemento_es_igual(void *_a, void *_b)
{
        char *a = _a;
        char *b = _b;

        if(a && b && *a == *b)
          return 0;

        return -1;
}


void prueba_buscar_elemento()
{
        lista_t *lista = lista_crear();
        char valor1 = 'd';
        char valor2 = 'h';
        char valor3 = 'x';
        char valor4 = 'y'; 
        char valor5 = 't';
        char valor6 = 't'; 
        lista_insertar(lista,&valor1);
        lista_insertar(lista,&valor2);
        lista_insertar_en_posicion(lista,&valor3, 6);
        lista_insertar_en_posicion(lista,&valor4, 0);
        lista_insertar_en_posicion(lista,&valor5, 3);
        lista_insertar(lista,&valor6);

        pa2m_afirmar(lista_buscar_elemento(lista,elemento_es_igual, &valor3) == &valor3, "Puedo conseguir el elemento en la lista");
        pa2m_afirmar(lista_buscar_elemento(NULL,elemento_es_igual, &valor1)==NULL , "No puedo buscar el elemento con la lista NULL");
        pa2m_afirmar(lista_buscar_elemento(lista,NULL, &valor1)==NULL , "No puedo buscar el elemento con la funcion es NULL");
        lista_destruir(lista);

}

bool comparador(void *_a, void *_b)
{
        char *a = _a;
        char *b = _b;

        if(a && b && *a == *b)
                return false;
        return true;
}

void prueba_de_con_cada_elemento()
{
        lista_t *lista = lista_crear();
        char valor1 = 'd';
        char valor2 = 'h';
        char valor3 = 'x';
        char valor4 = 'y'; 
        char valor5 = 't';
        char valor6 = 't'; 
        lista_insertar(lista,&valor1);
        lista_insertar(lista,&valor2);
        lista_insertar(lista,&valor3);
        lista_insertar(lista,&valor4);
        lista_insertar(lista,&valor5);
        lista_insertar(lista,&valor6);
        pa2m_afirmar(lista_con_cada_elemento(lista, comparador, &valor4) == 4, "Busca el 4 elemento con el iterador interno devuelve 4 elementos iterados");
        pa2m_afirmar(lista_con_cada_elemento(NULL, comparador, &valor4) == 0, "No se puede iterar con el ietrador interno con lista NULL");
        pa2m_afirmar(lista_con_cada_elemento(lista, comparador, &valor6) == 5, "Con el iterador interno puedo iterar toda la lista");  
        pa2m_afirmar(lista_con_cada_elemento(lista, NULL, &valor4) == 0, "No se puede iterar con el ietrador interno con funcion NULL");
        lista_destruir(lista);
}
void destruir_elemento(void * elemento)
{
                if(!elemento)
                                return;
                free(elemento);
}

void prueba_nueva_primitiva_de_lista()
{
        lista_t *lista = lista_crear();
        int valores[8];
        int i = 0;
        bool hubo_error = false;
        while ( i < 8 && !hubo_error){
                valores[i] = i;
               lista =  lista_insertar_en_posicion(lista, &valores[i] ,0);
               if(!lista)
                        hubo_error = true;
                i++;
        }
       
      
        pa2m_afirmar(lista_tamanio(lista) ==8,"El valor de cantidad es 8.");
        pa2m_afirmar(lista_buscar_y_eliminar(lista, comparador, &valores[5]) == &valores[5], "se elimino el elemento correcto.");
        pa2m_afirmar(lista_tamanio(lista) ==7,"El valor de cantidad disminuye a 7.");
        pa2m_afirmar(lista_buscar_y_eliminar(lista, comparador, &valores[0]) == &valores[0], "se elimino el elemento correcto.");
        pa2m_afirmar(lista_tamanio(lista) ==6,"El valor de cantidad disminuye a 6.");
        pa2m_afirmar(lista_buscar_y_eliminar(lista, comparador, &valores[4]) == &valores[4], "se elimino el elemento correcto.");
        pa2m_afirmar(lista_tamanio(lista) ==5,"El valor de cantidad disminuye a 5.");
        pa2m_afirmar(lista_buscar_y_eliminar(lista, comparador, &valores[2]) == &valores[2], "se elimino el elemento correcto.");
        pa2m_afirmar(lista_tamanio(lista) ==4,"El valor de cantidad disminuye a 4.");
        pa2m_afirmar(lista_buscar_y_eliminar(lista, comparador, &valores[1]) == &valores[1], "se elimino el elemento correcto.");
        pa2m_afirmar(lista_tamanio(lista) ==3,"El valor de cantidad disminuye a 3.");
        pa2m_afirmar(lista_buscar_y_eliminar(lista, comparador, &valores[3]) == &valores[3], "se elimino el elemento correcto.");
        pa2m_afirmar(lista_tamanio(lista) ==2,"El valor de cantidad disminuye a 2.");
        pa2m_afirmar(lista_buscar_y_eliminar(lista, comparador, &valores[6]) == &valores[6], "se elimino el elemento correcto.");
        pa2m_afirmar(lista_tamanio(lista) ==1,"El valor de cantidad disminuye a 1.");
        pa2m_afirmar(lista_buscar_y_eliminar(lista, comparador, &valores[7]) == &valores[7], "se elimino el elemento correcto.");
        pa2m_afirmar(lista_tamanio(lista) ==0,"El valor de cantidad disminuye a 0.");
        pa2m_afirmar(lista_vacia(lista) == true, "La lista quedo vacia.");
        lista_destruir_todo(lista, NULL);
}
void pruebas_TDA_lista()
{
        pa2m_nuevo_grupo("Pruebas de creacion de lista.");
        crear_una_lista_me_devuelve_una_tamanio_0_y_nodo_apuntando_a_NULL();
        lista_vacia_con_lista_NULL_debe_devolver_true();
        pa2m_nuevo_grupo("Pruebas de agregar elementos al final de la lista .");
        lista_tamanio_si_la_lista_es_NULL_devuelve_0();
        lista_primero_si_la_lista_es_NULL_devuelve_NULL();
        lista_ultimo_si_la_lista_es_NULL_devuelve_NULL();
        insertar_en_una_lista_nula_es_un_error();
        insertar_un_elemento_nulo_inserta_el_elemento();
        insertar_elementos_al_final_de_la_lista_aumenta_la_cantidad_y_el_nodo_ultimo();
        pa2m_nuevo_grupo("Pruebas de agregar elementos en posiciones arbitrarias de la lista.");
        quitar_elementos_en_posiciones_arbitrarias_de_una_lista_nula_es_un_error();
        insertar_elementos_en_posiciones_arbitrarias_de_la_lista_aumenta_la_cantidad();
        pa2m_nuevo_grupo("Pruebas de quitar elementos a la lista.");
        quitar_elementos_al_final_de_la_lista_cambia_la_cantidad_y_cambia_el_nodo_ultimo();
        quitar_elementos_al_final_de_una_lista_nula_es_un_error();
        pa2m_nuevo_grupo("Pruebas de quitar elementos en posiciones arbitrarias de la lista.");
        quitar_elementos_en_posicion_arbitraria_de_la_lista_disminuye_la_cantidad_y_cambia_el_nodo_ultimo();
        pa2m_nuevo_grupo("Pruebas del destructor de lista.");
        probar_operaciones_destructor_lista();
        pa2m_nuevo_grupo("Pruebas del iterador externo.");
        pruebas_del_iterador_externo();
        crear_iterador_externo_con_lista_NULL_es_un_error();
        prueba_iterador_externo();
        pa2m_nuevo_grupo("Mas pruebas de lista.");
        pa2m_nuevo_grupo("Pruebas de lista elemento en posicion.");
        prueba_elemento_en_posicion();
        pa2m_nuevo_grupo("Pruebas de buscar elemento.");
        prueba_buscar_elemento();
        prueba_de_con_cada_elemento();
        pa2m_nuevo_grupo("Prueba de la nueva primitiva.");
        prueba_nueva_primitiva_de_lista();
}
void pruebas_de_creacion_de_pila()
{
        pila_t *pila = pila_crear();
        pa2m_afirmar(pila !=NULL, "Puedo crear una pila correctamente.");
        pa2m_afirmar(pila_vacia(pila) == true, "La pila creada esta vacia.");
        pa2m_afirmar(pila_tamanio(pila)==0, "La pila creada tiene tamanio 0.");
        pa2m_afirmar(pila_tope(pila)==NULL, "La pila creada tiene tope NULL.");

        pila_destruir(pila);
}

void pila_tamanio_si_la_pila_es_NULL_devuelve_0(){
        pa2m_afirmar(pila_tamanio(NULL) ==0,"La pila NULL no tiene tiene cantidad.");
}
void pila_vacia_con_pila_NULL_debe_devolver_true()
{
        pa2m_afirmar(pila_vacia(NULL)== true, "La pila no puede estar con elementos si es cola NULL.");
}

void apilar_en_una_pila_NULL_es_un_error()
{
        int elemento = 20;
        pa2m_afirmar(pila_apilar(NULL ,&elemento ) ==NULL, "No puedo apilar con una pila NULL."); 
}

void apilar_un_elemento_NULL_apila_el_elemento()
{
        pila_t *pila = pila_crear();
        
        pa2m_afirmar(pila_apilar(pila , NULL) !=NULL, "Puedo apilar un elemento NULL.");
        pa2m_afirmar(pila_vacia(pila) == false, "La pila no esta vacia.");
        pa2m_afirmar(pila_tamanio(pila)==1, "El tamanio de la pila es 1.");
        pa2m_afirmar(pila_tope(pila)== NULL, "El tope de la pila es NULL.");

        pila_destruir(pila);
}

void apilar_elementos_en_la_pila_incremento_la_cantidad_y_el_nodo_al_que_apunta_nodo_fin()
{
        pila_t *pila = pila_crear();
        int elemento1 = 4;
        int elemento2= 10;
        int elemento3 = 30;
        
        pa2m_afirmar(pila_apilar(pila , &elemento1) !=NULL, "Puedo apilar un elemento.");
        pa2m_afirmar(pila_tamanio(pila)==1, "El tamanio de la pila es 1.");
        pa2m_afirmar(pila_tope(pila)== &elemento1, "El tope de la pila es el correcto.");

        pa2m_afirmar(pila_apilar(pila , &elemento2) !=NULL, "Puedo apilar un segundo elemento.");
        pa2m_afirmar(pila_tamanio(pila)==2, "El tamanio de la pila es 2.");
        pa2m_afirmar(pila_tope(pila)== &elemento2, "El tope de la pila es el correcto.");

        pa2m_afirmar(pila_apilar(pila , &elemento3) !=NULL, "Puedo apilar un tercer elemento.");
        pa2m_afirmar(pila_tamanio(pila)==3, "El tamanio de la pila es 3.");
        pa2m_afirmar(pila_tope(pila)== &elemento3, "El tope de la pila es el correcto.");
        pila_destruir(pila);

}

void tope_de_pila_NULL_debe_devolver_NULL()
{
        pa2m_afirmar(pila_tope(NULL)== NULL, "No existe el tope de la pila NULL.");
}

void desapilar_elementos_en_la_pila_disminuye_la_cantidad_y_cambia_el_nodo_al_que_apunta_nodo_fin()
{
        pila_t *pila = pila_crear();

        int elemento1 = 4;
        int elemento2= 10;
        int elemento3 = 30;
        pila_apilar(pila , &elemento1);
        pila_apilar(pila , &elemento2);
        pila_apilar(pila , &elemento3);

        pa2m_afirmar(pila_desapilar(pila) !=NULL, "Puedo desapilar un elemento.");
        pa2m_afirmar(pila_tamanio(pila)==2, "El tamanio de la pila es 2.");
        pa2m_afirmar(pila_tope(pila)== &elemento2, "El tope de la pila es el correcto.");

        pa2m_afirmar(pila_desapilar(pila) !=NULL, "Puedo desapilar un elemento.");
        pa2m_afirmar(pila_tamanio(pila)==1, "El tamanio de la pila es 1.");
        pa2m_afirmar(pila_tope(pila)== &elemento1, "El tope de la pila es el correcto.");

        pila_destruir(pila);
  }

void desapilar_en_una_pila_NULL_es_un_error()
{
        pa2m_afirmar(pila_desapilar(NULL) ==NULL, "No puedo desapilar con una pila NULL."); 
}

void pruebas_TDA_pila()
{
        pa2m_nuevo_grupo("Pruebas del creacion de pila.");
        pruebas_de_creacion_de_pila();
        pila_tamanio_si_la_pila_es_NULL_devuelve_0();
        pila_vacia_con_pila_NULL_debe_devolver_true();
        pa2m_nuevo_grupo("Pruebas de apilar.");
        apilar_en_una_pila_NULL_es_un_error();
        apilar_un_elemento_NULL_apila_el_elemento();
        apilar_elementos_en_la_pila_incremento_la_cantidad_y_el_nodo_al_que_apunta_nodo_fin();
        tope_de_pila_NULL_debe_devolver_NULL();
        pa2m_nuevo_grupo("Pruebas de desapilar.");
        desapilar_elementos_en_la_pila_disminuye_la_cantidad_y_cambia_el_nodo_al_que_apunta_nodo_fin();
        desapilar_en_una_pila_NULL_es_un_error();



}

void pruebas_de_creacion_de_cola()
{
        cola_t *cola = cola_crear();
        pa2m_afirmar(cola !=NULL, "Puedo crear una cola correctamente.");
        pa2m_afirmar(cola_vacia(cola) == true, "La cola creada esta vacia.");
        pa2m_afirmar(cola_tamanio(cola)==0, "La cola creada tiene tamanio 0.");
        pa2m_afirmar(cola_frente(cola)==NULL, "La cola creada tiene frente NULL.");

        cola_destruir(cola);
}

void cola_tamanio_si_la_cola_es_NULL_devuelve_0(){
        pa2m_afirmar(cola_tamanio(NULL) ==0,"La cola NULL no tiene tiene cantidad.");
}
void cola_frente_con_cola_NULL_debe_devolver_NULL()
{
        pa2m_afirmar(cola_frente(NULL)== NULL, "No existe el el frente de la cola NULL.");
}
void cola_vacia_con_cola_NULL_debe_devolver_true()
{
        pa2m_afirmar(cola_vacia(NULL)== true, "La cola no puede estar con elementos si es cola NULL.");
}

void encolar_en_una_cola_NULL_es_un_error()
{
      int elemento_a_encolar = 40;
      pa2m_afirmar(cola_encolar(NULL ,&elemento_a_encolar) ==NULL, "No puedo encolar con una cola NULL."); 
}

void encolar_un_elemento_NULL_encola_el_elemento()
{
        cola_t *cola = cola_crear();
        
        pa2m_afirmar(cola_encolar(cola , NULL) !=NULL, "Puedo encolar un elemento NULL.");
        pa2m_afirmar(cola_vacia(cola) == false, "La cola no esta vacia.");
        pa2m_afirmar(cola_tamanio(cola)==1, "El tamanio de la cola es 1.");
        pa2m_afirmar(cola_frente(cola)== NULL, "El frente de la cola es NULL.");

        cola_destruir(cola);
}

void encolar_elementos_en_la_cola_incremento_la_cantidad_y_el_nodo_al_que_apunta_nodo_fin(cola_t *cola)
{
        int elemento1 = 4;
        int elemento2= 10;
        int elemento3 = 30;
        
        pa2m_afirmar(cola_encolar(cola , &elemento1) !=NULL, "Puedo encolar un elemento.");
        pa2m_afirmar(cola_tamanio(cola)==1, "El tamanio de la cola es 1.");
        pa2m_afirmar(cola_frente(cola)== &elemento1, "El frente de la cola es el correcto.");
        pa2m_afirmar(cola_vacia(cola) == false, "La cola ya no esta vacia.");

        pa2m_afirmar(cola_encolar(cola , &elemento2) !=NULL, "Puedo encolar un segundo elemento.");
        pa2m_afirmar(cola_tamanio(cola)==2, "El tamanio de la cola es 2.");

        pa2m_afirmar(cola_encolar(cola , &elemento3) !=NULL, "Puedo encolar un tercer elemento.");
        pa2m_afirmar(cola_tamanio(cola)==3, "El tamanio de la cola es 3.");

}


void desencolar_elementos_en_la_cola_disminuye_la_cantidad_y_cambia_el_nodo_al_que_apunta_nodo_fin()
{
        cola_t *cola = cola_crear();
        encolar_elementos_en_la_cola_incremento_la_cantidad_y_el_nodo_al_que_apunta_nodo_fin(cola);
        pa2m_nuevo_grupo("Pruebas de desencolar.");

        pa2m_afirmar(cola_desencolar(cola) !=NULL, "Puedo desencolar un elemento.");
        pa2m_afirmar(cola_tamanio(cola)==2, "El tamanio de la cola es 2.");

        pa2m_afirmar(cola_desencolar(cola) !=NULL, "Puedo desencolar un elemento.");
        pa2m_afirmar(cola_tamanio(cola)==1, "El tamanio de la cola es 1.");

        cola_destruir(cola);
}
 void pruebas_TDA_cola()
 {
        pa2m_nuevo_grupo("Pruebas del creacion de cola.");
        pruebas_de_creacion_de_cola();
        cola_tamanio_si_la_cola_es_NULL_devuelve_0();
        cola_frente_con_cola_NULL_debe_devolver_NULL();
        cola_vacia_con_cola_NULL_debe_devolver_true();
        pa2m_nuevo_grupo("Pruebas de encolar.");
        encolar_en_una_cola_NULL_es_un_error();
        encolar_un_elemento_NULL_encola_el_elemento();
        desencolar_elementos_en_la_cola_disminuye_la_cantidad_y_cambia_el_nodo_al_que_apunta_nodo_fin();
        desencolar_en_una_cola_NULL_es_un_error(); 
 }



int main() 
{
        pa2m_nuevo_grupo("Pruebas y mas pruebas.");

        pa2m_nuevo_grupo("Pruebas de Lista.");
        pruebas_TDA_lista();

        pa2m_nuevo_grupo("Pruebas de pila.");
        pruebas_TDA_pila();

        pa2m_nuevo_grupo("Pruebas de cola.");
        pruebas_TDA_cola();

        return pa2m_mostrar_reporte();

        return 0;
}
