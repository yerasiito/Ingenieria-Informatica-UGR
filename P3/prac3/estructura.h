/*

	Informática Gráfica					Curso 2022-23
	
	Dpto. Lenguajes y Sistemas Informaticos
	E.T.S.I. Informaica
	Univ. de Granada
	
	J.C. Torres

        Modulo de creacion de elementos geometricos para gruas. Creado a partir del código de las práacticas de CAD (https://lsi2.ugr.es/~cad/).
	 
*/
#ifndef __estructuraH__ // Para evitar doble inclusion
#define __estructuraH__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>


// =========================== caja ================================================

void caja( float a, float b, float m);
/* Construye un paralelepipedo alineado con los ejes de
dimension a x b x m. El objeto se construye en el semiespacio y>=0, con el origen en el
centro de la base. 
*/

void cilindro(float x0, float y0, float z0, 
		    float x1, float y1, float z1, 
		    float a);
/*
	Crea un cilindro con centro de las bases en
	x0,y0,z0 y x1,y1,z1, y radio de la base a.
*/


void cono(float x0, float y0, float z0, 
		    float x1, float y1, float z1, 
		    float a);
/*
	Crea un cono con centro de las bases en
	x0,y0,z0 y x1,y1,z1, y radio de la base a.
*/


// ========================== paralelepipedo ===========================================

void paralelepipedo(float x0, float y0, float z0, 
		    float x1, float y1, float z1, 
		    float a, float b);
/*
	Crea un paralelepipedo con centro de las bases en
	x0,y0,z0 y x1,y1,z1, y tamaño de la base axb.
*/


// =========================== creaEstructura ==========================================

void creaEstructura(float x0, float y0, float z0, 
		    float x1, float y1, float z1, float a, float b, int n);
/*
	Crea un fragmento de estructura de una grua, con centro de las bases en
	x0,y0,z0 y x1,y1,z1. Las secciones de las bases tienen tamaño axb
	n es el numero de niveles que tiene la estructura.

	Los perfiles tienen seccion cuadrada, dada por el parametro seccion.
	
	Para crear la estructura se utiliza el procedimiento paralelepipedo.
*/

void creaBrazo(float x0, float y0, float z0, 
		    float x1, float y1, float z1, float a, int n);
/*
	Crea un fragmento del brazo de una grua, con centro en una de las aristas 
	de cada extremos en
	x0,y0,z0 y x1,y1,z1. Los lados de las bases tienen tamaño a,
	n es el numero de tramos.

	Los perfiles tienen seccion triangular
	
	Para crear la estructura se utiliza el procedimiento paralelepipedo.
*/

void creaTorre(float x0, float y0, float z0, 
		    float x1, float y1, float z1, float a, float b, int n);
/*
	Crea un fragmento de la terminación de la estructura de una grua, 
	con centro de las bases en
	x0,y0,z0 y x1,y1,z1. Las secciones de las bases tienen tamaño axb
	n es el numero de niveles que tiene la estructura.

	Los perfiles tienen seccion cuadrada, dada por el parametro seccion.
	
	Para crear la estructura se utiliza el procedimiento paralelepipedo.
*/

void creaGancho(float x0, float y0, float z0, float alto);
/*	Crea un gancho colgando verticalmente del punto (x0,y0,z0) de tamaño alto
*/



#endif

