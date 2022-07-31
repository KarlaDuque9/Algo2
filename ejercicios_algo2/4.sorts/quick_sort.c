/*	ENUNCIADO
Terminamos los tres métodos de ordenamiento con quick sort. Programar ahora este algoritmo, cumpliendo 
las mismas condiciones de los ejercicios anteriores.


*/

//	RESOLUCION

void swap(int *vector, int a, int b ){
	int aux =  vector[a];
	vector[a] = vector[b];
	vector[b] = aux;
			
}

int pivotear(int *vector, int tamanio,_Bool ascendente ){
	int pos_pivote = tamanio-1;
	int post_final_pivote = 0;
	for (int i = 0; i < tamanio; i++){
			if((ascendente && vector[i] < vector[pos_pivote]) ||(!ascendente && vector[i] > vector[pos_pivote])){
				swap(vector,i, post_final_pivote);
				post_final_pivote++;
		}
	}
	swap(vector,pos_pivote, post_final_pivote);

	return post_final_pivote;
}

void quick_sort(int* numeros, int tope, _Bool ascendente){
    if(tope <=1)
			return;
	int pos_pivote = pivotear(numeros, tope,ascendente);
	quick_sort(numeros, pos_pivote, ascendente);
	quick_sort(numeros+pos_pivote+1, tope-pos_pivote-1, ascendente);
}