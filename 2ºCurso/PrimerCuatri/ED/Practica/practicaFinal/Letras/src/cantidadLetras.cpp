#include <map>

#include "diccionario.h"
#include "conjuntoLetras.h"

using namespace std;

/**
* @file cantidadLetras.cpp
* @brief Programa de prueba donde a partir de un diccionario y un conjunto de letras, genera
* un archivo de salida con las frecuencias absolutas y relativas de cada letra del diccionario.
* Ademas actualiza las cantidades y puntuaciones del archivo conjunto de letras(letras.txt).
* @author Yeray López Ramírez
* @author Jaime Castillo Ucles
* @date Diciembre 2021
*/

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		cout << "Uso: cantidad_letras <diccionario.txt> <letras.txt> <ficherosalida.txt>" << endl;
		exit(EXIT_SUCCESS);
	}

	///////////////////////////////////////////////////////////////////////////////////////////
    //CARGAR FICHERO DICCIONARIO.txt y LETRAS.txt
	///////////////////////////////////////////////////////////////////////////////////////////
	fstream f(argv[1]);
	Diccionario D;
	conjuntoLetras Letras;

	if (!f)
	{
		cerr << "Error: No se puede abrir el fichero diccionario" << endl;
		return 0;
	}
	while(!f.eof())
        f >> D;
	f.close();

	f.open(argv[2]);
	if (!f)
	{
		cerr << "Error: No se puede abrir el fichero de letras" << endl;
		return 0;
	}
	f >> Letras;
	f.close();

	///////////////////////////////////////////////////////////////////////////////////////////
    //CALCULO DE APARICIONES
    ///////////////////////////////////////////////////////////////////////////////////////////

	map<char,int> frecsAbsolutas;
	map<char,int>::iterator itMap;
	double  frecTotal = 0;
    string palabra;

	for (conjuntoLetras::iterator it = Letras.begin(); it != Letras.end(); ++it)
		frecsAbsolutas.insert(make_pair((*it).getCaracter(), 0));

	for (Diccionario::iterator itDic = D.begin(); itDic != D.end(); ++itDic)
	{
		palabra = (*itDic);
		for (size_t i = 0; i < palabra.size(); i++){
            itMap = frecsAbsolutas.find(toupper(palabra.at(i)));
			if(itMap != frecsAbsolutas.end())
			{
				(*itMap).second++;
				frecTotal++;
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////
    //ESCRITURA DE LOS RESULTADOS EN LOS ARCHIVOS
	///////////////////////////////////////////////////////////////////////////////////////////

	char car;
	double frecRelativa;
	fstream fLetras(argv[2], fstream::out | fstream::trunc);

	if (!fLetras)
	{
		cerr << "Error: No se puede abrir el fichero de letras" << endl;
		return 0;
	}

	f.open(argv[3], fstream::out | fstream::trunc);
	if (!f)
	{
		cerr << "Error: No se puede abrir el fichero de salida" << endl;
		return 0;
	}

	fLetras << Letras.formato << endl;
	f << "#Letra	FAbs.	FRel." << endl;

    int factorCorrPuntos = 5; //Las primeras letras tendran menos puntuacion a pesar de aparecer poco
	for (conjuntoLetras::iterator it = Letras.begin(); it != Letras.end(); ++it)
	{
		car = (*it).getCaracter();
		frecRelativa = frecsAbsolutas[car] / frecTotal;

		f << car << "\t" << frecsAbsolutas[car] << "\t" << frecRelativa << "\n";

		frecRelativa *= 100;

		if (frecRelativa < 1)
			fLetras << car << "\t" << 1 << "\t";
		else
			fLetras << car << "\t" << (int) frecRelativa << "\t";

		if (10/frecRelativa > 10)
            if(factorCorrPuntos > -1)
                fLetras << (10 - factorCorrPuntos--) << endl;
            else fLetras << 10 << endl;
		else if (10/frecRelativa < 1)
			fLetras << 1 << endl;
		else
			fLetras << (int) (10/frecRelativa) << endl;
	}
	fLetras.close();
	f.close();
}
