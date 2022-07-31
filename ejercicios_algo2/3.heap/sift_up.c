/*	ENUNCIADO
En esta guía, buscamos programar las funciones más importantes del heap. Para eso, iremos paso por paso programando lo que necesitamos y asegurándonos 
de que funciona, antes de pasar a la siguiente parte. En la página de la materia hay un apunte donde se explica la lógica de cada una de las funciones 
que implementaremos.

Uno de los primeros métodos que se elige programar de un tda es el insertar. Para implementar la versión de esta función en el heap, es conveniente 
empezar con esta función, sift_up. Se recibe el vector de enteros y la posicion a partir de la cual se debe hacer sift_up.

No te confundas, no estás programando heap_insertar todavía. Esa función es la del siguiente ejercicio, ahora estás programando sift_up, que será muy 
útil para heap insertar.

Aclaración: en todos los ejercicios, supondremos que se tiene un heap maximal.


*/

//	RESOLUCION

void swap(int *vector, int post1, int post2 )
{
	int aux =  vector[post1];
	vector[post1] = vector[post2];
	vector[post2] = aux;
			
}


void sift_up(int* vector, int pos_actual){
    	if(pos_actual == 0)
			return;

		int padre = (pos_actual-1)/2;

		if(vector[pos_actual] >vector[padre]){
				swap(vector, padre, pos_actual);
				sift_up(vector,padre);
		}
}