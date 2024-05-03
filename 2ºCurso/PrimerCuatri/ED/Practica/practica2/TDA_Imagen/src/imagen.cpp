/**
* @file imagen.cpp
* @brief Fichero con las definiciones del TDA Imagen
* @author Yeray Lopez Ramirez
* @author Jaime Castillo Ucles
*/

#include "imagen.h"
#include <cmath>

using namespace std;

// FUNCIONES AUXILIARES DE MEM DINAMICA
void Imagen::Reservar(){
    img = 0;
    if(filas > 0 && cols > 0) {
        img = new ::byte *[filas];
        for(int i = 0; i < filas; i++)
            img[i] = new ::byte[cols];

    }
}

void Imagen::Liberar(){
    if(img != 0){
        for (int i = 0; i < filas; i++)
            delete [] img[i];
        delete []img;
        img = 0;
        filas = 0;
        cols = 0;
    }
}

// CONSTRUCTORES

Imagen::Imagen(){
    filas = 0;
    cols = 0;
    Reservar();
}

Imagen::Imagen(int _filas, int _cols){
    filas = _filas;
    cols = _cols;
    Reservar();
}

//constructor de copia
Imagen::Imagen(const Imagen & otra){
    filas = otra.num_filas();
    cols = otra.num_columnas();
    Reservar();
    for(int i = 0; i < filas; i++)
        memcpy (img[i], otra.img[i], otra.cols*sizeof(unsigned char));

}

Imagen::~Imagen(){
    Liberar();
}

Imagen & Imagen::operator=(const Imagen & otra){
    if(this != &otra){
        Liberar();
        Reservar();
        filas = otra.num_filas();
        cols = otra.num_columnas();

        copiar(this->img, otra.img, otra.num_columnas(), otra.num_columnas());
    }

    return *this;
}

void Imagen::copiar(::byte **destino, ::byte **orig, int filas, int columnas){
    for(int i = 0; i < filas; i++)
        for(int j = 0; j < columnas; j++)
            destino[i][j] = orig[i][j];
}

int Imagen::num_filas() const{
	return filas;
}

int Imagen::num_columnas() const{
	return cols;
}

void Imagen::asigna_pixel(int filas, int cols, unsigned char valor){
	img[filas][cols] = valor;
}

::byte Imagen::valor_pixel(int filas, int cols) const{
	return img[filas][cols];
}

void Imagen::umbralizar(){ 
    //Media aritmetica, primer T(k)
    float T1 = 0, sum = 0, cont = 0;
    for(int i=0;i<num_filas();i++){
        for(int j = 0; j < num_columnas(); j++){
            sum += valor_pixel(i,j);
            cont++;
        }
    }

    T1 = sum/cont;
    //Interración de la función T(k)
    float T2 = 0, sum2 = 0, sum1 = 0;
    int cont1 = 0, cont2 = 0;
    while(T1 != T2 && T1 >= 0){
        for(int i = 0; i < num_filas(); i++){
            for(int j = 0; j < num_columnas(); j++){
                if(valor_pixel(i,j) >= T1){
                    sum1 += valor_pixel(i,j);
                    cont1++;
                }
                else if(valor_pixel(i,j) < T1){
                    sum2 += valor_pixel(i,j);
                    cont2++;
                }
            }
        }
        T2 = T1;
        T1 = ((sum1/cont1) +(sum2/cont2))/2;
        cout << "\r" << T1;
    }
    //Umbralización
    for(int i = 0; i < num_filas(); i++){
        for(int j = 0; j < num_columnas(); j++)
            if(valor_pixel(i, j) > T1)
                asigna_pixel(i,j,NEGRO);
            else
                asigna_pixel(i, j, BLANCO);
    }
}

int Imagen :: Media(int f1, int c1, int f2, int c2){
    double val = 0;
    //OJO: pixel 256 es 255 aqui
    for(int i = f1 ; i <= f2 ; i++)
        for(int j = c1; j <= c2 ; j++)
            val += (int) img[i][j];
    val = (int) (0.5 + val / ((f2-f1+1)*(c2-c1+1))); //+0.5 para redondear
    return val;
}

Imagen Imagen::iconizar(int nf, int nc){
    Imagen icono(nf, nc);
    //Comprueba si es posible hacer la iconización según una reducción nx de nxn.
    //¿Es múltiplo las dimensiones de la matriz original con la del icono?

    bool continua = false;
    if(nf == nc && num_filas() == num_columnas() && num_filas()%nf == 0)
        continua = true;

    //Saco el icono.
    if(continua){
        int proporcion=0, incr_fila=0, incr_columna=0;
        proporcion=(num_filas()/nf);
        int sum;
        for(int i = 0; i < nf; i++){
            incr_columna=0;
            for(int j = 0; j < nc; j++){
                sum = 0;
                for(int k = 0; k < proporcion; k++)
                    for(int l = 0; l < proporcion; l++)
                        sum += valor_pixel(k+incr_fila, l+incr_columna);	
                incr_columna += proporcion;
                icono.asigna_pixel(i,j,(sum/(proporcion*proporcion)+0.5));
            }
            incr_fila += proporcion;
        }
    }
    return icono;
}

void Imagen::contrastar(::byte minimo, ::byte maximo){
    //Necesitamos saber el máximo y el mínimo valor de gris que tiene la imagen actualmente, para declarar la fórmula del contraste
    int a = 255;
    int b = 0;
    for (int i = 0; i < num_filas(); i++)
        for( int j = 0; j < num_columnas(); j++)
            if(valor_pixel(i,j) <= a)
                a = valor_pixel(i,j);
            else if(valor_pixel(i,j) > b)
                b=valor_pixel(i,j);

    //Asignamos el nuevo contraste
    const double cociente_constante = (double) (maximo - minimo) /(b-a);
    for(int i=0; i<num_filas(); i++)
        for(int j=0; j<num_columnas(); j++)
            asigna_pixel(i, j, round(minimo + (cociente_constante * (valor_pixel(i, j) -a ))));
            
}
