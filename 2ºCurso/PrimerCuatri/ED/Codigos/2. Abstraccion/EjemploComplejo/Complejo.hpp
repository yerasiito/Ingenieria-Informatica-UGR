#ifndef complejo_h
#define complejo_h

#include <iostream>
using namespace std;

class Complejo{
private:
  double v_real;
  double v_imaginario;
public:
  Complejo(double r=0, double i=0);
  double imaginaria () const;
  double real() const;
  Complejo operator+(Complejo c1);
  Complejo operator-(Complejo c1);
  friend ostream & operator<<(ostream & flujo, const Complejo c);
  friend istream & operator>>(istream & flujo, Complejo &c);
};

#endif // complejo_h
