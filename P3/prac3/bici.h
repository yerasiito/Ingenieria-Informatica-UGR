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
#include "objetoRevolucion.h"

// =========================== ortoedro ================================================

void ortoedro(float x0, float y0, float z0,
		    float x1, float y1, float z1, float a, float b);
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
// =========================== Bicicleta ==========================================

class Bici:Objeto3D{
	private:
		Malla sillin;
		ObjetoRevolucion rueda;
		
		float escale = 1, escala_r1 = 1, escala_r2 = 1, grosor_r = 1;

		float defaultColor[4] = {1, 1, 1, 1};
		float cuerpoColor[4] = {1, 0.2, 0.2, 1};
		float sillinColor[4] = {0.1, 0.1, 0.1, 1};

		float metalicColor[4] = {0.792, 0.8, 0.807, 1};

		float llantaColor[4] = {0.69, 0.702, 0.717, 1};
		float ruedaColor[4] = {0.305, 0.29, 0.278, 1};
		float pedalColor[4] = {0.3, 0.3, 0.3, 1};
		 float colorR[4] = { 1.0, 0.55, 0.0, 1};
	public:
		/*Parametros animacion*/
		int multiplicador = 1;
		float angulo = 0;
		float avance = 0;
		float rota_rueda = 0;
		float altura_sillin = 0;

		/**
		 * Constructor
		 * @param escale : tamanio de la bici
		 * @param escala_rueda : tamanio de la rueda
		 * @param grosor_rueda : grosor de la rueda
		*/
		Bici(float escalar, float escala_rueda1, float escala_r2, float grosor_r);
		/**
		 * Crea el cuerpo de la bicicleta: armazon, manillar, uniones de las ruedas
		*/
		void creaCuerpoBici();


		void Rueda();

		/**
		 * Crea las ruedas y las llantas
		*/
		void creaRuedas();

		/**
		 * Crea el pedal en sí a base de cajas
		*/
		void pedal(float pos_x, float pos_y, float pos_z, float tam_x, float tam_y, float tam_z);

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

		/**
		 * Dibuja todos los componentes de la bicicleta
		*/
		void draw();
};


#endif

