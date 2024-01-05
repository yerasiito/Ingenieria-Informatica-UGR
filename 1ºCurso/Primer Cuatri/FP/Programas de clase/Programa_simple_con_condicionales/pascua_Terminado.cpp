/**
  * @file pascua.cpp
  * @brief Calcula la fecha del domingo de Pascua de un año
  *
  * @author Fulanito...
  * @date Octubre-2020
  *
  *  La fecha del domingo de Pascua corresponde al primer domingo después de la primera
  * luna llena que sigue al equinoccio de primavera. El algoritmo que se presenta a
  * continuación (denominado Cómputus) permite calcular esta fecha y es válido para años
  * comprendidos entre 1900 y 2100. Para un determinado año, los cálculos que hay que
  * realizar son:
  *    - A = año mod 19
  *    - B = año mod 4
  *    - C = año mod 7
  *    - D = (19 * A + 24) mod 30
  *    - E = (2 * B + 4 * C + 6 * D + 5) mod 7
  *    - N = (22 + D + E)
  * donde mod significa módulo (resto de dividir el primero entre el segundo).
  *
  * El valor de N corresponde al día de marzo en el que se sitúa el domingo de Pascua.
  * En el caso de que sea mayor que 31, el valor se refiere a un día de abril. Además, hay
  * dos excepciones:
  *    1.- Si la fecha obtenida es el 26 de abril, entonces la Pascua caerá en el 19
  *        de abril.
  *    2.- Si es el 25 de abril, con D = 28, E = 6 y A > 10, entonces la Pascua es el 18
  *       de abril.
  * Escriba un programa que lea un año y muestre el día y mes en el que se celebró o
  * celebrará el domingo de pascua para ese año.
  * En la siguiente lista tiene algunos datos para verificar que el ejercicio es correcto:
  *    - Año 2005 -> Pascua el 27 de marzo
  *    - Año 2011 -> Pascua el 24 de abril
  *    - Año 2049 -> Pascua el 18 de abril
  *    - Año 2076 -> Pascua el 19 de abril
  *
  */
#include <iostream>
using namespace std;

int main()
{
    int anio,a,b,c,d,e,dia;
    cout <<"Este programa calcula el dia de domingo de Pascua" << endl;

        cout <<"Introduzca el anio: ";
        cin >> anio;

    //Cálculo

    a = anio % 19;
    b = anio % 4;
    c = anio % 7;
    d = (19 * a + 24) % 30;
    e = (2 * b + 4 * c + 6 * d + 5) % 7;
    dia = (22 + d + e);

    //Salida de Datos...

    cout << "\nLa Fecha del Domingo de Pascua de " << anio <<" es el ";

    if (dia<=31)
        cout << dia << " de Marzo ";
    else if(dia==31 + 25)
        cout << "18 de Abril ";
    else if(dia==31 + 26 && d == 28 && e == 6 && a > 10)
        cout << "19 de Abril ";
    else
        cout << dia - 31 << " de Abril ";
    return 0;
}
