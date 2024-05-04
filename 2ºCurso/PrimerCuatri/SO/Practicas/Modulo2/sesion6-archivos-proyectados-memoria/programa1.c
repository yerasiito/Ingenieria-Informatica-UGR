// Bloqueo de múltiples archivos

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	struct flock cerrojo;
	int fd;

	while(--argc > 0){
		if ((fd = open(*++argv, O_RDWR)) == -1){
			perror("Error en open");
			continue;
		}
	}

	cerrojo.l_type = F_WRLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;

	// Bloqueo de escritura del archivo completo
	while(fcntl(fd, F_SETLK, &cerrojo) == -1){
		// si el cerrojo falla, vemos quién lo bloquea
		while(fcntl(fd, F_GETLK, &cerrojo) == -1){
			printf("%s bloqueado por %d desde %d hasta %d para %c", *argv, cerrojo.l_pid, cerrojo.l_start, cerrojo.l_len, cerrojo.l_type == F_WRLCK ? 'w' : 'r');
			if (!cerrojo.l_len) break;
			cerrojo.l_start += cerrojo.l_len;
			cerrojo.l_len = 0;
		}
	}

	cerrojo.l_type = F_ULOCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;
	if (fcntl(fd, F_SETLKW, &cerrojo) == -1)
		perror("Error en desbloqueo\n");

	return 0;
}