#include <sys/types.h> //Para estructura pid_t 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int main( int argc, char **argv) {

	pid_t pid[10];
	int child_pid[10];
	int i, status;
	
	for (i=0; i< atoi(argv[1]); i++) {
		pid[i] = fork();
		if (pid[i] == 0) {
			printf("Soy el hijo: %d\n", getpid());
			exit(EXIT_SUCCESS);
		}
	}
	
	for (i=0; i< atoi(argv[1]); i++) {
		child_pid[i] = wait(&status);
		if(child_pid[i]>0)
            {
             	if (WIFEXITED(status)) 
					{
                    printf("child %d exited, status=%d\n",child_pid[i], WEXITSTATUS(status));
               } 
					else if (WIFSIGNALED(status)) 
					{
                    printf("child %d killed (signal %d)\n", child_pid[i], WTERMSIG(status));
               } 
					else if (WIFSTOPPED(status)) 
					{
                    printf("child %d stopped (signal %d)\n", child_pid[i], WSTOPSIG(status));
               } 
            }
            else
{
                printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
            }	
	}
	exit(EXIT_SUCCESS);
	



}
