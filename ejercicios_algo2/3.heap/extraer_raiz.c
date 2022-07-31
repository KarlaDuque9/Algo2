/*	ENUNCIADO

Finalmente llegamos a la temida función heap_borrar, o heap_extraer_raiz en este caso. Se debe quitar el elemento raíz del heap, 
que por propiedad de heap maximal, será el mayor elemento del heap. Sin más preámbulo, implementémosla.

*/

//	RESOLUCION

extern void sift_down(int* vector, int tope, int pos_actual);
void intercambiar_valores(int *vector, int post1, int post2 ){

	int aux =  vector[post1];
	vector[post1] = vector[post2];
	vector[post2] = aux;
			
}


int heap_extraer_raiz(int* vector, int* tope){
 
    int extraido =  vector[0];
    if(*tope == 0)
        return extraido;
	intercambiar_valores(vector,0, (*tope)-1);
	(*tope)--;
	sift_down(vector,*tope, 0);
	return extraido;
}