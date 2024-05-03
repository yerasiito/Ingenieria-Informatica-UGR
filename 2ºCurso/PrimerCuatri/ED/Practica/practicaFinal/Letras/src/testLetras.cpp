#include "diccionario.h"
#include "conjuntoLetras.h"
#include "bolsaLetras.h"

using namespace std;

/**
* @file testLetras.cpp
* @brief Archivo de prueba para el juego de las Letras. Requiere de:
* -un diccionario.txt
* -un letras.txt(con el formato dado en el guion)
* -el numero de letras a generar
* -modalidad
* @author Yeray López Ramírez
* @author Jaime Castillo Ucles
* @date Diciembre 2021
*/
int main(int argc, char * argv[]){

	if (argc != 5){
		cerr << "Numero incorrecto de argumentos." << endl
			  << "Uso : " << argv[0] << " <Diccionario> <letras> <numero_letras> <modalidad de juego> "
			  << endl
			  << "Modos de juego: " << endl << "\t L (Longitud de palabra) "
			  << "\t P (Puntuacion de la palabra)" << endl;
		exit(1);
	}

	int nLetras = atoi(argv[3]);

	if (nLetras <= 0){
		cout << "El numero de letras a jugar no puede ser menor a 0" << endl;
		exit(2);
	}

	if (argv[4][0] != 'P' && argv[4][0] != 'L'){
		cout << "Modalidades de juego incorrectas" << endl;
		exit(3);
	}

	ifstream f(argv[1]);

	if(!f) {
		cout << "No se puede abrir el fichero" << argv[1] << endl;
		exit(4);
	}

	Diccionario d;
	f >> d;

	f.close();

	conjuntoLetras Letras;
	f.open(argv[2], fstream::in);

	if(!f) {
		cout << "No se puede abrir el fichero" << argv[2] << endl;
		exit(5);
	}

	f >> Letras;

	f.close();

	bolsaLetras bolsa(Letras);

	bool salir = false;
	char jugar;

    cout << "Modo de Juego:";
	if (argv[4][0] == 'P')
        cout << "PUNTUACIÓN" << endl;
    else{
        cout << " LONGITUD" << endl;
    }

	while(!salir){
		bolsaLetras nueva(bolsa.getLetras( nLetras )); //Lo llama pocas veces, no pasa nada

		cout << "Las letras a jugar son: ";

		cout << nueva;

		string palabraUsuario;

		cout << endl << "Tu respuesta: ";
		cin >> palabraUsuario;

		if (nueva.palabraValida(palabraUsuario)){
			if(d.Esta(palabraUsuario)){
				cout << "\nPalabra encontrada: " << palabraUsuario << "\t Puntuacion: " << Letras.PuntuacionPalabra(palabraUsuario, argv[4][0]) << endl << endl;
			}
			else{
				cout << endl << "La palabra '"<< palabraUsuario << "' no existe" << endl << endl;
			}
		}
		else{
			cout << endl << "La palabra dada contiene caracteres que no se han proporcionado" << endl;
		}

		set<pair<int,string>> soluciones = nueva.getSoluciones(Letras, d, argv[4][0]);

		set<pair<int,string>>::const_iterator it;

		cout << "Soluciones posibles: " << endl;
		for(it = soluciones.begin(); it != soluciones.end(); ++it){
			cout << " Puntuacion: " << it->first << " - Palabra: " << it->second << endl;
		}

		if(soluciones.size() > 0){
			cout << endl << "La mejor solucion es: '"
                 << soluciones.rbegin()->second << "' con una puntuacion de "
                 << soluciones.rbegin()->first << " puntos." << endl;

		}else {
			cout << endl << "No existen soluciones posibles las letras dadas y en el diccionario " << argv[1] << endl;
		}

		do{
			cout << "¿Quieres seguir jugando? [S/N] ";

            cin >> jugar; //convierte a mayuscula
            jugar = toupper(jugar);
		}while(jugar != 'S' && jugar != 'N');

		if (jugar != 'S')
			salir = true;
	}

	return 0;
}
