/**
* @file bolsaLetras.cpp
* @author Yeray López Ramírez
* @author Jaime Castillo Ucles
* @date Diciembre 2021
*/

#include "bolsaLetras.h"

bolsaLetras::bolsaLetras(const bolsaLetras &otra){
	bolsa = otra.bolsa;
}

bolsaLetras::bolsaLetras(const conjuntoLetras & c){
	conjuntoLetras::iterator it;

	for (it = c.begin(); it != c.end(); ++it)
		aniadeLetra((*it));

}

int bolsaLetras::tama() const{
	return bolsa.size();
}

unordered_multiset<char> bolsaLetras::getBolsa(){
	return bolsa;
}

void bolsaLetras::aniadeLetra(const Letra & L){

	char caracter = L.getCaracter();

	for(int i = 0; i < L.getFrecuencia(); i++){
		bolsa.insert(toupper(caracter)); //Lo convierte a mayuscula
	}

}

void bolsaLetras::aniadeLetra(const char & caracter){
	bolsa.insert(toupper(caracter)); //Lo convierte a mayuscula
}

void bolsaLetras::quitaLetra(const Letra & L, bool todas){
	quitaLetra(L.getCaracter(), todas);
}

void bolsaLetras::quitaLetra(const char & caracter, bool todas){
    bolsaLetras::iterator it;
	it.it = bolsa.find(caracter);
    if(todas)
        bolsa.erase(*(it.it)); //Borra todas
    else
        bolsa.erase(it.it); //Borra solo 1
}

bolsaLetras bolsaLetras::getLetras(int num){
	bolsaLetras aux;

	if (num < tama()){
		bolsaLetras::iterator it;
		int pos;

		for (int i = 0; i < num; i++){
			it = begin();
			srand(time(NULL));
			pos = rand() % tama();
			for(int i = 0; i < pos; i++) //Avanza hasta pos (no podemos obtener el elemento con su indice)
				++it;
			aux.aniadeLetra((*it));
			it.it = bolsa.erase(it.it);
		}
	}

	return aux;
}

set<pair<int,string>> bolsaLetras::getSoluciones(const conjuntoLetras & Letras, const Diccionario & d, const char & modo){
	set<pair<int,string>> soluciones {};
    pair<int,string> sol;
    Diccionario::iterator it;
    for(it = d.begin(); it != d.end(); ++it){
        if(palabraValida((*it))){
            sol.second = (*it);
            sol.first = Letras.PuntuacionPalabra((*it), modo);

            soluciones.insert(sol);
        }
    }

    return soluciones;
}

bool bolsaLetras::Esta(const Letra & L){
	return ( bolsa.find(L.getCaracter()) != bolsa.end()) ;
}

bool bolsaLetras::Esta(const char & c){
	return ( bolsa.find(c) != bolsa.end()) ;
}

bool bolsaLetras::palabraValida(const string palabra){
	bool esValida = true;
    bolsaLetras aux = *this;
    size_t i;
	for(i = 0; i < palabra.size() && esValida; i++){
		esValida = aux.bolsa.find(toupper(palabra.at(i))) != bolsa.end();
        if(esValida)
            aux.quitaLetra(toupper(palabra.at(i)),false); //Borra solo UNA instancia de esa letra
    }
	return esValida;
}

istream & operator>> (istream &is, bolsaLetras &bolsa){
	conjuntoLetras c;

	is >> c;

	conjuntoLetras::iterator it;

	for (it = c.begin(); it != c.end(); ++it){
		bolsa.aniadeLetra((*it));
	}

	return is;
}


ostream & operator << (ostream &os, const bolsaLetras &b){
	bolsaLetras::iterator it;

	for (it = b.begin(); it != b.end(); ++it){
		os << (*it) << " ";
	}

	return os;
}

bolsaLetras::iterator bolsaLetras::begin(){
	iterator iterador;
	iterador.it = bolsa.begin();
	return iterador;

}

bolsaLetras::iterator bolsaLetras::begin() const{
	iterator iterador;
	iterador.it = bolsa.begin();
	return iterador;
}

bolsaLetras::iterator bolsaLetras::end(){
	iterator iterador;
	iterador.it = bolsa.end();
	return iterador;
}

bolsaLetras::iterator bolsaLetras::end() const{
	iterator iterador;
	iterador.it = bolsa.end();
	return iterador;
}
char bolsaLetras::iterator::operator* (){
	return (*it);
}

bool bolsaLetras::iterator::operator==(const bolsaLetras::iterator &i){
	return i.it == this->it;
}

bool bolsaLetras::iterator::operator!=(const bolsaLetras::iterator &i){
	return i.it != this->it;
}

bolsaLetras::iterator & bolsaLetras::iterator::operator++(){
	++it;
	return (*this);
}
