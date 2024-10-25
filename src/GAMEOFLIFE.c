#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs

#include "tam.h"
#include "actual.h"
#include "print.h"


#define D_WIDTH  640
#define D_HEIGHT 480
#define FPS 60.0
#define ENTER "Presione ENTER para continuar"

static void ini(int celda[][ANCHO],ALLEGRO_FONT *,ALLEGRO_EVENT);		// funcion para definir el mapa inicial (aleatorio o manual)
static int end(int celda[][ANCHO]);
static int getnum(void);	//funcion para recibir el numero de generaciones



int main (void)
{
	int celda[ALTO][ANCHO];//matriz con las celulas vivas y muertas
	int gen=0, num = 0,i=0,err,sim;
	
	/**********/

	ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_FONT * font36 = NULL;
    ALLEGRO_FONT * font24 = NULL;
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;

    bool done = false;



    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro.\n");
        return -1;
    }

    if (!al_install_keyboard())
    {
    	fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

	event_queue = al_create_event_queue(); //Allegro usa cola eventos, como las colas del super pero sin comida :( (por orden de llegada)
	if (!event_queue)
	{
		fprintf(stderr, "failed to create event_queue!\n");
		return -1;
	}

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon

    /* Crea el display*/
    display = al_create_display(D_WIDTH, D_HEIGHT);

    if (!display) {
        fprintf(stderr, "Failed to create display.\n");
        al_destroy_event_queue(event_queue);
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
        if (!timer) {
            fprintf(stderr, "failed to create timer!\n");
            al_destroy_event_queue(event_queue);
            al_destroy_display(display);
            return -1;
        }

    //Registra el display a la cola de eventos, los eventos del display se iran guardando en la cola
    // a medida que vayan sucediendo
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    /* Fuentes */
    font36 = al_load_ttf_font("res/Times New Roman.ttf", 36, 0); //HAY CREAR UN FONT PARA CADA TAMAÑO DE LETRA :(

    if (!font36) {
        fprintf(stderr, "Could not load 'Times New Roman.ttf'.\n");
        return -1;
    }

    font24 = al_load_ttf_font("res/Times New Roman.ttf", 24, 0);

    if (!font24)
    {
    	fprintf(stderr, "Could not load 'Times New Roman.ttf'.\n");
    	return -1;
    }
    /****/

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font36, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16), ALLEGRO_ALIGN_CENTER,
    	"~~Juego de la vida~~");

    al_flip_display();

    al_rest(1.5);

    al_draw_text(font24, al_map_rgb(255, 255, 255), 10, (D_HEIGHT / 16)+50, 0,
    		ENTER);
    al_flip_display();

    al_start_timer(timer);
    while(!done)
    {
    	ALLEGRO_EVENT event;

    	if (al_get_next_event(event_queue, &event))
    	{
    		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER)
    		{
    			switch(i)
    				{
    					case 0:
    						al_clear_to_color(al_map_rgb(0, 0, 0));
    						al_draw_text(font36, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16), ALLEGRO_ALIGN_CENTER,
    								"~~Bienvenido al Juego de la vida~~");
    						al_flip_display();
    						al_rest(1.0);
    						al_draw_text(font36, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16)+50, ALLEGRO_ALIGN_CENTER,
    						    	ENTER);
    						al_flip_display();
    						al_rest(1.0);
    						i++;
    						break;
    					case 1:
    						al_clear_to_color(al_map_rgb(0, 0, 0));
    						al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16), ALLEGRO_ALIGN_CENTER,
    								"En este juego se mostrará una matriz de dimensiones ");
    						al_flip_display();
    						al_rest(1.0);
    						al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16)+50, ALLEGRO_ALIGN_CENTER,
    								" predetermiadas con células vivas o muertas");
    						al_flip_display();
    						al_rest(1.0);
    						i++;
    						break;

    					case 2:
    						al_clear_to_color(al_map_rgb(0, 0, 0));
    						al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16), ALLEGRO_ALIGN_CENTER,
    								"Al pasar de generación, las células vivas que tengan exactamente");
    						al_flip_display();
    						al_rest(1.0);
    						al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16)+50, ALLEGRO_ALIGN_CENTER,
    						    	"2 o 3 vecinos vivos, sobreviven;las células muertas que tengan");
    						al_flip_display();
    						al_rest(1.0);
    						al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16)+100, ALLEGRO_ALIGN_CENTER,
    						    	" exactamente 3, reviven. El resto, muere.");
    						al_flip_display();
    						al_rest(1.0);
    						al_draw_text(font36, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16)+150, ALLEGRO_ALIGN_CENTER,
    						    	ENTER);
    						al_flip_display();
    						al_rest(1.0);
    						i++;
    						break;
    					case 3:
    						al_clear_to_color(al_map_rgb(0, 0, 0));
    						al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16), ALLEGRO_ALIGN_CENTER,
    						"Seleccione el simbolo en la consola");
    						al_flip_display();
    						do
    						{
    							err=0;
    							sim=getchar();//elegir el simbolo para ser usado en las celulas vivas
    							if(sim<33||sim>254)	// todos los caracteres "imprimibles" y "extendido" de la tabla ASCII
    							{
    								al_clear_to_color(al_map_rgb(0, 0, 0));
    								al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16), ALLEGRO_ALIGN_CENTER,
    								"Símbolo inválido. Presione ENTER e ingrese un símbolo válido");
    								al_flip_display();
    								//verifica que el simbolo utilizado sea valido
    								err=1;
    							}
    							while(getchar()!='\n')
    							{
    							}
    						}while(err==1);
    						i++;
    						break;
    					case 4:
    						ini(celda,font24,event);//inicia el mundo falta arreglar que tome la a o la m
    						i++;
    						break;
    					case 5:
    						i++;
    						break;

    				}
    			if(i==6)
    			{
    				done=true;
    			}
    		}
		}
    }
    done=false;


    al_rest(4.0);

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

	/*********/

	
	
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


