/**
* @file conjuntoLetras.cpp
* @author Yeray López Ramírez
* @author Jaime Castillo Ucles
* @date Diciembre 2021
*/

#include "conjuntoLetras.h"

const string conjuntoLetras::formato = "#Letra Frecuencia Puntos";

int conjuntoLetras::tama() const{
	return Letras.size();
}

set<Letra> conjuntoLetras::getLetras() const{
	return Letras;
}

void conjuntoLetras::aniadeLetra(const Letra &Letra){
	Letras.insert(Letra);
}

void conjuntoLetras::quitaLetra(const Letra &Letra){
	Letras.erase(Letra);
}

Letra conjuntoLetras::getLetra(const char &c) const{
	Letra L;
	L.setCaracter(c);
	return *(Letras.find(L));
}

bool conjuntoLetras::Esta(const Letra &Letra) const{
	return (Letras.find(Letra) != Letras.end());
}

int conjuntoLetras::PuntuacionPalabra(const string palabra, const char & modo) const{
	int total = 0;

	if (modo == 'P'){
		Letra L;
		for(size_t i = 0; i < palabra.size(); i++){
			L.setCaracter(toupper(palabra.at(i))); //Convierte la letra en mayusucla
			L = (*Letras.find(L));

			total += L.getPuntuacion();
		}
	}
	else
		total = palabra.size();

	return total;
}


int conjuntoLetras::frecuenciaTotal() const{
	int total = 0;

	set<Letra>::iterator it;

	for (it = Letras.begin(); it != Letras.end(); ++it)
		total += (*it).getFrecuencia();

	return total;
}

conjuntoLetras conjuntoLetras::contarLetras(const Diccionario &d){
    conjuntoLetras aux;
    Letra L;

    Diccionario::iterator dit;
    set<Letra>::iterator sit;
    string palabra;

    for(dit = d.begin(); dit != d.end(); ++dit){
        palabra = (*dit);
        for(size_t i=0; i < palabra.size(); i++){
            L.setCaracter(toupper(palabra.at(i))); //La convierte en mayuscula
            sit = Letras.find(L);
            if(sit != Letras.end()){ //Si la letra no existe, no hace nada
                L = (*sit);
                L.setFrecuencia(L.getFrecuencia()+1);
            }
        }
    }
    return aux;
}


istream & operator>> (istream &is, conjuntoLetras &conjunto){

	Letra L;
	string primeraLinea;

	getline(is, primeraLinea);

	if(primeraLinea.empty() || primeraLinea != conjunto.formato){
		cerr << "ERROR: No se puede leer el conjunto de letras. La primera linea del "
             << "archivo letras.txt debe tener el formato: \n\t" << conjunto.formato << endl;
        exit(1);
	} else {
		while (is >> L ){
			conjunto.Letras.insert(L);
		}
	}

	return is;
}

ostream & operator<< (ostream &os, const conjuntoLetras &conjunto){

	os << conjunto.formato << endl;

	conjuntoLetras::iterator it;

	for(it = conjunto.begin(); it != conjunto.end(); ++it){
		os << (*it);
	}
	return os;

}

conjuntoLetras::iterator conjuntoLetras::begin(){
	iterator iterador;
	iterador.it = Letras.begin();
	return iterador;
}

conjuntoLetras::iterator conjuntoLetras::begin() const{
	iterator iterador;
	iterador.it = Letras.begin();
	return iterador;

}

conjuntoLetras::iterator conjuntoLetras::end(){
	iterator iterador;
	iterador.it = Letras.end();
	return iterador;
}

conjuntoLetras::iterator conjuntoLetras::end() const{
	iterator iterador;
	iterador.it = Letras.end();
	return iterador;
}

conjuntoLetras::iterator & conjuntoLetras::iterator::operator++(){
	++it;
	return (*this);
}

bool conjuntoLetras::iterator::operator==(const conjuntoLetras::iterator &i){
	return i.it == it;
}

bool conjuntoLetras::iterator::operator!=(const conjuntoLetras::iterator &i){
	return i.it != it;
}

Letra conjuntoLetras::iterator::operator* (){
	return (*it);
}
