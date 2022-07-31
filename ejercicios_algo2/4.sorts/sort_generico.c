/*	ENUNCIADO
Finalmente, llegamos a lo más genérico de lo genérico. Ahora no recibimos un puntero de void*s, ahora recibimos directamente un void*. 
Sabemos que se apunta a un vector, pero no sabemos de qué tipo de dato. Por fortuna, también recibimos la cantidad de elementos que hay en el vector y 
el tamaño de los elementos almacenados. También se recibe la función comparadora, que se comporta de la misma manera que la función anterior, a saber: 
La función comparadora devuelve un valor positivo si el primer elemento debería ir primero o un valor negativo si el segundo debería ir primero. En caso 
de que sean iguales, se devuelve 0.


*/

//	RESOLUCION

void sort_generico(void *vector, int cant_elementos, int tamanio_un_elemento, int (*comparador)(const void *, const void*)){
    for(int j =0; j< cant_elementos; j++){
			for(int i = 0; i <cant_elementos-j-1; i++){
				if(comparador(vector+(i*tamanio_un_elemento), vector+((i+1)*tamanio_un_elemento))>0){
							
					char aux[tamanio_un_elemento];
					memcpy(aux,vector+(i*tamanio_un_elemento), tamanio_un_elemento);
					memcpy(vector+(i*tamanio_un_elemento),vector+((i+1)*tamanio_un_elemento), tamanio_un_elemento);
					memcpy(vector+((i+1)*tamanio_un_elemento),aux, tamanio_un_elemento);
								
				}
			}

		}
}