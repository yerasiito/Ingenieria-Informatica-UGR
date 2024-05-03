/**
* @file letra.cpp
* @author Yeray López Ramírez
* @author Jaime Castillo Ucles
* @date Diciembre 2021
*/
#include "letra.h"

Letra::Letra(){
	caracter = 'A'; //Por defecto 'A'
	frecuencia = 0;
	puntuacion = 0;
}

Letra::Letra(const char &c, const int &frec, const int &punt){
	caracter = c;
	frecuencia = frec;
	puntuacion = punt;
}

char Letra::getCaracter() const{
	return caracter;
}

int Letra::getPuntuacion() const{
   return puntuacion;
}

int Letra::getFrecuencia() const{
	return frecuencia;
}

void Letra::setCaracter(const char &c){
	caracter = c;
}

void Letra::setFrecuencia( const int &frec){
	frecuencia = frec;
}

void Letra::setPuntuacion(const int &punt){
	puntuacion = punt;
}

bool Letra::operator== (const Letra &otra) const{
	return getCaracter() == otra.getCaracter();
}

bool Letra::operator< (const Letra &otra) const{
	return caracter < otra.getCaracter();
}

istream & operator>> (istream &is, Letra &L){
	is >> L.caracter;
	is >> L.frecuencia;
	is >> L.puntuacion;

	return is;
}

ostream & operator<< (ostream &os, const Letra &L){
	os << L.caracter << "\t"
       << L.frecuencia << "\t"
       << L.puntuacion << endl;

	return os;
}
