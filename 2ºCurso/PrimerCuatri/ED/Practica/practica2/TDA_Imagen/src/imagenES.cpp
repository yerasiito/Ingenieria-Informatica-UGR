 /**
  * @file imagenES.cpp
  * @brief Fichero con definiciones para la E/S de imagenes
  * @author Yeray Lopez Ramirez
  * @author Jaime Castillo Ucles
  * Permite la E/S de archivos de tipo PGM,PPM
  */

#include <fstream>
#include <string>
#include <cmath>

#include "imagenES.h"

using namespace std;


TipoImagen LeerTipo(ifstream& f){
  char c1,c2;
  TipoImagen res= IMG_DESCONOCIDO;

  if (f){
    c1=f.get();
    c2=f.get();
    if (f && c1=='P')
      switch (c2) {
        case '5': res= IMG_PGM; break;
        case '6': res= IMG_PPM; break;
        default: res= IMG_DESCONOCIDO;
      }
  }
  return res;
}

// _____________________________________________________________________________

TipoImagen LeerTipoImagen(const char *nombre){
  ifstream f(nombre);
  return LeerTipo(f);
}


// _____________________________________________________________________________

char SaltarSeparadores (ifstream& f){
  char c;
  do{
    c= f.get();
  } while (isspace(c));
  f.putback(c);
  return c;
}

// _____________________________________________________________________________

bool LeerCabecera (ifstream& f, int& fils, int& cols){
    int maxvalor;
    string linea;
    while (SaltarSeparadores(f)=='#')
      getline(f,linea);
    f >> cols >> fils >> maxvalor;
    
    if (/*str &&*/ f && fils>0 && fils<5000 && cols>0 && cols<5000){
        f.get(); // Saltamos separador
        return true;
    }
    else 
      return false;
}



// _____________________________________________________________________________

unsigned char *LeerImagenPPM (const char *nombre, int& fils, int& cols){
  unsigned char *res=0;
  fils=0;
  cols=0;
  ifstream f(nombre);
  
  if (LeerTipo(f)==IMG_PPM){
    if (LeerCabecera (f, fils, cols)){
        res= new unsigned char[fils*cols*3];
        f.read(reinterpret_cast<char *>(res),fils*cols*3);
        if (!f){
          delete[] res;
          res= 0;
        }
    }
  }
  return res;
}

// _____________________________________________________________________________

unsigned char *LeerImagenPGM (const char *nombre, int& fils, int& cols){
  unsigned char *res=0;
  fils=0;
  cols=0;
  ifstream f(nombre);
  
  if (LeerTipo(f)==IMG_PGM){
    if (LeerCabecera (f, fils, cols)){
      res= new unsigned char[fils*cols];
      f.read(reinterpret_cast<char *>(res),fils*cols);
      if (!f){
        delete[] res;
        res= 0;
      }
    }
  }
  return res;
}

// _____________________________________________________________________________

bool EscribirImagenPPM (const char *nombre, const unsigned char *datos, 
                        const int fils, const int cols){
  ofstream f(nombre);
  bool res= true;
  
  if (f){
    f << "P6" << endl;
    f << cols << ' ' << fils << endl;
    f << 255 << endl;
    f.write(reinterpret_cast<const char *>(datos),fils*cols*3);
    if (!f)
      res=false;
  }
  return res;
}
// _____________________________________________________________________________

bool EscribirImagenPGM (const char *nombre, const unsigned char *datos, 
                        const int fils, const int cols){
  ofstream f(nombre);
  bool res= true;
  
  if (f){
    f << "P5" << endl;
    f << cols << ' ' << fils << endl;
    f << 255 << endl;
    f.write(reinterpret_cast<const char *>(datos),fils*cols);
    if (!f)
      res=false;
  }
  return res;
}
//------------------------------------------------------------------------
Imagen TransformadorFichImg (const char *fichero){
	int  filas =0;
	int  columnas =0;
	int  escala =0;
	unsigned char *res = LeerImagenPGM (fichero, filas, columnas);
	Imagen img(filas,columnas);
	for(int i=0; i<filas; i++){
		for(int  j=0; j<columnas; j++){
			img.asigna_pixel(i, j, res[escala]);
			escala++;
		}
	}

	return img;
}

