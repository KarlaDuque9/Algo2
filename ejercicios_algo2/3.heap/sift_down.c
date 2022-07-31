/*	ENUNCIADO

Ya entendimos sift_up y cómo usarla en heap_insertar. Pasemos a entender sift_down, que de manera análoga nos sirve para heap_extraer_raiz.

Se recibe el vector de enteros, el tope del mismo y la posición a partir de la cual hay que aplicar la función.

*/

//	RESOLUCION

void swap(int *vector, int post1, int post2 )
{
	int aux =  vector[post1];
	vector[post1] = vector[post2];
	vector[post2] = aux;
			
}


void sift_down(int* vector, int tope, int pos_actual){

	int hijo_izq = 2*pos_actual+1;
	int hijo_der = 2*pos_actual+2;

	if(hijo_izq >= tope)
		return;

	int hijo_mas_grande = hijo_izq;
	if(hijo_der < tope){
		if (vector[hijo_der] > vector[hijo_izq])
			hijo_mas_grande = hijo_der;				
				
		}

	if(vector[pos_actual] < vector[hijo_mas_grande]){
		swap(vector,pos_actual, hijo_mas_grande);
		sift_down(vector, tope,hijo_mas_grande);
	}
}