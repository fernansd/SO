#include <sys/types.h> //Para estructura pid_t 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

void llamaCalculadora(); 
void llamaGedit(char **archivos, int argc); 
void status_handler(int *status, pid_t pid);

int main (int argc, char **argv) {
	pid_t pid_gedit, pid_calc;
	pid_calc =	fork();
	int status_calc, status_gedit;

	switch (pid_calc) {
		case -1:
			printf("Error forking Calc\n");
			break;
		case 0:
			llamaCalculadora();
			break;
		default:
			printf("calc\n");
			waitpid(pid_calc,&status_calc, 0);
			status_handler(&status_calc, pid_calc);	
			pid_gedit = fork();

	}

	switch(pid_gedit) {
		case -1:
			printf("Error forking Gedit\n");
			break;
		case 0:
			llamaGedit(argv,argc);
			break;
		default:
			printf("gedit\n");
			waitpid(pid_gedit,&status_gedit,0);
			status_handler(&status_gedit, pid_gedit);
	}

return 0;
}

void llamaCalculadora() {
	if(execlp("gnome-calculator","gnome-calculator",NULL)){
		printf("Error ejecutando la calculadora\n");
		exit(EXIT_FAILURE);
	}
}

void llamaGedit(char **archivos, int argc) {
	if(execlp("/usr/bin/gedit","gedit",archivos, NULL)){
		printf("Error ejecutando gedit\n Saliendo del programa\n");
		exit(EXIT_FAILURE);
	}
}

void status_handler(int *status, pid_t pid) {
	     if(*status)
	      {
	       	if (WIFEXITED(*status)) 
				{
	              printf("child %d exited, status=%d\n",pid, WEXITSTATUS(*status));
	         } 
				else if (WIFSIGNALED(*status)) 
				{
	              printf("child %d killed (signal %d)\n", pid, WTERMSIG(*status));
	         } 
				else if (WIFSTOPPED(*status)) 
				{
	              printf("child %d stopped (signal %d)\n", pid, WSTOPSIG(*status));
	         } 
	      }
	      else 
			{
	          printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");

	      } 

}
