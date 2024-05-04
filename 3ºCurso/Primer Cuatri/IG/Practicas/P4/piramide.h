/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Yeray Lopez Ramirez

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================

	entradaTeclado.h
*/

#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "modelo.h"

class Piramide:Objeto3D
{
private:
  float lado;
  float alto;
  float Nx=0,Ny=0; //Normales de la piramide regular
  float color[4] = { 0, 0.5, 0.8, 1 };

public:
  Piramide(float l = 1, float h = 1);

  //Dados 2 longitudes (vectores) que forman un triangulo rectangulo, calcula la normal
  void calcularNormal(float base, float altura);

  void draw();
};

#endif