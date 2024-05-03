/**
  * @file imagenES.h
  * @brief Fichero cabecera para la E/S de imagenes 
  * Permite la E/S de archivos de tipo PGM,PPM
  * @author Yeray Lopez Ramirez
  * @author Jaime Castillo Ucles
  */

#ifndef _IMAGEN_ES_H_
#define _IMAGEN_ES_H_

#include "imagen.h"

/**
  * @brief Tipo de imagen
  *
  * Declara una serie de constantes para representar los distintos tipos
  * de imagenes que se pueden manejar.
  *
  * @see LeerTipoImagen
  */
enum TipoImagen {IMG_DESCONOCIDO, IMG_PGM, IMG_PPM};

/**
 * @brief Tipo de imagen
 * @param f el archivo de lectura
 * @return la imagen inicializada
 */
TipoImagen LeerTipo(ifstream& f);

/**
  * @brief Devuelve el tipo de imagen del archivo
  *
  * @param nombre indica el archivo de disco que consultar
  * @return Devuelve el tipo de la imagen en el archivo
  *
  * @see TipoImagen
  */
TipoImagen LeerTipoImagen (const char *nombre);

/**
 * @brief Se salta los separadores de la cabecera del archivo
 * @param f el archivo a leer
 * @return la cabecera sin los separadores
 */
char SaltarSeparadores (ifstream& f);

/**
 * @brief Lee la cabecera del archivo
 * @param f el archivo a leer
 * @param fils Numero de filas
 * @param cols Numero de columnas
 * @return 
 */
bool LeerCabecera (ifstream& f, int& fils, int& cols);


/**
  * @brief Lee una imagen de tipo PPM
  *
  * @param nombre archivo a leer
  * @param fils Parametro de salida con las filas de la imagen.
  * @param cols Parametro de salida con las columnas de la imagen.
  * @return puntero a una nueva zona de memoria que contiene @a fils x @a cols x 3
  * bytes que corresponden a los colores de todos los pixeles en formato
  * RGB (desde la esquina superior izqda a la inferior drcha). En caso de que no
  * no se pueda leer, se devuelve cero. (0).
  * @post En caso de exito, el puntero apunta a una zona de memoria reservada en
  * memoria dinamica. Sera el usuario el responsable de liberarla.
  */
unsigned char *LeerImagenPPM (const char *nombre, int& fils, int& cols);

/**
  * @brief Escribe una imagen de tipo PPM
  *
  * @param nombre archivo a escribir
  * @param datos punteros a los @a fils x @a cols x 3 bytes que corresponden a los valores
  *    de los pixeles de la imagen en formato RGB.
  * @param fils filas de la imagen
  * @param cols columnas de la imagen
  * @return si ha tenido exito en la escritura.
  */
bool EscribirImagenPPM (const char *nombre, const unsigned char *datos, 
                        const int fils, const int cols);

/**
  * @brief Lee una imagen de tipo PGM
  *
  * @param nombre archivo a leer
  * @param fils Parametro de salida con las filas de la imagen.
  * @param cols Parametro de salida con las columnas de la imagen.
  * @return puntero a una nueva zona de memoria que contiene @a fils x @a cols
  * bytes que corresponden a los grises de todos los pixeles
  * (desde la esquina superior izqda a la inferior drcha). En caso de que no
  * no se pueda leer, se devuelve cero. (0).
  * @post En caso de exito, el puntero apunta a una zona de memoria reservada en
  * memoria dinamica. Sera el usuario el responsable de liberarla.
  */
unsigned char *LeerImagenPGM (const char *nombre, int& fils, int& cols);

/**
  * @brief Escribe una imagen de tipo PGM
  *
  * @param nombre archivo a escribir
  * @param datos punteros a los @a fils x @a cols bytes que corresponden a los valores
  *    de los pixeles de la imagen de grises.
  * @param fils filas de la imagen
  * @param cols columnas de la imagen
  * @return si ha tenido exito en la escritura.
  */
bool EscribirImagenPGM (const char *nombre, const unsigned char *datos, 
                        const int fils, const int cols);
  /**
  * @brief Devuelve un objeto del TDA Imagen de un fichero PGM
  * @param *fichero Nombre del fichero PGM
  * @return Objeto del TDA Imagen
  * @pre Fichero de formato obligatorio PGM
  */
Imagen TransformadorFichImg (const char *fichero);
 
 /**
 * @brief Produce un fichero PGM de un objeto Imagen
 * @param *fichero Nombre del fichero PGM
 * @param img la matriz imagen
 */
 void TransformadorImgFich(const char *fichero, Imagen &img);
 
 /**
 * @brief Produce un fichero umbralizado a partir de uno no umbralizado.
 * @param *ficheroNoUmbralizado Nombre del fichero de entrada
 * @param *ficheroUmbralizado Nombre del fichero que va a salir
 */
 void umbralizarES(const char *ficheroNoUmbralizado, const  char *ficheroUmbralizado);
 
 /**
 * @brief Produce el icono
 * @param *fichero Nombre del fichero de entrada
 * @param *ficheroiconizado Nombre del fichero que va a salir
 * @param filas Num filas del icono
 * @param columnas Num columnas del icono
 * @pre filas <= filas de la imagen  && columnas <= columnas de la imagen && ambas mayores que 0
 */
 void iconizarES(const char *fichero, const char *ficheroiconizado, int filas, int columnas);
 
 /**
 * @brief Aumenta el contraste de la imagen
 * @param *fichero Nombre del fichero de entrada
 * @param *ficherocontrastado Nombre del fichero que va a salir
 * @param minimo Minimo del rango de constraste
 * @param maximo Maximo del rango de contraste
 * @pre min <= max
 */
 void ContrastarES(const char *fichero, const char *ficherocontrastado, ::byte minimo, ::byte maximo);
 
 /**
 * @brief Genera una cantidad de imagenes intermedias para generar despues el morphing
 * @param ficheroorig Nombre del fichero de entrada
 * @param ficherordo Nombre del fichero de salida
 * @param ficherointermedios Nombre de los ficheros intermedios
 */
 
 void MorphingES(const char *ficheroorig, const char *ficherordo, const char *ficherointermedios);

#endif //_IMAGEN_ES_H_

/* Fin Fichero: imagenES.h */
