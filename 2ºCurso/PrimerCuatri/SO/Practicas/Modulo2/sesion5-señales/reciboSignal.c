#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static void sig_USR_hdlr(int sigNum){
	if (sigNum == SIGUSR1)
		printf("\nRecibida la señal SIGUSR1\n\n");
	else
		printf("\nRecibida la señal SIGUSR2\n\n");
}

int main(int argc, char *argv[]){
	struct sigaction sig_USR_nact;
	if (setvbuf(stdout, NULL, _IONBF, 0)){
		perror("\nError en setvbuf");
	}

	// Inicializar la estructura sig_USR_nact para especificar la nueva acción para la señal.
	sig_USR_nact.sa_handler = sig_USR_hdlr;

	// 'sigemptyset' inicia el conjunto de señales dado al conjunto vacío
	sigemptyset(&sig_USR_nact.sa_mask);
	sig_USR_nact.sa_flags = 0;

	// Establecer mi manejador particular de señal para SIGUSR1
	if (sigaction(SIGUSR1, &sig_USR_nact, NULL) < 0){
		perror("\nError al establecer el manejador de señal para SIGUSR1");
		exit(-1);
	}

	// Establecer mi manejador particular de señal para SIGUSR2
	if (sigaction(SIGUSR2, &sig_USR_nact, NULL) < 0){
		perror("\nError al establecer el manejador de señal para SIGUSR2");
		exit(-1);
	}

	for(;;){};
}