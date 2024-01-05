//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

// Elimina ocurrencias de una competencia (versión eficiente)
// La entrada de cin de este programa es un .txt con todo el Quijote

#include <iostream>
using namespace std;

int main (){
	const char TERMINADOR = '#';
	const long long MAX_NUM_CARACTERES = 25e+5;
	char v[MAX_NUM_CARACTERES];
	char a_borrar;
	char caracter;
	int pos_escritura, pos_lectura, utilizados_v, utilizados_final;
	
   caracter = cin.get();
   utilizados_v = 0;
   
   while (caracter != TERMINADOR){
      v[utilizados_v] = caracter;
      caracter = cin.get();
      utilizados_v++;
   }
   
   a_borrar = cin.get();
	
	utilizados_final = 0;
	pos_escritura = 0;
	pos_lectura = 0;
	
	for (int i = pos_escritura ; i < utilizados_v ; i++){
		if (v[pos_lectura] == a_borrar){
			while (v[pos_lectura] == a_borrar){
				pos_lectura++;	
			}

			v[pos_escritura] = v[pos_lectura];
			utilizados_final++;
		}
		else{
			v[pos_escritura] = v[pos_lectura];
		}
		
		pos_escritura++;
		pos_lectura++;
	}
	
	for (int i = 0 ; i <= utilizados_final ; i++){
		cout << v[i];
	}
      
}

