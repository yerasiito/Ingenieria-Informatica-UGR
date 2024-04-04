/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: yerasito
 *
 * Created on 31 de marzo de 2022, 11:18
 */

#include <cstdlib>
#include<iostream>
#include <vector>
#include <fstream>

using namespace std;

/*
 * 
 */

void compraVentaTrivial(vector<int> secuencia, int & c, int & v){
	int valor_menor=999; //Variable Intermedia para evaluar
	int comprar_dia, vender_dia;
	for(int i=0; i<secuencia.size(); i++){
		for(int j=i+1; j<secuencia.size() - i; j++){ //Tamanio normal del vector y le restamos la parte que ya se ha visto, por eso -i. Y igual, j=i+1 empieza en la siguiente a la que estamos comparando que es i.
			if(secuencia[i]-secuencia[j]<valor_menor){
				valor_menor=secuencia[i]-secuencia[j];
				c = i+1; //Los vectores empiezan en 0, pero los días no (empiezan en 1) hay que sumarle uno para que concuerde.
				v = j+1;
			}
		}
	}
}

int main(int argc, char** argv) {
    vector<int> secuencia{};
    
    string filename("secuencia.txt");
    int number;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (input_file >> number) {
        secuencia.push_back(number);
    }
    cout << endl;
    input_file.close();

    cout << "Secuencia: ";
    for(int i = 0; i < secuencia.size(); i++)
        cout << secuencia[i] << " ";
    cout << endl;
    
    int compra, venta;
    
    compraVentaTrivial(secuencia, compra, venta);
    
    cout << "El resultado es: " << endl;
    
    cout << "Dia de compra: " << compra << " con valor " << secuencia[compra] << endl;
    cout << "Dia de venta: " << venta << " con valor " << secuencia[venta] << endl;
    cout << endl;
    
    
    return 0;
}

