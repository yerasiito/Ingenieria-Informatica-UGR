#include <stdio.h>
//generar fichero .s : gcc cmov.c -S -Wall -fverbose-asm
//Modificar el fichero .s para optimizar etc
//Compilar con: gcc cmov.s -o cmov

int main(){
	volatile int a=0;
	volatile int b=1;
	int c;

	c = (a==b)?3:7;

	printf("c: %i\n", c);
	return(0);
}
