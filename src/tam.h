#ifndef TAM
#define TAM
#define ANCHO 10
#define ALTO 10
#define D_WIDTH  640
#define D_HEIGHT 480
#if (ALTO<=0 || ANCHO<=0)
	#error El alto y ancho debe ser positivo
#elif (ALTO>50 || ANCHO>50 || (ALTO*ANCHO)>1000)
	#warning La salida sera dificil de ver
#endif
//Error y advertencias para el alto y el ancho de la matriz

#endif
