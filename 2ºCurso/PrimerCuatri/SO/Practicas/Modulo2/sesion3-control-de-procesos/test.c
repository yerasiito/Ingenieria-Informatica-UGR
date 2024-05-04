#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    printf("id. de usuario: %d\n", getuid());
    printf("id. grupo: %d\n", getgid());
    return 0;
}
