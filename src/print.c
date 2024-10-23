#include "print.h"
#include <stdio.h>

void printmapa(int celula, int celda[][ANCHO])
{
	int i,j;
	for ( i = 0; i < ALTO; i++) 
	{
		for ( j = 0; j < ANCHO; j++) 
		{
			putchar('|');
			celda[i][j] ? putchar(celula) : putchar(' ');//chequea en cada posicion de la matriz si la celula esta viva o muerta
		}
		putchar('|');
		puts("\n");
	}
	puts("\n");
}
