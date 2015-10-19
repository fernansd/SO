#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h>

void * imprime(void *param) {
	int cont;
	char *cadena= (char*) param;
	for(cont=0; cont<strlen(cadena); cont++) {
		printf("%c",cadena[cont]);
	}
	pthread_exit(NULL);
}


int main () {

	pthread_t h1,h2;

	pthread_create(&h1,NULL,(void *) imprime,(void *) "hola ");
	pthread_create(&h2,NULL,(void *) imprime,(void *) "mundo");

	pthread_join(h1,NULL);
	pthread_join(h2,NULL);

	printf("\n");
	exit(EXIT_SUCCESS);

}
