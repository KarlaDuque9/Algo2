/*
Brock piensa que los músculos impresionan a las chicas, con la excusa de que quiere cuidar su salud, además de estar con una figura envidiable para el verano, 
sigue el consejo de la doctora Joy, anotar todas las calorías que ingiere en un casillero que corresponde a la hora y tipo de comida. Pero en los fines de 
semana… Se da sus buenos permitidos y no quiere ponerse a sumar.

Ayúdale haciendo una función que recibe la matriz que contiene los valores de las calorías que consumió cada día y devuelva el total de calorías.

*/

//	RESOLUCION

#include "solucion.h"

int sumar_calorias_rec(int cantidad_filas, int cantidad_columnas, int matriz[MAX_TAM][MAX_TAM], int i, int j,int cantidad_calorias){
    cantidad_calorias += matriz[i][j];
    if(i == cantidad_filas && j == cantidad_columnas)
        return cantidad_calorias;
    else if(j == cantidad_columnas)
        return sumar_calorias_rec(cantidad_filas, cantidad_columnas,matriz, i+1,0,cantidad_calorias);
    return sumar_calorias_rec(cantidad_filas, cantidad_columnas,matriz,i,j+1,cantidad_calorias);
        
}

int sumar_calorias(int cantidad_filas, int cantidad_columnas, int matriz[MAX_TAM][MAX_TAM]){
     
    return sumar_calorias_rec(cantidad_filas,cantidad_columnas,matriz,0,0,0);
}