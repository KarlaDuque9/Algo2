#include "pa2mm.h"
#include "src/estructuras.h"
#include "src/sala.h"
#include "src/objeto.h"
#include "src/interaccion.h"
#include "src/cantidad_objetos.h"

#include "string.h"
#include <stdbool.h>

void pruebasCrearObjeto()
{
	pa2m_afirmar(objeto_crear_desde_string(NULL) == NULL,
		     "No puedo crear un objeto a partir de un string NULL");
	pa2m_afirmar(objeto_crear_desde_string("") == NULL,
		     "No puedo crear un objeto a partir de un string vacío");
	pa2m_afirmar(objeto_crear_desde_string("a;b") == NULL,
		     "\"a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;b") == NULL,
		     "\"a;;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;b") == NULL,
		     "\";a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;b;c") == NULL,
		     "\"a;b;c\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;true") == NULL,
		     "\"a;;true\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;false") == NULL,
		     "\";a;false\" no es un string objeto válido");

	struct objeto *objeto1 = objeto_crear_desde_string("nombre;desc;true");
	pa2m_afirmar(objeto1, "\"nombre;desc;true\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto1->nombre, "nombre") == 0, "El nombre del objeto es \"nombre\"");
	pa2m_afirmar(strcmp(objeto1->descripcion, "desc") == 0,
		     "La descripcion del objeto es \"desc\"");
	pa2m_afirmar(objeto1->es_asible == true, "El objeto es asible");

	struct objeto *objeto2 = objeto_crear_desde_string("A;Be;false\n");
	pa2m_afirmar(objeto2, "\"A;Be;false\\n\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto2->nombre, "A") == 0, "El nombre del objeto es \"A\"");
	pa2m_afirmar(strcmp(objeto2->descripcion, "Be") == 0,
		     "La descripcion del objeto es \"Be\"");
	pa2m_afirmar(objeto2->es_asible == false, "El objeto no es asible");

	free(objeto1);
	free(objeto2);
}

void pruebasCrearInteracciones()
{
	pa2m_afirmar(interaccion_crear_desde_string(NULL) == NULL,
		     "No puedo crear una interacción a partir de un string NULL");
	pa2m_afirmar(interaccion_crear_desde_string("") == NULL,
		     "No puedo crear una interacción a partir de un string vacío");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c:d:e") == NULL,
		     "\"a;b;c:d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d") == NULL,
		     "\"a;b;c;d\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d:e") == NULL,
		     "\"a;b;c;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;d:e") == NULL,
		     "\"a;b;_;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;de:f:g") == NULL,
		     "\"a;b;_;de:f:g\" no es un string interacción válido");

	struct interaccion *inter1 = interaccion_crear_desde_string("a;b;c;d:e:f");
	pa2m_afirmar(inter1, "\"a;b;c;d:e:f\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter1->objeto, "a") == 0, "El nombre del objeto es \"a\"");
	pa2m_afirmar(strcmp(inter1->verbo, "b") == 0, "El verbo es \"b\"");
	pa2m_afirmar(strcmp(inter1->objeto_parametro, "c") == 0, "El segundo objeto es \"c\"");
	pa2m_afirmar(inter1->accion.tipo == DESCUBRIR_OBJETO,
		     "El tipo de acción es DESCUBRIR_OBJETO");
	pa2m_afirmar(strcmp(inter1->accion.objeto, "e") == 0, "El objeto de la acción es \"e\"");
	pa2m_afirmar(strcmp(inter1->accion.mensaje, "f") == 0, "El mensaje de la acción es \"f\"");

	struct interaccion *inter2 = interaccion_crear_desde_string("OB;VER;_;m:_:MSG");
	pa2m_afirmar(inter1, "\"OB;VER;_;m:_:MSG\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter2->objeto, "OB") == 0, "El nombre del objeto es \"OB\"");
	pa2m_afirmar(strcmp(inter2->verbo, "VER") == 0, "El verbo es \"VER\"");
	pa2m_afirmar(strcmp(inter2->objeto_parametro, "") == 0, "El segundo objeto es vacío");
	pa2m_afirmar(inter2->accion.tipo == MOSTRAR_MENSAJE,
		     "El tipo de acción es MOSTRAR_MENSAJE");
	pa2m_afirmar(strcmp(inter2->accion.objeto, "") == 0, "El objeto de la acción es vacío");
	pa2m_afirmar(strcmp(inter2->accion.mensaje, "MSG") == 0,
		     "El mensaje de la acción es \"MSG\"");

	free(inter1);
	free(inter2);
}

