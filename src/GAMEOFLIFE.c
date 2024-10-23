#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs

#include "tam.h"
#include "actual.h"
#include "print.h"

#define D_WIDTH  640
#define D_HEIGHT 480

static void ini(int celda[][ANCHO]);		// funcion para definir el mapa inicial (aleatorio o manual)
static int end(int celda[][ANCHO]);
static int getnum(void);	//funcion para recibir el numero de generaciones



int main (void)
{
	int celda[ALTO][ANCHO];//matriz con las celulas vivas y muertas
	int gen=0, num = 0,i,sim,sig,err;
	
	/*********

	Ejemplo 7 de allegro: fonts. Implementar bien (ya estan los includes)

	*********/

	puts("~~Bienvenido al Juego de la vida~~\nPresione ENTER para continuar\n");
	do
	{
		sig=getchar();
	}
	while(sig!='\n');
	
	puts("En este juego se mostrará una matriz de dimensiones predetermiadas con células vivas o muertas\n");
	do
	{
		sig=getchar();
	}
	while(sig!='\n');
	
	puts("Al pasar de generación, las células vivas que tengan exactamente 2 o 3 vecinos vivos, sobreviven;\nlas células muertas que tengan exactamente 3, reviven. El resto, muere.\n\nPresione ENTER para iniciar el juego\n");
	do
	{
		sig=getchar();
	}
	while(sig!='\n');    
	do
	{
		err=0;
		puts("Seleccione el símbolo con el cual representar a las celulas vivas\n");
		sim=getchar();//elegir el simbolo para ser usado en las celulas vivas
		if(sim<33||sim>254)	// todos los caracteres "imprimibles" y "extendido" de la tabla ASCII 
		{
			puts("Símbolo inválido. Presione ENTER e ingrese un símbolo válido\n");//verifica que el simbolo utilizado no sea el mismo que el de las celulas muertas
			err=1;
		}
		while(getchar()!='\n')
		{
		}
	}
	
	while(err==1);
	
	
	ini(celda);//inicia el mundo con la funcion: random o manual
	
	do
	{
		if(num == 0)
		{
			num++;
		}
		printmapa(sim,celda);
		gen += num;
		printf("Es la generación %d\nHay %d células vivas\n",gen,end(celda));

		if(end(celda)==0) // chequea si queda alguna célula viva
		{
			puts("Todas las células han muerto\n");
			break;	//finaliza el programa si todas las celulas estan muertas
		}
		else
		{
			puts("Ingrese la cantidad de generaciones que desea avanzar. Para avanzar una generación sola, presione ENTER.\n");
		}
		
		do
		{
			num = getnum();
			if(num==-1)	//si el se le carga un caracter invalido pide ingresar otro
			{
				puts("Introduzca un número\n");
			}
		}
		while(num==-1);

		for(i=(num?num:1) ; i>0 ; i--)
		{
			next_gen(celda);
		}
	}
	while(num != 'q');	// espera a que se carque 'q' para terminar el programa

    return 0;

}


static void ini(int celda[][ANCHO])
{
	int init,i,j;
	
	srand (time(NULL));	// inicializa seed random

	printf("Si desea que el estado inicial de las celulas sea aleatorio, ingrese 'a'. Si prefiere inicializarlo manualmente, ingrese 'm'.\n");
	do
	{
		init = getchar();
		if(init!='a' && init!='m')
		{
			puts("Elija exclusivamente 'a' o 'm'\n");
		}
	}
	while(init!='a' && init!='m');
	while(getchar()!='\n')
		{
		}
	if(init=='a')
	{
		for (i = 0 ; i < ALTO ; i++) 
		{
			for (j = 0 ; j < ANCHO ; j++) 
			{
				celda[i][j]=rand() % 2;	// randomiza cada celda, con 1 y 0
			}
		}
	}
	else
	{
		puts("Seleccione el estado de la célula: 1 si está viva o 0 si está muerta\n");
		for ( i = 0; i < ALTO; i++) 
		{
			for ( j = 0 ; j < ANCHO ; j++) 
			{
				printf("Estado de la célula en la posición %d,%d\n",i+1,j+1);	// se les suma 1 para que el primer el elemento de la matriz sea (1,1) y no (0,0)
				do
				{
					celda[i][j]=getnum();
					if(celda[i][j]!=1 && celda[i][j]!=0)
					{
						puts("Solo se puede seleccionar 1 o 0\n");
					}
				}
				while(celda[i][j]!=1 && celda[i][j]!=0);
			}
		}
	}
}

static int end(int celda[][ANCHO])
{
	int i, j,vivos=0;
	for (i = 0 ; i < ALTO ; i++) 
	{
		for (j = 0 ; j < ANCHO ; j++) 
		{
			if(celda[i][j]==1)	//chequea para cada celula si esta con vida
			{
				vivos++;
			}    
		}
	}
	return vivos;	//devuelve la cantidad de celulas vivas
}

static int getnum(void)
{
	char c;
	int digito, num = 0, error = 0;

	while ((c = getchar()) != '\n')        // mira el caracter hasta un 'enter'
	{
		digito = c - '0';        // transforma el caracter en su numero correspondiente
		if (digito >= 0 && digito <= 9)
		{
			num = num*10 + digito;        // desplaza los digitos. unidad -> decena -> centena -> etc
		}
		else if(c=='q')      
		{
			num=c;
		}
		else
		{
			error++;
		}
	}

	if(error != 0)
	{
		num=-1;
	}
	return num;
}
