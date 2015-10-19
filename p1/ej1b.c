#include <sys/types.h> //Para estructura pid_t 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

void status_handler(int status, int pid) {
	if (WIFEXITED(status)) 
				{
                   printf("child %d exited, status=%d\n",pid, WEXITSTATUS(status));
              } 
				else if (WIFSIGNALED(status)) 
				{
                   printf("child %d killed (signal %d)\n", pid, WTERMSIG(status));
              } 
				else if (WIFSTOPPED(status)) 
				{
                   printf("child %d stopped (signal %d)\n", pid, WSTOPSIG(status));
              } 
           }
           else
{
            printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
            }	

}

int main( int argc, char **argv) {

	pid_t pid;
	int child_pid;
	int i, status;
	
	for (i=0; i< atoi(argv[1]); i++) {
		pid = fork();
		switch(pid){
			case -1:
				printf("Error forking\n");
			case 0:
				printf("Hijo con pid %d\n",getpid());
			default:
				pid = wait(&status);
				status_handler(status,pid);
				
		}
	}

