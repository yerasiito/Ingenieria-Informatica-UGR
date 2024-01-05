//////////////////////////////////////////////////////////////////////////
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Juan Carlos Cubero
//////////////////////////////////////////////////////////////////////////

// Generador aleatorio de números enteros


#include <random>  // para la generación de números pseudoaleatorios
#include <chrono>  // para la semilla
#include <iostream>
using namespace std;


class GeneradorAleatorioEnteros{
private:
   mt19937 generador_mersenne;   // Mersenne twister
   uniform_int_distribution<int>  distribucion_uniforme;

   long long Nanosec(){
      return chrono::high_resolution_clock::now().time_since_epoch().count();
   }

public:
   GeneradorAleatorioEnteros()
      :GeneradorAleatorioEnteros(0, 1){
   }

   GeneradorAleatorioEnteros(int min, int max){
      const int A_DESCARTAR = 70000; // Panneton et al. ACM TOMS Volume 32 Issue 1, March 2006
      auto semilla = Nanosec();

      generador_mersenne.seed(semilla);
      generador_mersenne.discard(A_DESCARTAR);
      distribucion_uniforme = uniform_int_distribution<int> (min, max);
   }

   int Siguiente(){
      return distribucion_uniforme(generador_mersenne);
   }
};


int main(){
   int num_a_generar;
   GeneradorAleatorioEnteros aleat_num_a_generar(1,5);
   GeneradorAleatorioEnteros aleat_0_1;

   for (int i = 0; i < 4; i++){
   num_a_generar = aleat_num_a_generar.Siguiente();
   cout << "\n El numero aleatorio entre 1 y 5 es: " << num_a_generar << endl;
      for(int j = 0; j < num_a_generar; j++){
         cout << " " << aleat_0_1.Siguiente();
      }
   }

}
