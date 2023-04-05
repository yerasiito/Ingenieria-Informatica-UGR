#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include "fact.h"

using namespace std;
using namespace std::chrono;

void funcion_lenta() {
  //this_thread::sleep_for(2000ms);
  fact(40);
}

int main() {
  auto momentoInicio = high_resolution_clock::now();
  funcion_lenta();
  auto momentoFin = high_resolution_clock::now();

  // Calculo el tiempo que le ha tomado al algoritmo ejecutarse
  milliseconds tiempo = duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
  cout <<"Tiempo Pasado: " <<tiempo.count() <<endl;

  auto momentoInicio2 = std::clock();
  funcion_lenta();
  auto momentoFin2 = std::clock();

  // Calculo el tiempo que le ha tomado al algoritmo ejecutarse
  auto tiempo2 = 1000.0*(momentoFin2 - momentoInicio2)/CLOCKS_PER_SEC;
  cout <<"Tiempo CPU Proceso: " <<tiempo2 <<endl;
}
