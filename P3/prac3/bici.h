/*

	Informática Gráfica					Curso 2022-23
	
	E.T.S.I. Informaica
	Univ. de Granada
	
	Yeray Lopez Ramirez

        Modulo de creacion de elementos geometricos para una bicicleta.
	 
*/
#ifndef __biciH__ // Para evitar doble inclusion
#define __biciH__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>


// =========================== caja ================================================

void caja(float x0, float y0, float z0,
		    float x1, float y1, float z1, float a, float b = 0);
/**
Crea un cubo con las bases en x0,y0,z0 y x1,y1,z1, y profundidad de la base a.
**/

// =========================== cilindro ================================================

void cilindro(float x0, float y0, float z0, 
		    float x1, float y1, float z1, float a, float b);
/*
	Crea un cilindro con centro de las bases en
	x0,y0,z0 y x1,y1,z1, y radio de la base a.
*/
// =========================== creaCuerpo ==========================================

/**
 * Crea el cuerpo de la bicicleta: armazon, manillar, uniones de las ruedas
*/
void creaCuerpoBici();

/**
 * Crea las ruedas y las llantas
*/
void creaRuedas(float escala, float grosor);

/**
 * Crea el pedal en sí a base de cajas
*/
void pedal();

/**
 * Crea un piñon con el tamaño y el número de engranajes dado
*/
void pinion(float tam, int num_engranajes);

/**
 * Dibuja los piñones y los pedales
*/
void creaSistemaPedales();

/**
 * Crea las cadenas de los piñones
*/
void cadenas(int num_cadenas, float pendiente);

#endif

