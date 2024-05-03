#include <stdio.h>
#include <cstring>
#include "fecha.h"

using namespace std;


void constructor (Fecha & f, int dia, int mes, int anio){
  f.dia = dia;
  f.mes = mes;
  f.anio = anio;
}

void lee(Fecha & f, char * cadena){
  sscanf(cadena, "%d/%d/%d", &(f.dia), &(f.mes), &(f.anio));
}

int dia(Fecha f){
  return f.dia;
}

int mes(Fecha f){
  return f.mes;
}

int anio(Fecha f){
  return f.anio;
}

char * Escribe (Fecha f, char * cadena){
  sprintf(cadena, "%2d/%2d/%4d", f.dia, f.mes, f.anio);
  return cadena;
}

void Siguiente(Fecha f, Fecha &g){
  int limite_dia;
  switch (f.mes) {
    case 2:
      limite_dia = 28;
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      limite_dia = 30;
      break;
    default:
      limite_dia = 31;
      break;
  }
  
  g = f;
  
  while ((g.dia +1) > limite_dia)
  {
    g.dia -= limite_dia;
    if (g.mes == 12)
    {
      g.mes = 0;
      g.anio++;
    }
    g.mes++;
  }
  g.dia++;
}


void Anterior(Fecha & f){
  
}



bool menor(Fecha f1, Fecha f2){
  bool resultado;
  if (f1.anio>f2.anio)
    resultado = false;
  else if (f1.anio<f2.anio)
    resultado = true;
  else if (f1.mes>f2.mes) //Años iguales. Vemos el mes
    resultado = false;
  else if (f1.mes<f2.mes)
    resultado = true;
  else if(f1.dia>=f2.dia) //Años y meses iguales. Vemos el día
    resultado = false;
  else if(f1.dia<f2.dia)
    resultado = true;
  else
    resultado = false;
  
  return resultado;
}

bool menor_o_igual(Fecha f1, Fecha f2){
  return true;
}


