#include <iostream>
#include "Complejo.hpp"

using namespace std;

Complejo::Complejo(double r, double i){
  v_real = r;
  v_imaginario = i;
}

double Complejo::real() const{
  return v_real;
}

double Complejo::imaginaria() const{
  return v_imaginario;
}

Complejo Complejo::operator+(Complejo c){
  return Complejo(this->real()+c.real(), this->imaginaria()+c.imaginaria());
}

Complejo Complejo::operator-(Complejo c){
  return Complejo(this->real()-c.real(), this->imaginaria()-c.imaginaria());
}

ostream & operator<<(ostream & flujo, const Complejo c){
  flujo << "(" << c.real() << "," << c.imaginaria() << ")";
  return flujo;
}

istream & operator>>(istream & flujo, Complejo &c){
  char caracter;
  double r, i;
  flujo >> caracter >> r >> caracter >> i >> caracter;
  c = Complejo(r,i);
  return flujo;
}

