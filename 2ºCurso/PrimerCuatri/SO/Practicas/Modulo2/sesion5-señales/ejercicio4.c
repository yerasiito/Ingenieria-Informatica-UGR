/*
	Crea una máscara a la que sólo le añade la señal SIGTERM.
	Aplica la máscara y con ello bloquea la señal SIGTERM.
	Realiza un sleep de 10s, y si durante este tiempo le mandamos dicha señal no reaccionará porque está bloqueada
	Desbloquea la señal SIGTERM reanudando la máscara antigua y comprueba si la hemos introducido comprobando si la variable signal_recibida está activada.
		(Si estaba activada nos muestra que la señal ya ha sido recibida, si no, acaba el programa sin mostrar nada)
 */

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int signal_recibida = 0;

static void manejador (int sig){
	signal_recibida = 1;
};

int main(int argc, char *argv[]){
	sigset_t conjunto_mascaras;
	sigset_t conj_mascaras_original;
	struct sigaction act;

	// Iniciamos a 0 todos los elementos de la estructura act
	memset(&act, 0, sizeof(act));
	
	act.sa_handler = manejador;

	if (sigaction(SIGTERM, &act, 0)){
		perror("sigaction");
		return 1;
	}

	// Iniciamos un nuevo conjunto de máscaras
	sigemptyset(&conjunto_mascaras);

	// Añadimos SIGTERM al conjunto de máscaras
	sigaddset (&conjunto_mascaras, SIGTERM);

	// Bloqueamos SIGTERM
	if (sigprocmask(SIG_BLOCK, &conjunto_mascaras, &conj_mascaras_original) < 0){
		perror("primer sigprocmask");
		return 1;
	}

	sleep(10);

	// Restauramos la señal - desbloqueamos SIGTERM
	if (sigprocmask(SIG_SETMASK, &conj_mascaras_original, NULL) < 0){
		perror("segundo sigprocmask");
		return 1;
	}

	sleep(1);

	if (signal_recibida)
		printf("\nSeñal recibida\n");
	
	return 0;
}