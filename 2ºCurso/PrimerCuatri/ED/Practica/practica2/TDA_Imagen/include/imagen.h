/**
* @file imagen.h
* @brief T.D.A Imagen
* @author Yeray Lopez Ramirez
* @author Jaime Castillo Ucles
*/

#ifndef imagen_h
#define imagen_h

#include <cstring>
#include <iostream>

using namespace std;

typedef unsigned char byte; //tipo base de cada pixel

/*
* @brief  T.D.A Imagen
*
* Una instancia @e c del tipo de datos abstracto @c Imagen es un objeto que se correponde con una matriz
* bidimensional que representa una imagen de niveles de grises formadaque tiene el propósito de poder crear programas de manipulación y reprocesamiento
* de imágenes con la finalidad de mejorarlas o crear arte.
*
* @author Jaime Castillo Uclés
* @date 30 Octubre 2021
*
*/
class Imagen{
	private:
		const static ::byte BLANCO=0;
		const static ::byte NEGRO=255;
		int filas; //Número de filas de la matriz
		int cols; //Número de columnas de la matriz
		::byte **img; //Puntero al vector de punteros
	public:

	/**
	* @brief Constructor por defecto
	*/
	Imagen();

	/**
	* @brief Constructor de copia
	* @param otra Imagen que se le pasa de copia
	*/
	Imagen(const Imagen & otra);

	/**
	* @brief Constructor por parámetros
	* @param filas Número de filas que va a tener la imagen
	* @param cols Número de columnas que va a tener la imagen
	* @pre filas>0 && cols>0
	* @post
	*/
	Imagen(int filas, int cols);

	/**
	* @brief Destructor de la clase. Libera los recursos ocupados por la imagen
	*/
	~Imagen();
	/**
	* @brief Reserva memoria dinámica
	*/
	void Reservar();

	/**
	* @brief Libera memoria dinámica
	*/
	void Liberar();

	/**
	* @brief Calcula el número de filas de una imagen
	* @return número de filas de una imagen
	*/
	int num_filas () const;

	/**
	* @brief Calcula el número de columnas de una imagen
	* @return número de columnas de una imagen
	*/
	int num_columnas () const;

	/**
	* @brief Operador asignación
	*/
	Imagen & operator=(const Imagen & otra);

	/**
	* @brief Método que copia dos matrices
	* @param destino Matriz a copiar
	* @param orig Matriz a ser copiada
	* @param filas Número de filas
	* @param columnas Número de columnas
	*/

	void copiar(::byte **destino, ::byte **orig, int filas, int columnas);

	/**
	* @brief Asigna un valor entre 0 y 255 a cada punto de la imagen
	* @param fila Número de fila donde se va asignar el valor
	* @param cols Número de columna donde s eva asignar el valor
	* @param valor Número de valor que se va a asignar
	* @pre 0<= fila < num_filas()
	* @pre 0<= cols < num_columnas ()
	* @pre 0<= valor <= 255
	*/
	void asigna_pixel (int fila, int cols, unsigned char valor);

        /**
        * @brief Calcula el valor gris medio de la matriz, utilizado por Iconizar
        * @param f1 fila inicial
        * @param c1 columna inicial
        * @param f2 fila final (se incluye)
        * @param c2 columna final (se incluye)
        * @return el valor medio de gris de la matriz
        * @pre f1 <= f2 e c1 <= c2
        */
        int Media(int f1, int c1, int f2, int c2);

	/**
	* @brief Consulta el valor de luminosidad de la casilla (fila, cols) de la imagen
	* @param fila Número de fila donde está la casilla que se va a consultar
	* @param cols Número de columna donde está la casilla que se va a cosultar
	* @pre 0 <= fila < num_filas ()
	* @pre 0 <= col < num_columnas ()
	* @return El valor de luminosidad de la casilla, que está en el conjunto {0,1,...,255}
	*/
	::byte valor_pixel (int fila, int cols) const;

	/**
	* @brief Umbraliza la imagen gracias a la generación de un umbral
	* @post Se crea T el umbral generado automáticamente de la imagen
	*/
	void umbralizar();
	/**
	* @brief Devuelve un icono de la imagen
	* @param nf Número de filas del icono
	* @param nc Número de columnas del icono
	* @pre nf <= filas de la imagen dada
	* @pre nc <= columnas de la imagen dada
	* @pre nf && nc > 0
        * @pre nf y nc deben ser divisores del tamaño de la imagen
	*/
	Imagen iconizar(int nf, int nc);

	/**
	* @brief Aumenta el contraste de la imagen
	* @param minimo
	* @param maximo
	* @pre min <= max
	*/
	void contrastar(::byte minimo, ::byte maximo);

};

#endif //imagen_h
