#include <iostream>

int opcion;

double salario_base;             //En este ejercicio se utilizarán las tres opciones para calcular el salario final.
double salario_final;            //Al final del codigo se responde a la cuestion de cual es la alternativa más adecuada.

int main()
{
    cout <<"Este programa calcula el salario final tras aplicar un aumento del 2%, de tres formas distintas(internamente).\n\n";

    cout << " Elige una opcion:";
    cin >> opcion;

    //En la opcion 1 se utiliza unicamente la variable salario_base y se le multiplica por 1.02 dentro del cout.

    if(opcion==1)
    {
    cout << "\nIntroduce el salario:";
    cin >> salario_base;

    cout << "\n -El salario final es " <<1.02*salario_base <<"\n";
    }

    //En la opcion 2 se declara una nueva variable llamada salario_final que será el producto del salario inicial por 1.02.

    if(opcion==2)
    {
        cout << "\n Introduce el salario:";
        cin >>salario_base;

        salario_final=salario_base*1.02;
        cout << "\n -El salario final es " <<salario_final <<"\n";
    }

    //En la opcion 3 tenemos una única variable de nuevo que se modifica(multiplicando por 1.02) tras conocer su valor.

    if(opcion==3)
    {
        cout << "\nIntroduce el salario:";
        cin >> salario_base;

        salario_base = salario_base*1.02;
        cout << "\n -El salario final es " <<salario_base <<"\n";
    }

    /*a) Directamente hacer el cómputo 1.02 * salario_base dentro de la sentencia cout
      b) Introducir una variable salario_final, asignarle la expresión anterior y mostrar su contenido en la sentencia cout
        c) Modificar la variable original salario_base con el resultado de incrementarla un 2%.

        Indique qué alternativa elige y justifíquela.*/

        //La mejor alternativa es la primera ya que requiere de menos variables y menos lineas de codigo.

}