static void ini(int celda[][ANCHO],ALLEGRO_FONT * font24,ALLEGRO_EVENT event)
{
	int i,j;
	bool done1=false,done2;
	
	srand (time(NULL));	// inicializa seed random


	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16), ALLEGRO_ALIGN_CENTER,
	"Si desea que el estado inicial de las celulas sea aleatorio,");
	al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16)+50, ALLEGRO_ALIGN_CENTER,
	" ingrese 'a'. Si prefiere inicializarlo manualmente, ingrese 'm'.");
	al_flip_display();

	while(!done1)
	{
		if(event.keyboard.keycode==ALLEGRO_KEY_A)
		{
			for (i = 0 ; i < ALTO ; i++)
			{
				for (j = 0 ; j < ANCHO ; j++)
				{
					celda[i][j]=rand() % 2;	// randomiza cada celda, con 1 y 0
				}
			}
			done1=true;
		}
		else if(event.keyboard.keycode == ALLEGRO_KEY_M)
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16), ALLEGRO_ALIGN_CENTER,
			"Seleccione el estado de la célula: 1 si está viva o 0 si está muerta");
			al_draw_text(font24, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 16)+50, ALLEGRO_ALIGN_CENTER,
			"Chequee en consola que posicion esta iniciando");
			for ( i = 0; i < ALTO; i++)
			{
				for ( done2=false, j = 0 ; j < ANCHO ; j++)
				{
					printf("Estado de la célula en la posición %d,%d\n",i+1,j+1);	// se les suma 1 para que el primer el elemento de la matriz sea (1,1) y no (0,0)
					while(!done2)
					{
						if(event.keyboard.keycode == ALLEGRO_KEY_1)
						{
							celda[i][j]=1;
							done2=true;

						}
						else if (event.keyboard.keycode == ALLEGRO_KEY_0)
						{
							celda[i][j]=0;
							done2=true;
						}
					}
				}
			}
			done1=true;
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
