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
    int beneficio, compra, venta, optimo = -999999;
    
    for(int i = 0; i < secuencia.size(); i++){
        compra = secuencia[i];
        for(int j = i+1; j < secuencia.size(); j++){
            venta = secuencia[j];
            beneficio = venta - compra;
            if(beneficio > optimo){
                optimo = beneficio;
                c = i;
                v = j;
            }
        }
    }
    
            
}

int main(int argc, char** argv) {
    vector<int> secuencia{};
    
    //Lectura del archivo
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
    input_file.close();

    //Imprime secuencia
    cout << "Secuencia: ";
    for(int i = 0; i < secuencia.size(); i++)
        cout << secuencia[i] << " ";
    cout << endl;
    
    //Calcula ventaCompra
    int compra = 0, venta = 1;
    
    compraVentaTrivial(secuencia, compra, venta);
    
    cout << "El resultado es: " << endl;
    
    cout << "Dia de compra: " << compra << " con valor " << secuencia[compra] << endl;
    cout << "Dia de venta: " << venta << " con valor " << secuencia[venta] << endl;
    cout << endl;
    
    
    return 0;
}

