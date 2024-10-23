#include "actual.h"
#include <stdio.h>


#define borde1(x) ((x)? (x)-1:(x))
#define borde2(x,y) ((x)==((y)-1)? (x):(x)+1)//condicionales para verificar si esta en el borde de la matriz

static int vecinos ( int fil, int col, int celda[][ANCHO]);	//funcion para contar vecinos




void next_gen(int celda[][ANCHO])
{
    int nuevoMundo[ALTO][ANCHO];//matriz donde se guarda la vida en la siguiente generacion
    int i, j, vec;
    
    for (i = 0; i < ALTO; i++) 
    {
        for (j = 0; j < ANCHO; j++) 
        {
            vec = vecinos(i, j,celda);//pone en vec la cantidad de vecinos de cada celula y guarda en nuevoMundo dependiendo de cuantas tengas
            if (vec == 3) 
            {
                nuevoMundo[i][j] = 1; 
            }
            else if (vec == 2)
            {
                nuevoMundo[i][j] = celda[i][j]; 
            }
            else
            {
                nuevoMundo[i][j] = 0; 
            }
        }
    }


    for (i = 0; i < ALTO; i++) 
    {
        for (j = 0; j < ANCHO; j++) 
        {
            celda[i][j] = nuevoMundo[i][j];//actualiza los valores del original
        }
  
    }
}
 

static int vecinos (int fil, int col,int celda[][ANCHO])
{
	int i,j,cant_vecinos=0;
	for(i = borde1(fil) ; i<ALTO && i <= borde2(fil,ALTO) ; i++)
	{
		for(j = borde1(col) ; j<ANCHO && j <= borde2(col,ANCHO) ; j++)//aumenta y decrementa i y j alrededor de la celula elegida
		{
			if (celda[i][j] == 1)
			{
				cant_vecinos++;
			}
		}
	}
	cant_vecinos -= celda[fil][col];//si la celula esta viva se debe restar a la cuenta de cantidad de vecinos

	return cant_vecinos;
}


