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
#include <chrono>
#include <ctime>

using namespace std::chrono;

using namespace std;

high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;
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
    int compra = 0, venta = 1;

    if (argc != 2)
    {
        cerr << "Formato " << argv[0] << " <num_elem>" << endl;
        return -1;
    }

    srandom(time(0));
  int n = atoi(argv[1]);

    for (int i = 0; i < n; i++)
    {
        secuencia.push_back(random()%500);
    }


    tantes = high_resolution_clock::now();

    compraVentaTrivial(secuencia, compra, venta);

    tdespues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    cout << n << " " << transcurrido.count() << endl;

    
    return 0;
}

