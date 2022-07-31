/*	ENUNCIADO
Al igual que en el ejercicio anterior, se pide ordenar el vector de números pasados por parámetro. Se cuenta con las funciones sift_up y 
sift_down ya implementadas.


*/

//	RESOLUCION

extern void sift_up(int* vector, int tope);
extern void sift_down(int* vector, int tope, int pos_actual);

void heapify(int *numeros, int tope ){
    int actual = tope-1;
    while(actual >=0){
        sift_down(numeros, tope, actual);
        actual--;
    } 
}
void swapeo(int *vector, int pos1, int pos2){
    int aux = vector[pos1];
    vector[pos1] = vector[pos2];
    vector[pos2] = aux;
}

void heap_sort(int* numeros, int tope, _Bool ascendente){
    heapify(numeros, tope);
    int auxiliar = tope;
    for(int i =0; i< tope; i++){
        int aux = numeros[0];
        numeros[0] = numeros[auxiliar-1];
        numeros[auxiliar-1] = aux;
        sift_down(numeros, tope,0);
        auxiliar--;
    }
    if(ascendente){
        for(int i =0; i < tope; i++){
            for(int j =0; j < tope-1-i; j++){
                if(numeros[j] > numeros[j+1])
                    swapeo(numeros, j , j+1);
            }
        }
    }

}