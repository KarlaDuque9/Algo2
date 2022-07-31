/*	ENUNCIADO
Empezamos con el primero de los tres sorts que se ven en la materia Algo2Mendez. Como ya estamos en temas de Algo2, en vez de recibir un vector 
desordenado y otro donde ir enviando los elementos ordenados, se recibe solamente un vector. Al principio, se recibe el vector desordenado, y al 
finalizar el algoritmo, el mismo debe encontrarse ordenado.

Este algoritmo puede hacerse de manera tanto iterativa como recursiva, cualquiera está bien (mientras funcione, claro).

Como venimos viendo hasta ahora, se recibe también un booleano para decidir si debemos ordenar de manera ascendente o descendente el vector.


*/

//	RESOLUCION

void merge(int *vector1, int n1, int *vector2, int n2, _Bool ascendente)
{
		int vector3[n1+n2];
		int i1 = 0, i2 = 0 , i3 = 0;

		while(i1 < n1 && i2 < n2){
            if(ascendente){
				if(vector1[i1] <= vector2[i2]){
					vector3[i3]= vector1[i1];
					i1++;
				}
				else{
					vector3[i3] = vector2[i2];
					i2++;
				}
            }else{
				if(vector1[i1] >= vector2[i2]){
					vector3[i3]= vector1[i1];
					i1++;
				}
				else{
					vector3[i3] = vector2[i2];
					i2++;
				}               
            }
				i3++;
		}
		
		while(i1 < n1){
				vector3[i3]= vector1[i1];
				i1++;
				i3++;
		}
		while(i2 < n2){
				vector3[i3]= vector2[i2];
				i2++;
				i3++;
		}
		for(int i =0; i < n1+n2; i++)
				vector1[i] = vector3[i]; 

}


void merge_sort(int* numeros, int tope, _Bool ascendente){
    if(tope <=1)
			return;
	int mitad =  tope/2;

	merge_sort(numeros, mitad, ascendente);
	merge_sort(numeros+mitad, tope-mitad, ascendente);

	merge(numeros, mitad, numeros+mitad, tope-mitad, ascendente);
}