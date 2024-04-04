#include<iostream>
#include<gmpxx.h>

//g++ -lstdc++ -lgmpxx -lgmp  -o fibonacci fibonacci.cpp
//time ./fibonacci 1000000 > myfib.txt

using namespace std;

mpz_class fibonacci(int);

mpz_class fibonacci(int n){
	mpz_class suma = 1;
	if(n <= 1){
		return n;
	}
	else{
		mpz_class x = 1, y = 0;
		for(long i = 2; i <= n; i++){
			suma = x+y;
			y = x;
			x = suma;
		}
	}
	return suma;
}

int main(int argc, char ** argv){
	long n;
	if(argc == 2)
		n = atol(argv[1]);
	else{
		cout << "Número de argumentos incorrecto." << endl;
		exit(1);
	}

	mpz_class fib = fibonacci(n);
	cout << fib << endl;
	return 0;
	
}
