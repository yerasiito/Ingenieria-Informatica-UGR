/*
	Programa que suspenda la ejecución del proceso actual hasta que se reciba la señal SIGUSR1.
*/

#include <stdio.h>
#include <signal.h>

int main(){
	sigset_t new_mask;

	// inicializa la nueva máscara de señales
	sigemptyset(&new_mask);

	sigfillset(&new_mask);

	sigdelset(&new_mask, SIGUSR1);

	// esperara a cualquier señal menos a SIGUSR1
	sigsuspend(&new_mask);
}