void pruebas_crear_sala()
{
	pa2m_afirmar(sala_crear_desde_archivos("/ASD/ASD/", "dasD/sa2asdd") == NULL,
		     "No puedo crear la sala a partír de archivos inexistentes");

	pa2m_afirmar(sala_crear_desde_archivos("", "chanu/int.csv") == NULL,
		     "No puedo crear la sala sin objetos");

	pa2m_afirmar(sala_crear_desde_archivos("chanu/obj.dat", "chanu/vacio.txt") == NULL,
		     "No puedo crear la sala sin interacciones");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala != NULL, "Puedo crear la sala a partir de archivos no vacíos");
	pa2m_afirmar(cantidad_objetos(sala) == 9, "Se leyeron 9 objetos");
	pa2m_afirmar(cantidad_interacciones(sala) == 9, "Se leyeron 9 interacciones");

	sala_destruir(sala);
}
int vector_contiene_nombres_esperados(char *nombres[], const char *esperados[],int cantidad)
{
	int encontrados = 0;
	for (int i = 0; i < cantidad; i++) {
		for (int j = 0; j < cantidad; j++) {
			if (strcmp(nombres[i], esperados[j]) == 0) {
				encontrados++;
				break;
			}
		}
	}
	return encontrados;
}
void pruebas_nombre_objetos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos(NULL, &cantidad) == NULL,
		     "No puedo obtener los nombres de objetos de una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 9, "La cantidad de elementos del vector coincide con lo esperado");

	const char *esperados[] = { "habitacion",    "mesa",  "interruptor", "pokebola", "cajon",
				    "cajon-abierto", "llave", "anillo",	     "puerta" };

	pa2m_afirmar(vector_contiene_nombres_esperados(objetos2,esperados, cantidad)==cantidad, "Todos los nombres de objeto son los esperados");


	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void  pruebas_nombre_objetos_conocidos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos_conocidos(NULL, &cantidad) == NULL,
		     "No puedo obtener los nombres de objetos de una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos_conocidos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 1, "La cantidad de elementos del vector coincide con lo esperado");

	const char *esperados[] = { "habitacion"};


	int comparaciones_exitosas = 0;

	for (int i = 0; i < cantidad; i++)
		if (strcmp(objetos2[i], esperados[i]) == 0)
			comparaciones_exitosas++;
	pa2m_afirmar(vector_contiene_nombres_esperados(objetos2,esperados, cantidad)==cantidad, "Todos los nombres de objeto son los esperados");


	free(objetos);
	free(objetos2);
	sala_destruir(sala);	
}

void pruebas_interacciones()
{
	pa2m_afirmar(sala_es_interaccion_valida(NULL, "hacer", NULL, NULL) == false,
		     "No es válido pedir interacciones de una sala NULL");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala_es_interaccion_valida(sala, NULL, "", "") == false, "No es válida una intearcción con verbo NULL");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "hacer", NULL, "") == false, "No es válida una intearcción con objeto NULL");

	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == true, "Puedo examinar la habitación");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "usar", "llave", "cajon") == true, "Puedo usar la llave en el cajón");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "pokebola", "") == true, "Puedo abrir la pokebola");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "cajon-abierto", "") == true, "Puedo examinar el cajón abierto");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "romper", "todo", "") == false, "No puedo romper todo");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "mesa", "") == false, "No puedo abrir la mesa");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "techo", "") == false, "No puedo examinar el techo");

	sala_destruir(sala);
}

void mostrar_mensaje(const char *mensaje,enum tipo_accion accion,void *aux)
{
	return;
}


