#include "src/hash.h"
#include "src/lista/src/lista.h"
#include <stdlib.h>
#include "pa2m.h"
#include <string.h>

typedef struct par{
	void *elemento;
	char *clave;
}par_t;

struct hash {
	lista_t** tabla;
	size_t capacidad;
	size_t cant_elementos;
};

void pruebas_crear_hash()
{
		hash_t *hash = hash_crear(3);
		pa2m_afirmar(hash != NULL, "Se creo el hash correctamente");
		pa2m_afirmar(hash_cantidad(hash) == 0, "El hash creado no tiene elementos ");
		pa2m_afirmar(hash->capacidad == 3 , "LA capacidad del hash es la correcta");
		hash_destruir(hash);
}
void destruir_elemento(void * elemento)
{
		if(!elemento)
				return;
		free(elemento);
}
void pruebas_de_distribucion_del_hash()
{
	hash_t *hash = hash_crear(10);

    int* valores[50000];


    bool hay_error = false;
    int i =0 ;
    char clave[7] ;
    void *anterior = NULL;
    while ( i < 50000 &&  hay_error == false ) {
        valores[i] = malloc(sizeof(int));
        if(!valores[i]){
        	hash_destruir_todo(hash,destruir_elemento);
        	hay_error = true;
        }
        sprintf(clave,"%i", i);
        *valores[i] = i;
        hash = hash_insertar(hash, clave, valores[i], &anterior);
        destruir_elemento(anterior);
        if (!hash ||!hash_contiene(hash, clave)){
        		hay_error = true;
        }
        i++;
    }
 
    pa2m_afirmar( hay_error == false, "Prueba hash almacenar muchos elementos");
    pa2m_afirmar(3 != hash->capacidad, "se redimensiono correctamente");
    pa2m_afirmar(hash_cantidad(hash) == 50000, "La cantidad de elementos en el hash es el correcto");

		

	hash_destruir_todo(hash,destruir_elemento);
}
void pruebas_de_has_insertar_obtener_y_contene()
{
		hash_t *hash = hash_crear(3);
		int valor1 = 50;
		pa2m_afirmar(hash_insertar(hash,"KARLA",&valor1, NULL) != NULL, "Se pudo insertar un elemento en el hash");
		pa2m_afirmar(hash_contiene(hash,"KARLA")== true, "La clave que se inserto se encuentra en el hash");
		pa2m_afirmar(hash_obtener(hash,"KARLA")== &valor1, "El elemento que se inserto se encuentra en el hash");
		int valor2 = 70;
		pa2m_afirmar(hash_insertar(hash,"SANTI",&valor2, NULL) != NULL, "Se pudo insertar un elemento en el hash");
		pa2m_afirmar(hash_contiene(hash,"SANTI")== true, "La clave que se inserto se encuentra en el hash");
		pa2m_afirmar(hash_obtener(hash,"KARLA")== &valor1, "El elemento que se inserto se encuentra en el hash");




		hash_destruir(hash);


}
void pruebas_de_has_quitar()
{
		hash_t *hash = hash_crear(3);
		int valor1 = 50;
		int valor2 = 70;
		char clave1[40];
		strcpy(clave1, "KARLA");
		char clave2[40];
		strcpy(clave2, "SANTI");

		hash_insertar(hash,clave1,&valor1, NULL);
		hash_insertar(hash,clave2,&valor2, NULL);
		strcpy(clave2, "LATINITINA");
		hash_insertar(hash,clave2,&valor2, NULL);
		pa2m_afirmar(hash_quitar(hash,"LATINITINA") != &clave2, "Se pudo quitar un elemento del hash");
		pa2m_afirmar(hash_contiene(hash,"LATINITINA")== false, "El hash no deberia tener la clave que se elimino");
		pa2m_afirmar(hash_obtener(hash,"LATINITINA")== NULL, "El elemento que se elimino no esta en el hash");
		pa2m_afirmar(hash_cantidad(hash) ==2, "La cantidad de elementos en el hash es el correcto");

		pa2m_afirmar(hash_quitar(hash,"KARLA") != &clave1, "Se pudo quitar un elemento del hash");
		pa2m_afirmar(hash_contiene(hash,"KARLA")== false, "El hash no deberia tener la clave que se elimino");
		pa2m_afirmar(hash_obtener(hash,"KARLA")== NULL, "El elemento que se elimino no esta en el hash");
		pa2m_afirmar(hash_cantidad(hash) ==1, "La cantidad de elementos en el hash es el correcto");

		pa2m_afirmar(hash_quitar(hash,"SANTI") != &clave2, "Se pudo quitar un elemento del hash");
		pa2m_afirmar(hash_contiene(hash,"SANTI")== false, "El hash no deberia tener la clave que se elimino");
		pa2m_afirmar(hash_obtener(hash,"SANTI")== NULL, "El elemento que se elimino no esta en el hash");
		pa2m_afirmar(hash_cantidad(hash) ==0, "La cantidad de elementos en el hash es el correcto");


		hash_destruir(hash);

}

bool mostrar_patente(const char *clave, void *valor, void *aux)
{
	if (!clave)
		return false;

	aux = aux;

	printf("Patente en el hash: %s\n", clave);

	return true;
}

bool nombre(const char *clave, void *valor, void *_aux)
{
	if (!clave)
		return false;

	if(_aux){
		int *aux = _aux;
		if(*aux == 4)
				return false;
		(*aux)++;
	}
	
	return true;
}

void iterador_interno()
{
		hash_t *hash = hash_crear(7);
		int* valores[8];

	    bool hay_error = false;
	    int i =0 ;
	    char clave[7] ;
	    void *anterior = NULL;
	    while ( i < 8 &&  hay_error == false ) {
	        valores[i] = malloc(sizeof(int));
	        if(!valores[i]){
	        	hash_destruir_todo(hash,destruir_elemento);
	        	hay_error = true;
	        }
	        sprintf(clave,"%i", i);
	        *valores[i] = i;
	        hash = hash_insertar(hash, clave, valores[i], &anterior);
	        destruir_elemento(anterior);
	        if (!hash ||!hash_contiene(hash, clave)){
	        		hay_error = true;
	        }
	        i++;
	    }

	    size_t cantidad_invocaciones =0;
	    size_t cant_claves = hash_con_cada_clave(hash, nombre,NULL);
	    pa2m_afirmar(cant_claves == 8 , "Se iteraron todos los elementos con el iterador externo");
	    cant_claves = hash_con_cada_clave(hash, nombre,&cantidad_invocaciones);
	    pa2m_afirmar(cantidad_invocaciones == cant_claves-1 , "Se iteraron la cantidad correcta de elementos");
	    
	   	hash_destruir_todo(hash,destruir_elemento);



}

int main()
{
	pa2m_nuevo_grupo("Pruebas de hash crear");
	pruebas_crear_hash();
	pa2m_nuevo_grupo("Pruebas de hash insertar");
	pruebas_de_has_insertar_obtener_y_contene();
	pa2m_nuevo_grupo("Pruebas de distribuir");
	pruebas_de_distribucion_del_hash();
	pa2m_nuevo_grupo("Pruebas de quitar");
	pruebas_de_has_quitar();
	pa2m_nuevo_grupo("Pruebas de iterador");
	iterador_interno();

	return pa2m_mostrar_reporte();
}