void TransformadorImgFich(const char *fichero, Imagen &img){
	unsigned char *res= new unsigned char[img.num_columnas()*img.num_filas()];
	int escala=0;
	for(int i=0; i<img.num_filas(); i++)
		for(int  j=0; j<img.num_columnas(); j++){
			res[escala] = img.valor_pixel(i, j);
			escala++;
		}
	EscribirImagenPGM (fichero, res, img.num_filas(), img.num_columnas());
}


//-------------------------------------------------------------------------------------
//FUNCIONES ESPECIALES
//----------------------------------------------------------------------------------------

void umbralizarES(const char *ficheroNoUmbralizado, const  char *ficheroUmbralizado){
	Imagen img=TransformadorFichImg(ficheroNoUmbralizado);
	img.umbralizar();
    TransformadorImgFich(ficheroUmbralizado, img);


}
void iconizarES(const char *fichero, const char *ficheroiconizado, int filas, int columnas){
	Imagen img= TransformadorFichImg(fichero);
	Imagen icono = img.iconizar(filas, columnas);
	TransformadorImgFich(ficheroiconizado, icono);

}
 void ContrastarES(const char *fichero, const char *ficherocontrastado, ::byte minimo, ::byte maximo){
	Imagen img = TransformadorFichImg(fichero);
	img.contrastar(minimo,maximo);
	TransformadorImgFich(ficherocontrastado, img);
 }
 
void MorphingES(const char *ficheroorig, const char *ficherordo, const char *ficherointermedios){
	char nombre;
 	Imagen imgInicial = TransformadorFichImg(ficheroorig);
 	Imagen imgFinal = TransformadorFichImg(ficherordo);
 	//Estar seguro que imgInicial y imgFinal tienen las mismas dimensiones.

 	if(imgInicial.num_filas() == imgFinal.num_filas() && imgInicial.num_columnas() == imgFinal.num_columnas()){
        int a = imgInicial.num_filas(), b = imgInicial.num_columnas();
        int matrix_interaccion[a][b];
        int matrix_cuando[a][b];
        int matrix_constcambio[a][b];

        for(int i = 0; i < imgInicial.num_filas(); i++){
            for(int j = 0; j < imgInicial.num_columnas(); j++){
                matrix_interaccion[i][j] = abs(imgInicial.valor_pixel(i,j) - imgFinal.valor_pixel(i,j));
                if(matrix_interaccion[i][j]==0)
                    matrix_constcambio[i][j]=0;
                else
                    matrix_constcambio[i][j]=255/matrix_interaccion[i][j];
                matrix_cuando[i][j]= 0;
            }
        }
        ::byte incr=1;
        int intermedios=255; //Vamos a crear el morphing desde 255 interacciones.
        for(int i=0; i<intermedios; i++){
            for(int a=0; a<imgInicial.num_filas(); a++){
                for(int b=0; b<imgInicial.num_columnas(); b++){
                    if(matrix_cuando[a][b]>=matrix_constcambio[a][b]){
                        matrix_cuando[a][b]=0;
                        if(imgFinal.valor_pixel(a,b) > imgInicial.valor_pixel(a,b))
                            imgInicial.asigna_pixel(a,b,imgInicial.valor_pixel(a,b) + incr);
                        else if(imgFinal.valor_pixel(a,b) < imgInicial.valor_pixel(a,b))
                            imgInicial.asigna_pixel(a,b,imgInicial.valor_pixel(a,b) - incr);
                        else
                            imgInicial.asigna_pixel(a,b,imgInicial.valor_pixel(a,b));
                    }
                    else
                        matrix_cuando[a][b]+=1;
                }
            }
            string intermedio = ficherointermedios;
            intermedio += "/img" + to_string(i);
            const char *ficherosIntermedios = intermedio.c_str();
            TransformadorImgFich(ficherosIntermedios, imgInicial);
        }
	}
 	else
 		cout<<"No tienen las mismas dimensiones" << endl;
 }
 
/* Fin Fichero: imagenES.cpp */