void pruebas_de_acerinteracciones(){
	pa2m_afirmar(sala_es_interaccion_valida(NULL, "hacer", NULL, NULL) == false,
		     "No es válido pedir interacciones de una sala NULL");
	sala_t *sala = sala_crear_desde_archivos("ejemplo/objetos.txt", "ejemplo/interacciones.txt");
	pa2m_afirmar(sala !=NULL, "Puedo crear la sala con archvios de objetos e interacciones existentes");

	int cantidad = 0;
	char ** objeto1= sala_obtener_nombre_objetos_conocidos(sala,&cantidad);
	pa2m_afirmar(cantidad == 1, "La cantidad de elementos conocidos es 1.");
	pa2m_afirmar(strcmp(objeto1[0], "habitacion") == 0, "El elemento conocido es la habitacion.");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", mostrar_mensaje, NULL) == 2, "Puedo examinar la habitación realiza dos interaccines");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", mostrar_mensaje, NULL) == 0, "no puedo abrir la puerta");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "salir", "puerta-abierta", "", mostrar_mensaje, NULL) == 0, " la puerta no esta abierta");

	cantidad = 0;
	char ** objeto= sala_obtener_nombre_objetos_conocidos(sala,&cantidad);
	pa2m_afirmar(objeto !=NULL, "Puedo obtener los nombres de los objetos");
	pa2m_afirmar(cantidad == 3, "La cantidad de elementos conocidos es 3.");

	const char *esperados1[] = { "habitacion", "pokebola","puerta" };
	pa2m_afirmar(vector_contiene_nombres_esperados(objeto,esperados1, cantidad)==cantidad, "Los elementos conocidos son la habitacion, pokebola y la puerta.");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", mostrar_mensaje, NULL) == 0, "Examinar la habitación no vuelve a descubrir los objetos");
	cantidad = 0;
	char ** objetos_poseidos= sala_obtener_nombre_objetos_poseidos(sala,&cantidad);
	pa2m_afirmar(cantidad == 0, "La cantidad de objetos poseidos es 0.");
	free(objetos_poseidos);
	
	pa2m_afirmar(sala_agarrar_objeto(sala,"pokebola") ,"Puedo agarrar pokebola");
	cantidad=0;
	char ** objeto3= sala_obtener_nombre_objetos_conocidos(sala,&cantidad);
	pa2m_afirmar(objeto3 !=NULL, "Puedo obtener los nombres de los objetos otra vezzzz");
	pa2m_afirmar(cantidad == 2, "La cantidad de elementos conocidos es 2(pokebola se elimino).");
	const char *esperados2[] = { "habitacion", "puerta"};
	pa2m_afirmar(vector_contiene_nombres_esperados(objeto3,esperados2, cantidad)==cantidad, "Los objetos son la puerta y habitacion");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", mostrar_mensaje,NULL) == 2, "Puedo abrir la pokebola");
	cantidad=0;
	char ** objeto4= sala_obtener_nombre_objetos_conocidos(sala,&cantidad);
	pa2m_afirmar(objeto4 !=NULL, "Puedo obtener los nombres de los objetos otraaaa vezzzzzzzzzz");
	pa2m_afirmar(cantidad == 3, "La cantidad de elementos conocidos sigue siendo 3(se agrego la llave).");
	const char *esperados3[] = { "habitacion", "puerta", "llave"};
	pa2m_afirmar(vector_contiene_nombres_esperados(objeto4,esperados3, cantidad)==cantidad,  "Los objetos son la llave, puerta y habitacion");
	pa2m_afirmar(sala_describir_objeto(sala,"pokebola") == NULL, "No puedo describir la pokebola(no existe)");
	pa2m_afirmar(sala_agarrar_objeto(sala,"llave") ,"Puedo agarrar llave");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", mostrar_mensaje, NULL) == 1, "Puedo abrir llave puerta y se ejecuta una accion");
	cantidad=0;
	char ** objeto5= sala_obtener_nombre_objetos_conocidos(sala,&cantidad);
	pa2m_afirmar(objeto5 !=NULL, "Puedo obtener los nombres de los objetos otra ves XD");
	pa2m_afirmar(cantidad == 2, " al reemplazar(puerta con puerta-abierta) me quedan 2 objetos");
	const char *esperados4[] = { "habitacion", "puerta-abierta"};
	pa2m_afirmar(vector_contiene_nombres_esperados(objeto5,esperados4, cantidad)==cantidad, "Los objetos son la puerta-abierta y habitacion");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "salir", "puerta-abierta", "", mostrar_mensaje,NULL) == 1, "Puedo salir puerta");
	pa2m_afirmar(sala_escape_exitoso(sala)== true, "Logre salir de la sala");



	free(objeto);
	free(objeto3);
	free(objeto1);
	free(objeto4);
	free(objeto5);
	sala_destruir(sala);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de objetos");
	pruebasCrearObjeto();

	pa2m_nuevo_grupo("Pruebas de creación de interacciones");
	pruebasCrearInteracciones();

	pa2m_nuevo_grupo("Pruebas de creación de sala");
	pruebas_crear_sala();

	pa2m_nuevo_grupo("Pruebas del vector de nombres");
	pruebas_nombre_objetos();

	pa2m_nuevo_grupo("Pruebas del vector de nombres conocidos");
	pruebas_nombre_objetos_conocidos();

	pa2m_nuevo_grupo("Pruebas de interacciones");
	pruebas_interacciones();

	pa2m_nuevo_grupo("Pruebas de funcionamiento en un escenario ");
	pruebas_de_acerinteracciones();

	return pa2m_mostrar_reporte();
}
