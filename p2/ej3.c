// -- ej3.c --
// Ejercicio nº3 de la Práctica 2
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct Argumentos {
	int * vector;
	int longitud;
};


int main (int argc, char* argv[]) {
	if(argc != 2) {
		printf("Número de parámetros incorrecto\nLa llamada es de la forma:\n"
				   "<nombre ejecutable> <numero de hebras a crear>\n");
		exit(EXIT_FAILURE);
	}

	int n_hebras = atoi(argv[1]);
	if (n_hebras > 5) {
		printf("El número de hebras es demasiado grande, introduce uno menor o igual a 5 y mayor que 0\n");
		exit(EXIT_FAILURE);
	}

	//Generamos el vector de números a sumar
	srand(time(NULL));
	int numeros[10], i;
	printf("Vector generado: ");
	for(i=0; i<10; i++) {
		numeros[i] = rand()%10;
		printf("%d, ",numeros[i]);
	}
	printf("\n\n");


	/** Repartimos el número de elementos entre todas la hebras
	  * en caso de que el reparto no sea equitativo, se crea
	  * una de las hebras se cargará con el resto 
	  */
	int reparto;
	reparto = 10/n_hebras;
	struct Argumentos arg[n_hebras];
	
	i=0;
	if(10%n_hebras) { 
		arg.vector = numeros;
		arg.longitud = 10%n_hebras;
		pthread_create(&hebras[i],NULL,(void *) sumaVector,&arg);
		i=1;
	}
	for(i=0; i<n_hebras; i++) {
		arg[i].vector = numeros+
	}

	//Creamos las hebras
	for(i=0; i<n_hebras; i++) {
		pthread_create(&hebras[i],NULL,(void *) sumaVector,&numeros);
	}


	

exit(EXIT_SUCCESS);
}
