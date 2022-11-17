/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Yeray Lopez Ramirez

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informaticos
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

=======================================================/
	modulo dado.c

*/
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "textura.h"
#include "file_ply_stl.h"
#include "lector-jpg.h"
#include <iostream>

Textura::Textura(){}

Textura::Textura(const char *nombre_archivo){
  image = nombre_archivo;
  data = LeerArchivoJPEG(image, anchoT, altoT);
  activar();
}

void Textura::activar(){
    texId = new GLuint;
    glGenTextures (1 , texId );
    glBindTexture( GL_TEXTURE_2D , *texId );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, anchoT, altoT, 0, GL_RGB,
    GL_UNSIGNED_BYTE, image);
};