#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMO 100

void imprimir_pantalla_inicial(){
	printf("BIENVENIDO AL JUEGO DE INTERACTUAR CON OBJETOS SI YA CONOCE EL JUEGO PUEDE COMNENZAR A JUGAR Y  SI AUN NO CONOCE EL JUEGO ESCRIBA AYUDA\n");
	printf("AYUDA TE VA A DECIR COMO PODES INTERACTUAR Y TE MUESTRA LOS OBJETOS CON LOS QUE PODES INTERACTUAR\n");
}
void pedir_interaccion(bool salir){
	if(!salir)
			printf("DECIME LA INTERACCION QUE QUETRES HACER\n");
}
int cuantas_palabras_tiene(char *buffer)
{
	size_t cantidad = strlen(buffer);
	int cantidad_espacios = 0;
	size_t i =0;
	while(i < cantidad){
			if(buffer[i] == ' ')
					cantidad_espacios++;
			i++;
	}
	return cantidad_espacios+1;
}
void mostrar_mensaje(const char *mensaje,enum tipo_accion accion,void *aux)
{
	bool *salir = aux;
	if(accion == ACCION_INVALIDA){
			printf("No se como hacer eso\n");
	}else if ( accion == ESCAPAR){
			printf("%s\n",mensaje);
			*salir = true;
	}else{
			printf("%s\n",mensaje);
	}
	

}
void realizar_ayuda(sala_t *sala)
{
	printf("PARA JUGAR TIENE QUE USAR EL FORMATO <VERBO> <OBJETO> <OBJETO>\n");
	printf("SI NO QUERES INTERACTUAR CON UN SEGUNDO OBJETO EL FORMATO ES <VERBO> <OBJETO>\n");
	printf("TAMBIEN PODES AGARRAR OBJETOS CON EL COMANDO <agarrar> <nombre_objeto> o si queres describir el comando es <describir> <nombre_objeto> \n");
	printf("SI QUERES SALIR DEL JUEGO ESCRIBE SALIR \n");

	int cantidad =0;
	char **conocidos = sala_obtener_nombre_objetos_conocidos(sala,&cantidad );
	printf("🍁OBJETOS CONOCIDOS🍁\n");
	for (int i = 0; i < cantidad; i++)
	{
		printf("%s\n",conocidos[i]);
	}
	printf("----------------------------------------------------------------------\n");
	printf("🌳TODOS LOS OBJETOS🌳\n");
	cantidad = 0;
	char **objetos = sala_obtener_nombre_objetos(sala,&cantidad );
	for (int i = 0; i < cantidad; i++)
	{
		printf("%s\n",objetos[i]);
	}
	printf("----------------------------------------------------------------------\n");
	cantidad = 0;
	char **poseidos = sala_obtener_nombre_objetos_poseidos(sala,&cantidad );
	printf("🍂OBJETOS POSEIDOS🍂 \n");
	if(cantidad == 0)
			printf("AUN NO TENES NADA EN POSECION\n");
	for (int i = 0; i < cantidad; i++)
	{
		printf("%s\n",poseidos[i]);
	}
	printf("----------------------------------------------------------------------\n");
	free(conocidos);
	free(objetos);
	free(poseidos);
	return;
}

void evaluar_comandos(bool *salir , sala_t *sala)
{
	char buffer[MAXIMO];
	char *string_1;
	char *string_2;
	char *string_3;
	fgets(buffer,MAXIMO, stdin);
	int cantidad = cuantas_palabras_tiene(buffer);

	switch(cantidad){
			case 1:
					if(strcmp(buffer,"ayuda\n") == 0 || strcmp(buffer,"AYUDA\n") == 0)
							realizar_ayuda(sala);
					else if(strcmp(buffer,"salir\n") == 0 || strcmp(buffer, "SALIR\n") ==0){
							printf("GRACIAS POR JUGAR 😎😎\n");
							*salir = true;
					}
			break;

			case 2:
					string_1 = strtok(buffer," ");
					string_2 = strtok(NULL, "\n");
					if(strcmp(string_1, "agarrar") == 0){
							if(sala_agarrar_objeto(sala,string_2))
									printf("lograste agarrar el objeto\n");
							else
									printf("el objeto no se puede agarrar\n");
					}else if(strcmp(string_1, "describir") == 0){
							char *mensaje = sala_describir_objeto(sala, string_2);
							printf("%s\n", mensaje);

					}else{
							if(sala_ejecutar_interaccion(sala,string_1,string_2, "", mostrar_mensaje, salir) == 0)
									printf("NO SE COMO HACER ESO\n");
					}
			break;

			default:
					string_1 = strtok(buffer," ");
					string_2 = strtok(NULL, " ");
					string_3 = strtok(NULL, "\n");
					sala_ejecutar_interaccion(sala,string_1,string_2, string_3, mostrar_mensaje, salir);
			break;
	}

}



int main(int argc, char *argv[])
{
	//Los archivos deben venir como parámetros del main
	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	imprimir_pantalla_inicial();
	bool salir = false;
	while(!salir && !sala_escape_exitoso(sala)){
		evaluar_comandos(&salir, sala );
		sala_escape_exitoso(sala);
		pedir_interaccion(salir);

	}
	if(sala_escape_exitoso(sala))
			printf("MUY BIEN JUGADO 😎😎\n");
	
	printf("SE ACABO EL JUEGO :( ;GRACIAS POR JUGAR \n");
	sala_destruir(sala);

	return 0;
}
