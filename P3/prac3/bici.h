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


// =========================== cilindro ================================================

void cilindro(float x0, float y0, float z0, 
		    float x1, float y1, float z1, float a, float b);
/*
	Crea un cilindro con centro de las bases en
	x0,y0,z0 y x1,y1,z1, y radio de la base a.
*/

// =========================== creaEstructura ==========================================

/**
 * Crea el cuerpo de la bicicleta: armazon, manillar, uniones de las ruedas
*/
void creaCuerpoBici();

/**
 * Crea las ruedas y las llantas
*/
void creaRuedas(float escala, float grosor);


/**
 * Crea los piñones y los pedales
*/
void creaSistemaPedales();

#endif

