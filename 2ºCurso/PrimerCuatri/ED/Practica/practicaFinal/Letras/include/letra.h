#ifndef __LETRA_H__
#define __LETRA_H__

#include <iostream>

using namespace std;


/** @file letra.h
  * @brief T.D.A. Clase Letra
  * Clase letra que representa la unidad mínima del juego.
  * Formada por:
  * Caracter Frecuencia Puntuacion
  *
  * @author Yeray López Ramírez
  * @author Jaime Castillo Ucles
  * @date Diciembre 2021
  */
class Letra{
private:
    char caracter;
    int frecuencia;
    int puntuacion;
public:

    /**
    * @brief Constructor por defecto.
    */
    Letra();

    /**
    * @brief Constructor con parámetros
    * @param c El caracter a añadir
    * @param frec La frecuencia que aparece
    * @param punt La puntuacion asignada a la letra
    */
    Letra(const char &c, const int &frec, const int &punt);

    /**
    * @brief Devuelve el caracter asociado al objeto Letra
    * @return caracter El caracter del objeto Letra
    */
    char getCaracter() const;

    /**
    * @brief Devuelve la puntuacion asociada al objeto Letra
    * @return puntuacion La puntuacion asociada al caracter
    */
    int getPuntuacion () const;

    /**
    * @brief Obtener la cantidad asociada a una letra
    * @return frecuencia La frecuencia con la que aparece el caracter
    */
    int getFrecuencia() const;

    /**
    * @brief Cambia el caracter actual(o vacio) por el caracter pasado por parámetro
    * @param c El carácter asociado a la Letra
    */
    void setCaracter(const char &c);

    /**
    * @brief Cambia el frecuencia actual(o vacia) por la frecuencia pasada por parámetro
    * @param frec La frecuencia asociada a la Letra
    */
    void setFrecuencia(const int &frec);

    /**
    * @brief Cambia la puntuación actual(o vacia) por la puntuación pasada por parámetro
    * @param punt La puntuación asociada a la Letra
    */
    void setPuntuacion(const int &punt);

    /**
    * @brief Sobrecarga del operator ==, comprueba si una letra es igual a otra
    * @param otra Objeto Letra a comparar con la Letra actual
    * @return true si son iguales, false en otro caso
    */
    bool operator== (const Letra & otra) const;

    /**
    * @brief Sobrecarga del operator <, comprueba si una letra es menor a otra
    * @param otra Objeto Letra a comparar con la Letra actual
    * @return true si this mejor a otra, false en otro caso
    */
    bool operator< (const Letra & otra) const;


    /**
    * @brief Lee de un flujo de entrada de una Letra
    * @param is el flujo de entrada
    * @param L Objeto Letra donde se realiza la lectura
    * @return el flujo de entrada
    */
    friend istream & operator>> (istream &is, Letra &L);


    /**
    * @brief Escribe en un flujo de salida una Letra
    * @param os el flujo de salida
    * @param L Objeto Letra que se escribe
    * @return el flujo de salida
    */
    friend ostream & operator<< (ostream &os, const Letra &L);

};

#endif
