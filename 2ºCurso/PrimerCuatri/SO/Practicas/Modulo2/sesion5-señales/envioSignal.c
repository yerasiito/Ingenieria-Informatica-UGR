/*
	Utilización de la llamada kill para enviar una señal:
	0: SIGTERM
	1: SIGUSR1
	2: SIGUSR2

	a un proceso cuyo identificador de proceso es PID.
 */

#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char *argv[]){
	long int pid;
	int signal;

	if (argc < 3){
		printf("\nSintaxis de ejecución: envioSignal [012] <PID>\n\n");
		exit(-1);
	}

	pid = strtol(argv[2], NULL, 10);

	if (pid == LONG_MIN || pid == LONG_MAX){
		if (pid == LONG_MIN)
			printf("\nError por desbordamiento inferior LONG_MIN %d", pid);
		else
			printf("\nError por desbordamiento superior LONG_MAX %d", pid);
		
		perror("\nError en strtol");
		exit(-1);
	}

	signal = atoi(argv[1]);

	switch(signal){
		case 0: kill(pid, SIGTERM); break;
		case 1: kill(pid, SIGUSR1); break;
		case 2: kill(pid, SIGUSR2); break;
		default: printf("\nNo puedo enviar este tipo de señal");
	}

	return 0;
}