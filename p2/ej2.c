// -- ej2.c --
// Ejercicio nº2 de la Práctica 2
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

//Función que se pasa al crear las hebras
void * generaAleatorios(int *indice) {

	int num1, num2;
	int * suma = (int*) malloc(sizeof(int));
	num1 = rand()%10;
	num2 = rand()%10;
	suma = num1 + num2;

	//Imprime para poder comprobar que se pasa correctamente suma al main
	printf("En la hebra %d -> %d + %d = %d\n",*indice,num1,num2,suma);
	pthread_exit((void *) suma);
}

int main (int argc, char* argv[]) {
	if(argc != 2) {
		printf("Número de parámetros incorrecto\nLa llamada es de la forma:\n"
				   "<nombre ejecutable> <numero de hebras a crear>\n");
	}

	int i, n_hebras = atoi(argv[1]);
	pthread_t hebras[n_hebras];
	srand(time(NULL));

	for (i=0; i<n_hebras; i++) {
		pthread_create(&hebras[i],NULL,(void *) generaAleatorios,&i);
		usleep(100000);
			
	}

	int valor, suma = 0;
	for (i=0; i<n_hebras; i++) {
		pthread_join(hebras[i],(void *) &valor);	
		suma = suma + valor;
	}
	printf("El valor de la suma de todo es %d\n",suma);



exit(EXIT_SUCCESS);
}
